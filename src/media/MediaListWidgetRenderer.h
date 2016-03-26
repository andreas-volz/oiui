#ifndef MEDIA_LIST_WIDGET_RENDERER_H
#define MEDIA_LIST_WIDGET_RENDERER_H

/* STD */
#include <string>

/* stateval */
#include <stateval/stateval.h>

/* local */
#include "Media.h"

// FIXME: don't use global data!!! only a test until callback is correct memeber => SPANK 
static Media *gMedia = NULL;

// the design idea behin a WidgetRenderer is to hide/wrap the specific widget type in the cpp file to not blood into the application
class MediaListWidgetRenderer : public WidgetRenderer
{
public:
  MediaListWidgetRenderer();
  virtual ~MediaListWidgetRenderer();
  
  void render(void *renderObject, const std::string &varName, Variable *var);

  Variable *getRenderedValue(void *renderObject, const std::string &varName);

  void setMedia(Media *media);
  
private:
  Media *mMedia;
};

#endif // MEDIA_LIST_WIDGET_RENDERER_H
