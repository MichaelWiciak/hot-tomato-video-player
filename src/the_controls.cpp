#include "the_controls.h"
#include "the_store.h"
#include "the_utils.h"
#include <QDebug>
#include <QFile>
#include <QHBoxLayout>
#include <QIcon>
#include <QKeyEvent>
#include <QResizeEvent>
#include <QVBoxLayout>

TheControls::TheControls() {
  loadConfig();

  createWidgets();
  initialiseSignalsAndSlots();

  updatePlayBtn();
  updateMuteBtn();
  updateVolumeSlider();
  updateTimeSkipBtns();
  updateRepeatBtn();
  initialisePlaybackSpeeds();
  initialiseStyleSheet();
}

void TheControls::loadConfig() {
  isMuted = store.getIsMuted();
  volume = store.getVolume();
  playbackSpeed = store.getPlaybackSpeed();
}

void TheControls::createWidgets() {

  QVBoxLayout *layout = new QVBoxLayout;
  QHBoxLayout *h1Layout = new QHBoxLayout;
  QHBoxLayout *h2Layout = new QHBoxLayout;

  h1Layout->setSpacing(8);
  h2Layout->setSpacing(8);
  layout->setSpacing(0);

  timelineSlider = new QSlider(Qt::Horizontal);
  fastforwardBtn = new QPushButton();
  fastforwardBtn->setToolTip("Fastforward");
  rewindBtn = new QPushButton();
  rewindBtn->setToolTip("Rewind");
  nextBtn = new QPushButton();
  nextBtn->setToolTip("Next");
  previousBtn = new QPushButton();
  previousBtn->setToolTip("Previous");
  repeatBtn = new QPushButton;

  rewindBtn->setObjectName("rewindBtn");
  fastforwardBtn->setObjectName("fastforwardBtn");

  playBtn = new QPushButton();
  volumeBtn = new QPushButton();
  volumeSlider = new QSlider(Qt::Horizontal);
  fullscreenBtn = new QPushButton();
  fullscreenBtn->setToolTip("Fullscreen");
  playbackSpeedDropdown = new QComboBox();
  playbackSpeedDropdown->setToolTip("Change playback speed");
  positionLabel = new QLabel(TheUtils::prettyTime(position));
  durationLabel = new QLabel(TheUtils::prettyTime(duration));

  timelineSlider->setMinimum(0);

  // playback speed doesnt work on windows, so hide it
  if (TheUtils::isWindows())
    playbackSpeedDropdown->setHidden(true);

  // fullscreen doesnt work nicely on linux, so hide it
  else if (TheUtils::isLinux()) {
    fullscreenBtn->setHidden(true);
  }

  nextBtn->setIcon(QIcon(":/icons/forward.png"));
  previousBtn->setIcon(QIcon(":/icons/backward.png"));
  fastforwardBtn->setIcon(QIcon(":/icons/arrow-uturn-right.png"));
  rewindBtn->setIcon(QIcon(":/icons/arrow-uturn-left.png"));
  fullscreenBtn->setIcon(QIcon(":/icons/arrows-pointing-out.png"));

  volumeSlider->setMinimum(0);
  volumeSlider->setMaximum(100);
  volumeSlider->setValue(volume);

  h1Layout->addWidget(positionLabel);
  h1Layout->addWidget(timelineSlider, 1);
  h1Layout->addWidget(repeatBtn);
  h1Layout->addWidget(durationLabel);

  h2Layout->addWidget(playBtn);
  h2Layout->addWidget(rewindBtn);
  h2Layout->addWidget(fastforwardBtn);
  h2Layout->addWidget(previousBtn);
  h2Layout->addWidget(nextBtn);
  h2Layout->addStretch(1);
  h2Layout->addWidget(playbackSpeedDropdown);
  h2Layout->addWidget(volumeBtn);
  h2Layout->addWidget(volumeSlider);
  h2Layout->addWidget(fullscreenBtn);

  layout->addLayout(h1Layout);
  layout->addLayout(h2Layout);

  setLayout(layout);
}

