#include "the_window.h"
#include "a_video.h"
#include "the_appbar.h"
#include "the_buttons.h"
#include "the_controls.h"
#include "the_player.h"
#include "the_recents.h"
#include "the_settings.h"
#include "the_store.h"
#include "the_tutorial.h"
#include "the_video.h"
#include <QCoreApplication>
#include <QDebug>
#include <QKeyEvent>

TheWindow::TheWindow() {
  setProperty("theme", store.getTheme());
  setProperty("buttonSize", store.getButtonSize());

  // the widget that will show the video

  // the QMediaPlayer which controls the playback
  ThePlayer *player = new ThePlayer;
  TheVideo *videoWidget = new TheVideo;

  player->setNotifyInterval(100);
  player->setVideoOutput(videoWidget);

  // collect all the videos in the folder
  if (store.getDefaultDirectory() != "") {
    player->loadVideoDirectory(store.getDefaultDirectory().toStdString());
  }

  // create the main window and layout
  QWidget *central = new QWidget;
  QVBoxLayout *main = new QVBoxLayout();
  QHBoxLayout *panels = new QHBoxLayout();
  QVBoxLayout *body = new QVBoxLayout();

  body->setSpacing(0);
  body->setMargin(0);
  main->setSpacing(0);
  main->setMargin(0);
  panels->setSpacing(0);
  panels->setMargin(0);

  TheRecents *recentsPanel = new TheRecents;
  TheSettings *settingsPanel = new TheSettings;

  TheAppBar *appBar = new TheAppBar;
  TheTutorial *tutorialText = new TheTutorial(store.getTutorialStatus());

  body->addWidget(appBar);
  body->addWidget(tutorialText);

  body->addLayout(panels);

  panels->addWidget(settingsPanel);
  panels->addLayout(main, 1);
  panels->addWidget(recentsPanel);

  central->setLayout(body);
  setCentralWidget(central);
  setWindowTitle("Hot Tomato Video Player");
  setMinimumSize(400, 500);

  QFile *styleSheet = new QFile(":/styles/globals.qss");
  styleSheet->open(QFile::ReadOnly);
  setStyleSheet(styleSheet->readAll());
  delete styleSheet;

  // the video control buttons
  TheControls *controls = new TheControls;

  // the new buttons
  TheButtons *buttons = new TheButtons;

  // connect controls and player
  QObject::connect(controls, SIGNAL(volumeChanged(int)), player,
                   SLOT(setVolume(int)));
  QObject::connect(controls, SIGNAL(shouldPlay()), player, SLOT(play()));
  QObject::connect(controls, SIGNAL(shouldPause()), player, SLOT(pause()));
  QObject::connect(controls, SIGNAL(positionChanged(qint64)), player,
                   SLOT(setPosition(qint64)));
  QObject::connect(player, SIGNAL(positionChanged(qint64)), controls,
                   SLOT(setPosition(qint64)));
  QObject::connect(player, SIGNAL(durationChanged(qint64)), controls,
                   SLOT(setDuration(qint64)));
  QObject::connect(controls, SIGNAL(playbackRateChanged(qreal)), player,
                   SLOT(setPlaybackRate(qreal)));
  QObject::connect(controls, SIGNAL(fullscreenChanged(bool)), videoWidget,
                   SLOT(setFullScreen(bool)));
  QObject::connect(videoWidget, SIGNAL(fullScreenChanged(bool)), controls,
                   SLOT(setFullscreen(bool)));
  QObject::connect(appBar, SIGNAL(settingsIsOpenChanged(bool)), settingsPanel,
                   SLOT(setVisible(bool)));
  QObject::connect(appBar, SIGNAL(recentsIsOpenChanged(bool)), recentsPanel,
                   SLOT(setVisible(bool)));
  QObject::connect(appBar, SIGNAL(helpBtnClicked()), tutorialText,
                   SLOT(helpWindow()));
  QObject::connect(recentsPanel, SIGNAL(onVideoSelected(AVideo *)), player,
                   SLOT(videoSelectedFromRecents(AVideo *)));
  QObject::connect(appBar, SIGNAL(addFileBtnClicked()), tutorialText,
                   SLOT(hideTutorial()));
  QObject::connect(buttons, SIGNAL(jumpTo(AVideo *)), player,
                   SLOT(jumpTo(AVideo *)));
  QObject::connect(appBar, SIGNAL(addFileBtnClicked()), player,
                   SLOT(openFile()));
  QObject::connect(player, SIGNAL(videoAdded(AVideo *)), buttons,
                   SLOT(addVideo(AVideo *)));
  QObject::connect(videoWidget, SIGNAL(onVideoAdded(QString)), player,
                   SLOT(addVideo(QString)));

  QObject::connect(player, SIGNAL(stateChanged(QMediaPlayer::State)), controls,
                   SLOT(stateChanged(QMediaPlayer::State)));
  QObject::connect(controls, SIGNAL(next()), player->playlist(), SLOT(next()));
  QObject::connect(controls, SIGNAL(previous()), player->playlist(),
                   SLOT(previous()));
  QObject::connect(player, SIGNAL(videoAdded(AVideo *)), recentsPanel,
                   SLOT(render()));
  QObject::connect(settingsPanel, SIGNAL(timeSkipChanged()), controls,
                   SLOT(updateTimeSkipBtns()));

  QObject::connect(videoWidget, SIGNAL(togglePlayPause()), controls,
                   SLOT(playBtnClicked()));
  QObject::connect(videoWidget, SIGNAL(fastforward()), controls,
                   SLOT(fastforwardBtnClicked()));
  QObject::connect(videoWidget, SIGNAL(rewind()), controls,
                   SLOT(rewindBtnClicked()));
  QObject::connect(videoWidget, SIGNAL(mute()), controls,
                   SLOT(muteBtnClicked()));
  QObject::connect(videoWidget, SIGNAL(fullscreen()), controls,
                   SLOT(fullscreenBtnClicked()));
  QObject::connect(videoWidget, SIGNAL(next()), controls,
                   SLOT(nextBtnClicked()));
  QObject::connect(videoWidget, SIGNAL(previous()), controls,
                   SLOT(previousBtnClicked()));
  QObject::connect(videoWidget, SIGNAL(volumeUp()), controls, SLOT(volumeUp()));
  QObject::connect(videoWidget, SIGNAL(volumeDown()), controls,
                   SLOT(volumeDown()));
  QObject::connect(player, SIGNAL(clearButtons()), buttons, SLOT(reset()));
  QObject::connect(player->playlist(), SIGNAL(currentIndexChanged(int)),
                   buttons, SLOT(currentIndexChanged(int)));
  QObject::connect(controls,
                   SIGNAL(playbackModeChanged(QMediaPlaylist::PlaybackMode)),
                   player, SLOT(setPlaybackMode(QMediaPlaylist::PlaybackMode)));
  QObject::connect(settingsPanel, SIGNAL(restartApp()), this,
                   SLOT(restartApp()));

  // add the video and the buttons to the top level widget
  main->addWidget(videoWidget, 1);
  main->addWidget(controls);
  main->addWidget(buttons);

  buttons->addVideos(&player->getNewVideos());
}

void TheWindow::restartApp() {
  // exists with restart code
  QCoreApplication *app = QCoreApplication::instance();
  if (app)
    app->exit(RESTART_EXIT_CODE);
}
