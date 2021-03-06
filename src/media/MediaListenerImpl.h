#ifndef MEDIALISTENERIMPL_H
#define MEDIALISTENERIMPL_H

#include <dbus-c++/dbus.h>
#include <OICFMedia/OICFMediaListener.h>
#include "MediaListWidgetRenderer.h"

/* stateval */
#include <stateval/stateval.h>

/* framework */
#include "../framework/Logger.h"

class MediaListenerImpl : public OICFMediaListener
{
public:
  MediaListenerImpl(DBus::Connection &connection);

  void setMedia(Media *media);

private:
  void getWindowListResult(const LineVector &titleList, const int32_t &start, const int32_t &end, const int32_t &size);
  void updateSelectedPath(const LineVector &path);
  void updateSelectedTitle(const Line &title);
  void updatePlayPosition(const int64_t &pos, const int64_t &duration);
  void updateDeviceList(const DeviceEnum &enumtest);

  Logger mLogger;
  MediaListWidgetRenderer mediaRenderer;
  Widget *mListWidget;
  LineVector mTitleList;
};

#endif // MEDIALISTENERIMPL_H
