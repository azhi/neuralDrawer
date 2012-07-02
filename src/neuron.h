#ifndef NEURON_H
#define NEURON_H

#include "extended_array.h"
#include "field.h"

class Neuron
{
public:
  Neuron(Bounds bounds, int id);
  double get_result_sum(Field* field);
  void correct_answer(Field* field);
  void load_cache();
  void save_cache();

private:
  Extended_array<double>* coeffs;
  int id;
  
};

#endif // NEURON_H
