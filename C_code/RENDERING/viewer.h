#ifndef VIEWER_H
#define VIEWER_H

#include <OpenGL/gl.h> // use this on my mac
#include <OpenGL/glu.h> // use this on my mac
#include <GLUT/glut.h> // use this on my mac

//#include <GL/glut.h> // use this on rooster
//#include <GL/glu.h> // use this on rooster
#include <QApplication>
//#include <QtOpenGL/QGLWidget>
//#include <QWidget>
//#include <QtOpenGL/QtOpenGL>
//#include <QtOpenGL/QGLFormat>

#include <QGLViewer/qglviewer.h>
//#if QT_VERSION >= 0x040000
//#include <QKeyEvent>
//#endif

#include "../MISC/general.h"
#include "../EXP/experiment.h"
//#include "../WORLD/simple_agents.h"
//#include "../WORLD/simple_objects.h"

using namespace qglviewer;

class Viewer : /*public QGLWidget*/ public QGLViewer
{
 protected:
  
  Q_OBJECT;
 public:
  Viewer(QWidget *parent, Experiment *_exp, int argc, char** argv  );
  virtual ~Viewer();

  Experiment *exp;
  
 protected:
  //virtual void init();
  //virtual void draw();
  
 private:
  unsigned char *pRGB;
  double Xcam,Ycam,Zcam,theta,phi;
  //double viewangle;

  //void paintEvent(QPaintEvent *event);
  void paintEvent(QPaintEvent *event) override;

};

#endif
