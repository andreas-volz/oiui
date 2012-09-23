#ifndef NAVIGATIONLISTENERIMPL_H
#define NAVIGATIONLISTENERIMPL_H

#include <dbus-c++/dbus.h>
#include <OICFNavigation/OICFNavigationListener.h>

class NavigationListenerImpl : public OICFNavigationListener
{
public:

  NavigationListenerImpl(DBus::Connection &connection);

private:
  void updateGPSPositionWGS84(const CoordWGS84 &pos);

  void searchCityResult(const std::vector< std::string >& cities);
  void getNextValidCharactersResult(const std::string& validChars);


};

#endif // MEDIALISTENERIMPL_H
