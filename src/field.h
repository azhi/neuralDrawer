#ifndef FIELD_H
#define FIELD_H

#include <list>
#include "extended_array.h"

using namespace std;

struct Field_list_element
{
  int x, y;
  Field_list_element() : x(0), y(0) {}
  Field_list_element(int x, int y) : x(x), y(y) {}
};

class Field
{
public:
  Field(Bounds bounds);
  ~Field();
  void add_pixel(int x, int y);
  list<Field_list_element>* get_pixels_list();
  size_t get_size();
  void clear();
  
  Bounds bounds;
  
private:  
  list<Field_list_element>* pixels;
  
};

#endif // FIELD_H
