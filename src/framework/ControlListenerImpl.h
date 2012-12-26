#ifndef CONTROLLISTENERIMPL_H
#define CONTROLLISTENERIMPL_H

#include <dbus-c++/dbus.h>
#include <OICFControl/OICFControlListener.h>

class ControlListenerImpl : public OICFControlListener
{
public:

  ControlListenerImpl(DBus::Connection &connection);

  void onAxisListener(const AxisEvent &event);
  void onButtonListener(const ButtonEvent &event);
  void onRotaryListener(const RotaryEvent &event);

private:

};

#endif // CONTROLLISTENERIMPL_H
