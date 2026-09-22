#include "the_appbar.h"
#include <QFile>
#include <QHBoxLayout>
#include <QIcon>
#include <iostream>

TheAppBar::TheAppBar() {
  setObjectName("appbar");
  createWidgets();
  initialiseSignalsAndSlots();
  initialiseStyleSheet();
  updateToggleRecentsBtn();
  updateToggleSettingsBtn();
  updateAddFileBtn();
  updateHelpBtn();
}

void TheAppBar::createWidgets() {
  QHBoxLayout *layout = new QHBoxLayout;

  logo = new QLabel("HTVP");
  logo->setObjectName("appbar__title");
  helpBtn = new QPushButton;
  addFileBtn = new QPushButton; // Button to add a file into HTVP
  toggleSettingsBtn = new QPushButton;
  toggleRecentsBtn = new QPushButton;

  layout->addWidget(logo);
  layout->addStretch(1);
  layout->addWidget(helpBtn);
  layout->addWidget(addFileBtn);
  layout->addWidget(toggleSettingsBtn);
  layout->addWidget(toggleRecentsBtn);

  setLayout(layout);
}

void TheAppBar::initialiseSignalsAndSlots() {
  QObject::connect(toggleSettingsBtn, SIGNAL(clicked()), this,
                   SLOT(toggleSettingsBtnClicked()));
  QObject::connect(toggleRecentsBtn, SIGNAL(clicked()), this,
                   SLOT(toggleRecentsBtnClicked()));
  QObject::connect(addFileBtn, SIGNAL(clicked()), this,
                   SIGNAL(addFileBtnClicked()));
  QObject::connect(helpBtn, SIGNAL(clicked()), this, SIGNAL(helpBtnClicked()));
}

void TheAppBar::initialiseStyleSheet() {
  // set styles
  QFile *styleSheet = new QFile(":/styles/the_appbar.qss");
  styleSheet->open(QFile::ReadOnly);
  setStyleSheet(styleSheet->readAll());
  delete styleSheet;
}

void TheAppBar::updateToggleSettingsBtn() {
  toggleSettingsBtn->setIcon(QIcon(":/icons/cog-8-tooth.png"));
  toggleSettingsBtn->setToolTip("Open Settings");
}

void TheAppBar::updateToggleRecentsBtn() {
  toggleRecentsBtn->setIcon(QIcon(":/icons/queue-list.png"));
  toggleRecentsBtn->setToolTip("Open Recents");
}

void TheAppBar::updateAddFileBtn() {
  addFileBtn->setIcon(QIcon(":/icons/plus.png"));
  addFileBtn->setToolTip("Open Video");
}

void TheAppBar::updateHelpBtn() {
  helpBtn->setIcon(QIcon(":icons/question-mark-circle.png"));
  helpBtn->setToolTip("Show Help");
}

void TheAppBar::toggleSettingsBtnClicked() {
  settingsIsOpen = !settingsIsOpen;
  recentsIsOpen = false;
  emit settingsIsOpenChanged(settingsIsOpen);
  emit recentsIsOpenChanged(recentsIsOpen);
}

void TheAppBar::toggleRecentsBtnClicked() {
  settingsIsOpen = false;
  recentsIsOpen = !recentsIsOpen;
  emit settingsIsOpenChanged(settingsIsOpen);
  emit recentsIsOpenChanged(recentsIsOpen);
}
