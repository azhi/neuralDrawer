#include "main_controller.h"

Main_controller::Main_controller()
{
  sdl_controller = new SDL_controller();
  last = new Coord();
  education_mode = true;
}

void Main_controller::draw_by_neural_network()
{
  
}

void Main_controller::process_next_pixel()
{
  
}

void Main_controller::init_nn_and_field(Coord* bc)
{
  field = new Field(Bounds(-bc->x, SCREEN_WIDTH - bc->x, -bc->y, SCREEN_HEIGTH - bc->y));
  Coord begin = transform_to_rel_coord(*bc);
  field->set_pixel(begin.x, begin.y);
  neural_network = new Neural_network(Bounds(-bc->x, SCREEN_WIDTH - bc->x, -bc->y, SCREEN_HEIGTH - bc->y));
}

void Main_controller::set_begin_coordinates(Coord* bc)
{
  draw_begin_coordinates = *bc;
  *last = *bc;
}

Coord Main_controller::transform_to_rel_coord(Coord abs_src)
{
  return Coord(abs_src.x - draw_begin_coordinates.x, abs_src.y - draw_begin_coordinates.y);
}

Coord Main_controller::transform_to_abs_coord(Coord rel_src)
{
  return Coord(rel_src.x + draw_begin_coordinates.x, rel_src.y + draw_begin_coordinates.y);
}

void Main_controller::main_loop()
{
  while (1)
  {
    Controller_event event = sdl_controller->get_event();
    switch ( event.type )
    {
      case BEGIN_DRAW:
      {
        Coord* data = (Coord*) event.data;
        set_begin_coordinates(data);
        init_nn_and_field(data);
        break;
      }
      case DRAW_BY_NEURAL_NETWORK:
        // TODO:
        break;
      case SAVE_CACHE:
        neural_network->save_cache();
        break;
    }
    for (int i = 0; i < 100; ++i)
    {
      vector<Pixel_list_el> line = sdl_controller->process_mouse_movement(last);
      sdl_controller->redraw();
      if ( !line.empty() )
      {
        vector<Pixel_list_el>::iterator cur_pixel = line.begin();
        while ( cur_pixel != line.end() )
        {
           Coord coord = transform_to_rel_coord(cur_pixel->abs_coordinates);
//           neural_network->make_decision(field, true, cur_pixel->rel_next);
           field->set_pixel(coord.x, coord.y);
          ++cur_pixel;
        }
      }
    }
    sdl_controller->redraw();
  }
}
