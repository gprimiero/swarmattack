#ifndef _PARAMETERS_
#define _PARAMETERS_

#include "general.h"
#include <algorithm>

class Parameters
{
  
 private:
  
  unsigned int  m_currentGeneration;

  /* parameters read from file init_run.txt */
  unsigned int  m_nbMaxGenerations;
  unsigned int  m_nbMaxEvaluations;
  unsigned int  m_nbMaxIterations;
  
  unsigned int  m_nbAgentsPerGroup;
  unsigned int  m_dumpStatsEvery;
  std::string   m_statsFileDir;
  vector <int>  m_worldDimensions;
  int           m_initNbAttacker;
  int           m_initNbExplorer;
  int           m_initNbZeros;
  int           m_memory_size;
  int           m_threshold_change_knowledge;
  int           m_threshold_acquire_knowledge;
  int           m_step_size;
  int           m_comm_range;
  double        increasing_factor;
  double        decreasing_factor;
  double        init_prob_change_knowldege;
  /* ---------------------------------- */

  /* parameters from command line at run time*/
  unsigned long m_rootSeed;
  bool m_mode_evolution;
  bool m_mode_viewing;
  bool m_mode_evaluation;
  std::string   m_runName;
  /* ---------------------------------- */
  
 public:
  Parameters ( int argc, char** argv );
  ~Parameters();
  void usage ( void );
  void parse_command_line( int argc, char** argv );
  void read_run_parameter_file( void );
  void init_random_generator( void );
  void reset_seed( void );
  void dump_simulation_seed( void );
  char* getCmdOption(char ** begin, char ** end, const std::string & option);
  bool cmdOptionExists(char** begin, char** end, const std::string& option);

  inline void increment_current_generation( void ) { m_currentGeneration++; }
  
  // Accessors
  inline void setRunName                    ( char* runName )    { m_runName = runName; }
  inline void setCurrentGeneration          ( const int v )      { m_currentGeneration = v; } 

  inline bool isModeEvolution                         () const { return m_mode_evolution;}
  inline bool isModeViewing                           () const { return m_mode_viewing;}
  inline bool isModeEvaluation                        () const { return m_mode_evaluation;}
  
  inline unsigned int  getCurrentGeneration           () const { return m_currentGeneration; } 
  inline unsigned long getRootSeed                    () const { return m_rootSeed; }
  inline unsigned int  getNbAgentsPerGroup            () const { return m_nbAgentsPerGroup; }
  inline unsigned int  getNbMaxGenerations            () const { return m_nbMaxGenerations; }
  inline unsigned int  getNbMaxEvaluations            () const { return m_nbMaxEvaluations; }
  inline unsigned int  getNbMaxIterations             () const { return m_nbMaxIterations; }
  
  inline std::string   getRunName                     () const { return m_runName; }
  inline unsigned int  getDumpStatsEvery              () const { return m_dumpStatsEvery;}
  inline std::string   getStatsFileDir                () const { return m_statsFileDir;}
  inline std::vector <int> getWorldDimensions         () const { return m_worldDimensions;}
  inline int           getInitNbAttacker              () const { return m_initNbAttacker;}
  inline int           getInitNbExplorer              () const { return m_initNbExplorer;}
  inline int           getInitNbZeros                 () const { return m_initNbZeros;}
  inline int           getMemory_size                 () const { return m_memory_size;}
  inline int           getThreshold_change_knowledge  () const { return m_threshold_change_knowledge;}
  inline int           getThreshold_acquire_knowledge () const { return m_threshold_acquire_knowledge;}
  inline int           getStep_size                   () const { return m_step_size;}
  inline int           getComm_range                  () const { return m_comm_range; }
  inline double        getIncreasingFactor            () const { return increasing_factor;}
  inline double        getDecreasingFactor            () const { return decreasing_factor;}
  inline double        getInitProbChangeKnowldege     () const { return init_prob_change_knowldege;}
};
#endif
