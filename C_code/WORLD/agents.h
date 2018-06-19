#include "../MISC/general.h"
#include "../MISC/parameters.h"

//#define _NOT_PROB_

class Agents 
{
 private:
  Parameters *m_parameters;
  vector <int> m_pos;
  vector <int> m_knowledge;
  vector <int> m_tmp_knowledge;
  vector <int> m_memory;
  static const int  nb_directions = 8;
  string status;
  double m_increasing_factor;
  double m_decreasing_factor;
  double m_prob_of_change_knowledge;
  
 public:
  Agents ( Parameters* params, vector <int> pos );
  ~Agents();
  inline vector <int> get_pos        () const {return m_pos;}
  inline vector <int> get_knowledge  () const {return m_knowledge;}
  inline void set_knowledge ( vector <int> k, string s) {
    m_knowledge = k;
    m_tmp_knowledge  = m_knowledge;
    status = s;
  }
  inline string getStatus             ( void ) const { return status;}
  inline void   setStatus             ( const string s ) { status = s;}
  
  void assign_random_position         ( void );
  void random_walk                    ( void );
  void update_next_cycle_knowledge    ( void );
  void compute_next_cycle_knowledge   ( const vector <int> k );
  void clear_memory                   ( void );
  void update_memory                  ( const vector <int> k );
  int  update_knowledge               ( int item_type, int threshold);
  int  update_knowledge               (  const vector <int> k );
  double get_increasing_factor        ( void ) { return m_increasing_factor;}
  double get_decreasing_factor        ( void ) { return m_decreasing_factor;} 
  double get_prob_of_change_knowledge ( void ) { return m_prob_of_change_knowledge;}
};
