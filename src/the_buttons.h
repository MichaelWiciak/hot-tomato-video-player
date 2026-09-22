#ifndef THE_BUTTONS_H
#define THE_BUTTONS_H

#include "a_video.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QList>
#include <QMediaPlayer>
#include <QObject>
#include <QPushButton>
#include <QScrollArea>

class TheButton : public QFrame {
  Q_OBJECT
public:
  TheButton(AVideo *videoInfo);

private:
  AVideo *videoInfo;
  QMediaPlayer *player;
  QPushButton *button;
  QLabel *filenameLabel;
  QLabel *durationLabel;

private slots:
  void onClick();
  void durationChanged(qint64);

signals:
  void jumpTo(AVideo *);
};

class TheButtons : public QScrollArea {
  Q_OBJECT
public:
  TheButtons();

  void addVideos(const QList<AVideo *> *videos);

private:
  void createWidgets();
  void initialiseStyleSheet();
  int currentPosition = 0;
  void updateButtons();
  QHBoxLayout *layout;

  QList<TheButton *> buttons;

public slots:
  void addVideo(AVideo *video);
  void reset();
  void currentIndexChanged(int position);

signals:
  void jumpTo(AVideo *);
};

#endif // THE_BUTTONS_H
