#include "main_controller.h"

Main_controller::Main_controller()
{
  sdl_controller = new SDL_controller();
  last = new Coord();
  cur_picture = new list<Field_list_element>;
  education_mode = true;
}

list<Field_list_element> Main_controller::get_picture()
{
  list<Field_list_element> res;
  Coord* begin = new Coord(100, 100);
  res.push_back(Field_list_element(begin->x, begin->y));
  set_begin_coordinates(begin);
  init_nn_and_field(begin);
  neural_network->load_cache();
  for (int i=0; i<350; ++i)
  {
    Decision dec = neural_network->make_decision(field, false, NULL);
    last->x = last->x+dec.dx; last->y = last->y + dec.dy;
    res.push_back(Field_list_element(last->x, last->y));
    Coord rel_last = transform_to_rel_coord(*last);
    field->add_pixel(rel_last.x, rel_last.y);
  }
  return res;
}

void Main_controller::process_line()
{
  list<Field_list_element>::iterator cur_pixel = cur_picture->begin();
  while ( cur_pixel != cur_picture->end() )
  {
    Coord from = transform_to_rel_coord(Coord(cur_pixel->x, cur_pixel->y));
    ++cur_pixel;
    Coord to = transform_to_rel_coord(Coord(cur_pixel->x, cur_pixel->y));
    neural_network->make_decision(field, true, new Decision(to.x - from.x, to.y - from.y));
    field->add_pixel(to.x, to.y);
  }
}

void Main_controller::init_nn_and_field(Coord* bc)
{
  delete field;
  delete neural_network;
  field = new Field(Bounds(-bc->x, SCREEN_WIDTH - bc->x, -bc->y, SCREEN_HEIGTH - bc->y));
  field->add_pixel(0, 0);
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
	printf("setting begin coordinates...\n");
        set_begin_coordinates(data);
	printf("initialazing NN and field...\n");
        init_nn_and_field(data);
	cur_picture->clear();
        break;
      }
      case END_DRAW:
	printf("loading cache...\n");
	neural_network->load_cache();
	printf("starting processing line...\n");
	process_line();
	printf("saving cache...\n");
	neural_network->save_cache();
	printf("Finished education!\n");
	break;
      case DRAW_BY_NEURAL_NETWORK:
      {
        list<Field_list_element> pic = get_picture();
	sdl_controller->set_state_of_screen(pic);
	sdl_controller->redraw();
        break;
      }
      case SAVE_CACHE:
        neural_network->save_cache();
        break;
    }
    for (int i = 0; i < 100; ++i)
    {
      list<Field_list_element>* line = sdl_controller->process_mouse_movement(last);
      sdl_controller->redraw();
      if ( !(line == NULL) && !line->empty() )
 	cur_picture->splice(cur_picture->end(), *line);
    }
    sdl_controller->redraw();
  }
}
