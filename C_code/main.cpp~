#include "./MISC/parameters.h"
#include "./EXP/experiment.h"
#include "./EXP/first_exp.h"

#ifdef _GRAPHICS_
#include "./RENDERING/viewer.h"
#include "./RENDERING/interface.h"
#endif

Parameters* parameters;

int main(int argc, char** argv)
{  
  //parse the command line  
  parameters = new Parameters( argc, argv );

  //Init the Experiment
  std::vector< Experiment* > exp;
  exp.push_back(new First_experiment ( parameters ) );
  
  //Evolutionary mode
  if( parameters->isModeEvolution() ){    
    while(parameters->getCurrentGeneration() < parameters->getNbMaxGenerations() )
      {
	exp[0]->runOneGeneration( );
	parameters->increment_current_generation();
      }
  }
  //Viewing mode
  else if( parameters->isModeViewing() ){
#ifdef _GRAPHICS_
    QApplication application(argc, argv);
    Viewer *viewer = new Viewer ( 0, exp[0], argc, argv );
    Interface *render = new Interface( 0, exp[0], viewer );
    render->show();
    return application.exec();
    delete viewer;
    delete render;    
#endif
  }
  //Evaluation mode
  else if( parameters->isModeEvaluation() ){
    
  }

  for(int i = 0; i < exp.size(); i++)
    delete exp[i];
  exp.clear();
  
  delete parameters;
  return 0;
}
