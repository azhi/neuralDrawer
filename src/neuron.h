#ifndef NEURON_H
#define NEURON_H

#include "extended_array.h"
#include "field.h"

class Neuron
{
public:
  Neuron(Bounds bounds);
  long get_result_sum(Field* field)
  void correct_answer();

private:
  Extended_array<int>* coeff;
  
};

#endif // NEURON_H