//    ______
//   /_  __/___  ____ ___  ___  ____
//    / / / __ \/ __ `__ \/ _ \/ __ \
//   / / / /_/ / / / / / /  __/ /_/ /
//  /_/  \____/_/ /_/ /_/\___/\____/
//              video for sports enthusiasts...
//
//

#include "the_window.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[]) {
  // let's just check that Qt is operational first
  qDebug() << "Qt version: " << QT_VERSION_STR << Qt::endl;
  int exitCode = 0;

  // restarts the application if the exit code is the restart code
  do {
    // create the Qt Application
    QApplication app(argc, argv);

    // create our window
    TheWindow window;

    // showtime!
    window.show();

    exitCode = app.exec();
  } while (exitCode == TheWindow::RESTART_EXIT_CODE);

  // wait for the app to terminate
  return exitCode;
}
