#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

/* EFLxx */
#include <evasxx/Evasxx.h>
#include <edjexx/Edjexx.h>
#include <elementaryxx/Elementaryxx.h>

/* OICF */
#include <OICFMedia/OICFMediaListener.h>

/* local */
#include "../framework/searchFile.h"
#include "../framework/util.h"
#include "MediaListWidgetRenderer.h"
#include "Media.h"

using namespace std;

MediaListWidgetRenderer::MediaListWidgetRenderer() :
  mLogger("oiui.Media.MediaListWidgetRenderer"),
  mMedia(NULL)
{

}

MediaListWidgetRenderer::~MediaListWidgetRenderer()
{
}

// TODO: move this callback as member function (also to have access to logger)
static void _sel_cb(void *data, Evas_Object *obj, void *event_info)
{
  Elm_Object_Item *list_it = static_cast<Elm_Object_Item*>(event_info);
  cout << "Selected label: " << elm_object_item_text_get(list_it) << endl;;

  void *attached_data = elm_object_item_data_get(list_it);

  Line *l = static_cast<Line*>(attached_data);

  cout << "selected: ID: " << l->id << ", Name: " << l->name << ", Type: " << l->type << endl;
  gMedia->selectTitle(*l);
}

void MediaListWidgetRenderer::render(void *renderObject, const std::string &varName, Variable *var)
{  
  Edjexx::Part *part = static_cast<Edjexx::Part*>(renderObject);

  if(part)
  {
    if(var)
    {
      if(var->getType () == Variable::TYPE_VOIDPTR)
      {     
        VoidPtr *vp = static_cast <VoidPtr*>(var);
        if(!vp->isZero())
        {
          LineVector *titleList = static_cast<LineVector*>(vp->getData());
          
          Evasxx::Object &ext_eo3 = part->getExternalObject();
          Evasxx::Object &eo3 = part->getSwallow();
          //LOG4CXX_DEBUG(mLogger, "Edje External Widget type: " << ext_eo3.getType());
          //LOG4CXX_DEBUG(mLogger, "Edje Part Widget type: " << eo3.getType());

          if (ext_eo3.getType() == "elm_list")
          {
            Elmxx::Object &elm_object = *(static_cast <Elmxx::Object *>(&ext_eo3));
            
            //LOG4CXX_DEBUG(mLogger, "Elm Widget type: " << elm_object.getWidgetType());

            if (elm_object.getWidgetType() == "Elm_List")
            {
              Elmxx::List *list = static_cast <Elmxx::List*>(&elm_object);

              list->clear();
              for (LineVector::const_iterator vs_it = titleList->begin();
                   vs_it != titleList->end();
                   ++vs_it)
              {
                const Line &l = *vs_it;

                LOG4CXX_TRACE(mLogger, "ID: " << l.id << " Name: " << l.name); 

               string iconTypeName;
                switch(l.type)
                {
                  case Line::Title:
                    iconTypeName = "MediaAudiofileIcon";
                    break;

                  case Line::Folder:
                    iconTypeName = "MediaFolderIcon";
                    break;

                  case Line::FolderUp:
                    iconTypeName = "MediaFolderUpIcon";
                    break;

                    default:
                    cout << "default: " << endl;
                }

                // TODO: hm, who frees the icons? memory leak! I think edje C object is freed by ElmList, but
                // Edjexx object will leak. Think about to live by solution in Eflxx or use the new Edje C++ API
                Edjexx::Object *icon = new Edjexx::Object(*ext_eo3.getCanvas(),searchDataFile("sm/screens/oiui_screens.edj"), iconTypeName);
                list->append(l.name, icon, NULL, _sel_cb, &l);
              }
  
              list->go();
            }
          }
        }
      }
    }
    else // delete list objects
    {
      LOG4CXX_TRACE(mLogger, "delete all list objects");
      // TODO: still needed?
    }
  }
}

void MediaListWidgetRenderer::setMedia(Media *media)
{
  mMedia = media;
  gMedia = mMedia;
}

Variable *MediaListWidgetRenderer::getRenderedValue(void *renderObject, const std::string &varName)
{
  return NULL;
}
