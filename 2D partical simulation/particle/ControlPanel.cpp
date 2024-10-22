//  Copyright (c) 2022 Daniel Moreno. All rights reserved.
//

#include "ControlPanel.hpp"
#include "App.hpp"

namespace course
{
  enum ControlPanelIds
  {
    ControlPanel_StartId = 2000,

    ID_ButtonStart,
    ID_ButtonStop,
    ID_ButtonNext,
    ID_ButtonReset,  
  };

  ControlPanel::ControlPanel(wxWindow* parent) :
    wxPanel{ parent }
  {
    //create a vertical box sizer to stack children vertically
    wxBoxSizer* vBox{ new wxBoxSizer{wxVERTICAL} };

    //start button
    startButton_ = new wxButton{this,ID_ButtonStart,"Start"};
    Bind(wxEVT_BUTTON, &ControlPanel::onStartButtonClick, this, ID_ButtonStart);
    vBox->Add(startButton_,0,wxEXPAND);

    //stop button
    stopButton_ = new wxButton{ this,ID_ButtonStop,"Stop" };
    Bind(wxEVT_BUTTON, &ControlPanel::onStopButtonClick, this, ID_ButtonStop);
    vBox->Add(stopButton_, 0, wxEXPAND);
    
    //next button
    nextButton_ = new wxButton{this,ID_ButtonNext,"Next"};
    Bind(wxEVT_BUTTON,&ControlPanel::onNextButtonClick,this, ID_ButtonNext);
    vBox->Add(nextButton_, 0, wxEXPAND);

    //reset button
    resetButton_ = new wxButton{ this, ID_ButtonReset, "Reset" };
    Bind(wxEVT_BUTTON, &ControlPanel::onResetButtonClick, this, ID_ButtonReset);
    vBox->Add(resetButton_, 0, wxEXPAND);

    //parameters group
    {
      paramsBox_ = new wxStaticBox{ this, wxID_ANY, "Parameters" };
      wxStaticBoxSizer* staticBoxSizer{ new wxStaticBoxSizer{paramsBox_, wxVERTICAL} };

      constexpr int rows{ 4 };
      constexpr int cols{ 2 };
      constexpr int vGap{ 4 };
      constexpr int hGap{ 8 };
      wxFlexGridSizer* fgs = new wxFlexGridSizer{rows, cols, vGap, hGap};

      //Velocity X label
      wxStaticText* velocity_x_label{ new wxStaticText{paramsBox_, wxID_ANY, "Start Velocity X:"} };
      velocity_x_ = new wxTextCtrl{ paramsBox_, wxID_ANY, "0.000000",
        wxDefaultPosition, wxDefaultSize, wxTE_RIGHT };
      fgs->Add(velocity_x_label);
      fgs->Add(velocity_x_, 1, wxEXPAND);

      //Velocity Y label
      wxStaticText* velocity_y_label{ new wxStaticText{paramsBox_, wxID_ANY, "Start Velocity Y:"} };
      velocity_y_ = new wxTextCtrl{ paramsBox_, wxID_ANY, "0.000000",
  wxDefaultPosition, wxDefaultSize, wxTE_RIGHT };
      fgs->Add(velocity_y_label);
      fgs->Add(velocity_y_, 1, wxEXPAND);

      //Radius_label
      wxStaticText* radius_label{ new wxStaticText{paramsBox_, wxID_ANY, "Radius:"} };
      radius_ = new wxTextCtrl{ paramsBox_, wxID_ANY, "0.100000",
        wxDefaultPosition, wxDefaultSize, wxTE_RIGHT };
      fgs->Add(radius_label);
      fgs->Add(radius_, 1, wxEXPAND);

      //Collision_label
      wxStaticText* collision_label{ new wxStaticText{paramsBox_, wxID_ANY, "Collision:"} };
      collision_ = new wxTextCtrl{ paramsBox_, wxID_ANY, "0.900000",
        wxDefaultPosition, wxDefaultSize, wxTE_RIGHT };
      fgs->Add(collision_label);
      fgs->Add(collision_, 1, wxEXPAND);
      fgs->AddGrowableCol(1, 1);

      staticBoxSizer->Add(fgs);
      vBox->Add(staticBoxSizer, 0, wxEXPAND);
    }

    SetSizer(vBox);

    //update event
    Bind(wxEVT_UPDATE_UI, &ControlPanel::onUpdateUI, this);

    SetMinSize(wxSize{ 200,-1 });
    SetMaxSize(wxSize{ 400,-1 });
  }

  ControlPanel::~ControlPanel()
  {

  }

  void ControlPanel::onUpdateUI(wxUpdateUIEvent& event)
  {
    MainWindow& mainWindow{ wxGetApp().mainWindow() };
    resetButton_->Enable(!mainWindow.isSimulationRunning());
    paramsBox_->Enable(!mainWindow.isSimulationRunning());
  }

  void ControlPanel::onStartButtonClick(wxCommandEvent& event)
  {
      wxGetApp().mainWindow().simulationStart();
  }

  void ControlPanel::onStopButtonClick(wxCommandEvent& event)
  {
      wxGetApp().mainWindow().simulationStop();
  }

  void ControlPanel::onNextButtonClick(wxCommandEvent& event)
  {
      wxGetApp().mainWindow().simulationOneStep();
  }

  void ControlPanel::onResetButtonClick(wxCommandEvent& event)
  {
    wxGetApp().mainWindow().simulationReset();
  }

  Vector2d ControlPanel::velocity() const
  {
      double velocity_x{ std::stod(velocity_x_->GetValue().ToStdString()) };
      double velocity_y{ std::stod(velocity_y_->GetValue().ToStdString()) };
      return { velocity_x,velocity_y };
  }

  double ControlPanel::radius() const
  {
      double radius{ std::stod(radius_->GetValue().ToStdString()) };
      return radius;
  }

  double ControlPanel::collision() const
  {
      double collision{ std::stod(collision_->GetValue().ToStdString()) };
      return collision;
  }
}