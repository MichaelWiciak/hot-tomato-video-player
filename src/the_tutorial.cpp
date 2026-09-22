#include "the_tutorial.h"
#include "the_help.h"
#include "the_store.h"
#include <QFile>
#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>

TheTutorial::TheTutorial(bool status) {
  setObjectName("tutorialBanner");

  // configure layout
  QHBoxLayout *layout = new QHBoxLayout;
  layout->setMargin(0);
  layout->setSpacing(8);
  layout->setAlignment(Qt::AlignCenter);

  // info icon
  QLabel *iconLabel = new QLabel;
  iconLabel->setPixmap(QPixmap(":/icons/information-circle.png")
                           .scaled(28, 28, Qt::KeepAspectRatioByExpanding));

  // QLabel to explain how to add videos to users
  QString tutorialText =
      QString("Press the + button in the top right to add videos to HTVP");
  QLabel *label = new QLabel(tutorialText);

  layout->addWidget(iconLabel);
  layout->addWidget(label);

  setLayout(layout);

  setHidden(!status);

  initialiseStyleSheet();
}

// Hides the tutorial if the user proves they can
void TheTutorial::hideTutorial() {
  if (store.getTutorialStatus()) {
    store.setTutorialStatus(false);
  }
  setHidden(true);
}

void TheTutorial::helpWindow() {
  TheHelp *help_window = new TheHelp();
  help_window->show();
  store.setTutorialStatus(false);

  setHidden(true);
}

void TheTutorial::initialiseStyleSheet() {
  // set styles
  QFile *styleSheet = new QFile(":/styles/the_tutorial.qss");
  styleSheet->open(QFile::ReadOnly);
  setStyleSheet(styleSheet->readAll());
  delete styleSheet;
}
