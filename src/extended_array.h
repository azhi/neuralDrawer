#ifndef EXTENDED_ARRAY_H
#define EXTENDED_ARRAY_H

#include <stdlib.h>
#include <stdio.h>

struct Bounds
{
  int min_x, max_x, min_y, max_y;
  Bounds(int min_x, int max_x, int min_y, int max_y) : min_x(min_x), max_x(max_x),
						       min_y(min_y), max_y(max_y) {};
};

template < typename Val_type > class Extended_array
{
public:
  Extended_array(Bounds bounds) : bounds(bounds)
  {
    size_x = bounds.max_x - bounds.min_x + 1;
    size_y = bounds.max_y - bounds.min_y + 1;
    array = (Val_type*) calloc(sizeof(Val_type), size_x*size_y);
    clear();
  }
  
  Val_type get_element_at(int x, int y)
  {
    return array[(x-bounds.min_x)*size_y+(y-bounds.min_y)];
  }
  
  void set_element_at(int x, int y, Val_type val)
  {
    array[(x-bounds.min_x)*size_y+(y-bounds.min_y)] = val;
  }
  
  void clear()
  {
    for (int i = 0; i < bounds.max_x - bounds.min_x + 1; ++i)
      for (int j = 0; j < bounds.max_y - bounds.min_y + 1; ++j)
        array[i*size_y+j] = 0;
  }
  
  Bounds bounds;

private:
  Val_type* array;
  int size_x, size_y;
  
};

#endif // EXTENDED_ARRAY_H
