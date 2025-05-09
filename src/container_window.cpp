#include "../include/o4_project/container_window.h"
#include "container.h"
#include "container_model.h"
#include <QIcon>
#include <QPushButton>
#include <qapplication.h>
#include <qboxlayout.h>
#include <qframe.h>
#include <qicon.h>
#include <qlabel.h>
#include <qlayoutitem.h>
#include <qlogging.h>
#include <qmessagebox.h>
#include <qnamespace.h>
#include <qobject.h>
#include <qpushbutton.h>
#include <qscrollarea.h>
#include <qsharedpointer.h>
#include <qsizepolicy.h>
#include <qwidget.h>

ContainerWindow::ContainerWindow(ContainerModel *model, QWidget *parent)
    : QFrame{parent}, model{model}, layout{new QVBoxLayout{this}},
      scrollArea{new QScrollArea}, rows{new QVBoxLayout}, rowsWidget{new QWidget{this}},
      newContainerButton(new QPushButton) {
  setFrameShape(StyledPanel);
  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  setNames();
  initLabel();

  rowsWidget->setLayout(rows);
  rows->setSpacing(0);
  rows->setAlignment(Qt::AlignTop);
  initNewContainerButton();
  updateRows();

  scrollArea->setWidgetResizable(true);
  scrollArea->setWidget(rowsWidget);
  layout->addWidget(scrollArea);
  updateRows();
  dumpParents();
}

void ContainerWindow::initLabel() {
  QLabel *containersLabel = new QLabel{"<b>Containers</b>"};
  containersLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
  layout->addWidget(containersLabel);
  layout->addSpacing(20);
}

void ContainerWindow::initNewContainerButton() {
  newContainerButton->setText("Add new");
  QIcon plusIcon{":/icons/plus.svg"};
  newContainerButton->setIcon(plusIcon);
  newContainerButton->setFlat(true);
  newContainerButton->setMinimumHeight(40);

  connect(newContainerButton, &QPushButton::clicked, this, [this]() {
    bool ok = false;
    auto name = QInputDialog::getText(
        this, "New Container", "Enter Container name:", QLineEdit::Normal, "",
        &ok);
    if (ok) {
      this->model->newContainerRequest(name);
    }
  });
}

void ContainerWindow::updateRows() {
  clearRows();
  const QIcon deleteIcon{":/icons/trash.svg"};
  static constexpr unsigned int minRowHeight = 40;
  static constexpr unsigned int maxRowHeight = minRowHeight * 2;

  if (deleteIcon.isNull()) {
    qDebug() << "Couldn't load icon\n";
  }

  auto containers = model->getContainers();
  for (auto const &container : containers) {
    QWidget *row = new QWidget;
    row->setMinimumHeight(minRowHeight); // TODO: fix magic numbers?
    row->setMaximumHeight(maxRowHeight);
    QHBoxLayout *box = new QHBoxLayout;
    box->setContentsMargins(0, 0, 4, 4);
    box->setSpacing(0);

    QPushButton *button = new QPushButton{container->name};
    button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(button, &QPushButton::clicked, this,
            [this, container]() { emit containerSelected(container.get()); });

    QPushButton *deleteButton = new QPushButton;
    deleteButton->setIcon(deleteIcon);
    deleteButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    connect(deleteButton, &QPushButton::clicked, this,
            [this, container]() { confirmDelete(container.get()); });

    row->setLayout(box);
    box->addWidget(button);
    box->addWidget(deleteButton);
    rows->addWidget(row);
  }
  rows->addWidget(newContainerButton);
}

void ContainerWindow::clearRows() {
  QLayoutItem *item;
  rows->removeWidget(newContainerButton);
  while ((item = rows->takeAt(0)) != nullptr) {
    item->widget()->deleteLater();
  }
  delete item;
}

const QVector<std::shared_ptr<Container>>
ContainerWindow::getContainers() const {
  return {};
}

void ContainerWindow::confirmDelete(Container *container) {
  QMessageBox messageBox{this};
  messageBox.setIcon(QMessageBox::Icon::Warning);
  messageBox.setText(QString{"Delete items: %1"}.arg(container->name));
  messageBox.setDefaultButton(QMessageBox::Cancel);
  messageBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
  auto choice = messageBox.exec();
  if (choice == QMessageBox::Yes) {
    model->removeContainerRequest(container);
  }
}

void ContainerWindow::dumpParents() {
  qDebug() << "\n---------Dumping objects and parents of "
           << this->objectName();
  QVector<QObject *> objects = {this, layout,     scrollArea,
                                rows, rowsWidget, newContainerButton};
  for (auto object : objects) {
    if (!object) {
      qDebug() << "An object is null!";
      return;
    }
    qDebug() << "Name:" << object->objectName() << " : Parent:"
             << (object->parent() ? object->parent()->objectName() : "null");
  }
  qDebug() << "\n";
}

void ContainerWindow::setNames() {
  layout->setObjectName("Layout");
  this->setObjectName("ContainerWindow");
  rowsWidget->setObjectName("RowsWidget");
  scrollArea->setObjectName("ScrollArea");
  rows->setObjectName("Rows");
  newContainerButton->setObjectName("NewContainerButton");
}
