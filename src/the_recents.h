#ifndef THE_RECENTS_H
#define THE_RECENTS_H

#include "a_video.h"
#include <QFrame>
#include <QListWidget>
#include <QObject>
#include <QPushButton>

class DeleteButton : public QPushButton {
  Q_OBJECT
public:
  DeleteButton(QString text, QString video);
signals:
  void clicked(QString);

private slots:
  void btnClicked() { emit clicked(video); };

private:
  QString video;
};

class TheRecentsItem : public QListWidgetItem {
public:
  TheRecentsItem(AVideo *newVideoInfo, QListWidget *parent);
  AVideo *getVideoInfo() const { return videoInfo; }
  void setVideoInfo(AVideo *newVideoInfo) { videoInfo = newVideoInfo; }

  DeleteButton *getDeleteBtn() const { return deleteBtn; }

private:
  AVideo *videoInfo;
  DeleteButton *deleteBtn;
};

class TheRecents : public QFrame {
  Q_OBJECT
public:
  TheRecents();

private:
  const char debugPrefix[24] = "[the_recents]: ";

  void createWidgets();
  void initialiseStyleSheet();
  void initialiseSignalsAndSlots();

  QListWidget *list;

private slots:
  void videoSelected();
  void videoRemoved(QString);

public slots:
  /**
   * re-renders the list
   */
  void render();

signals:
  void onVideoSelected(AVideo *);
};

#endif // THE_RECENTS_H
