#include "neural_network.h"

Neural_network::Neural_network(Bounds bounds)
{
  for (int i = 0; i < 8; ++i)
    neurons[i] = new Neuron(bounds, i);
}

void Neural_network::load_cache()
{
  for (int i = 0; i < 8; ++i)
    neurons[i]->load_cache();
}

void Neural_network::save_cache()
{
  for (int i = 0; i < 8; ++i)
    neurons[i]->save_cache();
}

Decision Neural_network::make_decision(Field* field, bool do_correction, Decision* rigth_answer)
{
  double result_sums[8];
  printf("Result sums: ");
  for (int i = 0; i < 8; ++i)
  {
    result_sums[i] = neurons[i]->get_result_sum(field);
    printf("%lf ", result_sums[i]);
  }
  printf("\n");
  double max_sum = 0.0f; int max_sum_index = 0;
  for (int i = 0; i < 8; ++i)
    if ( result_sums[i] > max_sum )
    {
      max_sum = result_sums[i];
      max_sum_index = i;
    }
    
  Decision res;
  printf("Choose: %d %lf\n", max_sum_index, max_sum);
  switch (max_sum_index)
  {
    case 0: res.dx = -1; res.dy = -1; break;
    case 1: res.dx = -1; res.dy = 0; break;
    case 2: res.dx = -1; res.dy = 1; break;
    case 3: res.dx = 0; res.dy = 1; break;
    case 4: res.dx = 1; res.dy = 1; break;
    case 5: res.dx = 1; res.dy = 0; break;
    case 6: res.dx = 1; res.dy = -1; break;
    case 7: res.dx = 0; res.dy = -1; break;
  }
  
  if ( do_correction && ( res.dx != rigth_answer->dx || res.dy != rigth_answer->dy ) )
  {
    if ( rigth_answer->dx == -1 )
    {
      if ( rigth_answer->dy == -1 )
        neurons[0]->correct_answer(field);
      else if ( rigth_answer->dy == 0 )
        neurons[1]->correct_answer(field);
      else if ( rigth_answer->dy == 1 )
        neurons[2]->correct_answer(field);
    }
    
    if ( rigth_answer->dx == 0 )
    {
      if ( rigth_answer->dy == -1 )
        neurons[7]->correct_answer(field);
      else if ( rigth_answer->dy == 1 )
        neurons[3]->correct_answer(field);
    }
    
    if ( rigth_answer->dx == 1 )
    {
      if ( rigth_answer->dy == -1 )
        neurons[6]->correct_answer(field);
      else if ( rigth_answer->dy == 0 )
        neurons[5]->correct_answer(field);
      else if ( rigth_answer->dy == 1 )
        neurons[4]->correct_answer(field);
    }
  }
  
  return res;
}
