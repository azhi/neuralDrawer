#ifndef MAIN_CONTROLLER_H
#define MAIN_CONTROLLER_H

#include "sdl_controller.h"
#include "field.h"
#include "neural_network.h"
#include <SDL/SDL.h>

class Main_controller
{
public:
  Main_controller();
  void draw_by_neural_network();
  void process_next_pixel();
  void process_event(SDL_Event event);
  void main_loop();

private:
  SDL_controller* sdl_controller;
  Field* field;
  Neural_network* neural_network;
  bool education_mode;
  
};

#endif // MAIN_CONTROLLER_H
