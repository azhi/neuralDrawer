#ifndef NEURON_H
#define NEURON_H

#include "extended_array.h"
#include "field.h"

class Neuron
{
public:
  Neuron(Bounds bounds);
  double get_result_sum(Field* field);
  void correct_answer(Field* field);

private:
  Extended_array<double>* coeffs;
  
};

#endif // NEURON_H
