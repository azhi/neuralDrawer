#include "neuron.h"

Neuron::Neuron(Bounds bounds)
{
  coeffs = new Extended_array<double>(bounds);
}

double Neuron::get_result_sum(Field* field)
{
  double res = 0.0f;
  for (int i = field->bounds.min_x; i <= field->bounds.max_x; ++i)
    for (int j = field->bounds.min_y; i <= field->bounds.max_y; ++j)
      if ( field->get_pixel(i, j) )
        res += coeffs->get_element_at(i, j);
  return res;
}

void Neuron::correct_answer(Field* field)
{
  for (int i = coeffs->bounds.min_x; i <= coeffs->bounds.max_x; ++i)
    for (int j = coeffs->bounds.min_y; i <= coeffs->bounds.max_y; ++j)
      if ( field->get_pixel(i, j) )
        coeffs->set_element_at(i, j, (coeffs->get_element_at(i, j) + 1) / 2.0f);
      else
        coeffs->set_element_at(i, j, coeffs->get_element_at(i, j) / 2.0f);
}
