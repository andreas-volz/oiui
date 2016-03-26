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

using namespace std;

MediaListenerImpl::MediaListenerImpl(DBus::Connection &connection) :
  OICFMediaListener(connection),
  mListWidget(NULL)
{
  StateMachineAccessor &stateMachineAccessor = StateMachineAccessor::getInstance();

  mListWidget = stateMachineAccessor.getWidget("MediaMainView", "List01");

  mListWidget->setWidgetRender(mediaRenderer);
}

void MediaListenerImpl::setMedia(Media *media)
{
  mediaRenderer.setMedia(media);
}

void MediaListenerImpl::getWindowListResult(const LineVector &titleList, const int32_t &start, const int32_t &end, const int32_t &size)
{
  cout << "receive MediaListenerImpl::getWindowListResult" << endl;

  mTitleList = titleList;
  
  StateMachineAccessor &stateMachineAccessor = StateMachineAccessor::getInstance();
  Variable *av = stateMachineAccessor.getVariable("MediaList");
  assert(av);

  VoidPtr *vp = static_cast<VoidPtr*>(av);
  vp->change(&mTitleList);
  
  mListWidget->setProperty("list", *vp);
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
