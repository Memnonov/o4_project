#include "../include/o4_project/tutorial_window.h"
#include <QScrollArea>

TutorialWindow::TutorialWindow(QWidget *parent)
    : ModeFrame{parent} {
  setObjectName("TutorialWindow");
  layout->setAlignment(Qt::AlignCenter);
  auto scrollArea = new QScrollArea;
  layout->addWidget(scrollArea);
  auto tutorial = new QLabel;
  tutorial->setAlignment(Qt::AlignCenter);
  scrollArea->setWidget(tutorial);
  scrollArea->setWidgetResizable(true);
  tutorial->setText(R"(
Welcome to Treasure Hoard 1.0!
In this quick guide, we'll walk you through the main functions of the application.

1. Browsing Items

When in browsing mode, you can select a container to inspect its contents.
You can also add or remove containers as needed.

Inside a container, you can:
Add new items
Remove existing items
Select an item to view its full description
You can quickly add an item if the container has only a few items, using the Quick Add button located below the last item.

When adding new items or containers:
Name is always required.
Other fields (such as description, tags, etc.) are optional.
However, we recommend adding tags (e.g., weapon, armor, healing, magic, tool, junk) to make sorting and searching easier.

2. Searching Items
If you're unsure where an item is located, you can use Search Mode.

Search options include:
Item name
Tag
Container name
Description text
You can also sort your search results by any column (alphabetically, by tag, container, or description) to find what you need more easily.

When you find an item:
Select it to view full information.
From there, you can also move the item to a different container if needed.

3. Moving Items
There are two ways to move items between containers:
Quick Move
When both the source and destination containers are open, you can click the arrow symbol at the right end of the item box to move the item directly.

Batch Move
Alternatively, you can select one or multiple items and press the Move Item button to transfer them to a chosen container.

Note:
If no container or item is selected, the move action will not be available.

4. Oops! (Undo / Redo)
Mistakes happen — don't worry!

At the top of the screen, you will find a Log panel with Undo and Redo buttons next to it:
Press Undo to reverse the last change.
Press Redo to reapply a change you just undid.
This lets you easily correct accidental deletions or moves.

Final Tip:
Try to use clear, consistent names and tags to keep your loot organized.

Have fun adventuring!
                       )");
}
