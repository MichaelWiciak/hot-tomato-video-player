//
// Created by twak on 11/11/2019.
//

#ifndef CW2_THE_PLAYER_H
#define CW2_THE_PLAYER_H

#include <QApplication>
#include <QList>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QTimer>
#include <vector>

#include "a_video.h"

// Change what extensions the file selector dialog shows depending on the
// platform he application is running on and the video formats that it supports.
#if defined(_WIN32)
#define SUPPORTED_EXTENSIONS "Videos (*.wmv)"
#else
#define SUPPORTED_EXTENSIONS "Videos (*.mp4 *.MOV)"
#endif

class ThePlayer : public QMediaPlayer {
  Q_OBJECT

private:
  QList<AVideo *> videos;

  QTimer *mTimer;
  long updateCount = 0;

  QMediaPlaylist *_playlist;

public:
  ThePlayer();

  void loadVideoDirectory(std::string directory);

  void addVideo(std::string path);

  const QList<AVideo *> &getNewVideos() const { return videos; }

private:
  QString currentDirectory = "";
  bool setShouldAddVideo(bool newShouldAddVideo) {
    bool last = shouldAddVideo;
    shouldAddVideo = newShouldAddVideo;
    return last;
  }

  bool shouldAddVideo = true;

private slots:
  void openFile();

public slots:
  void jumpTo(AVideo *video);
  void addVideo(QString path);
  void videoSelectedFromRecents(AVideo *video);
  void setPlaybackMode(QMediaPlaylist::PlaybackMode mode);

signals:
  void videoAdded(AVideo *);
  void clearButtons();
};

#endif // CW2_THE_PLAYER_H
