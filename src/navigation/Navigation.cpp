#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

/* Project */
#include "Navigation.h"
#include "../framework/EventHandler.h"

/* STD */
#include <iostream>

using namespace std;

Navigation::Navigation(OICFNavigation &oicfNavigation) :
  mOICFNavigation(oicfNavigation)
{
  EventHandler &eventHandler(EventHandler::instance());
  eventHandler.connect("MAP_ZOOM_IN", sigc::mem_fun(this, &Navigation::smCommandZoomIn));
  eventHandler.connect("MAP_ZOOM_OUT", sigc::mem_fun(this, &Navigation::smCommandZoomOut));
  eventHandler.connect("MAP_SCROLL_LEFT", sigc::mem_fun(this, &Navigation::smCommandScrollLeft));
  eventHandler.connect("MAP_SCROLL_RIGHT", sigc::mem_fun(this, &Navigation::smCommandScrollRight));
  eventHandler.connect("MAP_SCROLL_TOP", sigc::mem_fun(this, &Navigation::smCommandScrollTop));
  eventHandler.connect("MAP_SCROLL_BOTTOM", sigc::mem_fun(this, &Navigation::smCommandScrollBottom));
  eventHandler.connect("MAP_JUMP_CURSOR", sigc::mem_fun(this, &Navigation::smCommandMapJumpCursor));
  eventHandler.connect("NAVIGATION_ROUTE_1", sigc::mem_fun(this, &Navigation::smCommandNavigationRoute1));
  eventHandler.connect("NAVIGATION_ROUTE_2", sigc::mem_fun(this, &Navigation::smCommandNavigationRoute2));
  eventHandler.connect("NAVIGATION_ROUTE_3", sigc::mem_fun(this, &Navigation::smCommandNavigationRoute3));
}

void Navigation::smCommandZoomIn()
{
  cout << "smCommandZoomIn" << endl;
  mOICFNavigation.zoomIn();
}

void Navigation::smCommandZoomOut()
{
  cout << "smCommandZoomOut" << endl;
  mOICFNavigation.zoomOut();
}

void Navigation::smCommandScrollLeft()
{
  mOICFNavigation.moveMapSteps(West, 0);
}

void Navigation::smCommandScrollRight()
{
  mOICFNavigation.moveMapSteps(East, 0);
}

void Navigation::smCommandScrollTop()
{
  mOICFNavigation.moveMapSteps(North, 0);
}

void Navigation::smCommandScrollBottom()
{
  mOICFNavigation.moveMapSteps(South, 0);
}

void Navigation::smCommandMapJumpCursor()
{
  mOICFNavigation.jumpToPointer();
}

void Navigation::smCommandNavigationRoute1()
{
  mOICFNavigation.generic1("Langen (Hessen)", "Robert-Bosch-Straße", "");
}

void Navigation::smCommandNavigationRoute2()
{
  mOICFNavigation.generic1("Brachttal", "Gärtnerweg", "");
}

void Navigation::smCommandNavigationRoute3()
{
  mOICFNavigation.generic1("Erlangen", "Frauenweiherstraße", "");
}
