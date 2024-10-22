//  Copyright (c) 2022 Daniel Moreno. All rights reserved.
//

#include "CanvasGL.hpp"

#include <wx/frame.h>
#include <wx/dcclient.h>
#include <wx/dc.h>

#include "App.hpp"

#include <stdexcept>

namespace course
{
  CanvasGL::CanvasGL(wxWindow* parent) :
    wxGLCanvas{ parent },
    context_{ std::make_unique<wxGLContext>(this) }
  {
    Bind(wxEVT_PAINT, &CanvasGL::onPaint, this);

    // To avoid flashing on MSW
    SetBackgroundStyle(wxBG_STYLE_CUSTOM);
  }

  void CanvasGL::onPaint(wxPaintEvent& event)
  {
    render();
  }

  void CanvasGL::initGL()
  {
    static bool initDone{ false };
    if (!initDone)
    {
      //background color
      glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

      //depth
      glEnable(GL_DEPTH_TEST);

      //shading model
      glShadeModel(GL_SMOOTH);

      //lighting
      glEnable(GL_LIGHTING);
      glEnable(GL_LIGHT0);
      GLfloat al[] = { 0.2, 0.2, 0.2, 1.0 };
      glLightModelfv(GL_LIGHT_MODEL_AMBIENT, al);
      glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

      //add one light
      GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
      GLfloat light_diffuse[] = { 0.6, 0.6, 0.6, 1.0 };
      GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
      GLfloat light_position[] = { -1.0, 1.0, -1.0, 0.0 };
      glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
      glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
      glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
      glLightfv(GL_LIGHT0, GL_POSITION, light_position);

      initDone = true;
    }
  }

  void CanvasGL::configureViewport(int x1, int y1, int x2, int y2)
  {
    initGL();

    //make the viewport occupy the whole canvas
    const wxSize canvasSize{ GetSize() };
    glViewport(0, 0, canvasSize.x, canvasSize.y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //set the projection transformation
    glOrtho(x1, x2, y1, y2, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
  }

  void CanvasGL::render()
  {
    if (!IsShown())
    {
      return;
    }

    wxGLCanvas::SetCurrent(*context_);
    wxPaintDC(this);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // ----------------- draw --------------------
    configureViewport(-1, 1, -1 , 1);
    glLoadIdentity();

    drawParticle();

    //--------------------------------------------
    glFlush();
    SwapBuffers();
  }

  void CanvasGL::drawSphere(
    float cx, float cy, float cz, float r, int lats, int longs)
  {
    for (int i = 0; i <= lats; i++)
    {
      double lat0 = M_PI * (-0.5 + (double)(i - 1) / lats);
      double z0 = sin(lat0);
      double zr0 = cos(lat0);

      double lat1 = M_PI * (-0.5 + (double)i / lats);
      double z1 = sin(lat1);
      double zr1 = cos(lat1);

      glBegin(GL_QUAD_STRIP);
      for (int j = 0; j <= longs; j++)
      {
        double lng = 2 * M_PI * (double)(j - 1) / longs;
        double x = cos(lng);
        double y = sin(lng);

        glNormal3f(x * zr0, y * zr0, z0);
        glVertex3f(r * x * zr0 + cx, r * y * zr0 + cy, r * z0 + cz);
        glNormal3f(x * zr1, y * zr1, z1);
        glVertex3f(r * x * zr1 + cx, r * y * zr1 + cy, r * z1 + cz);
      }
      glEnd();
    }
  }

  void CanvasGL::drawParticle()
  {
    glColor4f(0.1f, 1.0f, 0.0f, 1.0f); //change color if desired :-)
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_DIFFUSE);

    //TODO: draw particle at correct position

    const Simulation& simulation{ wxGetApp().simulation() };
    const float x{ static_cast<float>(simulation.position().x())};
    const float y{ static_cast<float>(simulation.position().y()) };
    const float r{ static_cast<float>(simulation.radius()) };
    drawSphere(x, y, 0, r);


    glDisable(GL_COLOR_MATERIAL);
  }
}