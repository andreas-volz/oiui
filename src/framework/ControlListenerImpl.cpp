#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "ControlListenerImpl.h"

/* STD */
#include <iostream>
#include <pthread.h>
#include <signal.h>
#include <cassert>

/* stateval */
#include <stateval/stateval.h>

using namespace std;

ControlListenerImpl::ControlListenerImpl(DBus::Connection &connection)
  : OICFControlListener(connection)
{
}

void ControlListenerImpl::onAxisListener(const AxisEvent &event)
{
  const int &time = event.time;
  const int &value = event.value;
  const int &number = event.number;

  StateMachineAccessor &StateMachineAccessor(StateMachineAccessor::getInstance());

  cout << "onAxisListener" << endl;

  /*if ((number == KeyEvent::X) && (value == KeyEvent::Min))
  {
    StateMachineAccessor.pushEvent("oispaxis,X,min");
  }
  else if ((number == KeyEvent::X) && (value == KeyEvent::Max))
  {
    StateMachineAccessor.pushEvent("oispaxis,X,max");
  }
  else if ((number == KeyEvent::Y) && (value == KeyEvent::Min))
  {
    StateMachineAccessor.pushEvent("oispaxis,Y,min");
  }
  else if ((number == KeyEvent::Y) && (value == KeyEvent::Max))
  {
    StateMachineAccessor.pushEvent("oispaxis,Y,max");
  }*/
}

void ControlListenerImpl::onButtonListener(const ButtonEvent &event)
{
  const int &time = event.time;
  const int &value = event.value;
  const int &number = event.number;

  StateMachineAccessor &StateMachineAccessor(StateMachineAccessor::getInstance());

  cout << "key number: " << number << endl;

  if ((number == ButtonEvent::Navigation) && (value == ButtonEvent::Down))
  {
    StateMachineAccessor.pushEvent("oicf,button,Navigation,down");
  }
  else if ((number == ButtonEvent::Media) && (value == ButtonEvent::Down))
  {
    StateMachineAccessor.pushEvent("oicf,button,Media,down");
  }
  else if ((number == ButtonEvent::Menu) && (value == ButtonEvent::Down))
  {
    StateMachineAccessor.pushEvent("oicf,button,Menu,down");
  }
  else if ((number == ButtonEvent::Phone) && (value == ButtonEvent::Down))
  {
    StateMachineAccessor.pushEvent("oicf,button,Phone,down");
  }
  else if ((number == ButtonEvent::Return) && (value == ButtonEvent::Down))
  {
    StateMachineAccessor.pushEvent("oicf,button,Return,down");
  }
  else if ((number == ButtonEvent::DDS) && (value == ButtonEvent::Down))
  {
    StateMachineAccessor.pushEvent("oicf,button,DDS,down");
  }
  else if ((number == ButtonEvent::Volume) && (value == ButtonEvent::Down))
  {
    StateMachineAccessor.pushEvent("oicf,button,Volume,down");
  }
  
}

void ControlListenerImpl::onRotaryListener(const RotaryEvent &event)
{

}
