#ifndef EXTENDED_ARRAY_H
#define EXTENDED_ARRAY_H

#include <stdlib.h>
#include <stdio.h>
#include <list>

using namespace std;

struct Bounds
{
  int min_x, max_x, min_y, max_y;
  Bounds(int min_x, int max_x, int min_y, int max_y) : min_x(min_x), max_x(max_x),
						       min_y(min_y), max_y(max_y) {};
};

template < typename Val_type >
struct Element
{
  Val_type val;
  long count;
  Element() : val(0), count(0) {}
  Element(Val_type val, long count) : val(val), count(count) {}
};


template < typename Val_type > class Extended_array
{
public:    
  Extended_array(Bounds bounds) : bounds(bounds)
  {
    size_x = bounds.max_x - bounds.min_x + 1;
    size_y = bounds.max_y - bounds.min_y + 1;
    array = (list< Element<Val_type> >**) calloc(sizeof(list< Element<Val_type> >*), size_x*size_y);
    clear();
  }
  
  ~Extended_array()
  {
    delete[] array;
  }
  
  list< Element<Val_type> >* get_list(int x, int y)
  {
    return array[(x-bounds.min_x)*size_y+(y-bounds.min_y)];
  }
  
  Val_type get_element_at(int x, int y, int count)
  {
    Val_type res;
    if ( x >= bounds.min_x && x <= bounds.max_x &&
         y >= bounds.min_y && y <= bounds.max_y )
    {
      list< Element<Val_type> >* cl = array[(x-bounds.min_x)*size_y+(y-bounds.min_y)];
      typename list< Element<Val_type> >::iterator cf = cl->begin();
      while ( cf != cl->end() )
      {
	if ( cf->count == count )
	{
	  res = cf->val;
	  break;
	}
	++cf;
      }
    }
    return res;
  }
  
  void set_element_at(int x, int y, int count, Val_type val)
  {
    list< Element<Val_type> >* cl = array[(x-bounds.min_x)*size_y+(y-bounds.min_y)];
    typename list< Element<Val_type> >::iterator cf = cl->begin();
    while ( cf != cl->end() )
    {
      if ( cf->count == count )
      {
	cf->val = val;
	break;
      }
      ++cf;
    }
    
    if ( cf == cl->end() )
      cl->push_back(Element<Val_type>(val, count));
  }
  
  void clear()
  {
    for (int i = 0; i < bounds.max_x - bounds.min_x + 1; ++i)
      for (int j = 0; j < bounds.max_y - bounds.min_y + 1; ++j)
      {
        array[i*size_y+j] = new list< Element<Val_type> >;
      }
  }
  
  Bounds bounds;

private:
  list< Element<Val_type> >** array;
  int size_x, size_y;
  
};

#endif // EXTENDED_ARRAY_H
