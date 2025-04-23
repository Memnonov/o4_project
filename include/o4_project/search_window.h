// Copyright [2025] Auli Jussila & Mikko Memonen

#ifndef SEARCH_WINDOW_H
#define SEARCH_WINDOW_H

#include "mode_frame.h"

class SearchWindow : public ModeFrame {
 public:
  SearchWindow(QWidget *parent = nullptr); 
  ~SearchWindow() {}

 private:
  QLabel *placeholder;

  // Makes this concrete.
  virtual void dummyFunction() {}
};

#endif // !SEARCH_WINDOW_H
