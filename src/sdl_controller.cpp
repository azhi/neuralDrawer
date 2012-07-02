#include "sdl_controller.h"

SDL_controller::SDL_controller()
{
  init();
  do_draw = false;
}

void SDL_controller::init()
{
  if ( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_EVENTTHREAD ) < 0 )
  {
    fprintf(stderr, "Unable to init SDL: %s", SDL_GetError());
    exit(EXIT_FAILURE);
  }
  
  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGTH, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
  if ( !screen )
  {
    fprintf(stderr, "Unable to set videomode: %s", SDL_GetError());
    exit(EXIT_FAILURE);
  }
  
  drawingArea = SDL_CreateRGBSurface(SDL_HWSURFACE, SCREEN_WIDTH - 100, SCREEN_HEIGTH, 32,
                                     0, 0, 0, 0);
  if ( !drawingArea )
  {
    fprintf(stderr, "Unable to create surface: %s", SDL_GetError());
    exit(EXIT_FAILURE);
  }
  
  SDL_FillRect(drawingArea, NULL, SDL_MapRGB(drawingArea->format, 255, 255, 255));
  SDL_Rect lay_coord; lay_coord.x = 0; lay_coord.y = 0;
  SDL_Rect src; src.x = 0; src.y = 0;
  src.w = SCREEN_WIDTH - 100; src.h = SCREEN_HEIGTH;
  SDL_BlitSurface(drawingArea, &src, screen, &lay_coord);
  SDL_Flip(screen);
  SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
}

Controller_event SDL_controller::get_event()
{
  Controller_event res;
  SDL_Event event;
  while ( SDL_PollEvent(&event) )
  {
    switch ( event.type )
    {
      case SDL_KEYDOWN:
        if ( event.key.keysym.sym == SDLK_F11 )
          redraw();
        break;
      case SDL_MOUSEBUTTONDOWN:
        if ( event.button.button == SDL_BUTTON_LEFT )
        {
          do_draw = true;
          res.type = BEGIN_DRAW;
          Coord* data = new Coord(event.button.x, event.button.y);
          res.data = (void*) data;
        }
        break;
      case SDL_MOUSEBUTTONUP:
        if ( event.button.button == SDL_BUTTON_LEFT )
          do_draw = false;
        break;  
//       case SDL_MOUSEMOTION:
//         if ( event.motion.state & SDL_BUTTON(1) )
//           put_pixel(event.motion.x, event.motion.y);
//         break;
      case SDL_QUIT:
        printf("Exiting...\n");
        exit(0);
    }
  }
  return res;
}

vector<Pixel_list_el> SDL_controller::process_mouse_movement(Coord* last_pos)
{
  int x = 0, y = 0;
  vector<Pixel_list_el> res;
  if ( do_draw )
  {
    SDL_GetMouseState(&x, &y);
    res = draw_line(last_pos->x, last_pos->y, x, y);
  }
  last_pos->x = x; last_pos->y = y;
  return res;
}

vector<Pixel_list_el> SDL_controller::draw_line(int x1, int y1, int x2, int y2)
{
  vector<Pixel_list_el> res;
  const int deltaX = abs(x2 - x1);
  const int deltaY = abs(y2 - y1);
  const int signX = x1 < x2 ? 1 : -1;
  const int signY = y1 < y2 ? 1 : -1;

  int error = deltaX - deltaY;
  int lastX = -1, lastY = -1;
  
  put_pixel(x2, y2);
  while (x1 != x2 || y1 != y2)
  {
    put_pixel(x1, y1);
    
    if ( lastX != -1 || lastY != -1 )
      res.push_back( Pixel_list_el(Coord(lastX,lastY), Decision(x1-lastX, y1-lastY) ) );
    lastX = x1; lastY = y1;
    
    const int error2 = error * 2;
    if (error2 > -deltaY)
    {
      error -= deltaY;
      x1 += signX;
    }
    if (error2 < deltaX)
    {
      error += deltaX;
      y1 += signY;
    }
  }
  return res;
}

void SDL_controller::redraw()
{
  SDL_Rect lay_coord; lay_coord.x = 0; lay_coord.y = 0;
  SDL_Rect src; src.x = 0; src.y = 0;
  src.w = SCREEN_WIDTH - 100; src.h = SCREEN_HEIGTH;
  SDL_BlitSurface(drawingArea, &src, screen, &lay_coord);
  SDL_Flip(screen);
}

void SDL_controller::set_state_of_screen(Extended_array<bool>* pixels)
{
  SDL_FillRect(drawingArea, NULL, SDL_MapRGB(drawingArea->format, 255, 255, 255));
  slock(drawingArea);
  for ( int i = pixels->bounds.min_x; i <= pixels->bounds.max_x; ++i )
    for ( int j = pixels->bounds.min_y; j <= pixels->bounds.max_y; ++j )
      if ( pixels->get_element_at(i, j) )
        // FIXME: wrong coordinates
        draw_pixel(drawingArea, i, j, 0, 0, 0);
  sulock(drawingArea);
}

void SDL_controller::put_pixel(int x, int y)
{
  slock(drawingArea);
  draw_pixel(drawingArea, x, y, 0, 0, 0);
  sulock(drawingArea);
}

void SDL_controller::draw_pixel(SDL_Surface *screen, int x, int y, Uint8 R, Uint8 G, Uint8 B)
{
  Uint32 color = SDL_MapRGB(screen->format, R, G, B);
  switch (screen->format->BytesPerPixel)
  {
    case 1: // Assuming 8-bpp
    {
      Uint8 *bufp;
      bufp = (Uint8 *)screen->pixels + y*screen->pitch + x;
      *bufp = color;
    }
    break;
    case 2: // Probably 15-bpp or 16-bpp
    {
      Uint16 *bufp;
      bufp = (Uint16 *)screen->pixels + y*screen->pitch/2 + x;
      *bufp = color;
    }
    break;
    case 3: // Slow 24-bpp mode, usually not used
    {
      Uint8 *bufp;
      bufp = (Uint8 *)screen->pixels + y*screen->pitch + x * 3;
      if(SDL_BYTEORDER == SDL_LIL_ENDIAN)
      {
        bufp[0] = color;
        bufp[1] = color >> 8;
        bufp[2] = color >> 16;
      } else {
        bufp[2] = color;
        bufp[1] = color >> 8;
        bufp[0] = color >> 16;
      }
    }
    break;
    case 4: // Probably 32-bpp
    {
      Uint32 *bufp;
      bufp = (Uint32 *)screen->pixels + y*screen->pitch/4 + x;
      *bufp = color;
    }
    break;
  }
}

void SDL_controller::slock(SDL_Surface *screen)
{
  if ( SDL_MUSTLOCK(screen) )
  {
    if ( SDL_LockSurface(screen) < 0 )
    {
      return;
    }
  }
}

void SDL_controller::sulock(SDL_Surface *screen)
{
  if ( SDL_MUSTLOCK(screen) )
  {
    SDL_UnlockSurface(screen);
  }
}
