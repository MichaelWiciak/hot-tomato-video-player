#include "a_video.h"
#include "the_utils.h"

AVideo::AVideo(QString videoPath) {
  this->iconPath = QString(TheUtils::getIconPathFromVideoPath(videoPath));
  this->videoPath = QString(videoPath);
}
