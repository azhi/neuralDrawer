#include "neuron.h"
#include "sdl_controller.h"
#include <string.h>
#include <fstream>
#include <math.h>

Neuron::Neuron(Bounds bounds, int id) : id(id)
{
  coeffs = new Extended_array<double>(bounds);
}

double Neuron::get_result_sum(Field* field)
{
  double res = 0.0f;
  list<Field_list_element>* pixels = field->get_pixels_list();
  list<Field_list_element>::iterator pixel = pixels->begin();
  while ( pixel != pixels->end() )
  {
    res += coeffs->get_element_at(pixel->x, pixel->y);
    ++pixel;
  }
  return res;
}

void Neuron::correct_answer(Field* field)
{
  list<Field_list_element>* pixels = field->get_pixels_list();
  Extended_array<bool> corrected = Extended_array<bool>(coeffs->bounds);
  list<Field_list_element>::iterator pixel = pixels->begin();
  long count = 0;
  double tmp;
  while ( pixel != pixels->end() )
  {
    for ( int i = -10; i <= 10; ++i )
      for ( int j = -10; j<= 10; ++j )
      {
	if ( i == 0  && j == 0 )
	  coeffs->set_element_at(pixel->x+i, pixel->y+j, (coeffs->get_element_at(pixel->x+i, pixel->y+j) + 1) / 2.0f * ((double) ++count/pixels->size()));
 	else
 	  coeffs->set_element_at(pixel->x+i, pixel->y+j, (coeffs->get_element_at(pixel->x+i, pixel->y+j) + 1) / 2.0f * ((double) ++count/pixels->size()) * sqrt(i*i+j*j)/14410.0f);
	corrected.set_element_at(pixel->x+i, pixel->y+j, 1);
      }
    ++pixel;
  }
  for( int i = coeffs->bounds.min_x; i <= coeffs->bounds.max_x; ++i )
    for( int j = coeffs->bounds.min_y; j <= coeffs->bounds.max_y; ++j )
      if ( !( (tmp = coeffs->get_element_at(i,j)) < 0.00001f) && !corrected.get_element_at(i, j) )
      {
	printf("BEFORE: f corrected coeffs at %d %d, nv: %lf\n", i, j, tmp);
        coeffs->set_element_at(i, j, tmp / 2.0f);
	printf("AFTER: f corrected coeffs at %d %d, nv: %lf\n", i, j, coeffs->get_element_at(i, j));
      }
}

void Neuron::load_cache()
{
  char* path = (char*) malloc(sizeof(char)*11);
  sprintf(path, "cache%d.txt", id);
  std::fstream cache;
  cache.open(path, std::fstream::in);
  if ( cache.is_open() )
    for (int i = -SCREEN_WIDTH; i <= SCREEN_WIDTH; ++i)
      for (int j = -SCREEN_HEIGTH; j <= SCREEN_HEIGTH; ++j)
      {
        double tmp;
        cache >> tmp;
        if ( i >= coeffs->bounds.min_x && i <= coeffs->bounds.max_x &&
             j >= coeffs->bounds.min_y && j <= coeffs->bounds.max_y )
          coeffs->set_element_at(i, j, tmp);
      }
  cache.close();  
}

void Neuron::save_cache()
{
  char* path = (char*) malloc(sizeof(char)*11);
  sprintf(path, "cache%d.txt", id);
  std::fstream cache;
  cache.open(path, std::fstream::out);
  if ( cache.is_open() )
    for (int i = -SCREEN_WIDTH; i <= SCREEN_WIDTH; ++i)
      for (int j = -SCREEN_HEIGTH; j <= SCREEN_HEIGTH; ++j)
      {
        if ( i >= coeffs->bounds.min_x && i <= coeffs->bounds.max_x &&
             j >= coeffs->bounds.min_y && j <= coeffs->bounds.max_y )
	{
          cache << coeffs->get_element_at(i, j) << " ";
	}
        else
          cache << 0.0f << " ";
        if ( j == coeffs->bounds.max_y )
          cache << std::endl;
      }
  cache.close();  
}
