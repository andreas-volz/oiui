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
  
  if ((number == AxisEvent::X) && (value == AxisEvent::Min))
  {
    StateMachineAccessor.pushEvent("oicf,axis,X,min");
  }
  else if ((number == AxisEvent::X) && (value == AxisEvent::Max))
  {
    StateMachineAccessor.pushEvent("oicf,axis,X,max");
  }
  else if ((number == AxisEvent::Y) && (value == AxisEvent::Min))
  {
    StateMachineAccessor.pushEvent("oicf,axis,Y,min");
  }
  else if ((number == AxisEvent::Y) && (value == AxisEvent::Max))
  {
    StateMachineAccessor.pushEvent("oicf,axis,Y,max");
  }
}

void ControlListenerImpl::onButtonListener(const ButtonEvent &event)
{
  const int &time = event.time;
  const int &value = event.value;
  const int &number = event.number;

  StateMachineAccessor &StateMachineAccessor(StateMachineAccessor::getInstance());

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
  const int &time = event.time;
  const int &value = event.value;
  const int &number = event.number;

  StateMachineAccessor &StateMachineAccessor(StateMachineAccessor::getInstance());

  if ((number == RotaryEvent::DDS) && (value == RotaryEvent::Left))
  {
    StateMachineAccessor.pushEvent("oicf,rotary,DDS,left");
  }
  else if ((number == RotaryEvent::DDS) && (value == RotaryEvent::Right))
  {
    StateMachineAccessor.pushEvent("oicf,rotary,DDS,right");
  }

}
