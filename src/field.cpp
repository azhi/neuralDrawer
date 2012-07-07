#include "field.h"

Field::Field(Bounds bounds) : bounds(bounds)
{
  pixels = new list<Field_list_element>;
}

Field::~Field()
{
  delete pixels;
}

void Field::add_pixel(int x, int y)
{
  pixels->push_back(Field_list_element(x, y));
}

list<Field_list_element>* Field::get_pixels_list()
{
  return pixels;
}

size_t Field::get_size()
{
  return pixels->size();
}

void Field::clear()
{
  pixels->clear();
}
