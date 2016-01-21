#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "NavigationListenerImpl.h"
#include <iostream>
#include <pthread.h>
#include <signal.h>
#include <cassert>
#include <cmath>

#include "../framework/util.h"

/* stateval */
#include <stateval/stateval.h>

using namespace std;

NavigationListenerImpl::NavigationListenerImpl(DBus::Connection &connection) :
  OICFNavigationListener(connection)
{

}

void NavigationListenerImpl::updateGPSPositionWGS84(const CoordWGS84 &pos)
{
  cerr << "updateGPSPositionWGS84" << endl;

  StateMachineAccessor &stateMachineAccessor = StateMachineAccessor::getInstance();
  Variable *av = stateMachineAccessor.getVariable("LatitudeValue");
  assert(av);
  String *latitudeValue = static_cast <String*>(av);
  latitudeValue->change (toStringWide (pos.latitude, 4));

  Variable *av2 = stateMachineAccessor.getVariable("LongitudeValue");
  assert(av2);
  String *longitudeValue = static_cast <String*>(av2);
  longitudeValue->change (toStringWide (pos.longitude, 4));

  Variable *av3 = stateMachineAccessor.getVariable("SpeedValue");
  assert(av3);
  String *speedValue = static_cast <String*>(av3);
  string str (toStringWide (pos.speed * 1000.0 / 60.0, 4));
  speedValue->change (str + " km/h");

  Variable *av4 = stateMachineAccessor.getVariable("HeadingValue");
  assert(av4);
  String *headingValue = static_cast <String*>(av4);
  headingValue->change (toStringWide (pos.track, 4) + " °");

  stateMachineAccessor.pushEvent (0); // UPDATE_VIEW.TODO: define constant?
  // FIXME: an update forces all screens to update: uptimisation needed!!!
}

void NavigationListenerImpl::searchCityResult(const std::vector< std::string >& cities)
{

}

void NavigationListenerImpl::getNextValidCharactersResult(const std::string& validChars)
{

}
