//  Copyright (c) 2022 Daniel Moreno. All rights reserved.
//

#pragma once

#include <wx/wx.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/tglbtn.h>

#include "Vector2d.hpp"

namespace course
{
  class ControlPanel : public wxPanel
  {
  public:
    ControlPanel(wxWindow* parent);
    virtual ~ControlPanel();

    //Parameters getters
    Vector2d velocity() const;
    double radius() const;
    double collision() const;

  private:
    void onUpdateUI(wxUpdateUIEvent& event);
    void onStartButtonClick(wxCommandEvent& event);
    void onStopButtonClick(wxCommandEvent& event);
    void onNextButtonClick(wxCommandEvent& event);
    void onResetButtonClick(wxCommandEvent& event);

    wxButton* startButton_;
    wxButton* stopButton_;
    wxButton* nextButton_;
    wxButton* resetButton_;
 
    wxStaticBox* paramsBox_;
    wxTextCtrl* velocity_x_;
    wxTextCtrl* velocity_y_;
    wxTextCtrl* radius_;
    wxTextCtrl* collision_;
  };
}