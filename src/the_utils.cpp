#include "the_utils.h"

QString TheUtils::getIconPathFromVideoPath(const QString videoPath) {
  // strips the last bit and adds .png
  QString thumb = videoPath.left(videoPath.length() - 4) + ".png";
  return thumb;
}

bool TheUtils::filenameIsValidVideo(const QString videoPath) {
  // if its windows, we want videos to end with .wmv
  if (isWindows())
    return videoPath.endsWith(".wmv");

  // for other OS, eg linux/macOS
  // we want videos to end with either .mp4 or .MOV
  return videoPath.endsWith(".mp4") || videoPath.endsWith(".MOV");
}

bool TheUtils::isWindows() {
#if defined(_WIN32)
  return true;
#endif
  return false;
}

QString TheUtils::prettyTime(qint64 time) {
  // retrieves seconds and minutes from the given time
  qint64 seconds = time / 1000;
  qint64 minutes = seconds / 60;
  seconds = seconds - minutes * 60;

  // notice we pad seconds and minutes with 0 until length 2, pretty right?
  return QStringLiteral("%1:%2")
      .arg(minutes, 2, 10, QLatin1Char('0'))
      .arg(seconds, 2, 10, QLatin1Char('0'));
}

bool TheUtils::isLinux() {
#if defined(Q_OS_LINUX)
  return true;
#endif
  return false;
}
