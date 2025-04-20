#include "../include/o4_project/container_window.h"
#include <QIcon>
#include <QPushButton>
#include <qapplication.h>
#include <qboxlayout.h>
#include <qicon.h>
#include <qlabel.h>
#include <qlayoutitem.h>
#include <qlogging.h>
#include <qnamespace.h>
#include <qpushbutton.h>
#include <qscrollarea.h>
#include <qsizepolicy.h>
#include <qwidget.h>

ContainerWindow::ContainerWindow(QWidget *parent)
    : QFrame{parent}, layout{new QVBoxLayout{this}},
      scrollArea{new QScrollArea{this}},
      newContainerButton(new QPushButton{this}) {

  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  initLabel();

  QWidget *rowsWidget = new QWidget{this};
  QVBoxLayout *rows = new QVBoxLayout{rowsWidget};
  createDummyRows(rows);
  initNewContainerButton(rows);

  scrollArea->setWidgetResizable(true);
  scrollArea->setWidget(rowsWidget);
  layout->addWidget(scrollArea);
}

void ContainerWindow::initLabel() {
  QLabel *containersLabel = new QLabel{"<b>Containers</b>"};
  containersLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
  layout->addWidget(containersLabel);
  layout->addSpacing(20);
}

void ContainerWindow::initNewContainerButton(QVBoxLayout *rows) {
  newContainerButton->setText("Add new");
  QIcon plusIcon{":/icons/plus.svg"};
  newContainerButton->setIcon(plusIcon);
  newContainerButton->setMinimumHeight(40);
  rows->addWidget(newContainerButton);
}

void ContainerWindow::createDummyRows(QVBoxLayout *rows) {
  // Creating dummy rows
  rows->setSpacing(0);
  // TODO(mikko): Fix asset paths.
  const QIcon deleteIcon{":/icons/trash.svg"};
  static constexpr unsigned int rowHeight = 40;

  if (deleteIcon.isNull()) {
    qDebug() << "Couldn't load icon\n";
  }

  for (unsigned int i = 0; i < 18; ++i) {
    QWidget *row = new QWidget;
    row->setMinimumHeight(rowHeight); // TODO(mikko): fix magic numbers
    QHBoxLayout *box = new QHBoxLayout;
    box->setContentsMargins(0, 0, 4, 4);
    box->setSpacing(0);

    QPushButton *button = new QPushButton{"Junk Container"};
    button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(button, &QPushButton::clicked, this,
            [this]() { emit containerSelected(); });

    QPushButton *deleteButton = new QPushButton;
    deleteButton->setIcon(deleteIcon);
    deleteButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);

    row->setLayout(box);
    box->addWidget(button);
    box->addWidget(deleteButton);
    rows->addWidget(row);
  }
}