void TheControls::initialiseSignalsAndSlots() {
  QObject::connect(playBtn, SIGNAL(clicked()), this, SLOT(playBtnClicked()));
  QObject::connect(volumeSlider, SIGNAL(valueChanged(int)), this,
                   SLOT(onVolumeChange(int)));
  QObject::connect(fullscreenBtn, SIGNAL(clicked()), this,
                   SLOT(fullscreenBtnClicked()));
  QObject::connect(volumeBtn, SIGNAL(clicked()), this, SLOT(muteBtnClicked()));
  QObject::connect(timelineSlider, SIGNAL(valueChanged(int)), this,
                   SLOT(onTimelineChange(int)));
  QObject::connect(fastforwardBtn, SIGNAL(clicked()), this,
                   SLOT(fastforwardBtnClicked()));
  QObject::connect(rewindBtn, SIGNAL(clicked()), this,
                   SLOT(rewindBtnClicked()));
  QObject::connect(playbackSpeedDropdown, SIGNAL(activated(int)), this,
                   SLOT(onPlaybackSpeedChange(int)));
  QObject::connect(nextBtn, SIGNAL(clicked()), this, SLOT(nextBtnClicked()));
  QObject::connect(previousBtn, SIGNAL(clicked()), this,
                   SLOT(previousBtnClicked()));
  QObject::connect(repeatBtn, SIGNAL(clicked()), this,
                   SLOT(repeatBtnClicked()));
}

void TheControls::updatePlayBtn() {
  if (isPlaying) {
    playBtn->setIcon(QIcon(":/icons/pause.png"));
    playBtn->setToolTip("Pause");
  } else {
    playBtn->setIcon(QIcon(":/icons/play.png"));
    playBtn->setToolTip("Play");
  }
}

void TheControls::updateMuteBtn() {
  if (isMuted) {
    volumeBtn->setIcon(QIcon(":/icons/speaker-x-mark.png"));
    volumeBtn->setToolTip("Mute");

  } else {
    volumeBtn->setIcon(QIcon(":/icons/speaker-wave.png"));
    volumeBtn->setToolTip("Unmute");
  }
}

void TheControls::updateRepeatBtn() {
  if (playbackMode == QMediaPlaylist::CurrentItemOnce)
    repeatBtn->setIcon(
        QIcon(":/icons/arrow-path-rounded-square--disabled.png"));
  else if (playbackMode == QMediaPlaylist::CurrentItemInLoop)
    repeatBtn->setIcon(QIcon(":/icons/arrow-path-rounded-square--one.png"));
  else if (playbackMode == QMediaPlaylist::Loop)
    repeatBtn->setIcon(QIcon(":/icons/arrow-path-rounded-square--enabled.png"));
}

void TheControls::updateVolumeSlider() { volumeSlider->setEnabled(!isMuted); }

void TheControls::initialisePlaybackSpeeds() {
  int currentIndex = 3;

  for (ulong i = 0; i < thePlaybackSpeeds.size(); i++) {
    auto thePlaybackSpeed = thePlaybackSpeeds[i];
    playbackSpeedDropdown->addItem(thePlaybackSpeed.first);
    if (thePlaybackSpeed.second == playbackSpeed)
      currentIndex = i;
  }

  playbackSpeedDropdown->setCurrentIndex(currentIndex);
}

void TheControls::initialiseStyleSheet() {
  // set styles
  QFile *styleSheet = new QFile(":/styles/the_controls.qss");
  styleSheet->open(QFile::ReadOnly);
  setStyleSheet(styleSheet->readAll());
  delete styleSheet;
}

void TheControls::resizeEvent(QResizeEvent *event) {
  auto width = event->size().width();
  qDebug() << debugPrefix << "width" << width;
  playbackSpeedDropdown->setVisible(width > 600 && !TheUtils::isWindows());
  fastforwardBtn->setVisible(width > 600);
  rewindBtn->setVisible(width > 600);
  nextBtn->setVisible(width > 400);
  previousBtn->setVisible(width > 400);
  repeatBtn->setVisible(width > 400);
  volumeSlider->setVisible(width > 300);
}

