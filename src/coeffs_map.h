#ifndef COEFFS_CONTAINER_H
#define COEFFS_CONTAINER_H

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <unordered_map>
#include <list>
#include <math.h>
#include <stdexcept>

using namespace std;

struct Bounds
{
  int min_x, max_x, min_y, max_y;
  Bounds(int min_x, int max_x, int min_y, int max_y) : min_x(min_x), max_x(max_x),
						       min_y(min_y), max_y(max_y) {};
};

struct Hash_params
{
  int x,y;
  long pixels_count;  
  Hash_params() : x(0), y(0), pixels_count(0) {}
  Hash_params(int x, int y, long pixels_count) : x(x), y(y), pixels_count(pixels_count) {}
};

struct Element
{
  Hash_params hash_params;
  double val;
  Element() : hash_params(), val(0.0f) {}
  Element(Hash_params hash_params, double val) : hash_params(hash_params), val(val) {}
};

struct Hash_functor
{
  size_t operator()(const Hash_params& hp) const
  {
    return hash<int>()(pow(hp.x, 3) + pow(hp.y, 2) + hp.pixels_count);
  }
};

struct Equal_functor
{
  bool operator()(const Hash_params& hp1, const Hash_params& hp2) const
  {
    return hp1.x == hp2.x && hp1.y == hp2.y && hp1.pixels_count == hp2.pixels_count;
  }
};

typedef unordered_map<Hash_params, double, Hash_functor, Equal_functor> coeffs_hash_map;

class Coeffs_map
{
public:    
  Coeffs_map(Bounds bounds) : bounds(bounds)
  {
    size_x = bounds.max_x - bounds.min_x + 1;
    size_y = bounds.max_y - bounds.min_y + 1;
    data = new coeffs_hash_map();
    clear();
  }
  
  ~Coeffs_map()
  {
    delete data;
  }
  
  coeffs_hash_map* get_data()
  {
    return data;
  }
  
  double get_element_at(int x, int y, long pixels_count)
  {
    Hash_params hp = Hash_params(x, y, pixels_count);
    double res = 0.0f;
    coeffs_hash_map::iterator it;
    if ( ( it = data->find(hp) ) != data->end() )
      res = it->second;
    return res;
  }
  
  list<Element>* get_column_elements(int x, long count)
  {
    list<Element>* res = new list<Element>;

    for (int i = bounds.min_y; i < bounds.max_y; i++)
    { 
      Hash_params hp = Hash_params(x, i, count);
      double val = 0.0f;
      coeffs_hash_map::iterator it;
      if ( ( it = data->find(hp) ) != data->end() )
        val = it->second;
      if ( val != 0.0f )
        res->push_back(Element(hp, val));
    }

    return res;
  }
  
  void set_element_at(int x, int y, long pixels_count, double val)
  {
    Hash_params hp = Hash_params(x, y, pixels_count);
    (*data)[hp] = val;
  }
  
  void clear()
  {
    data->clear();
  }
  
  Bounds bounds;

private:
  coeffs_hash_map* data;
  int size_x, size_y;
  
};

#endif // COEFFS_CONTAINER_H
