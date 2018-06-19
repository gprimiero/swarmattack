#ifndef _FIRST_EXPERIMENT_
#define _FIRST_EXPERIMENT_

#include "experiment.h"

class First_experiment : public Experiment
{
 private:
  vector < vector <int> > neighbors;
  
 public:
  First_experiment( Parameters* params );
  virtual ~First_experiment();


  void init_evaluations_loop              ( void );
  void init_single_evaluation             ( void );
  bool stop_iterations_loop               ( void );
  bool stop_evaluations_loop              ( void );
  void finalise_single_evaluation         ( void );
  void finalise_evaluation_loop           ( void );

  void evaluate_solutions                 ( void );
  void adv                                ( void );
  void set_agents_position                ( void );

  void update_communication               ( void );
  void inter_agents_communication         ( void );
};
#endif
