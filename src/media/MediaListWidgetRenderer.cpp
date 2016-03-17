#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

/* EFLxx */
#include <evasxx/Evasxx.h>
#include <edjexx/Edjexx.h>
#include <elementaryxx/Elementaryxx.h>

/* local */
#include "MediaListWidgetRenderer.h"

MediaListWidgetRenderer::MediaListWidgetRenderer()
{

}

MediaListWidgetRenderer::~MediaListWidgetRenderer()
{

}

void MediaListWidgetRenderer::render(void *renderObject, const std::string &varName, Variable *var)
{
  Edjexx::Part *part = static_cast<Edjexx::Part*>(renderObject);

  if(part && var)
  {
    if(var->getType () == Variable::TYPE_LIST)
    {
      List *ls = static_cast <List *>(var);

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
          Elmxx::List &list = *(static_cast <Elmxx::List *>(&elm_object));

          // TODO: I think until the edited/merge feature is implemented it's the
          // best to clear the list before adding new elements...
          list.clear();
          for (List::Iterator ls_it = ls->begin();
               ls_it != ls->end();
               ++ls_it)
          {
            Variable *av = *ls_it;

            if (av->getType() == Variable::TYPE_STRING)
            {
              String *str = static_cast <String *>(av);
              list.append(str->getData(), NULL, NULL);
            }
            list.go();
          }
        }
      }
    }
  }
}

Variable *MediaListWidgetRenderer::getRenderedValue(void *renderObject, const std::string &varName)
{

}
