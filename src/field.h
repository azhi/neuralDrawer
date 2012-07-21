#ifndef FIELD_H
#define FIELD_H

#include <list>
#include "coeffs_list.h"

using namespace std;

struct Column
{
  list<int>* pixels;
  int x;
  Column() : pixels(NULL), x(0) {}
  Column(int x) : pixels(new list<int>), x(x) {}
  ~Column() { delete pixels; }
};

class Field
{
public:
  Field(Bounds bounds);
  ~Field();
  void add_pixel(int x, int y);
  list<Column*>* get_columns_list();
  size_t get_used_count();
  void clear();
  
  Bounds bounds;
  
private:  
  list<Column*>* columns;
  long cur_used_count;
  static bool my_cmp(const Column* c1, const Column* c2);
  
};

#endif // FIELD_H
