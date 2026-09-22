#include "the_recents.h"
#include "the_store.h"
#include "the_utils.h"
#include <QDebug>
#include <QFile>
#include <QHBoxLayout>
#include <QLabel>
#include <QList>
#include <QListWidget>
#include <QPushButton>
#include <QSize>
#include <QUrl>
#include <QVBoxLayout>

TheRecents::TheRecents() {
  setObjectName("recentsPanel");
  setHidden(true); // hide by default
  createWidgets();
  initialiseStyleSheet();
  initialiseSignalsAndSlots();
}

void TheRecents::createWidgets() {

  QVBoxLayout *layout = new QVBoxLayout;
  setLayout(layout);

  QLabel *titleLabel = new QLabel("Recents");
  titleLabel->setObjectName("recentsPanel__title");
  layout->addWidget(titleLabel);

  list = new QListWidget;
  layout->addWidget(list);
  list->setIconSize(QSize(50, 50));

  render();
}

void TheRecents::initialiseStyleSheet() {
  // set styles
  QFile *styleSheet = new QFile(":/styles/the_recents.qss");
  styleSheet->open(QFile::ReadOnly);
  setStyleSheet(styleSheet->readAll());
  delete styleSheet;
}

void TheRecents::initialiseSignalsAndSlots() {
  QObject::connect(list, SIGNAL(itemSelectionChanged()), this,
                   SLOT(videoSelected()));
}

void TheRecents::render() {
  list->clear();
  const QList<QString> videos = store.getHistory();

  for (const QString &video : videos) {
    auto item = new TheRecentsItem(new AVideo(video), list);
    QString thumb = TheUtils::getIconPathFromVideoPath(video);

    item->setIcon(QIcon(thumb));
    QObject::connect(item->getDeleteBtn(), SIGNAL(clicked(QString)), this,
                     SLOT(videoRemoved(QString)));
  }
}

void TheRecents::videoSelected() {
  qDebug() << debugPrefix << "new video selected";
  QList<QListWidgetItem *> test = list->selectedItems();

  if (test.size() == 0)
    return;

  auto item = dynamic_cast<TheRecentsItem *>(test[0]);

  emit onVideoSelected(item->getVideoInfo());
}

void TheRecents::videoRemoved(QString video) {
  qDebug() << debugPrefix << "removing video from recents" << video;
  store.removeVideoFromHistory(video);
  render();
}

TheRecentsItem::TheRecentsItem(AVideo *newVideoInfo, QListWidget *parent) {
  setVideoInfo(newVideoInfo);
  QFrame *wrapper = new QFrame;
  wrapper->setObjectName("recents__item");

  const QUrl *url = newVideoInfo->getUrl();
  QLabel *label = new QLabel(url->fileName());
  deleteBtn = new DeleteButton("", url->toLocalFile());
  //  delete url;
  QHBoxLayout *layout = new QHBoxLayout();
  layout->addWidget(label, 1);
  layout->addWidget(deleteBtn);

  wrapper->setLayout(layout);

  this->setSizeHint(wrapper->sizeHint());
  parent->addItem(this);
  parent->setItemWidget(this, wrapper);
}

DeleteButton::DeleteButton(QString text, QString video) : QPushButton(text) {
  this->video = video;
  QObject::connect(this, SIGNAL(clicked()), this, SLOT(btnClicked()));
  setObjectName("recents__removeVideoBtn");
}
