#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

/* local */
#include "MediaListenerImpl.h"

/* STD */
#include <iostream>
#include <signal.h>
#include <cassert>
#include <cmath>

/* stateval */
#include <stateval/stateval.h>

using namespace std;

MediaListenerImpl::MediaListenerImpl(DBus::Connection &connection) :
  OICFMediaListener(connection)
{
}

void MediaListenerImpl::getWindowListResult(const LineVector &titleList, const int32_t &start, const int32_t &end, const int32_t &size)
{
  cout << "receive MediaListenerImpl::getWindowListResult" << endl;

  StateMachineAccessor &stateMachineAccessor = StateMachineAccessor::getInstance();
  AbstractVariable *av = stateMachineAccessor.getVariable("ListExample");
  assert(av);
  List *li = static_cast <List*>(av);
  li->clear();

  for (LineVector::const_iterator vs_it = titleList.begin();
       vs_it != titleList.end();
       ++vs_it)
  {
    const Line &l = *vs_it;

    cout << "ID: " << l.id << " Name: " << l.name << endl;
    String *st = new String(l.name);
    li->pushBack(st);
  }

  //mediaScreen->setActiveList (titleList);
}

void MediaListenerImpl::updateSelectedPath(const LineVector &path)
{
  //mediaScreen->setCurrentPath (path);
}

void MediaListenerImpl::updateSelectedTitle(const Line &title)
{
  //mediaScreen->updateSelectedTitle (title);
}

void MediaListenerImpl::updatePlayPosition(const int64_t &pos, const int64_t &duration)
{
  //mediaScreen->updatePlayPosition (pos, duration);
}

void MediaListenerImpl::updateDeviceList(const DeviceEnum &enumtest)
{
  // TODO: implement me!
}