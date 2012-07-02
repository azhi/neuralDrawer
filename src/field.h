#ifndef FIELD_H
#define FIELD_H

#include "extended_array.h"

class Field
{
public:
  Field(Bounds bounds);
  bool get_pixel(int x, int y);
  void set_pixel(int x, int y);
  void clear();
  
  Bounds bounds;

private:
  Extended_array<bool>* pixels;
  
};

#endif // FIELD_H
