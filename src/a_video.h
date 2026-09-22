#ifndef A_VIDEO_H
#define A_VIDEO_H

#include <QIcon>
#include <QString>
#include <QUrl>

/**
 * Class representing a video
 */
class AVideo {
public:
  AVideo(QString videoPath);
  ~AVideo(){};

  const QString &getVideoPath() const { return videoPath; }
  const QString &getIconPath() const { return iconPath; }

  const QUrl *getUrl() { return new QUrl(QUrl::fromLocalFile(videoPath)); }
  const QIcon *getIcon() { return new QIcon(iconPath); }

private:
  QString videoPath;
  QString iconPath;
};

#endif // A_VIDEO_H
