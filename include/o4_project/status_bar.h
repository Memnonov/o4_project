#ifndef STATUS_BAR_H
#define STATUS_BAR_H

#include <QWidget>
#include <QLabel>
#include <QIcon>
#include <QPushButton>
#include <qpushbutton.h>
#include <QtLogging>
#include <QHBoxLayout>

class StatusBar : public QWidget {
  Q_OBJECT;
  
 public:
  explicit StatusBar(QWidget *parent = nullptr);

 signals:
  void refresh();
  void undoClicked();
  void redoClicked();

 private:
  QLabel *statusMessage;
  QPushButton *undoButton;
  QPushButton *redoButton;
};

#endif // !STATUS_BAR_H
