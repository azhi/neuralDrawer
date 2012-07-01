#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include "neuron.h"

struct Decision
{
  int dx, dy;
  Decision(int dx, int dy) : dx(dx), dy(dy) {}
}

class Neural_network
{
public:
  Neural_network(Bounds bounds);
  Decision make_decision(Field* field, bool do_correction, Decision rigth_answer);

private:
  Neuron neurons[8];
  
};

#endif // NEURAL_NETWORK_H