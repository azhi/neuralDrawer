#include "field.h"
#include <algorithm>

Field::Field(Bounds bounds) : bounds(bounds)
{
  columns = new list<Column*>;
  clear();
}

Field::~Field()
{
  delete columns;
}

void Field::add_pixel(int x, int y)
{
  Column* col_to_find = new Column();
  col_to_find->x = x;
  list<Column*>::iterator col = lower_bound(columns->begin(), columns->end(),
                                           col_to_find, my_cmp);
  delete col_to_find;
  if ( col != columns->end() && (*col)->x == x )
  {
    (*col)->pixels->push_back(y);
  }
  ++cur_used_count;
}

list<Column*>* Field::get_columns_list()
{
  return columns;
}

size_t Field::get_used_count()
{
  return cur_used_count;
}

void Field::clear()
{
  for (int i = bounds.min_x; i <= bounds.max_x; ++i)
  {
    Column* col = new Column(i);
    columns->push_back(col);
  }
  cur_used_count = 0;  
}

bool Field::my_cmp(const Column* c1, const Column* c2)
{
  return (c1->x < c2->x);
}
