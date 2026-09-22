#ifndef THE_STORE_H
#define THE_STORE_H

#include <QList>
#include <QString>

/**
 * The Store class
 */
class TheStore {

public:
  TheStore();

  // getters and setters

  /**
   * @brief get IsMuted
   * @return isMuted
   */
  bool getIsMuted() const { return isMuted; }
  /**
   * @brief set IsMuted
   * @param newIsMuted new isMuted
   */
  void setIsMuted(bool newIsMuted);

  /**
   * @brief get Volume
   * @return volume
   */
  int getVolume() const { return volume; }
  /**
   * @brief set Volume
   * @param newVolume new volume value
   */
  void setVolume(int newVolume);

  /**
   * @brief get PlaybackSpeed
   * @return playback speed
   */
  qreal getPlaybackSpeed() const { return playbackSpeed; }
  /**
   * @brief set PlaybackSpeed
   * @param newPlaybackSpeed new playback speed
   */
  void setPlaybackSpeed(qreal newPlaybackSpeed);

  /**
   * @brief get history
   * @return video history
   */
  QList<QString> getHistory() const { return history; };

  /**
   * @brief saves a video to history
   * @param videoPath
   * @return video history
   */
  void addVideoToHistory(const QString videoPath);

  /**
   * @brief removes a video from history
   * @param videoPath
   */
  void removeVideoFromHistory(const QString videoPath);

  /**
   * @brief get timeSkipSeconds
   * @return timeSkipSeconds
   */
  int getTimeSkipSeconds() const { return timeSkipSeconds; }

  /**
   * @brief set timeSkipSeconds
   * @param newTimeSkipSeconds
   */
  void setTimeSkipSeconds(int newTimeSkipSeconds);

  /**
   * @brief get defaultDirectory
   * @return defaultDirectory
   */
  const QString &getDefaultDirectory() const { return defaultDirectory; }

  /**
   * @brief set defaultDirectory
   * @param newDefaultDirectory
   */
  void setDefaultDirectory(const QString &newDefaultDirectory);

  /**
   * @brief set tutorialStatus
   * @param newTutorialStatus
   */
  void setTutorialStatus(bool newTutorialStatus);

  /**
   * @brief get tutorialStatus
   * @return tutorialStatus
   */
  const bool &getTutorialStatus() const { return tutorialStatus; }

  /**
   * @brief get theme
   * @return theme
   */
  const QString &getTheme() const { return theme; }

  void setTheme(const QString &newTheme);

  /**
   * get openFileDirectory
   * @return openFileDirectory
   */
  QString getOpenFileDirectory() const { return openFileDirectory; }

  /**
   * set openFileDirectory
   * @param openFileDirectory the new open file directory
   */
  void setOpenFileDirectory(const QString &openFileDirectory);

  /**
   * @brief get buttonSize
   * @return buttonSize
   */
  const QString &getButtonSize() const { return buttonSize; }

  /**
   * @brief set buttonSize
   * @param newButtonSize
   */
  void setButtonSize(const QString &newButtonSize);

private:
  // prefix for `qDebug()`;
  const char debugPrefix[24] = "[the_config]: ";

  /**
   * isMuted
   */
  bool isMuted = false;
  /**
   * isMuted Key
   */
  QString isMutedKey = "player.isMuted";
  /**
   * volume
   */
  int volume = 100;
  /**
   * volume key
   */
  QString volumeKey = "player.volume";
  /**
   * playback speed
   */
  qreal playbackSpeed = 1.00;
  /**
   * playback speed key
   */
  QString playbackSpeedKey = "player.playbackSpeed";

  /**
   * the video history
   */
  QList<QString> history;

  /**
   * the video history key
   */
  QString historyKey = "player.history";

  /**
   * fast forward / rewind amount
   */
  int timeSkipSeconds = 5;

  /**
   * key for time skip seconds
   */
  QString timeSkipSecondsKey = "player.timeSkipSeconds";

  /**
   * default directory for loading videos
   */
  QString defaultDirectory = "";

  /**
   * key for default directory
   */
  QString defaultDirectoryKey = "player.defaultDirectory";

  /**
   * default status for the tutorial
   */
  bool tutorialStatus = true;

  /**
   * key for tutorial status
   */
  QString tutorialStatusKey = "player.tutorialStatus";

  /**
   * theme
   */
  QString theme = "light";

  /**
   * theme key
   */
  QString themeKey = "player.theme";

  /**
   * buttonSize
   */
  QString buttonSize = "normal";

  /**
   * buttonSize key
   */
  QString buttonSizeKey = "player.buttonSize";

  /**
   * openFileDirectory
   */
  QString openFileDirectory = ".";

  /**
   * openFileDirectory
   */
  QString openFileDirectoryKey = "player.openFileDirectory";

  /**
   * config file path
   */
  QString configPath = "./config.json";
  /**
   * last updated key
   */
  QString lastUpdatedKey = "lastUpdated";

  /**
   * saves the current config
   */
  void save();
  /**
   * loads the saved config
   */
  void read();
};

/**
 * single store instance
 */
extern TheStore store;

#endif // THE_STORE_H
