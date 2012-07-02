#ifndef SDL_CONTROLLER_H
#define SDL_CONTROLLER_H

#include <SDL/SDL.h>
#include "extended_array.h"

#define SCREEN_WIDTH 500
#define SCREEN_HEIGTH 300

class SDL_controller
{
public:
  SDL_controller();
  void init();
  void set_state_of_screen(Extended_array<bool>* pixels);
  SDL_Event get_event();

private:
  SDL_Surface* screen;
  SDL_Surface* drawingArea;
  
  void put_pixel(int x, int y);
  void draw_pixel(SDL_Surface *screen, int x, int y, Uint8 R, Uint8 G, Uint8 B);
  void slock(SDL_Surface *screen);
  void sulock(SDL_Surface *screen);
  
};

#endif // SDL_CONTROLLER_H
