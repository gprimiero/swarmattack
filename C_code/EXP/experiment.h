#ifndef _EXPERIMENT_
#define _EXPERIMENT_

#include "../MISC/parameters.h"

//World
#include "../WORLD/agents.h"

class Experiment {
  
 private:
 protected:
  unsigned int m_evaluation;
  unsigned int m_iteration;
  
  Parameters *m_parameters;

  vector < Agents* >  agent;

 public:
  Experiment( Parameters* params );
  virtual ~Experiment();


  virtual void init_evaluations_loop      ( void ) = 0;
  virtual void init_single_evaluation     ( void ) = 0;
  virtual bool stop_evaluations_loop      ( void ) = 0;
  virtual bool stop_iterations_loop       ( void ) = 0;
  virtual void finalise_single_evaluation ( void ) = 0;
  virtual void finalise_evaluation_loop   ( void ) = 0;  
  virtual void evaluate_solutions         ( void ) = 0;
  virtual void adv                        ( void ) = 0;
  virtual void set_agents_position        ( void ) = 0;

  inline std::vector< Agents* > get_agents ( void ) { return agent; }
  inline Parameters* get_parameters       ( void ) { return m_parameters; }
    
  inline unsigned int getEvaluation       ( void ) const { return m_evaluation; }
  inline unsigned int getIteration        ( void ) const { return m_iteration; }
  
  void runOneGeneration                   ( void );
  void init_agents                        ( void );
  
};
#endif
