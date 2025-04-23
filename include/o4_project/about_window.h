// Copyright [2025] Auli Jussila & Mikko Memonen

#ifndef ABOUT_WINDOW_H
#define ABOUT_WINDOW_H

#include "mode_frame.h"

class AboutWindow : public ModeFrame {
 public:
  AboutWindow(QWidget *parent = nullptr); 
  ~AboutWindow() {}

 private:
  QLabel *placeholder;

  // Makes this concrete.
  virtual void dummyFunction() {}
};

#endif // !ABOUT_WINDOW_H
