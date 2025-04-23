// Copyright [2025] Auli Jussila & Mikko Memonen

#ifndef MODE_FRAME_H
#define MODE_FRAME_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QFrame>
#include <QHBoxLayout>
#include <qframe.h>

class ModeFrame : public QFrame {
  Q_OBJECT;

 public:
  ModeFrame(QWidget *parent = nullptr) : QFrame{parent}, layout{new QHBoxLayout} {
    setLayout(layout);
    setFrameShape(StyledPanel);
  }
  
  virtual ~ModeFrame() {
    delete layout;
  }

 protected:
  QHBoxLayout *layout;

 private:
  // Make an abstract class.
  virtual void dummyFunction() = 0;

};

#endif  // !MODE_FRAME_H
