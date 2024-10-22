//  Copyright (c) 2022 Daniel Moreno. All rights reserved.
//

#pragma once

#include <wx/wx.h>

#include "CanvasGL.hpp"
#include "ControlPanel.hpp"

#include <memory>

namespace course
{
  class MainWindow : public wxFrame
  {
  public:
    MainWindow();

    virtual ~MainWindow();

    //simulation controls
    void simulationStart();
    void simulationStop();
    void simulationReset();
    void simulationOneStep();
    bool isSimulationRunning() const;

  private:
    void onExit(wxCommandEvent& event);
    void onAbout(wxCommandEvent& event);
    void onSimulationStart(wxCommandEvent& event);
    void onSimulationStop(wxCommandEvent& event);
    void onSimulationReset(wxCommandEvent& event);

    void onUpdateUI(wxUpdateUIEvent& event);

    void onTimer(wxTimerEvent& event);

    //member variables
    wxMenu* menuSimulation_;
    wxMenu* menuFile_;
    wxMenu* menuHelp_;

    CanvasGL* canvas_;
    ControlPanel* control_;
    int updateMilliseconds_;
    bool running_;

    std::unique_ptr<wxTimer> timer_;
  };
}