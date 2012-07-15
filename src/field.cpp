#include "field.h"
#include <algorithm>

Field::Field(Bounds bounds) : bounds(bounds)
{
  columns = new list<Column>;
  clear();
}

Field::~Field()
{
  delete columns;
}

void Field::add_pixel(int x, int y)
{
  Column col_to_find = Column(NULL, x);
  list<Column>::iterator col = lower_bound(columns->begin(), columns->end(),
                                           col_to_find, my_cmp);
  if ( col != columns->end() && col->x == x )
  {
    col->pixels->push_back(y);
//     printf("added: %d=%d %d\npointer: %ld cs: %d\n", col->x, x, y, col->pixels, col->pixels->size());
  }
  ++cur_used_count;
}

list<Column>* Field::get_columns_list()
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
    //FIXME: new always gives the same pointer
    list<int>* y_list = new list<int>;
    Column col = Column(y_list, i);
    printf("for x=%d pointer=%ld\n", col.x, y_list);
    columns->push_back(col);
  }
  cur_used_count = 0;  
}

bool Field::my_cmp(const Column& c1, const Column& c2)
{
  return (c1.x < c2.x);
}
