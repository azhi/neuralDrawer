#ifndef NEURON_H
#define NEURON_H

#include "coeffs_list.h"
#include "field.h"

class Neuron
{
public:
  Neuron(Bounds bounds, int id);
  ~Neuron();
  double get_result_sum(Field* field, long count);
  void correct_answer(Field* field, long count);
  void load_cache();
  void save_cache();
  
private:
  Coeffs_list<double>* coeffs;
  int id;
  
};

#endif // NEURON_H
