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
  void init_nn_and_field(Coord* bc);
  void main_loop();
  void set_begin_coordinates(Coord* bc);
  Coord transform_to_rel_coord(Coord abs_src);
  Coord transform_to_abs_coord(Coord rel_src);

private:
  SDL_controller* sdl_controller;
  Field* field;
  Neural_network* neural_network;
  bool education_mode;
  Coord draw_begin_coordinates;
  Coord last;
  
};

#endif // MAIN_CONTROLLER_H
