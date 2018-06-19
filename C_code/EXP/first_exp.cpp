#include "first_exp.h"

/* ----------------------------------------------------------------------------------- */

First_experiment::First_experiment( Parameters* params ) : Experiment ( params ) {
  neighbors.resize( m_parameters->getNbAgentsPerGroup() );
}

/* ----------------------------------------------------------------------------------- */

First_experiment::~First_experiment() {}

/* ----------------------------------------------------------------------------------- */

void First_experiment::evaluate_solutions( void ) {
  init_evaluations_loop( );
  do{//Loop for evaluations for single trial
    init_single_evaluation( );
    do{//This is the loop for the iterations mean simulation steps
      adv();
    }while( stop_iterations_loop( ) );//Untill the last iteration
  }while( stop_evaluations_loop( ) );//Until the last evaluation
}

/* ----------------------------------------------------------------------------------- */

void First_experiment::init_evaluations_loop( ){
  m_evaluation = 0;//This is the counter for the evalutions
}

/* ----------------------------------------------------------------------------------- */

void First_experiment::init_single_evaluation( void ){ 
  m_iteration = 0;
}

/* ----------------------------------------------------------------------------------- */

void First_experiment::set_agents_position( void ){
}

/* ----------------------------------------------------------------------------------- */

void First_experiment::adv ( void ){
  
  if( m_parameters->isModeViewing() ) {
    //cerr << " Gen = " << m_parameters->getCurrentGeneration() << " Eval = " << m_evaluation << " iter = " << m_iteration << endl;
    if( !stop_iterations_loop( ) ){
      exit(0);
    }
  }

  update_communication();
  for(int i = 0; i < agent.size(); i++){
    agent[i]->random_walk();
  }
  
  m_iteration++;
}

/* ----------------------------------------------------------------------------------- */

void First_experiment::inter_agents_communication( void ){
  for(int i = 0; i < agent.size(); i++){
    if( !neighbors[i].empty() ){
      int mate = gsl_rng_uniform_int(GSL_randon_generator::r_rand, neighbors[i].size());
      agent[i]->compute_next_cycle_knowledge( agent[neighbors[i][mate]]->get_knowledge() );
    }
    else{
      //agent[i]->update_memory( vector <int> {0} );
    }
  }
  for(int i = 0; i < agent.size(); i++)
    agent[i]->update_next_cycle_knowledge();
  
}

/* ----------------------------------------------------------------------------------- */

void First_experiment::update_communication( void ){
  for(int i = 0; i < agent.size(); i++){
    neighbors[i].erase ( neighbors[i].begin(), neighbors[i].begin() + neighbors[i].size() );
    neighbors[i].clear();
    if( agent[i]->getStatus() != "fixed" ){
      for(int j = 0; j < agent.size(); j++){
	if( j != i ){
	  //if( find_distance(agent[i]->get_pos(), agent[j]->get_pos() ) < m_parameters->getComm_range() ) {
	  if( agent[i]->get_pos()[0] == agent[j]->get_pos()[0] &&
	      agent[i]->get_pos()[1] == agent[j]->get_pos()[1] ){
	    if( agent[j]->get_knowledge()[0] != 0 ){
	      neighbors[i].push_back(j);
	    }
	  }
	}
      }
    }
  }
  inter_agents_communication();
}

/* ----------------------------------------------------------------------------------- */

bool First_experiment::stop_iterations_loop(void)
{
  if(m_iteration >= m_parameters->getNbMaxIterations() )
    {
      finalise_single_evaluation( );
      m_iteration = 0;
      if( m_parameters->isModeEvolution() || m_parameters->isModeEvaluation() ){
	return false;
      }
      else if ( m_parameters->isModeViewing() ) {
      	if ( stop_evaluations_loop( ) ){
	  return true;
	}
	else{
	  return false;
	}
      }
    }
  else
    return true;
  return true;
}

/* ----------------------------------------------------------------------------------- */

bool First_experiment::stop_evaluations_loop(void)
{
  m_evaluation++;
  if( m_evaluation >= m_parameters->getNbMaxEvaluations() )
    {
      m_evaluation = 0;
      finalise_evaluation_loop( );
      return false;
    }
  else
    return true;
}

/* ----------------------------------------------------------------------------------- */

void First_experiment::finalise_single_evaluation( void ){
  vector <int> hist_prob = {0,0,0,0,0,0,0,0,0,0,0};
  int NbGood=0, NbBad=0,NbNeutral=0, NbZeros=0;
  for(int i = 0; i < agent.size(); i++){
    if( agent[i]->get_knowledge()[0] == 1 )
      NbGood++;
    else if ( agent[i]->get_knowledge()[0] == -1 )
      NbBad++;
    else if ( agent[i]->get_knowledge()[0] == 0 ){
      if( agent[i]->getStatus()=="no_fixed")
	NbNeutral++;
      else
	NbZeros++;
    }
    hist_prob[(int)(floor(agent[i]->get_prob_of_change_knowledge()*10))]++;
  }
  
  char fname[500];
  sprintf(fname, "%s%s.data", m_parameters->getStatsFileDir().c_str(), m_parameters->getRunName().c_str() );
  ofstream out ( fname, ios::app);
  out.setf( ios::fixed );
  out << "" << NbGood << " " << NbBad << " " << NbZeros << " " << NbNeutral;
  for(int i = 0; i < hist_prob.size(); i++){
    out << " " << hist_prob[i];
  }
  out << endl;
  out.close();
  
}

/* ----------------------------------------------------------------------------------- */

void First_experiment::finalise_evaluation_loop( void ){

}


/* ----------------------------------------------------------------------------------- */
