#ifndef SDL_CONTROLLER_H
#define SDL_CONTROLLER_H

#include <SDL/SDL.h>
#include "field.h"
#include "neural_network.h"
#include <list>

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
#define END_DRAW 2
#define DRAW_BY_NEURAL_NETWORK 4
#define SAVE_CACHE 8

struct Controller_event
{
  int type;
  void* data;
  Controller_event() : type(0), data(NULL) {}
  Controller_event(int type, void* data) : type(type), data(data) {}
};

class SDL_controller
{
public:
  SDL_controller();
  void init();
  void set_state_of_screen(list<Coord>* pixels);
  bool check_ranges(int x, int y);
  Controller_event get_event();
  void redraw();
  list<Coord>* process_mouse_movement(Coord* last_pos);

private:
  SDL_Surface* screen;
  SDL_Surface* drawingArea;
  bool do_draw;
  
  void put_pixel(int x, int y);
  list<Coord>* draw_line(int x1, int y1, int x2, int y2);
  void draw_pixel(SDL_Surface *screen, int x, int y, Uint8 R, Uint8 G, Uint8 B);
  void slock(SDL_Surface *screen);
  void sulock(SDL_Surface *screen);
  
};

#endif // SDL_CONTROLLER_H
