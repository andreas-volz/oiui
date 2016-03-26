#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

/* Project */
#include "Media.h"
#include "../framework/EventHandler.h"
#include "../framework/util.h"

/* STD */
#include <iostream>

/* stateval */
#include <stateval/stateval.h>

using namespace std;

Media::Media(OICFMedia &oicfMedia) :
  mOICFMedia(oicfMedia)
{
  EventHandler &eventHandler(EventHandler::instance());

  LineVector lv;
  mOICFMedia.selectPath(lv);

  eventHandler.connect("MEDIA_INCREMENT_TITLE", sigc::mem_fun(this, &Media::incrementTitle));
  eventHandler.connect("MEDIA_DECREMENT_TITLE", sigc::mem_fun(this, &Media::decrementTitle));
  eventHandler.connect("MEDIA_LOAD", sigc::mem_fun(this, &Media::load));
  eventHandler.connect("CHANGE_MEDIA_TITLE", sigc::mem_fun(this, &Media::changeMediaTitle));
  //eventHandler.connect("MEDIA_SELECT_TITLE", sigc::mem_fun(this, &Media::changeMediaTitle));
}

void Media::load()
{
  mOICFMedia.getWindowList(0, 100);
}

void Media::incrementTitle()
{
  mOICFMedia.incrementTitle(1);
}

void Media::decrementTitle()
{
  mOICFMedia.decrementTitle(1);
}

void Media::changeMediaTitle()
{
  // TODO: This code could maybe changed in some widget action magic

  StateMachineAccessor &stateMachineAccessor = StateMachineAccessor::getInstance();
  Variable *av = stateMachineAccessor.getVariable("MediaListTitle");
  assert(av);
  String *st = static_cast <String *>(av);
  static int count = 0;
  ++count;

  st->change("New Title string " + toString(count));

  stateMachineAccessor.pushEvent("VIEW_UPDATE");
}

void Media::selectTitle(const Line &title)
{
  mOICFMedia.selectTitle(title);
}
