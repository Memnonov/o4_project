// Copyright [2025] Auli Jussila & Mikko Memonen

#ifndef TUTORIAL_WINDOW_H
#define TUTORIAL_WINDOW_H

#include "mode_frame.h"

class TutorialWindow : public ModeFrame {
 public:
  TutorialWindow(QWidget *parent = nullptr); 
  ~TutorialWindow() {}

 private:
  QLabel *placeholder;

  // Makes this concrete.
  virtual void dummyFunction() {}
};

#endif // !TUTORIAL_WINDOW_H
