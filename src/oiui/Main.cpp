#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

/* Project */
#include "Main.h"

/* Project Framework */
#include "../framework/EventHandler.h"
#include "../framework/searchFile.h"

/* HMI Applications */
#include "../navigation/Navigation.h"
#include "../media/Media.h"

/* HMI Application Listeners */
#include "../framework/ControlListenerImpl.h"
#include "../media/MediaListenerImpl.h"
#include "../navigation/NavigationListenerImpl.h"

/* log4cxx */
#ifdef HAVE_LOG4CXX
#include "log4cxx/logger.h"
#include "log4cxx/basicconfigurator.h"
#include "log4cxx/propertyconfigurator.h"
#include "log4cxx/helpers/exception.h"
#endif // HAVE_LOG4CXX

#ifdef HAVE_LOG4CXX
using namespace log4cxx;
using namespace log4cxx::helpers;
#endif // HAVE_LOG4CXX

Main::Main(int argc, const char **argv) :
  mSMToDBusPipe(NULL)
{
  // initialize Glib thread system
  if (!Glib::thread_supported()) Glib::thread_init();

  Glib::Thread *thread = Glib::Thread::create(sigc::mem_fun(this, &Main::DBusMainLoop), false);

#ifdef HAVE_LOG4CXX
  //BasicConfigurator::configure ();
  cout << "searchDataDir():" << searchDataDir() << endl;
  PropertyConfigurator::configure(searchDataDir() + "/logging.prop");
#endif // HAVE_LOG4CXX

  // deactivate screensaver function
  //Ecorexx::XWindow::setDPMSEnabled (false);

  // TODO: only by variable...
  //Ecorexx::XWindow *xwin = mWindow.getXWindow ();
  //xwin->setNetWMWindowType (Ecorexx::XWindow::Menu);

  cout << "OISPInterface server started..." << endl;

  // *** STATE MACHINE ***
  cout << "data: " << searchDataDir() << endl;

  StateMachineAccessor &stateMachineAccessor(StateMachineAccessor::getInstance());
  stateMachineAccessor.load("smxml", searchDataDir() + "/sm/oiui.smxml");

  stateMachineAccessor.connect(sigc::mem_fun(this, &Main::smSignals));

  // hmmm? should run if statemachine is complete up??
  condSMInit.signal();
  
  stateMachineAccessor.run();

  StateMachineAccessor::destroy();
}

void Main::DBusMainLoop()
{
  cout << "+DBusMainLoop ()" << endl;
  DBus::_init_threading();

  DBus::default_dispatcher = &dispatcher;

  // increase DBus-C++ frequency
  new DBus::DefaultTimeout(100, false, &dispatcher);

  DBus::Connection conn = DBus::Connection::SessionBus();

  mSMToDBusPipe = dispatcher.add_pipe(Main::smHandler, NULL);

  EventHandler &eventHandler(EventHandler::instance());
  eventHandler.init();

  // create OICF listeners
  ControlListenerImpl controlListener(conn);
  MediaListenerImpl mediaListener(conn);
  NavigationListenerImpl mapViewerListener (conn);

  // create OICF callers
  OICFNavigation oicfNavigation(conn);
  OICFMedia oicfMedia(conn);

  // wait for starting all the statemachine stuff in the ecore thread...
  mutexSMInit.lock();
  condSMInit.wait(mutexSMInit);
  mutexSMInit.unlock();

  Navigation navigation(oicfNavigation);
  Media media(oicfMedia);

  dispatcher.enter();

  dispatcher.del_pipe(mSMToDBusPipe);

  cout << "-DBusMainLoop ()" << endl;
}

void Main::quit()
{
  cout << "clean exit" << endl;
}

// this function runs in the SM thread
void Main::smSignals(int event)
{
  cout << "smSignals (int event): " << event << endl;

  mSMToDBusPipe->write(static_cast <const void *>(&event), sizeof(event));
}

// this function runs in the DBus thread and is dispatched with data from SM thread
void Main::smHandler(const void *data, void *buffer, unsigned int nbyte)
{
  EventHandler &eventHandler(EventHandler::instance());

  int *event = static_cast <int *>(buffer);
  cout << "dispatched smSignals (int event): " << *event << endl;

  eventHandler.deliverEvent(*event);
}

/****************************/
int main(int argc, const char **argv)
{
  Main mainObject(argc, argv);

  return 0;
}
