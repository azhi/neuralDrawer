#include "field.h"

Field::Field(Bounds bounds) : bounds(bounds)
{
  pixels = new Extended_array<bool>(bounds);
}

bool Field::get_pixel(int x, int y)
{
  return pixels->get_element_at(x, y);
}

void Field::set_pixel(int x, int y)
{
  pixels->set_element_at(x, y, 1);
}

void Field::clear()
{
  pixels->clear();
}
