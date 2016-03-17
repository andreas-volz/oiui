#ifndef MEDIA_LIST_WIDGET_RENDERER_H
#define MEDIA_LIST_WIDGET_RENDERER_H

/* STD */
#include <string>

/* local */
#include "stateval/stateval.h"


// the design idea behin a WidgetRenderer is to hide/wrap the specific widget type in the cpp file to not blood into the application
class MediaListWidgetRenderer : public WidgetRenderer
{
public:
  MediaListWidgetRenderer();
  virtual ~MediaListWidgetRenderer();
  
  void render(void *renderObject, const std::string &varName, Variable *var);

  Variable *getRenderedValue(void *renderObject, const std::string &varName);
  


  // concept needed what data needs to be dispatched at insert and when signals arrive
  
  // provide all data accessor functions which are needed for this special WidgetRenderer type e.g.
  // before the MediaListWidgetRenderer needs Widget/Edje pointer to be able to change real data
  // void insertItem(pos, data);

  // provide signals when an item was activated/clicked/whatever 
  
protected:
 
};

#endif // MEDIA_LIST_WIDGET_RENDERER_H
