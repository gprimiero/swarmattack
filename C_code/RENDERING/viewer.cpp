#include "viewer.h"

Viewer::Viewer(QWidget *parent, Experiment *_exp, int argc, char** argv )
: QGLViewer()
{
  exp = _exp;
  //glutInit(&argc, argv);
  Xcam  = 0.0;
  Ycam  = 1.0;
  Zcam  = 3.0;
  theta = 0.0;
  phi   = -100.0;
}


Viewer::~Viewer()
{
  delete[] exp;
}

//void Viewer::init()
//{
  // //  resizeGL(200, 200);
  // glClearColor(0.0, 0.0, 0.0, 0.0);
  // //glClearDepth(0.0);
  // glClear(GL_COLOR_BUFFER_BIT );//| GL_DEPTH_BUFFER_BIT );
  // glFlush();
  // //setGridIsDrawn();
  // setSceneRadius( 3.0 );//300 cm
  // setSceneCenter(Vec(0.0, 0.0, 0.0) );
  // //showEntireScene();
  
  // camera()->setPosition(Vec(Xcam,Ycam,Zcam));
  // //camera()->setPosition(Vec(0,100,200));
  // //theta rotates the Camera around its Y axis\, and then phi rotates it around its X axis.
  // //float theta=M_PI, phi=(3.0*M_PI)/2.0;
  // //camera()->setOrientation(theta, phi );
  // camera()->setOrientation(theta, phi);

  // //initialiser le ciel
  // // mySky.LoadTexture( SKY_FRONT, "/Users/eliotuci/Simulations/epuck_aggregation/bin/sky.jpg" );
  // // mySky.LoadTexture( SKY_BACK, "/Users/eliotuci/Simulations/epuck_aggregation/bin/ground.jpg" );
  // // mySky.LoadTexture( SKY_RIGHT,"/Users/eliotuci/Simulations/epuck_aggregation/binbrick.jpg" );
  // // mySky.LoadTexture( SKY_LEFT, "/Users/eliotuci/Simulations/epuck_aggregation/bin/sky.jpg" );
  // // mySky.LoadTexture( SKY_TOP, "/Users/eliotuci/Simulations/epuck_aggregation/bin/sky.jpg" );
  // // mySky.LoadTexture( SKY_BOTTOM, "/Users/eliotuci/Simulations/epuck_aggregation/bin/brick.jpg" );
  
  // /* turn on default lighting */
  // glEnable(GL_LIGHTING);
  // glEnable(GL_LIGHT0);
  // GLfloat ambient[] = { 0.5f, 0.5f, 0.5f };
  // GLfloat diffuse[] = { 0.5f, 0.5f, 0.5f , 0.0f};
  // GLfloat specular[] = { 0.25f, 0.25f, 0.25f , 0.0f};
  // //GLfloat lightcolor[] = { 0.8, 0.8, 0.8 };
  
  // glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
  // glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
  // glLightfv(GL_LIGHT0, GL_SPECULAR, specular);  
  
//}


void Viewer::paintEvent(QPaintEvent *event){
  //create a QPainter and pass a pointer to the device.
  //A paint device can be a QWidget, a QPixmap or a QImage
  QPainter painter(this);

  int size = 13;
  int world_x_dim = exp->get_parameters()->getWorldDimensions()[0];
  int world_y_dim = exp->get_parameters()->getWorldDimensions()[0];
  //a simple line
  QPen myPen(Qt::red, 1, Qt::SolidLine);
  painter.setPen(myPen);
  for(int x = 1; x <= world_x_dim; x++){
    painter.drawLine(x*size,size,x*size, world_x_dim*size);
    painter.drawLine(size, x*size,world_x_dim*size, x*size);
  }

  for(int x = 1; x <= world_x_dim; x++){
    for(int y = 1; y <= world_y_dim; y++){
      painter.setBrush(QBrush(Qt::black, Qt::SolidPattern));
      QRectF rectangle(x*size, y*size, size, size );
      painter.drawRect( rectangle );
    }
  }
  
  for(int i = 0; i < exp->get_agents().size(); i++){
    if(exp->get_agents()[i]->get_knowledge()[0] ==0){
      if( exp->get_agents()[i]->getStatus()=="no_fixed")
	painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));
      else
	painter.setBrush(QBrush(QColor(100,100,100), Qt::SolidPattern));
    }
    else if(exp->get_agents()[i]->get_knowledge()[0]==1)
      if( exp->get_agents()[i]->getStatus()=="fixed")
	painter.setBrush(QBrush(QColor(0,255, 0), Qt::SolidPattern));
      else
	painter.setBrush(QBrush(Qt::green, Qt::SolidPattern));
    else if(exp->get_agents()[i]->get_knowledge()[0] == -1 )
      painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));
    QRectF rectangle( (1+exp->get_agents()[i]->get_pos()[0])*size, (1+exp->get_agents()[i]->get_pos()[1])*size, size, size );
    painter.drawRect( rectangle );
    //cerr << " Agent["<<i<<"] X = " << exp->get_agents()[i]->get_pos()[0]
    //	 << " Agent["<<i<<"] Y = " << exp->get_agents()[i]->get_pos()[1] << endl;

  }    
    
    //update();
}

//void Viewer::draw()
//{

  // GLfloat lightpos[] = { 0.0, 0.0, 7.0, 1.0 };
    // glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
    // glColor3f(0.0, 0.0, 0.0);

    
    // glColor3f(1.0, 0.0, 0.0);
    // for (int x = 0; x < 10; x++){
    //   glBegin(GL_LINES);
    //   glVertex2f(x, x);
    //   glVertex2f(x, 100);
    //   glEnd();
    // }

    
    // glFlush();  // Render now

 

    
    /*exp->getPlane()[0]->render();
    for(int r = 0; r < exp->getAgents().size(); r++ ){
      exp->getAgents()[r]->render( );
    }
    
    for(int ob = 0; ob < exp->getObjects().size(); ob++){
      if( !exp->getObjects()[ob]->is_removed() )
    	exp->getObjects()[ob]->render( );
	}*/
//}
