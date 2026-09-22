#ifndef THE_HELP_H
#define THE_HELP_H

#include <QMainWindow>
#include <QVBoxLayout>

class TheHelp : public QMainWindow {
public:
  TheHelp();

private:
  QVBoxLayout *helpLayout = new QVBoxLayout();

  void createHotkeyHelp();
  void createGeneralUsage();
};

#endif // THE_HELP_H
