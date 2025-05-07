// Copyright [2025] Auli Jussila & Mikko Memonen

#ifndef NAVIGATION_PANEL_H
#define NAVIGATION_PANEL_H

#include <QHBoxLayout>
#include <QLabel>
#include <QObject>
#include <QPushButton>
#include <QString>
#include <QWidget>
#include <QButtonGroup>
#include <QMap>
#include <QFrame>

class NavigationPanel : public QFrame {
  Q_OBJECT;

 public:
  enum class NavAction {
    BrowseItems,
    SearchItems,
    MoveItems,
    Tutorial,
    About,
    Quit
  };

  static const QMap<NavAction, QString> navActionMap;
  static QString navActionToString(NavAction action);
  
  explicit NavigationPanel(QWidget *parent = nullptr);
  ~NavigationPanel() = default;

  void setSelection(NavAction selection);

 private:
  QVBoxLayout *layout;
  QLabel *logo;
  QButtonGroup *buttons;

  void initButtons();
  void initLogo();
  void createButton(NavAction action);
  QIcon getNavIcon(NavAction action);

 signals:
  void buttonPressed(NavAction action);
};

#endif  // !NAVIGATION_PANEL_H
