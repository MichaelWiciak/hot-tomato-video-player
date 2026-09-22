#ifndef THE_SETTINGS_H
#define THE_SETTINGS_H

#include <QComboBox>
#include <QFrame>
#include <QLineEdit>
#include <QObject>
#include <QPushButton>

class TheSettings : public QFrame {
  Q_OBJECT
public:
  TheSettings();

private:
  /**
   * @brief creates all needed widgets
   */
  void createWidgets();

  /**
   * @brief initialises all Signals And Slots
   */
  void initialiseSignalsAndSlots();

  /**
   * @brief initialises the Style Sheet
   */
  void initialiseStyleSheet();

  /**
   * @brief line edit for directory (read only)
   */
  QLineEdit *directoryInput;

  /**
   * @brief push button for opening the directory picker
   */
  QPushButton *browseDirectoryBtn;

  /**
   * @brief for selecting themes
   */
  QComboBox *themeSelect;

  /**
   * @brief for changing button size
   */
  QComboBox *buttonSizeSelect;

  /**
   * @brief for editing the time skip amount (in seconds)
   */
  QLineEdit *timeSkipInput;

private slots:
  void timeSkipInputChanged(QString);
  void browseDirectoryBtnClicked();
  void themeChanged(QString);
  void buttonSizeChanged(QString);

signals:
  void timeSkipChanged();
  void restartApp();
};

#endif // THE_SETTINGS_H
