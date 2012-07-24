#ifndef COEFFS_COLUMN_HASH
#define COEFFS_COLUMN_HASH

#include <stdlib.h>
#include <unordered_map>
#include <math.h>

using namespace std;

typedef unordered_map<int, double*> column_map;

struct Hash_column_params
{
  int x;
  long pixels_count;  
  Hash_column_params() : x(0), pixels_count(0) {}
  Hash_column_params(int x, long pixels_count) : x(x), pixels_count(pixels_count) {}
};

struct Hash_column_functor
{
  size_t operator()(const Hash_column_params& hp) const
  {
    return hash<int>()(pow(hp.x, 2)) + hash<long>()(hp.pixels_count);
  }
};

struct Equal_column_functor
{
  bool operator()(const Hash_column_params& hp1, const Hash_column_params& hp2) const
  {
    return hp1.x == hp2.x && hp1.pixels_count == hp2.pixels_count;
  }
};

typedef unordered_map<Hash_column_params, column_map*, Hash_column_functor, Equal_column_functor> coeffs_column_hash_map;

#endif // COEFFS_COLUMN_HASH
