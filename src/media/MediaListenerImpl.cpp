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
  mLogger("oiui.Media.MediaListenerImpl"),
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
  LOG4CXX_TRACE(mLogger, "getWindowListResult");
  
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
  LOG4CXX_TRACE(mLogger, "updateSelectedTitle() name: " << title.name << " type: " << title.type << " id: " << title.id);
}

void MediaListenerImpl::updatePlayPosition(const int64_t &pos, const int64_t &duration)
{
  int p_sec = (int) pos % 60;
  int p_min = pos / 60;
  int p_hour = pos / 3600;
  
  int d_sec = (int) duration % 60;
  int d_min = duration / 60;
  int d_hour = duration / 3600;
  
  LOG4CXX_INFO(mLogger, "duration = " << d_hour << "h " << d_min << "m " << d_sec << "s");
  LOG4CXX_INFO(mLogger, "position = " << p_hour << "h " << p_min << "m " << p_sec << "s");
}

void MediaListenerImpl::updateDeviceList(const DeviceEnum &enumtest)
{
  // TODO: implement me!
}
