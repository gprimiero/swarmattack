#include "experiment.h"

/* ----------------------------------------------------------------------------------- */

Experiment::Experiment( Parameters* params ){
  m_parameters  = params;
  init_agents( );
}

/* ----------------------------------------------------------------------------------- */

Experiment::~Experiment( void ){

}

/* ----------------------------------------------------------------------------------- */


void Experiment::init_agents( void ){
  for(int i = 0; i < m_parameters->getNbAgentsPerGroup(); i++){
    agent.push_back( new Agents ( m_parameters, vector <int> {0, 0} ) );
    agent.back()->assign_random_position();
    if( i < m_parameters->getInitNbAttacker() )
      agent.back()->set_knowledge( vector<int>{-1}, "fixed" );
    else if( i < (m_parameters->getInitNbAttacker()+m_parameters->getInitNbExplorer()) )
      agent.back()->set_knowledge( vector <int> {1}, "fixed" );
    else if( i < (m_parameters->getInitNbAttacker()+m_parameters->getInitNbExplorer() +m_parameters->getInitNbZeros()) )
      agent.back()->set_knowledge( vector <int> {0}, "fixed" );
    else
      agent.back()->set_knowledge( vector <int> {0}, "no_fixed" );
  }

  
}

/* ------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------- */

void Experiment::runOneGeneration( void ){  
  evaluate_solutions ();
}

/* ------------------------------------------------------------------------------------------------- */
