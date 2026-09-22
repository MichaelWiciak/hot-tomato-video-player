#include "the_buttons.h"
#include "the_utils.h"
#include <QFile>
#include <QIcon>
#include <QStyle>
#include <QUrl>
#include <QWidget>

TheButton::TheButton(AVideo *videoInfo) {
  setObjectName("buttons__button");
  QGridLayout *layout = new QGridLayout;
  layout->setMargin(0);
  layout->setSpacing(0);

  player = new QMediaPlayer;
  player->setMedia(*videoInfo->getUrl());

  button = new QPushButton;
  durationLabel = new QLabel("00:00");
  durationLabel->setObjectName("buttons__duration");
  filenameLabel = new QLabel(videoInfo->getUrl()->fileName());
  filenameLabel->setObjectName("buttons__filename");
  filenameLabel->setAlignment(Qt::AlignCenter);

  this->videoInfo = videoInfo;
  const auto icon = *videoInfo->getIcon();

  if (icon.availableSizes().size() == 0) {
    button->setText(QUrl(videoInfo->getVideoPath()).fileName());
  } else {
    button->setIcon(*videoInfo->getIcon());
  }

  layout->addWidget(button, 0, 0, 5, 5);
  layout->addWidget(durationLabel, 4, 4, 1, 1);
  layout->addWidget(filenameLabel, 5, 0, 1, 5);
  setLayout(layout);

  QObject::connect(button, SIGNAL(clicked()), this, SLOT(onClick()));
  QObject::connect(player, SIGNAL(durationChanged(qint64)), this,
                   SLOT(durationChanged(qint64)));
}

void TheButton::onClick() { emit jumpTo(videoInfo); }

void TheButton::durationChanged(qint64 duration) {
  durationLabel->setText(TheUtils::prettyTime(duration));
}

TheButtons::TheButtons() {
  // scrollbar off since windows doesnt reserve space for vertical scrollbar
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setWidgetResizable(true);
  createWidgets();
  initialiseStyleSheet();
}

void TheButtons::addVideo(AVideo *video) {
  TheButton *button = new TheButton(video);
  layout->addWidget(button);
  buttons.append(button);

  QObject::connect(button, SIGNAL(jumpTo(AVideo *)), this,
                   SIGNAL(jumpTo(AVideo *)));
  updateButtons();
}

void TheButtons::addVideos(const QList<AVideo *> *videos) {
  for (int i = 0; i < videos->size(); i++) {
    addVideo((*videos)[i]);
  }
}

void TheButtons::reset() {
  for (int i = 0; i < buttons.size(); i++) {
    delete buttons[i];
  }
  buttons.clear();
}

void TheButtons::currentIndexChanged(int position) {
  currentPosition = position;
  updateButtons();
}

void TheButtons::createWidgets() {
  QWidget *wrapper = new QWidget;
  layout = new QHBoxLayout();

  wrapper->setLayout(layout);

  setWidget(wrapper);
  setWidgetResizable(true);
}

void TheButtons::initialiseStyleSheet() {
  // set styles
  QFile *styleSheet = new QFile(":/styles/the_buttons.qss");
  styleSheet->open(QFile::ReadOnly);
  setStyleSheet(styleSheet->readAll());
  delete styleSheet;
}

void TheButtons::updateButtons() {
  for (int i = 0; i < buttons.size(); i++) {
    buttons[i]->setProperty("active", currentPosition == i);

    // force styles re-paint
    style()->unpolish(buttons[i]);
    style()->polish(buttons[i]);
  }
}
