#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

/* STD */
#include <map>
#include <string>

/* SIGC */
#include <sigc++/sigc++.h>

typedef sigc::signal<void> EventHandlerSignal;
typedef sigc::slot<void> EventHandlerSlot;

class EventHandler
{
public:
  static EventHandler &instance();

  void init();

  // TODO: private or protected?
  void deliverEvent(int event);

  void connect(const std::string &event, const EventHandlerSlot &slot);
  void disconnect(int event);
  void disconnectAll();

private:
  EventHandler() {}
  EventHandler(const EventHandler &);
  virtual ~EventHandler();

  std::multimap <int, EventHandlerSignal *> mSignalList;
};

#endif // EVENT_HANDLER_H
