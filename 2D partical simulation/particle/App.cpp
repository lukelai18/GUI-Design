//  Copyright (c) 2022 Daniel Moreno. All rights reserved.
//

#include "App.hpp"

namespace course
{
  wxIMPLEMENT_APP_NO_MAIN(App);

  App::App() :
    wxApp{}
  {
    //create simulation
      simulation_ = new Simulation; //Initialize a simulation
  }

  App::~App()
  {
    //delete simulation
      delete simulation_;
  }

  bool App::OnInit()
  {
    //create window
      window_ = new MainWindow; //Initialize a window
      return true;
  }

  const Simulation& App::simulation() const
  {
    return *simulation_;
  }

  Simulation& App::simulation()
  {
    return *simulation_;
  }

  const MainWindow& App::mainWindow() const
  {
    return *window_;
  }

  MainWindow& App::mainWindow()
  {
      return *window_;
  }
}

int main(int argc, char* argv[])
{
  return wxEntry(argc, argv);
}