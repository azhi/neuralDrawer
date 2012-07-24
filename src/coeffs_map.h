#ifndef COEFFS_CONTAINER_H
#define COEFFS_CONTAINER_H

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <unordered_map>
#include <list>
#include <math.h>
#include <stdexcept>
#include "coeffs_full_hash.h"
#include "coeffs_column_hash.h"

using namespace std;

struct Bounds
{
  int min_x, max_x, min_y, max_y;
  Bounds(int min_x, int max_x, int min_y, int max_y) : min_x(min_x), max_x(max_x),
						       min_y(min_y), max_y(max_y) {};
};

class Coeffs_map
{
public:    
  Coeffs_map(Bounds bounds) : bounds(bounds)
  {
    size_x = bounds.max_x - bounds.min_x + 1;
    size_y = bounds.max_y - bounds.min_y + 1;
    all = new coeffs_full_hash_map();
    columns = new coeffs_column_hash_map();
    clear();
  }
  
  ~Coeffs_map()
  {
    // coeffs_full_hash_map::iterator el = all->begin();
    // while ( el != all->end() )
    // {
    //   delete el->second;
    //   ++el;
    // }
    delete all;
    delete columns;
  }
  
  coeffs_full_hash_map* get_all()
  {
    return all;
  }
  
  double get_element_at(int x, int y, long pixels_count)
  {
    Hash_full_params hp = Hash_full_params(x, y, pixels_count);
    double res = 0.0f;
    coeffs_full_hash_map::iterator it;
    if ( ( it = all->find(hp) ) != all->end() )
      res = *(it->second);
    return res;
  }
  
  column_map* get_column_elements(int x, long count)
  {
    Hash_column_params hp = Hash_column_params(x, count);
    column_map* res = NULL;
    coeffs_column_hash_map::iterator it;
    if ( ( it = columns->find(hp) ) != columns->end() )
      res = it->second;
    return res;
  }
  
  void set_element_at(int x, int y, long pixels_count, double val)
  {
    double* pval = NULL;
    Hash_full_params hfp = Hash_full_params(x, y, pixels_count);
    if ( all->count(hfp) )
      *( (*all)[hfp] ) = val;
    else
    {
      pval = new double;
      *pval = val;
      (*all)[hfp] = pval;
    }

    Hash_column_params hcp = Hash_column_params(x, pixels_count);
    column_map* pc = NULL;
    if ( columns->count(hcp) )
    {
      pc = (*columns)[hcp];
    }
    else
    {
      pc = new column_map;
      (*columns)[hcp] = pc;
    }

    if ( pc->count(y) )
      *( (*pc)[y] ) = val;
    else
      (*pc)[y] = pval;
  }
  
  void clear()
  {
    all->clear();
    columns->clear();
  }
  
  Bounds bounds;

private:
  coeffs_full_hash_map* all;
  coeffs_column_hash_map* columns;
  int size_x, size_y;
  
};

#endif // COEFFS_CONTAINER_H
