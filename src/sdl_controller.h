#ifndef SDL_CONTROLLER_H
#define SDL_CONTROLLER_H

#include <SDL/sdl.h>
#include "extended_array.h"

class SDL_controller
{
public:
  SDL_controller();
  void init();
  void set_state_of_screen(Extended_array* pixels)
  SDL_event get_event();

private:
  
};

#endif // SDL_CONTROLLER_H