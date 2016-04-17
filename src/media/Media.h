#ifndef MEDIA_H
#define MEDIA_H

#include <OICFMedia/OICFMedia.h>

class Media
{
public:
  Media(OICFMedia &oicfMedia);

  void selectTitle(const Line &title);
  
private:
  void load();
  void pause();
  void incrementTitle();
  void decrementTitle();
  void changeMediaTitle();
  
  OICFMedia &mOICFMedia;
};

#endif // MEDIA_H
