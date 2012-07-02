#include "neuron.h"
#include "sdl_controller.h"
#include <string.h>
#include <fstream>

Neuron::Neuron(Bounds bounds, int id) : id(id)
{
  coeffs = new Extended_array<double>(bounds);
}

double Neuron::get_result_sum(Field* field)
{
  double res = 0.0f;
  for (int i = field->bounds.min_x; i <= field->bounds.max_x; ++i)
    for (int j = field->bounds.min_y; i <= field->bounds.max_y; ++j)
      if ( field->get_pixel(i, j) )
        res += coeffs->get_element_at(i, j);
  return res;
}

void Neuron::correct_answer(Field* field)
{
  for (int i = coeffs->bounds.min_x; i <= coeffs->bounds.max_x; ++i)
    for (int j = coeffs->bounds.min_y; i <= coeffs->bounds.max_y; ++j)
      if ( field->get_pixel(i, j) )
        coeffs->set_element_at(i, j, (coeffs->get_element_at(i, j) + 1) / 2.0f);
      else
        coeffs->set_element_at(i, j, coeffs->get_element_at(i, j) / 2.0f);
}

void Neuron::load_cache()
{
  char* path = (char*) malloc(sizeof(char)*11);
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
          cache << coeffs->get_element_at(i, j) << " ";
        else
          cache << 0.0f << " ";
        if ( j == coeffs->bounds.max_y )
          cache << std::endl;
      }
  cache.close();  
}
