#ifndef THE_VIDEO_H
#define THE_VIDEO_H

#include <QObject>
#include <QVideoWidget>

class TheVideo : public QVideoWidget {
  Q_OBJECT
public:
  TheVideo();

private:
  const char debugPrefix[24] = "[the_video]: ";

  // for keyboard controls
  void keyPressEvent(QKeyEvent *event);

  // allows drag and drop files
  void dragEnterEvent(QDragEnterEvent *event);
  void dropEvent(QDropEvent *event);

private slots:
signals:
  void onVideoAdded(QString);

  // request controls
  void togglePlayPause();
  void volumeUp();
  void volumeDown();
  void mute();
  void next();
  void previous();
  void fastforward();
  void rewind();
  void fullscreen();
};

#endif // THE_VIDEO_H
