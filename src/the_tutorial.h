#ifndef THE_TUTORIAL_H
#define THE_TUTORIAL_H

#include <QFrame>

class TheTutorial : public QFrame {
  Q_OBJECT
public:
  TheTutorial(bool status);
private slots:
  /**
   * @brief hides the tutorial banner
   */
  void hideTutorial();

  /**
   * @brief shows help window
   */
  void helpWindow();

  /**
   * @brief initialises style sheet
   */
  void initialiseStyleSheet();
};

#endif // THE_TUTORIAL_H
