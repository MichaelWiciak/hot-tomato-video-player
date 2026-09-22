#ifndef THE_WINDOW_H
#define THE_WINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QObject>

class TheWindow : public QMainWindow {
  Q_OBJECT
public:
  TheWindow();
  static const int RESTART_EXIT_CODE = 1234;

private:
  const char debugPrefix[24] = "[the_window]: ";
private slots:
  /**
   * exits the app with a restart code to restart the app
   */
  void restartApp();
};

#endif // THE_WINDOW_H
