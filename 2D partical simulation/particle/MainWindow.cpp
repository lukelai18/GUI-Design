//  Copyright (c) 2022 Daniel Moreno. All rights reserved.
//

#include "MainWindow.hpp"
#include "App.hpp"

namespace course
{
  enum MenuWindowIds
  {
    MenuWindow_StartId = 1000,

    ID_SimulationStart,
    ID_SimulationStop,
    ID_SimulationReset,
  };

  MainWindow::MainWindow() :
    wxFrame{
      NULL,
      wxID_ANY,
      "Particle Simulation",
      wxDefaultPosition,
      wxSize{600, 400},
      wxDEFAULT_FRAME_STYLE | wxMINIMIZE_BOX },
    menuFile_{ new wxMenu{} },
    menuSimulation_{ new wxMenu{} },
    menuHelp_{ new wxMenu{} },
    canvas_{ new CanvasGL{ this } },
    control_{ new ControlPanel{ this } },
    updateMilliseconds_{ 10 },
    running_{ false },
    timer_{ std::make_unique<wxTimer>(this) }
  {
    // Create a menu bar for the frame
    menuFile_->Append(wxID_EXIT, wxGetStockLabel(wxID_EXIT), "Quits the application");

    menuSimulation_->Append(ID_SimulationStart, "St&art", "Start simulation");
    menuSimulation_->Append(ID_SimulationStop, "St&op", "Stop simulation");
    menuSimulation_->Append(ID_SimulationReset, "R&eset", "Reset simulation");

    menuHelp_->Append(wxID_ABOUT, wxGetStockLabel(wxID_ABOUT), "Displays the program information");

    wxMenuBar* menuBar{ new wxMenuBar{} };
    menuBar->Append(menuFile_, "&File");
    menuBar->Append(menuSimulation_, "&Simulation");
    menuBar->Append(menuHelp_, "&Help");

    SetMenuBar(menuBar);

    //menu event handlers
    Bind(wxEVT_MENU, &MainWindow::onExit, this, wxID_EXIT);
    Bind(wxEVT_MENU, &MainWindow::onAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MainWindow::onSimulationStart, this, ID_SimulationStart);
    Bind(wxEVT_MENU, &MainWindow::onSimulationStop, this, ID_SimulationStop);
    Bind(wxEVT_MENU, &MainWindow::onSimulationReset, this, ID_SimulationReset);

    //timer event
    Bind(wxEVT_TIMER, &MainWindow::onTimer, this);

    //update event
    Bind(wxEVT_UPDATE_UI, &MainWindow::onUpdateUI, this);

    //status bar
    CreateStatusBar(5);

    // Configure contents
    wxBoxSizer* hbox{ new wxBoxSizer{wxHORIZONTAL } };
    hbox->Add(canvas_, 2, wxSHAPED | wxALIGN_CENTER, 5);
    hbox->Add(control_, 1, wxEXPAND | wxALL, 5);
    SetSizer(hbox);

    // Show the frame
    Centre();
    Show();
  }

  MainWindow::~MainWindow()
  {

  }

  void MainWindow::onExit(wxCommandEvent& event)
  {
    Close();
  }

  void MainWindow::onAbout(wxCommandEvent& event)
  {
    wxMessageBox(
      "Particle Simulation Example (c) 2022\n"
      "by Daniel Moreno <daniel_moreno@brown.edu>",
      "About Particle Simulation");
  }

  void MainWindow::onTimer(wxTimerEvent& event)
  {
    // students must complete...
      simulationOneStep();
  }

  void MainWindow::onSimulationStart(wxCommandEvent& event)
  {
    // students must complete...
      simulationStart();
  }

  void MainWindow::onSimulationStop(wxCommandEvent& event)
  {
    // students must complete...
      simulationStop();
  }

  void MainWindow::onSimulationReset(wxCommandEvent& event)
  {
    // students must complete...
      simulationReset();
  }

  void MainWindow::simulationStart()
  {
    timer_->Start(updateMilliseconds_);
    running_ = true;
  }

  void MainWindow::simulationStop()
  {
    timer_->Stop();
    running_ = false;
  }

  void MainWindow::simulationReset()
  {
    if (running_)
    {
      simulationStop();
    }
    wxGetApp().simulation().reset(
      control_->radius(),
      control_->collision(),
      control_->velocity());
    UpdateWindowUI();
  }

  void MainWindow::simulationOneStep()
  {
    Simulation& simulation{ wxGetApp().simulation() };
    simulation.oneStep();
    if (simulation.running() == false)
    { //stop timer
      simulationStop();
    }
    UpdateWindowUI();
  }

  bool MainWindow::isSimulationRunning() const
  {
    return running_;
  }

  void MainWindow::onUpdateUI(wxUpdateUIEvent& event)
  {
    //update canvas
    canvas_->Refresh();

    //update status bar
    Simulation& simulation{ wxGetApp().simulation() };
    auto disp = [](const Vector2d& v)
    {
      return std::to_string(v.x()) + "," + std::to_string(v.y());
    };
    SetStatusText("P: " + disp(simulation.position()), 0);
    SetStatusText("V: " + disp(simulation.velocity()), 1);
    SetStatusText("E: " + std::to_string(simulation.energy()), 2);
    SetStatusText("Time: " + std::to_string(simulation.time()), 3);
    SetStatusText(running_ ? "RUNNING" : "", 4);

    //enable/disable menu items
    menuSimulation_->Enable(ID_SimulationStart, !isSimulationRunning());
    menuSimulation_->Enable(ID_SimulationStop, isSimulationRunning());
    menuSimulation_->Enable(ID_SimulationReset, !isSimulationRunning());
  }
}