#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <OICFNavigation/OICFNavigation.h>

/* framework */
#include "../framework/Logger.h"

class Navigation
{
public:
  Navigation(OICFNavigation &oicfNavigation);

private:

  // TODO: move to OICF!!
  enum PanDirection
  {
    North,
    East,
    West,
    South
  };

  void smCommandZoomIn();
  void smCommandZoomOut();

  void smCommandScrollLeft();
  void smCommandScrollRight();
  void smCommandScrollTop();
  void smCommandScrollBottom();

  void smCommandMapJumpCursor();

  void smCommandActivateLastDestination();

  void smCommandNavigationRoute1();
  void smCommandNavigationRoute2();
  void smCommandNavigationRoute3();

  Logger mLogger;
  OICFNavigation &mOICFNavigation;
};

#endif // NAVIGATION_H
