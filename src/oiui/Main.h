#ifndef MAIN_H
#define MAIN_H

/* stateval */
#define HAVE_EFL // needed for EFL support
#include <stateval/stateval.h>
#include <stateval/private/Thread.h>

/* DBus-cxx */
#include <dbus-c++/dbus.h>

/* Glib */
#include <glibmm.h>

class Main
{
public:
  Main(int argc, const char **argv);

private:
  void DBusMainLoop();

  void quit();

  void smSignals(int event);
  static void smHandler(const void *data, void *buffer, unsigned int nbyte);

  DBus::BusDispatcher dispatcher;
  DBus::Pipe *mSMToDBusPipe;

  Threading::Condition condSMInit;
  Threading::Mutex mutexSMInit;
};

#endif // MAIN_H
