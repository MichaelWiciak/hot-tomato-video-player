#include "the_store.h"
#include <QDateTime>
#include <QDebug>
#include <QFile>
#include <QIODevice>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

TheStore store;

TheStore::TheStore() { read(); }

void TheStore::setIsMuted(bool newIsMuted) {
  isMuted = newIsMuted;
  save();
}

void TheStore::setVolume(int newVolume) {
  volume = newVolume;
  save();
}

void TheStore::setPlaybackSpeed(qreal newPlaybackSpeed) {
  playbackSpeed = newPlaybackSpeed;
  save();
}

void TheStore::addVideoToHistory(const QString videoPath) {
  if (history.contains(videoPath)) {
    history.removeOne(videoPath);
  };

  history.append(videoPath);
  save();
}

void TheStore::removeVideoFromHistory(QString videoPath) {
  history.removeOne(videoPath);
  save();
}

void TheStore::setTimeSkipSeconds(int newTimeSkipSeconds) {
  timeSkipSeconds = newTimeSkipSeconds;
  save();
}

void TheStore::setDefaultDirectory(const QString &newDefaultDirectory) {
  defaultDirectory = newDefaultDirectory;
  save();
}

void TheStore::setTutorialStatus(bool newTutorialStatus) {
  tutorialStatus = newTutorialStatus;
  save();
}

void TheStore::setTheme(const QString &newTheme) {
  theme = newTheme;
  save();
}

void TheStore::setOpenFileDirectory(const QString &newOpenFileDirectory) {
  openFileDirectory = newOpenFileDirectory;
  save();
}

void TheStore::setButtonSize(const QString &newButtonSize) {
  buttonSize = newButtonSize;
  save();
}

void TheStore::save() {
  qDebug() << debugPrefix << "writing to config file";
  QFile file(configPath);
  QJsonObject json;

  // dump values into json
  json[isMutedKey] = isMuted;
  json[volumeKey] = volume;
  json[playbackSpeedKey] = playbackSpeed;
  json[lastUpdatedKey] = QDateTime::currentMSecsSinceEpoch();
  json[timeSkipSecondsKey] = timeSkipSeconds;
  json[defaultDirectoryKey] = defaultDirectory;
  json[tutorialStatusKey] = tutorialStatus;
  json[themeKey] = theme;
  json[openFileDirectoryKey] = openFileDirectory;
  json[buttonSizeKey] = buttonSize;

  QJsonArray historyArray;

  for (int i = 0; i < history.size(); i++) {
    historyArray.append(history.at(i));
  }

  json[historyKey] = historyArray;

  QJsonDocument doc(json);

  // dont write if file is already opened
  if (file.isOpen()) {
    qDebug() << debugPrefix << "config file is already opened";
    return;
  }

  // dont write if no permission
  if (!file.open(QIODevice::WriteOnly)) {
    qDebug() << debugPrefix << "unable to open config file (write)";
    return;
  }

  file.write(doc.toJson());

  file.close();
  qDebug() << debugPrefix << "values saved to config file";
}

void TheStore::read() {
  qDebug() << debugPrefix << "reading from config file";
  QFile file(configPath);

  // dont read if no config file
  if (!file.exists()) {
    qDebug() << debugPrefix
             << "config file does not exist, using default values";
    return;
  }

  // dont read if no permission
  if (!file.open(QIODevice::ReadOnly)) {
    qDebug() << debugPrefix
             << "unable to read config file (read), using default values";
    return;
  }

  // convert to qt json object
  QByteArray bytes = file.readAll();
  QJsonDocument d = QJsonDocument::fromJson(bytes);
  QJsonObject json = d.object();

  // parse into class variables
  isMuted = QJsonValue(json.value(isMutedKey)).toBool();
  volume = QJsonValue(json.value(volumeKey)).toInt(volume);
  playbackSpeed =
      QJsonValue(json.value(playbackSpeedKey)).toDouble(playbackSpeed);
  QJsonArray historyArray = QJsonValue(json.value(historyKey)).toArray();
  timeSkipSeconds =
      QJsonValue(json.value(timeSkipSecondsKey)).toInt(timeSkipSeconds);
  defaultDirectory =
      QJsonValue(json.value(defaultDirectoryKey)).toString(defaultDirectory);
  tutorialStatus = QJsonValue(json.value(tutorialStatusKey)).toBool();
  theme = QJsonValue(json.value(themeKey)).toString(theme);
  openFileDirectory =
      QJsonValue(json.value(openFileDirectoryKey)).toString(openFileDirectory);
  buttonSize = QJsonValue(json.value(buttonSizeKey)).toString(buttonSize);

  for (int i = 0; i < historyArray.size(); i++) {
    history.append(historyArray[i].toString());
  }

  qDebug() << debugPrefix << "values initialised from config file";
}
