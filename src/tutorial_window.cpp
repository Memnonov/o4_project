#include "../include/o4_project/tutorial_window.h"
#include <QScrollArea>
#include <qnamespace.h>

TutorialWindow::TutorialWindow(QWidget *parent) : ModeFrame{parent} {
  setObjectName("TutorialWindow");
  layout->setAlignment(Qt::AlignCenter);
  auto scrollArea = new QScrollArea;
  layout->addStretch();
  layout->addWidget(scrollArea);
  layout->addStretch();
  auto tutorial = new QLabel{this};
  tutorial->setAlignment(Qt::AlignLeft);
  tutorial->setWordWrap(true);
  scrollArea->setWidget(tutorial);
  scrollArea->setWidgetResizable(true);
  // RRRRAAAAAW text string quick and messy formating!
  QString text{R"(
<b>Welcome to Treasure Hoard!<br></b>
In this quick guide, we'll walk you through the main functions of the application.<br>
<br>
<b>1. Browsing Items<br></b>
<br>
When in browsing mode, you can select a container to inspect its contents.<br>
You can also add or remove containers as needed.<br>
<br>
Inside a container, you can:<br>
Add new items<br>
Remove existing items<br>
Select an item to view its full description<br>
You can quickly add an item if the container has only a few items, using the Quick Add button located below the last item.<br>
<br>
When adding new items or containers:<br>
Name is always required.<br>
Other fields (such as description, tags, etc.) are optional.<br>
However, we recommend adding tags (e.g., weapon, armor, healing, magic, tool, junk) to make sorting and searching easier.<br>
<br>
<b>2. Searching Items<br></b>
If you're unsure where an item is located, you can use Search Mode.<br>
<br>
Search options include:<br>
Item name<br>
Tag<br>
Container name<br>
Description text<br>
You can also sort your search results by any column (alphabetically, by tag, container, or description) to find what you need more easily.<br>
<br>
When you find an item:<br>
Select it to view full information.<br>
From there, you can also move the item to a different container if needed.<br>
<br>
<b>3. Moving Items<br></b>
There are two ways to move items between containers:<br>
Quick Move<br>
When both the source and destination containers are open, you can click the arrow symbol at the right end of the item box to move the item directly.<br>
<br>
Batch Move<br>
Alternatively, you can select one or multiple items and press the Move Item button to transfer them to a chosen container.<br>
<br>
Note:<br>
If no container or item is selected, the move action will not be available.<br>
<br>
<b>4. Oops! (Undo / Redo)<br></b>
Mistakes happen — don't worry!<br>
<br>
At the top of the screen, you will find a Log panel with Undo and Redo buttons next to it:<br>
Press Undo to reverse the last change.<br>
Press Redo to reapply a change you just undid.<br>
This lets you easily correct accidental deletions or moves.<br>
<br>
<b>Final Tip:<br></b>
Try to use clear, consistent names and tags to keep your loot organized.<br>
<br>
Have fun adventuring!<b>
                       )"};
  tutorial->setText(text);
}
