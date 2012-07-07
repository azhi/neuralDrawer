#include "field.h"

Field::Field(Bounds bounds) : bounds(bounds)
{
  pixels = new list<Field_list_element>;
}

void Field::add_pixel(int x, int y)
{
  pixels->push_back(Field_list_element(x, y));
}

list<Field_list_element>* Field::get_pixels_list()
{
  return pixels;
}

void Field::clear()
{
  pixels->clear();
}
