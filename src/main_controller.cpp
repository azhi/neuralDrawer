#include "main_controller.h"

Main_controller::Main_controller()
{
  sdl_controller = new SDL_controller();
  field = new Field(Bounds(0, SCREEN_WIDTH - 1, 0, SCREEN_HEIGTH - 1));
  neural_network = new Neural_network(Bounds(0, SCREEN_WIDTH - 1, 0, SCREEN_HEIGTH - 1));
  education_mode = true;
}

void Main_controller::draw_by_neural_network()
{
  
}

void Main_controller::process_next_pixel()
{
  
}

void Main_controller::process_event(SDL_Event event)
{
  
}

void Main_controller::main_loop()
{
  while (1)
  {
    sdl_controller->get_event();
  }
}
