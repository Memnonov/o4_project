// Copyright [2025] Auli Jussila & Mikko Memonen

#ifndef MOVE_WINDOW_H
#define MOVE_WINDOW_H

#include "mode_frame.h"

class MoveWindow : public ModeFrame {
 public:
  MoveWindow(QWidget *parent = nullptr); 
  ~MoveWindow() {}

 private:
  QLabel *placeholder;

  // Makes this concrete.
  virtual void dummyFunction() {}
};

#endif // !MOVE_WINDOW_H
