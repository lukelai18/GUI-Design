//  Copyright (c) 2022 Daniel Moreno. All rights reserved.
//

#pragma once

#include <wx/wx.h>
#include <wx/glcanvas.h>

#include <memory>

namespace course
{
  class CanvasGL : public wxGLCanvas
  {
  public:
    CanvasGL(wxWindow* parent);

  private:
    void onPaint(wxPaintEvent& event);
    void render();
    void initGL();
    void configureViewport(int x1, int y1, int x2, int y2);
    void drawSphere(float cx, float cy, float cz, float r,
                    int lats = 60, int longs = 60);
    void drawParticle();

    std::unique_ptr<wxGLContext> context_;
  };
}