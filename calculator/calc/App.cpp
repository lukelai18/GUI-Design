//  Copyright (c) 2022 Daniel Moreno. All rights reserved.
//

#include "App.hpp"

namespace course
{
  wxIMPLEMENT_APP_NO_MAIN(App);

  App::App() :
    wxApp{},
    window_{ nullptr }
  {

  }

  App::~App()
  {
    //NOTE: `window_` is deleted by wxWidgets when closed
  }

  bool App::OnInit()
  {
    window_ = new MainWindow{};
    return true;
  }
}

//Allows to define a /SUBSYSTEM:CONSOLE application on Windows
int main(int argc, char* argv[])
{
  return wxEntry(argc, argv);
}