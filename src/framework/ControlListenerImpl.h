#ifndef CONTROLLISTENERIMPL_H
#define CONTROLLISTENERIMPL_H

#include <dbus-c++/dbus.h>
#include <OICFControl/OICFControlListener.h>

class ControlListenerImpl : public OICFControlListener
{
public:

  ControlListenerImpl(DBus::Connection &connection);

  void onAxisListener(const KeyEvent &eventAxis);
  void onButtonListener(const KeyEvent &eventButton);

private:

};

#endif // CONTROLLISTENERIMPL_H
