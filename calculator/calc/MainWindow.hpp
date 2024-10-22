//  Copyright (c) 2022 Daniel Moreno. All rights reserved.
//

#pragma once

#include <wx/wx.h>

namespace course
{
  class MainWindow : public wxFrame
  {
#ifdef _MSC_VER
    //Windows settings
    static constexpr int minWidth{ 540 };
    static constexpr int minHeight{ 440 };
    static constexpr int fontSize{ 24 };
#else
    static constexpr int minWidth{ 400 };
    static constexpr int minHeight{ 200 };
    static constexpr int fontSize{ 18 };
#endif

  public:
    MainWindow();

    virtual ~MainWindow();

  private:
    wxTextCtrl* display_;

    //Students may use the following member variables in their implementation
    // if choose so.
    //
    enum class Operator{ None, Add, Sub, Mul, Div };
    Operator operator_=Operator::None;
    double result_=0.0;
    //bool editing_;
    int NumOfDot = 0;
    bool OperFlag = false; //Judge whether there are operators
    bool ValidOpe = false; //Judge whether there are numbers previous to the operator
    bool ResultFlag = false;
    double op1 = 0;
    double op2 = 0;

    //menu event handlers
    void onExit(wxCommandEvent& event);
    void onAbout(wxCommandEvent& event);
    void onStudentAbout(wxCommandEvent& event);  //To handle to event in about student
    //TODO: add additional menu event handlers...

    //button event handlers
    void onButton0Click(wxCommandEvent& event);
    void onButton1Click(wxCommandEvent& event);
    void onButton2Click(wxCommandEvent& event);
    void onButton3Click(wxCommandEvent& event);
    void onButton4Click(wxCommandEvent& event);
    void onButton5Click(wxCommandEvent& event);
    void onButton6Click(wxCommandEvent& event);
    void onButton7Click(wxCommandEvent& event);
    void onButton8Click(wxCommandEvent& event);
    void onButton9Click(wxCommandEvent& event);

    void onButtonClearClick(wxCommandEvent& event);
    void onButtonDelClick(wxCommandEvent& event);
    void onButtonDivClick(wxCommandEvent& event);
    void onButtonMulClick(wxCommandEvent& event);
    void onButtonSubClick(wxCommandEvent& event);
    void onButtonAddClick(wxCommandEvent& event);
    void onButtonEqualClick(wxCommandEvent& event);
    void onButtonDotClick(wxCommandEvent& event);
    void onButtonSignClick(wxCommandEvent& event);
    //TODO: add additional button event handlers...

  };
}
