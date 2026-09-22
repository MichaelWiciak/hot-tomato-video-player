#include "the_video.h"
#include "the_utils.h"
#include <QDebug>
#include <QKeyEvent>
#include <QMimeData>

TheVideo::TheVideo() {
  // we allow dropping files
  setAcceptDrops(true);

  // sets the focus for controls to work
  setFocusPolicy(Qt::StrongFocus);
}

void TheVideo::keyPressEvent(QKeyEvent *event) {
  auto key = event->key();
  auto modifiers = event->modifiers();

  // map the corresponding keys to the correct signals/actions

  if (key == Qt::Key_Escape) {
    if (TheUtils::isLinux())
      return;
    setFullScreen(false);
    setFocus();
    return;
  }

  if (key == Qt::Key_Left) {
    qDebug() << debugPrefix << "rewind";
    emit rewind();
    return;
  }

  if (key == Qt::Key_Right) {
    qDebug() << debugPrefix << "fastforward";
    emit fastforward();
    return;
  }

  if (key == Qt::Key_Space) {
    qDebug() << debugPrefix << "play/pause";
    emit togglePlayPause();
    return;
  }

  if (key == Qt::Key_Up) {
    qDebug() << debugPrefix << "vol up";
    emit volumeUp();
    return;
  }

  if (key == Qt::Key_Down) {
    qDebug() << debugPrefix << "vol down";
    emit volumeDown();
    return;
  }

  if (key == Qt::Key_M) {
    qDebug() << debugPrefix << "mute";
    emit mute();
    return;
  }

  if (key == Qt::Key_F) {
    if (TheUtils::isLinux())
      return;
    emit fullscreen();
    setFocus();
    return;
  }

  if (key == Qt::Key_N && modifiers == Qt::ShiftModifier) {
    qDebug() << debugPrefix << "next";
    emit next();
    return;
  }

  if (key == Qt::Key_P && modifiers == Qt::ShiftModifier) {
    qDebug() << debugPrefix << "prev";
    emit previous();
    return;
  }

  qDebug() << debugPrefix << "Unsupported key pressed: " << key << "("
           << event->text() << ")";
}

void TheVideo::dragEnterEvent(QDragEnterEvent *event) {
  if (!event->mimeData()->hasUrls())
    return;

  // get all files that are being dragged
  auto urls = event->mimeData()->urls();
  for (auto url : urls) {
    // for each filename, we check if its valid
    auto filename = url.fileName();
    if (TheUtils::filenameIsValidVideo(filename)) {
      // tells the OS it is droppable
      event->acceptProposedAction();
    }
  }
}

void TheVideo::dropEvent(QDropEvent *event) {
  if (event->source() == this)
    return;

  event->acceptProposedAction();

  // get all files that are being dropped
  auto urls = event->mimeData()->urls();
  for (auto url : urls) {
    // check again if its valid
    if (TheUtils::filenameIsValidVideo(url.fileName())) {
      // adds the video
      emit onVideoAdded(url.path());
    }
  }
}