void TheControls::playBtnClicked() {
  isPlaying = !isPlaying;
  updatePlayBtn();

  if (isPlaying) {
    emit shouldPlay();
  } else {
    emit shouldPause();
  }
}

void TheControls::onVolumeChange(int newVolume) {
  //  muted = false;
  if (newVolume != 0)
    volume = newVolume;
  emit volumeChanged(newVolume);
  qDebug() << debugPrefix << "Volume: " << newVolume;
  updateMuteBtn();
  store.setVolume(volume);
}

void TheControls::muteBtnClicked() {
  isMuted = !isMuted;

  emit volumeChanged(isMuted ? 0 : volume);
  updateVolumeSlider();
  qDebug() << debugPrefix << "Is muted: " << isMuted;
  updateMuteBtn();
  store.setIsMuted(isMuted);
}

void TheControls::onTimelineChange(int value) {
  qDebug() << debugPrefix << "Position change: " << TheUtils::prettyTime(value)
           << value;
  emit positionChanged(value);
}

void TheControls::fastforwardBtnClicked() {
  emit positionChanged(position + store.getTimeSkipSeconds() * 1000);
}

void TheControls::rewindBtnClicked() {
  emit positionChanged(position - store.getTimeSkipSeconds() * 1000);
}

void TheControls::onPlaybackSpeedChange(int index) {
  qreal speed = thePlaybackSpeeds.at(index).second;
  qDebug() << debugPrefix << "Playback change: " << speed;
  emit playbackRateChanged(speed);
  store.setPlaybackSpeed(speed);
}

void TheControls::fullscreenBtnClicked() {
  isFullscreen = !isFullscreen;
  emit fullscreenChanged(isFullscreen);
}

void TheControls::repeatBtnClicked() {
  if (playbackMode == QMediaPlaylist::CurrentItemOnce)
    playbackMode = QMediaPlaylist::Loop;
  else if (playbackMode == QMediaPlaylist::Loop)
    playbackMode = QMediaPlaylist::CurrentItemInLoop;
  else if (playbackMode == QMediaPlaylist::CurrentItemInLoop)
    playbackMode = QMediaPlaylist::CurrentItemOnce;
  updateRepeatBtn();
  emit playbackModeChanged(playbackMode);
}

void TheControls::nextBtnClicked() {
  emit playbackModeChanged(QMediaPlaylist::Loop);
  emit next();
  emit playbackModeChanged(playbackMode);
}

void TheControls::previousBtnClicked() {
  emit playbackModeChanged(QMediaPlaylist::Loop);
  emit previous();
  emit playbackModeChanged(playbackMode);
}

void TheControls::volumeDown() { volumeSlider->setValue(volume - 10); }

void TheControls::volumeUp() { volumeSlider->setValue(volume + 10); }

void TheControls::setDuration(qint64 newDuration) {
  duration = newDuration;
  durationLabel->setText(TheUtils::prettyTime(duration));
  timelineSlider->setMaximum(duration);
}

void TheControls::setPosition(qint64 newPosition) {
  position = newPosition;
  positionLabel->setText(TheUtils::prettyTime(position));

  // block and unblock signal so value dont bounce back and forth
  bool wasSignalsBlocked = timelineSlider->blockSignals(true);
  timelineSlider->setValue(position);
  timelineSlider->blockSignals(wasSignalsBlocked);
}

void TheControls::setFullscreen(bool fullscreen) { isFullscreen = fullscreen; }

void TheControls::stateChanged(QMediaPlayer::State state) {
  isPlaying = state == QMediaPlayer::PlayingState;
  updatePlayBtn();
}

void TheControls::updateTimeSkipBtns() {
  fastforwardBtn->setText(QString("%1s").arg(store.getTimeSkipSeconds()));
  rewindBtn->setText(QString("%1s").arg(store.getTimeSkipSeconds()));
}
