#include "the_settings.h"
#include "the_store.h"
#include <QDebug>
#include <QFileDialog>
#include <QFormLayout>
#include <QLabel>
#include <QMessageBox>
#include <QObject>
#include <QVBoxLayout>

TheSettings::TheSettings() {
  setObjectName("settingsPanel");
  setHidden(true); // hide by default
  createWidgets();
  initialiseSignalsAndSlots();
  initialiseStyleSheet();
}

void TheSettings::createWidgets() {
  QVBoxLayout *layout = new QVBoxLayout;
  layout->setMargin(0);
  layout->setSpacing(0);
  layout->setAlignment(Qt::AlignTop);

  QLabel *titleLabel = new QLabel("Settings");
  titleLabel->setObjectName("settingsPanel__title");
  layout->addWidget(titleLabel);

  setLayout(layout);

  QVBoxLayout *form = new QVBoxLayout;
  form->setObjectName("settingsPanel__form");
  form->setMargin(0);
  form->setSpacing(0);

  directoryInput = new QLineEdit;
  buttonSizeSelect = new QComboBox;
  themeSelect = new QComboBox;
  timeSkipInput = new QLineEdit;
  browseDirectoryBtn = new QPushButton("Browse");

  layout->addLayout(form);

  QLabel *directoryLabel = new QLabel("Directory");
  directoryLabel->setObjectName("settingsPanel__form-label");
  form->addWidget(directoryLabel);
  form->addWidget(directoryInput);
  form->addWidget(browseDirectoryBtn);

  QLabel *themeLabel = new QLabel("Theme");
  themeLabel->setObjectName("settingsPanel__form-label");
  form->addWidget(themeLabel);
  form->addWidget(themeSelect);

  QLabel *buttonSizeLabel = new QLabel("Button Size");
  buttonSizeLabel->setObjectName("settingsPanel__form-label");
  form->addWidget(buttonSizeLabel);
  form->addWidget(buttonSizeSelect);

  QLabel *timeSkipLabel = new QLabel("Time Skip Amount");
  timeSkipLabel->setObjectName("settingsPanel__form-label");
  form->addWidget(timeSkipLabel);
  form->addWidget(timeSkipInput);

  directoryInput->setText(store.getDefaultDirectory());
  directoryInput->setReadOnly(true);

  themeSelect->addItem("light");
  themeSelect->addItem("dark");
  themeSelect->addItem("contrast");

  store.getTheme() == "light"
      ? themeSelect->setCurrentIndex(0)
      : (store.getTheme() == "dark" ? themeSelect->setCurrentIndex(1)
                                    : themeSelect->setCurrentIndex(2));

  buttonSizeSelect->addItem("small");
  buttonSizeSelect->addItem("normal");
  buttonSizeSelect->addItem("large");

  store.getButtonSize() == "small"
      ? buttonSizeSelect->setCurrentIndex(0)
      : (store.getButtonSize() == "normal"
             ? buttonSizeSelect->setCurrentIndex(1)
             : buttonSizeSelect->setCurrentIndex(2));

  timeSkipInput->setValidator(new QIntValidator(1, 60, this));
  timeSkipInput->setText(QString("%1").arg(store.getTimeSkipSeconds()));
}

void TheSettings::initialiseSignalsAndSlots() {
  QObject::connect(timeSkipInput, SIGNAL(textChanged(QString)), this,
                   SLOT(timeSkipInputChanged(QString)));
  QObject::connect(browseDirectoryBtn, SIGNAL(clicked()), this,
                   SLOT(browseDirectoryBtnClicked()));
  QObject::connect(themeSelect, SIGNAL(currentTextChanged(QString)), this,
                   SLOT(themeChanged(QString)));
  QObject::connect(buttonSizeSelect, SIGNAL(currentTextChanged(QString)), this,
                   SLOT(buttonSizeChanged(QString)));
}

void TheSettings::initialiseStyleSheet() {
  // set styles
  QFile *styleSheet = new QFile(":/styles/the_settings.qss");
  styleSheet->open(QFile::ReadOnly);
  setStyleSheet(styleSheet->readAll());
  delete styleSheet;
}

void TheSettings::timeSkipInputChanged(QString value) {
  int timeSkipSeconds = value.toInt();
  if (timeSkipSeconds == 0)
    timeSkipSeconds = 5;
  store.setTimeSkipSeconds(timeSkipSeconds);
  emit timeSkipChanged();
}

void TheSettings::browseDirectoryBtnClicked() {
  QString directory = QFileDialog::getExistingDirectory();
  if (directory.isEmpty())
    return;

  store.setDefaultDirectory(directory);
  directoryInput->setText(store.getDefaultDirectory());

  auto reply = QMessageBox::question(
      nullptr, "Directory Changed",
      QString("Directory changed to %1\nRestart now to take effect?")
          .arg(directory),
      QMessageBox::Yes | QMessageBox::No);
  if (reply == QMessageBox::Yes)
    emit restartApp();
}

void TheSettings::themeChanged(QString theme) {
  store.setTheme(theme);
  auto reply = QMessageBox::question(
      nullptr, "Theme Changed",
      QString("Theme changed to %1\nRestart now to take effect?").arg(theme),
      QMessageBox::Yes | QMessageBox::No);
  if (reply == QMessageBox::Yes)
    emit restartApp();
}

void TheSettings::buttonSizeChanged(QString buttonSize) {
  store.setButtonSize(buttonSize);
  auto reply = QMessageBox::question(
      nullptr, "Button Size Changed",
      QString("Button size changed to %1\nRestart now to take effect?")
          .arg(buttonSize),
      QMessageBox::Yes | QMessageBox::No);
  if (reply == QMessageBox::Yes)
    emit restartApp();
}
