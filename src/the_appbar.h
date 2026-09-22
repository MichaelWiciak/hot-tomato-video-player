#ifndef THE_APPBAR_H
#define THE_APPBAR_H

#include <QFileDialog>
#include <QFrame>
#include <QLabel>
#include <QMessageBox>
#include <QObject>
#include <QPushButton>
#include <QWidget>

class TheAppBar : public QFrame {
  Q_OBJECT
public:
  TheAppBar();

  bool getSettingsIsOpen() { return settingsIsOpen; }
  bool getRecentsIsOpen() { return recentsIsOpen; }

private:
  void createWidgets();
  void initialiseSignalsAndSlots();
  void initialiseStyleSheet();

  void updateToggleSettingsBtn();
  void updateToggleRecentsBtn();
  void updateAddFileBtn();
  void updateHelpBtn();

  bool settingsIsOpen = false;
  bool recentsIsOpen = false;

  QLabel *logo;
  QPushButton *addFileBtn;
  QPushButton *helpBtn;
  QPushButton *toggleSettingsBtn;
  QPushButton *toggleRecentsBtn;

private slots:
  void toggleSettingsBtnClicked();
  void toggleRecentsBtnClicked();

signals:
  void settingsIsOpenChanged(bool);
  void recentsIsOpenChanged(bool);
  void addFileBtnClicked();
  void helpBtnClicked();
};

#endif // THE_APPBAR_H
