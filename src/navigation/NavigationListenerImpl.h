#ifndef NAVIGATIONLISTENERIMPL_H
#define NAVIGATIONLISTENERIMPL_H

#include <dbus-c++/dbus.h>
#include <OICFNavigation/OICFNavigationListener.h>

/* framework */
#include "../framework/Logger.h"

class NavigationListenerImpl : public OICFNavigationListener
{
public:

  NavigationListenerImpl(DBus::Connection &connection);

private:
  void updateGPSPositionWGS84(const CoordWGS84 &pos);

  void searchCityResult(const std::vector< std::string >& cities);
  void getNextValidCharactersResult(const std::string& validChars);

  Logger mLogger;
};

#endif // MEDIALISTENERIMPL_H
