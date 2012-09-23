#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

/* Project */
#include "EventHandler.h"
#include <stateval/StateMachineAccessor.h>

/* STD */
#include <iostream>

using namespace std;

EventHandler &EventHandler::instance()
{
  static EventHandler _instance;
  return _instance;
}

EventHandler::~EventHandler()
{
}

void EventHandler::init()
{

}

void EventHandler::deliverEvent(int event)
{
  // emit event signals
  multimap <int, EventHandlerSignal *>::iterator findResult = mSignalList.find(event);
  multimap <int, EventHandlerSignal *>::iterator lastElement = mSignalList.upper_bound(event);

  if (findResult != mSignalList.end())
  {
    // emit also multible signals...
    for (; findResult != lastElement; ++findResult)
    {
      cout << "call event '" << event << "' to app" << endl;
      EventHandlerSignal *signal = (*findResult).second;
      signal->emit();
    }
  }
}

void EventHandler::connect(const std::string &event, const EventHandlerSlot &slot)
{
  StateMachineAccessor &StateMachineAccessor(StateMachineAccessor::getInstance());
  int ievent = StateMachineAccessor.findMapingEvent(event);

  EventHandlerSignal *signal = new EventHandlerSignal();
  mSignalList.insert(pair <int, EventHandlerSignal *> (ievent, signal));

  signal->connect(slot);
}

void EventHandler::disconnect(int event)
{
  // delete event signals
  multimap <int, EventHandlerSignal *>::iterator findResult = mSignalList.find(event);
  multimap <int, EventHandlerSignal *>::iterator lastElement = mSignalList.upper_bound(event);

  if (findResult != mSignalList.end())
  {
    // delete all connected handlers
    for (; findResult != lastElement; ++findResult)
    {
      EventHandlerSignal *signal = (*findResult).second;
      delete signal;
    }
  }
}

void EventHandler::disconnectAll()
{
  for (std::multimap <int, EventHandlerSignal *>::iterator s_it = mSignalList.begin();
       s_it != mSignalList.end();
       ++s_it)
  {
    int event = (*s_it).first;
    EventHandlerSignal *signal = (*s_it).second;

    delete signal;
  }
}
