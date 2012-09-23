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

void ControlListenerImpl::onAxisListener(const KeyEvent &eventAxis)
{
  const int &time = eventAxis.time;
  const int &value = eventAxis.value;
  const int &number = eventAxis.number;

  StateMachineAccessor &StateMachineAccessor(StateMachineAccessor::getInstance());

  cout << "onAxisListener" << endl;

  if ((number == KeyEvent::X) && (value == KeyEvent::Min))
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
  }
}

void ControlListenerImpl::onButtonListener(const KeyEvent &eventButton)
{
  const int &time = eventButton.time;
  const int &value = eventButton.value;
  const int &number = eventButton.number;

  StateMachineAccessor &StateMachineAccessor(StateMachineAccessor::getInstance());

  cout << "key number: " << number << endl;

  if ((number == KeyEvent::Navigation) && (value == KeyEvent::Down))
  {
    StateMachineAccessor.pushEvent("HK_NAV");
  }
  else if ((number == KeyEvent::Media) && (value == KeyEvent::Down))
  {
    StateMachineAccessor.pushEvent("HK_MEDIA");
  }
  else if ((number == KeyEvent::One) && (value == KeyEvent::Down))
  {
    StateMachineAccessor.pushEvent("oispkey,One,down");
  }
  else if ((number == KeyEvent::Two) && (value == KeyEvent::Down))
  {
    StateMachineAccessor.pushEvent("oispkey,Two,down");
  }
  else if ((number == KeyEvent::Start) && (value == KeyEvent::Down))
  {
    StateMachineAccessor.pushEvent("oispkey,Start,down");
  }
  else if ((number == KeyEvent::Menu) && (value == KeyEvent::Down))
  {
    StateMachineAccessor.pushEvent("oispkey,Menu,down");
  }
}
