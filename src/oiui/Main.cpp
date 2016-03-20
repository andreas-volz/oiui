#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

/* Project */
#include "Main.h"

/* Project Framework */
#include "../framework/EventHandler.h"
#include "../framework/searchFile.h"
#include "../framework/Logger.h"

/* HMI Applications */
#include "../navigation/Navigation.h"
#include "../media/Media.h"

/* HMI Application Listeners */
#include "../framework/ControlListenerImpl.h"
#include "../media/MediaListenerImpl.h"
#include "../navigation/NavigationListenerImpl.h"

Logger logger("oiui.Main");

using namespace std;

Main::Main(int argc, const char **argv) :
  mSMToDBusPipe(NULL)
{
  // initialize Glib thread system
  if (!Glib::thread_supported()) Glib::thread_init();


  Glib::Thread *thread = Glib::Thread::create(sigc::mem_fun(this, &Main::DBusMainLoop), false);
  
#ifdef HAVE_LOG4CXX
  log4cxx::PropertyConfigurator::configure(searchDataFile("logging.prop"));
#endif // HAVE_LOG4CXX

  // deactivate screensaver function
  //Ecorexx::XWindow::setDPMSEnabled (false);

  // TODO: only by variable...
  //Ecorexx::XWindow *xwin = mWindow.getXWindow ();
  //xwin->setNetWMWindowType (Ecorexx::XWindow::Menu);

  LOG4CXX_INFO(logger, "OISPInterface server started...");
  
  // *** STATE MACHINE ***
  StateMachineAccessor &stateMachineAccessor(StateMachineAccessor::getInstance());
  
  const std::string &dataLoadDir = searchDataDir("sm/oiui.smxml");
  LOG4CXX_INFO(logger, "dataLoadDir: " << dataLoadDir);
  stateMachineAccessor.setDataLoadDir(dataLoadDir);

  LOG4CXX_INFO(logger, "smxml: " + searchDataFile("sm/oiui.smxml"));
  stateMachineAccessor.load("smxml", searchDataFile("sm/oiui.smxml"));

  stateMachineAccessor.connect(sigc::mem_fun(this, &Main::smSignals));

  // if I activate this then DBUS isn't working
  //Glib::Thread *thread = Glib::Thread::create(sigc::mem_fun(this, &Main::DBusMainLoop), false);
  
  // signal the DBusMainLoop thread to run
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

  // wait for starting all the statemachine stuff in the ecore thread...
  mutexSMInit.lock();
  condSMInit.wait(mutexSMInit);
  mutexSMInit.unlock();
  
  // create OICF listeners
  ControlListenerImpl controlListener(conn);
  MediaListenerImpl mediaListener(conn);
  NavigationListenerImpl mapViewerListener (conn);

  // create OICF callers
  OICFNavigation oicfNavigation(conn);
  OICFMedia oicfMedia(conn);

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
