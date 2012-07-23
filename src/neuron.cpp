#include "neuron.h"
#include "sdl_controller.h"
#include <string.h>
#include <fstream>
#include <math.h>
#include <iostream>

Neuron::Neuron(Bounds bounds, int id) : id(id)
{
  coeffs = new Coeffs_map(bounds);
}

Neuron::~Neuron()
{
  delete coeffs;
}

double Neuron::get_result_sum(Field* field, long count)
{
  double res = 0.0f;
  list<Column*>* columns = field->get_columns_list();
  list<Column*>::iterator column = columns->begin();
  while ( column != columns->end() )
  {
    int x = (*column)->x;
    list<int>* pixels = (*column)->pixels;
    list<int>::iterator pixel_y = pixels->begin();
    while ( pixel_y != pixels->end() )
    {
      res += coeffs->get_element_at(x, *pixel_y, count);
      ++pixel_y;
    }
    ++column;
  }
  return res;
}

void Neuron::correct_answer(Field* field, long count)
{
  list<Column*>* columns = field->get_columns_list();
  list<Column*>::iterator column = columns->begin();
  while ( column != columns->end() )
  {
    int x = (*column)->x;
    list<int>* pixels = (*column)->pixels;
    list<int>::iterator pixel_y = pixels->begin();
    while ( pixel_y != pixels->end() )
    {
      coeffs->set_element_at(x, *pixel_y, count,
                           (coeffs->get_element_at(x, *pixel_y, count) + 1));
      ++pixel_y;
    }
  
    list<Element>* for_correction = coeffs->get_column_elements(x, count);
    list<Element>::iterator pixel = for_correction->begin();
    while ( pixel != for_correction->end() )
    {
      coeffs->set_element_at(x, pixel->hash_params.y, count, pixel->val / 2.0f);
      ++pixel;  
    }
    delete for_correction;
    
    ++column;
  }
}

void Neuron::load_cache()
{
  char* path = (char*) malloc(sizeof(char)*11);
  sprintf(path, "cache%d.txt", id);
  std::fstream cache;
  cache.open(path, std::fstream::in);
  long test = 0;
  if ( cache.is_open() )
  {
    int x, y;
    long count;
    double tmp;
    cache >> x; cache >> y;
    cache >> count; cache >> tmp;
    while ( !cache.eof() )
    {
      coeffs->set_element_at(x, y, count, tmp);
      cache >> x; cache >> y;
      cache >> count; cache >> tmp;
      ++test;
    }
  }
  printf("%d readed %ld lines\n", id, test);
  cache.close();
}

void Neuron::save_cache()
{
  char* path = (char*) malloc(sizeof(char)*11);
  sprintf(path, "cache%d.txt", id);
  std::fstream cache;
  cache.open(path, std::fstream::out);
  long test = 0;
  if ( cache.is_open() )
  {
    coeffs_hash_map* all = coeffs->get_data();
    coeffs_hash_map::iterator el = all->begin();
    while ( el != all->end() )
    {
      ++test;
      if ( el->second != 0.0f )
      {
        cache << el->first.x << " " << el->first.y << " " << el->first.pixels_count << " " << el->second << endl;
      }
      ++el;
    }
  }
  printf("%d saved %ld lines\n", id, test);
  cache.close();  
}
