// Copyright [2025] Auli Jussila & Mikko Memonen

#ifndef BROWSE_WINDOW_H
#define BROWSE_WINDOW_H

#include "mode_frame.h"
#include "container_window.h"
#include "items_window.h"
#include "item_info_window.h"

class BrowseWindow : public ModeFrame {
 public:
  BrowseWindow(QWidget *parent = nullptr); 
  ~BrowseWindow() {}

 private:
  ContainerWindow *containerWindow;
  ItemsWindow *itemsWindow;
  ItemInfoWindow *infoWindow;
  QStackedWidget *leftStack;
  QStackedWidget *rightStack;

  // Makes this concrete.
  virtual void dummyFunction() {}
  void initConnections();
  void handleContainerSelected();
  void handleItemsWindowClosed();
};

#endif // !BROWSE_WINDOW_H
