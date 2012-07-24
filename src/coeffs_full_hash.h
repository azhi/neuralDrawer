#ifndef COEFFS_FULL_HASH
#define COEFFS_FULL_HASH

#include <stdlib.h>
#include <unordered_map>
#include <math.h>

using namespace std;

struct Hash_full_params
{
  int x, y;
  long pixels_count;  
  Hash_full_params() : x(0), y(0), pixels_count(0) {}
  Hash_full_params(int x, int y, long pixels_count) : x(x), y(y), pixels_count(pixels_count) {}
};

struct Hash_full_functor
{
  size_t operator()(const Hash_full_params& hp) const
  {
    return hash<int>()(pow(hp.x, 3)) + hash<int>()(pow(hp.y, 2)) + hash<long>()(hp.pixels_count);
  }
};

struct Equal_full_functor
{
  bool operator()(const Hash_full_params& hp1, const Hash_full_params& hp2) const
  {
    return hp1.x == hp2.x && hp1.y == hp2.y && hp1.pixels_count == hp2.pixels_count;
  }
};

typedef unordered_map<Hash_full_params, double*, Hash_full_functor, Equal_full_functor> coeffs_full_hash_map;

#endif // COEFFS_FULL_HASH
