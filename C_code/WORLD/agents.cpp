#include "agents.h"

/* ----------------------------------------------------------------------------------- */

Agents::Agents( Parameters* params, vector <int> pos )
{
  m_parameters               = params;
  m_pos                      = pos;
  m_increasing_factor        = m_parameters->getIncreasingFactor();
  m_decreasing_factor        = m_parameters->getDecreasingFactor();
  m_prob_of_change_knowledge = m_parameters->getInitProbChangeKnowldege();
#ifdef _NOT_PROB_
  clear_memory ();
#endif
}

/* ----------------------------------------------------------------------------------- */

void Agents::clear_memory( void )
{
  m_memory.erase(m_memory.begin(), m_memory.begin() + m_memory.size() );
  m_memory.clear();
}

/* ----------------------------------------------------------------------------------- */

void Agents::assign_random_position( void ){
  m_pos[0] = gsl_rng_uniform_int(GSL_randon_generator::r_rand, m_parameters->getWorldDimensions()[0]);
  m_pos[1] = gsl_rng_uniform_int(GSL_randon_generator::r_rand, m_parameters->getWorldDimensions()[1]);
}

/* ----------------------------------------------------------------------------------- */

void Agents::random_walk            ( void ){

  int stepSize = gsl_rng_uniform_int(GSL_randon_generator::r_rand, m_parameters->getStep_size() );
  int stepDir  = gsl_rng_uniform_int(GSL_randon_generator::r_rand, nb_directions );

  switch( stepDir ){
  case 0 :
    m_pos[0] += stepSize;
    break;
  case 1 :
    m_pos[0] += stepSize;
    m_pos[1] -= stepSize;
    break;
  case 2 :
    m_pos[1] -= stepSize;
    break;
  case 3 :
    m_pos[0] -= stepSize;
    m_pos[1] -= stepSize;
    break;
  case 4 :
    m_pos[0] -= stepSize;
    break;
  case 5 :
    m_pos[0] -= stepSize;
    m_pos[1] += stepSize;
    break;
  case 6 :
    m_pos[1] += stepSize;
    break;
  case 7 :
    m_pos[0] += stepSize;
    m_pos[1] += stepSize;
    break;
  default :
    break;
  }
  if( m_pos[0] >= m_parameters->getWorldDimensions()[0] )
    m_pos[0] = m_pos[0] - m_parameters->getWorldDimensions()[0];
  else if( m_pos[0] < 0 )
    m_pos[0] = m_parameters->getWorldDimensions()[0] + m_pos[0];

  if( m_pos[1] >= m_parameters->getWorldDimensions()[1] )
    m_pos[1] -= m_parameters->getWorldDimensions()[1];
  else if( m_pos[1] < 0 )
    m_pos[1] = m_parameters->getWorldDimensions()[0] + m_pos[1];

  /*  cerr << " In update position "
      << " X " << m_pos[0]
      << " y " << m_pos[1]
      << endl; */
}

/* ----------------------------------------------------------------------------------- */

int Agents::update_knowledge( int item_type, int threshold){
  int counter = 0;
  for(int i = 0; i < m_memory.size(); i++){
    if ( m_memory[i] == item_type ){
      counter++;
      if( counter >= threshold ){
	return item_type;
      }
    }
  }
  return m_knowledge[0];
}

/* ----------------------------------------------------------------------------------- */

int Agents::update_knowledge( const vector <int> item_type ){

  if( m_knowledge[0] == 0 ){
    return item_type[0];
  }
  else{
    if( item_type[0] != m_knowledge[0] ){

      double new_prob_of_change_knowledge = m_prob_of_change_knowledge * m_increasing_factor;
      if( new_prob_of_change_knowledge > 1.0 )
	new_prob_of_change_knowledge = 1.0;

      if( gsl_rng_uniform( GSL_randon_generator::r_rand ) < m_prob_of_change_knowledge ) {
	m_prob_of_change_knowledge = new_prob_of_change_knowledge;
	return item_type[0];
      }
      else{
	m_prob_of_change_knowledge = new_prob_of_change_knowledge;
	return m_knowledge[0];
      }
    }
    else{
      m_prob_of_change_knowledge *= m_decreasing_factor;
      return m_knowledge[0];
    }
  }
}

/* ----------------------------------------------------------------------------------- */

void Agents::update_memory( const vector <int> k ){
  if( m_memory.size() < m_parameters->getMemory_size() )
    m_memory.push_back( k[0] );
  else{
    m_memory.erase(m_memory.begin());
    m_memory.push_back( k[0] );
  }
}

/* ----------------------------------------------------------------------------------- */

void Agents::compute_next_cycle_knowledge( const vector <int> k ){
#ifdef _NOT_PROB_
  update_memory( k );
#endif

#ifdef _NOT_PROB_
  if( m_knowledge[0] == 1){
    m_tmp_knowledge[0]  =  update_knowledge( -1, m_parameters->getThreshold_change_knowledge() );
  }
  else if( m_knowledge[0] == -1){
    m_tmp_knowledge[0]  = update_knowledge( 1, m_parameters->getThreshold_change_knowledge() );
  }
  else if( m_knowledge[0] == 0){
    if( gsl_rng_uniform( GSL_randon_generator::r_rand ) < 0.5 ) {
      m_tmp_knowledge[0] =  update_knowledge( -1, m_parameters->getThreshold_acquire_knowledge() );
      if( m_tmp_knowledge[0] == 0 ){
	m_tmp_knowledge[0] = update_knowledge( 1, m_parameters->getThreshold_acquire_knowledge() );
      }
    }
    else{
      m_tmp_knowledge[0] = update_knowledge( 1, m_parameters->getThreshold_acquire_knowledge() );
      if( m_tmp_knowledge[0] == 0 ){
	m_tmp_knowledge[0] = update_knowledge( -1, m_parameters->getThreshold_acquire_knowledge() );
      }
    }
  }
#else
  m_tmp_knowledge[0]  =  update_knowledge( k );
#endif
}

/* ----------------------------------------------------------------------------------- */

void Agents::update_next_cycle_knowledge( void ){
  if( m_knowledge[0] != m_tmp_knowledge[0] ){
    //clear_memory( );
    m_knowledge[0] = m_tmp_knowledge[0];
  }
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
