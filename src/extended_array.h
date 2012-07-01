#ifndef EXTENDED_ARRAY_H
#define EXTENDED_ARRAY_H

struct Bounds
{
  int min_x, max_x, min_y, max_y;
  Bounds(int min_x, int max_x, int min_y, int max_y) : min_x(mix_x), max_x(max_x),
						       min_y(min_y), max_y(max_y) {};
}

template < typename Val_type > class Extended_array
{
public:
  Extended_array(Bounds bounds);
  Val_type get_element_at(int x, int y)
  void set_element_at(int x, int y, Val_type val);
  void clear();

private:
  Val_type* array;
  
};

#endif // EXTENDED_ARRAY_H