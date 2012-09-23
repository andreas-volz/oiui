#ifndef MEDIA_H
#define MEDIA_H

#include <OICFMedia/OICFMedia.h>

class Media
{
public:
  Media(OICFMedia &oicfMedia);

private:
  void load();
  void incrementTitle();
  void decrementTitle();
  void changeMediaTitle();

  OICFMedia &mOICFMedia;
};

#endif // MEDIA_H
