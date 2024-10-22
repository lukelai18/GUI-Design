//  Copyright (c) 2022 Daniel Moreno. All rights reserved.
//

#pragma once

#include <wx/app.h>

#include "MainWindow.hpp"

namespace course
{
  class App : public wxApp
  {
    MainWindow* window_;
  public:
    App();
    virtual ~App();

    virtual bool OnInit() override;

    MainWindow& window() { return *window_; }
  };

  wxDECLARE_APP(App); //declares: wxGetApp()
}