#include "the_help.h"
#include <QLabel>
#include <QPlainTextEdit>

TheHelp::TheHelp() {
  setMinimumSize(400, 550);

  // Call function to create the layout for helping with hotkeys
  createGeneralUsage();
  createHotkeyHelp();

  QWidget *central = new QWidget();

  central->setLayout(helpLayout);

  setCentralWidget(central);
  setWindowTitle("Help");
}

void TheHelp::createHotkeyHelp() {
  // Create main text box and title for
  QPlainTextEdit *hotkeys = new QPlainTextEdit();
  QLabel *titleLabel = new QLabel();
  QFont titleFont("Arial", 18, QFont::Bold);
  QFont hotKeysFont("Arial", 13);
  QString title = QString("Hotkeys");
  QString hotKeys = QString("Spacebar = pause/play\n"
                            "Left Arrow = skip backward\n"
                            "Right Arrow = skip forwarnd\n"
                            "F = enter fullscreen\n"
                            "Escape = exit fullscreen\n"
                            "M = mute video\n"
                            "Up Arrow = volume up\n"
                            "Down Arrow = volume down\n"
                            "Shift+N = next video\n"
                            "Shift+P = previous video\n");
  titleLabel->setText(title);
  titleLabel->setFont(titleFont);
  hotkeys->setFont(hotKeysFont);

  hotkeys->setReadOnly(true);
  hotkeys->setPlainText(hotKeys);
  helpLayout->addWidget(titleLabel);
  helpLayout->addWidget(hotkeys);
}

void TheHelp::createGeneralUsage() {
  QPlainTextEdit *usageText = new QPlainTextEdit();
  QLabel *titleLabel = new QLabel();
  QFont titleFont("Arial", 18, QFont::Bold);
  QFont usageFont("Arial", 13);
  QString title = QString("General Usage");
  QString usage = QString(
      "- You can add videos using the plus button found in the top right of "
      "HTVP.\n"
      "- You can also add videos by dragging and dropping them into HTVP\n"
      "- You can set a default video directory in settings\n"
      "- You can control the video play by either using hotkeys or buttons");

  titleLabel->setText(title);
  titleLabel->setFont(titleFont);
  usageText->setFont(usageFont);

  usageText->setReadOnly(true);
  usageText->setPlainText(usage);
  helpLayout->addWidget(titleLabel);
  helpLayout->addWidget(usageText);
}
