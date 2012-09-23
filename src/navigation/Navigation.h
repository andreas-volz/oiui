#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <OICFNavigation/OICFNavigation.h>
//#include <OICFNavigation/OICFNavigation.h>

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

  void smCommandNavigationRoute1();
  void smCommandNavigationRoute2();
  void smCommandNavigationRoute3();

  OICFNavigation &mOICFNavigation;
};

#endif // NAVIGATION_H
