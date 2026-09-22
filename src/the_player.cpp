//
// Created by twak on 11/11/2019.
//

#include "the_player.h"
#include "the_store.h"
#include "the_utils.h"
#include <QFileDialog>
#include <QImageReader>
#include <QMessageBox>
#include <QMimeDatabase>
#include <QtCore/QDir>
#include <QtCore/QDirIterator>
#include <QtCore/QFileInfo>

ThePlayer::ThePlayer() : QMediaPlayer(nullptr) {
  _playlist = new QMediaPlaylist;
  setPlaylist(_playlist);
  _playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);

  setPlaybackRate(store.getPlaybackSpeed());
  setVolume(store.getIsMuted() ? 0 : store.getVolume());
}

void ThePlayer::loadVideoDirectory(std::string directory) {
  QString requestedDirectory = QString::fromStdString(directory);

  if (requestedDirectory == currentDirectory)
    return;

  emit clearButtons();
  videos.clear();

  currentDirectory = requestedDirectory;
  QDir dir(QString::fromStdString(directory));
  QDirIterator it(dir);

  while (it.hasNext()) { // for all files
    QString f = it.next();
    if (TheUtils::filenameIsValidVideo(f)) {
      addVideo(f);
    }
  }

  play();
}

void ThePlayer::addVideo(QString path) {
  // check if the path is empty
  if (path.isEmpty()) {
    qDebug() << "warning: empty path passed" << Qt::endl;
    return;
  }

  // fix for drag and drop on windows
  if (TheUtils::isWindows() && path[0] == '/') {
      path = path.remove(0, 1);
  }

  // check if the file is actually a video (ensure checks content, not just
  // extension)
  QMimeType fileMime =
      QMimeDatabase().mimeTypeForFile(path, QMimeDatabase::MatchContent);

  // check if the mime type is a video
  if (!fileMime.name().contains("video/")) {
    // check if the aliases contain video
    // NOTE: done becuase on windows, wmv files return "application/vnd.ms-asf"
    // instead of
    //       something useful like its alias "video/x-ms-wm"!
    bool containsVideo = false;

    // check each mime "alias"
    for (int i = 0; i < fileMime.aliases().size(); ++i) {
      if (fileMime.aliases().at(i).contains("video/")) {
        containsVideo = true;
        break;
      }
    }

    // if the aliases didn't contain video, we know for sure that the file is
    // not a video
    if (!containsVideo) {
      qDebug() << "warning:" << path
               << "Doesn't have a valid mime type for the player:"
               << fileMime.name() << fileMime.parentMimeTypes()
               << fileMime.aliases() << path;
      return;
    }
  }

  // add video to the list
  AVideo *newVideo = new AVideo(path);
  videos.append(newVideo);

  if (shouldAddVideo)
    store.addVideoToHistory(path);
  emit videoAdded(newVideo);

  // start playing the video
  _playlist->addMedia(*newVideo->getUrl());
}

void ThePlayer::videoSelectedFromRecents(AVideo *video) {
  QString path = video->getUrl()->toLocalFile();
  path = path.left(path.lastIndexOf("/"));

  bool old = setShouldAddVideo(false);
  loadVideoDirectory(path.toStdString());
  setShouldAddVideo(old);

  jumpTo(video);
}

void ThePlayer::setPlaybackMode(QMediaPlaylist::PlaybackMode mode) {
  playlist()->setPlaybackMode(mode);
}

void ThePlayer::addVideo(std::string path) {
  // call main add video function, casting the string to a qstring
  addVideo(QString::fromStdString(path));
}

// Accepted file formats = .mp4, .MOV, .wmv
void ThePlayer::openFile() {
  // Opens file explorer and only allows specific video player file types and
  // saves as a QString
  // Note: I just passed a random widget here to get this to work
  QString filename = QFileDialog::getOpenFileName(nullptr, tr("Open File"),
                                                  store.getOpenFileDirectory(),
                                                  SUPPORTED_EXTENSIONS);

  if (filename.isEmpty()) {
    QMessageBox::information(nullptr, tr("File"), "No path specified");
    return;
  }

  // check if the video is supported on the current platform
  if (!TheUtils::filenameIsValidVideo(filename)) {
    qDebug() << "warning: unsupported video format supplied" << Qt::endl;
    QMessageBox::information(nullptr, tr("Unsupported video"),
                             "The video supplied is in an unsupported video "
                             "format, please try a different file.");
    return;
  }

  // since the video is about to be added, we know that the directory that the
  // video was opened from is good to be saved for the next time the user adds
  // a file.
  QString videoDirectory = QFileInfo(filename).absoluteDir().absolutePath();

  // save the directory path in the store
  store.setOpenFileDirectory(videoDirectory);

  // add file
  addVideo(filename);
}

void ThePlayer::jumpTo(AVideo *video) {
  int index = 0;
  for (index = 0; index < videos.size(); index++) {
    auto vid = videos[index];
    if (vid->getVideoPath() == video->getVideoPath())
      break;
  }

  playlist()->setCurrentIndex(index);
  play();
}
