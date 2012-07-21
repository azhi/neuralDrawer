#ifndef COEFFS_LIST_H
#define COEFFS_LIST_H

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <algorithm>
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
  int x,y;
  long pixels_count;  
  Val_type val;
  Element() : x(0), y(0), val(0), pixels_count(0) {}
  Element(int x, int y, long pixels_count, Val_type val) : x(x), y(y),
                                                           pixels_count(pixels_count), val(val) {}
};


template < typename Val_type > class Coeffs_list
{
public:    
  Coeffs_list(Bounds bounds) : bounds(bounds)
  {
    size_x = bounds.max_x - bounds.min_x + 1;
    size_y = bounds.max_y - bounds.min_y + 1;
    data = new list< Element<Val_type> >;
    clear();
  }
  
  ~Coeffs_list()
  {
    delete data;
  }
  
  list< Element<Val_type> >* get_list()
  {
    return data;
  }
  
  Val_type get_element_at(int x, int y, long pixels_count)
  {
    Val_type res;
    Element<Val_type> el_to_find = Element<Val_type>(x, y, pixels_count, res);
    typename list< Element<Val_type> >::iterator el = lower_bound(data->begin(), data->end(),
                                                                  el_to_find, my_cmp);
    if ( full_cmp(*el, el_to_find) )
      res = el->val;
    return res;
  }
  
  list< Element<Val_type> >* get_column_elements(int x, long count)
  {
    list< Element<Val_type> >* res = new list< Element<Val_type> >;
    
    Element<Val_type> el_to_find = Element<Val_type>(x, -INT_MAX, count, 0);
    typename list< Element<Val_type> >::iterator low = lower_bound(data->begin(), data->end(),
                                                                  el_to_find, my_cmp);
    el_to_find.y = INT_MAX;
    typename list< Element<Val_type> >::iterator up = upper_bound(data->begin(), data->end(),
                                                                     el_to_find, my_cmp);
    --up;
    if ( low == up && ( low->x != x || low->pixels_count != count ) )
      return res;
    res->insert(res->end(), low, ++up);
    return res;
  }
  
  void set_element_at(int x, int y, long pixels_count, Val_type val)
  {
    Element<Val_type> inserting_el = Element<Val_type>(x, y, pixels_count, val);
    typename list< Element<Val_type> >::iterator el = lower_bound(data->begin(), data->end(),
                                                                  inserting_el, my_cmp);
    if ( el != data->end() && full_cmp(*el, inserting_el) )
    {
      el->val = val;
    }
    else
    {
      data->insert(el, inserting_el);
    }
  }
  
  void clear()
  {
    data->clear();
  }
  
  Bounds bounds;

private:
  list< Element<Val_type> >* data;
  int size_x, size_y;
  static bool my_cmp(const Element<Val_type>& el1, const Element<Val_type>& el2)
  {
    if ( el1.x < el2.x )
      return true;
    if ( el1.x == el2.x )
    {
      if ( el1.pixels_count < el2.pixels_count )
        return true;
      if ( el1.pixels_count == el2.pixels_count )
      {
        if ( el1.y < el2.y )
          return true;
      }
    }
    return false;
  }
  static bool full_cmp(const Element<Val_type>& el1, const Element<Val_type>& el2)
  {
    return el1.x == el2.x && el1.y == el2.y && el1.pixels_count == el2.pixels_count;
  }
  
};

#endif // COEFFS_LIST_H
