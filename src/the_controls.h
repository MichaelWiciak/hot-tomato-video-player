#ifndef THE_CONTROLS_H
#define THE_CONTROLS_H

#include <QComboBox>
#include <QLabel>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QObject>
#include <QPushButton>
#include <QSlider>
#include <QWidget>
#include <vector>

class TheControls : public QWidget {
  Q_OBJECT
public:
  TheControls();

private:
  const char debugPrefix[24] = "[the_controls]: ";
  void loadConfig();
  void createWidgets();
  void initialiseSignalsAndSlots();
  void updatePlayBtn();
  void updateMuteBtn();
  void updateRepeatBtn();
  void updateVolumeSlider();
  void initialisePlaybackSpeeds();
  void initialiseStyleSheet();

  void resizeEvent(QResizeEvent *event);

  int volume = 100;
  bool isMuted = false;
  bool isPlaying = true;
  bool isFullscreen = false;
  qreal playbackSpeed = 1.0;

  qint64 duration = 0;
  qint64 position = 0;

  QMediaPlaylist::PlaybackMode playbackMode = QMediaPlaylist::CurrentItemInLoop;

  /**
   * @brief progress bar
   */
  QSlider *timelineSlider;

  /**
   * @brief fast forward 5s
   */
  QPushButton *fastforwardBtn;

  /**
   * @brief rewind 5s
   */
  QPushButton *rewindBtn;

  /**
   * @brief previous video
   */
  QPushButton *previousBtn;

  /**
   * @brief next video
   */
  QPushButton *nextBtn;

  /**
   * @brief play/pause button
   */
  QPushButton *playBtn;

  /**
   * @brief for toggling mute/unmute
   */
  QPushButton *volumeBtn;

  /**
   * @brief for controlling volume
   */
  QSlider *volumeSlider;

  /**
   * @brief for toggling fullscreen
   */
  QPushButton *fullscreenBtn;

  /**
   * @brief for toggling repeating the video
   */
  QPushButton *repeatBtn;

  /**
   * @brief for controlling playback speed
   */
  QComboBox *playbackSpeedDropdown;

  QLabel *positionLabel;

  QLabel *durationLabel;

private slots:

  void onVolumeChange(int);
  void onTimelineChange(int);
  void onPlaybackSpeedChange(int);

public slots:
  void setDuration(qint64);
  void setPosition(qint64);
  void setFullscreen(bool);
  void stateChanged(QMediaPlayer::State);

  void playBtnClicked();
  void updateTimeSkipBtns();
  void fastforwardBtnClicked();
  void rewindBtnClicked();
  void muteBtnClicked();
  void fullscreenBtnClicked();
  void repeatBtnClicked();
  void nextBtnClicked();
  void previousBtnClicked();

  void volumeDown();
  void volumeUp();

signals:
  void fullscreenChanged(bool);
  void volumeChanged(int);
  void positionChanged(qint64);
  void playbackRateChanged(qreal);
  void shouldPlay();
  void shouldPause();
  void next();
  void previous();
  void playbackModeChanged(QMediaPlaylist::PlaybackMode);
};

const QString thePlaybackSpeed025 = "0.25", // x0.25 speed
    thePlaybackSpeed050 = "0.5",            // x0.5 speed
    thePlaybackSpeed075 = "0.75",           // x0.75 speed
    thePlaybackSpeed100 = "1",              // x1 speed
    thePlaybackSpeed125 = "1.25",           // x1.25 speed
    thePlaybackSpeed150 = "1.5",            // x1.5 speed
    thePlaybackSpeed175 = "1.75",           // x1.75 speed
    thePlaybackSpeed200 = "2";              // x2 speed

// available playback speeds
const std::vector<std::pair<QString, qreal>> thePlaybackSpeeds = {
    std::make_pair(thePlaybackSpeed025, 0.25),
    std::make_pair(thePlaybackSpeed050, 0.5),
    std::make_pair(thePlaybackSpeed075, 0.75),
    std::make_pair(thePlaybackSpeed100, 1.0),
    std::make_pair(thePlaybackSpeed125, 1.25),
    std::make_pair(thePlaybackSpeed150, 1.5),
    std::make_pair(thePlaybackSpeed175, 1.75),
    std::make_pair(thePlaybackSpeed200, 2.0),
};

#endif // THE_CONTROLS_H
