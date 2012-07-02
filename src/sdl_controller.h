#ifndef SDL_CONTROLLER_H
#define SDL_CONTROLLER_H

#include <SDL/SDL.h>
#include "extended_array.h"
#include "neural_network.h"
#include <vector>

using namespace std;

#define SCREEN_WIDTH 500
#define SCREEN_HEIGTH 300

struct Coord
{
  int x,y;
  Coord() : x(0), y(0) {}
  Coord(int x, int y) : x(x), y(y) {}
};

#define BEGIN_DRAW 1
#define DRAW_BY_NEURAL_NETWORK 2
#define SAVE_CACHE 4

struct Controller_event
{
  int type;
  void* data;
  Controller_event() : type(0), data(NULL) {}
  Controller_event(int type, void* data) : type(type), data(data) {}
};

struct Pixel_list_el
{
  Coord abs_coordinates;
  Decision rel_next;
  Pixel_list_el() : abs_coordinates( Coord() ), rel_next( Decision() ) {}
  Pixel_list_el(Coord coord, Decision decision) : abs_coordinates( coord ),
                                                  rel_next( decision ) {}
};

class SDL_controller
{
public:
  SDL_controller();
  void init();
  void set_state_of_screen(Extended_array<bool>* pixels);
  Controller_event get_event();
  void redraw();
  vector<Pixel_list_el> process_mouse_movement(Coord* last_pos);

private:
  SDL_Surface* screen;
  SDL_Surface* drawingArea;
  bool do_draw;
  
  void put_pixel(int x, int y);
  vector<Pixel_list_el> draw_line(int x1, int y1, int x2, int y2);
  void draw_pixel(SDL_Surface *screen, int x, int y, Uint8 R, Uint8 G, Uint8 B);
  void slock(SDL_Surface *screen);
  void sulock(SDL_Surface *screen);
  
};

#endif // SDL_CONTROLLER_H
