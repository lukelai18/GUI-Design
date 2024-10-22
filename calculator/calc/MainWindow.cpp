//  Copyright (c) 2022 Daniel Moreno. All rights reserved.
//

#include "MainWindow.hpp"

#include "App.hpp"
#include<sstream>

namespace course
{
  enum EventIDs
  {
    //button IDs the buttons in the caculator
    buttonId_0 = 1, //start at 1 because 0 is not supported in Mac OSX
    buttonId_1,
    buttonId_2,
    buttonId_3,
    buttonId_4,
    buttonId_5,
    buttonId_6,
    buttonId_7,
    buttonId_8,
    buttonId_9,

    buttonId_Dot,
    buttonId_Sign,

    buttonId_Clear,
    buttonId_Del,
    buttonId_Add,
    buttonId_Sub,
    buttonId_Mul,
    buttonId_Div,
    buttonId_Eq,

    //menu IDs
    menuId_Student  //uncomment this line to create a menu Id for "About student"

  };

  MainWindow::MainWindow() :
    wxFrame{
      nullptr,
      wxID_ANY,
      "C++ Calculator",
      wxDefaultPosition,
      wxSize{minWidth, minHeight} }
  {
    // Create a menu bar for the frame
    wxMenu* menuFile{ new wxMenu{} }; //For the file
    menuFile->Append(wxID_EXIT, wxGetStockLabel(wxID_EXIT), "Quits the application");

    wxMenu* menuHelp{ new wxMenu{} }; //For the help
    menuHelp->Append(menuId_Student, "&About student...", "Displays the student information");
    menuHelp->AppendSeparator();
    menuHelp->Append(wxID_ABOUT, "&About...", "Displays the program information");

    wxMenuBar* menuBar{ new wxMenuBar{} }; //The name of the menubar
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");

    SetMenuBar(menuBar);

    // Configure contents
    wxFont font{ fontSize, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL };
    wxBoxSizer* sizer{ new wxBoxSizer{wxVERTICAL} };

    display_ = new wxTextCtrl{this, -1, "0", wxPoint{-1, -1}, wxSize{-1, -1}, wxTE_RIGHT | wxTE_READONLY };
    display_->SetFont(font);

    sizer->Add(display_, 0, wxEXPAND | wxTOP | wxBOTTOM, 4);
    wxGridSizer* gs = new wxGridSizer{ 5, 4, 4, 4 };

    //addButton is a lambda function which adds a button with the given
    // text and id
    // Students may use this function if they wish.
    auto addButton = [this, gs, &font](const char* text, int id = -1)
    {
      wxButton* button{ new wxButton{this, id, text} };

      button->SetFont(font);
      gs->Add(button, 0, wxEXPAND);
    };

    //addSpace adds a widget with an empty string to occupy positions where
    // we do not want buttons
    auto addSpace = [this, gs]()
    {
      wxStaticText* text{ new wxStaticText{this, -1, ""} };
      gs->Add(text, 0, wxEXPAND);
    };
    //Add the button
    addButton("C", buttonId_Clear); addButton("<<", buttonId_Del);  addSpace();                   addButton("/", buttonId_Div);
    addButton("7", buttonId_7);     addButton("8", buttonId_8);     addButton("9", buttonId_9);   addButton("*", buttonId_Mul);
    addButton("4", buttonId_4); addButton("5", buttonId_5); addButton("6", buttonId_6); addButton("-",buttonId_Sub);
    addButton("1", buttonId_1); addButton("2", buttonId_2); addButton("3", buttonId_3); addButton("+",buttonId_Add);
    //TODO: add missing button rows..
    addButton("+/-", buttonId_Sign);addButton("0", buttonId_0);     addButton(".", buttonId_Dot); addButton("=", buttonId_Eq);

    sizer->Add(gs, 1, wxEXPAND);
    SetSizer(sizer);
    SetMinSize(wxSize{ minWidth, minHeight });

    //menu event handlers, each event has a handler
    Bind(wxEVT_MENU, &MainWindow::onExit, this, wxID_EXIT);
    Bind(wxEVT_MENU, &MainWindow::onAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU,&MainWindow::onStudentAbout,this, menuId_Student);
    //TODO: bind other menu event handlers...

    //button event handlers
    Bind(wxEVT_BUTTON,&MainWindow::onButton0Click,this,buttonId_0);
    Bind(wxEVT_BUTTON,&MainWindow::onButton1Click,this,buttonId_1);
    Bind(wxEVT_BUTTON,&MainWindow::onButton2Click,this,buttonId_2);
    Bind(wxEVT_BUTTON, &MainWindow::onButton3Click,this,buttonId_3);
    Bind(wxEVT_BUTTON,&MainWindow::onButton4Click,this,buttonId_4);
    Bind(wxEVT_BUTTON,&MainWindow::onButton5Click,this,buttonId_5);
    Bind(wxEVT_BUTTON,&MainWindow::onButton6Click,this,buttonId_6);
    Bind(wxEVT_BUTTON, &MainWindow::onButton7Click, this, buttonId_7);
    Bind(wxEVT_BUTTON, &MainWindow::onButton8Click, this, buttonId_8);
    Bind(wxEVT_BUTTON, &MainWindow::onButton9Click, this, buttonId_9);

    Bind(wxEVT_BUTTON, &MainWindow::onButtonClearClick, this, buttonId_Clear);
    Bind(wxEVT_BUTTON, &MainWindow::onButtonDelClick, this, buttonId_Del);
    Bind(wxEVT_BUTTON, &MainWindow::onButtonDivClick, this, buttonId_Div);
    Bind(wxEVT_BUTTON, &MainWindow::onButtonMulClick, this, buttonId_Mul);
    Bind(wxEVT_BUTTON, &MainWindow::onButtonSubClick, this, buttonId_Sub);
    Bind(wxEVT_BUTTON, &MainWindow::onButtonAddClick, this, buttonId_Add);
    Bind(wxEVT_BUTTON, &MainWindow::onButtonEqualClick, this, buttonId_Eq);
    Bind(wxEVT_BUTTON, &MainWindow::onButtonDotClick, this, buttonId_Dot);
    Bind(wxEVT_BUTTON, &MainWindow::onButtonSignClick, this, buttonId_Sign);
    //TODO: bind other button event handlers...

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
      "C++ Calculator Example (c) 2022\nby Daniel Moreno <daniel_moreno@brown.edu>",
      "About C++ Calculator"); //Show this message
  }

  void MainWindow::onStudentAbout(wxCommandEvent &event)
  {
      wxMessageBox(
          "Assignment completed by Zekai Lai<zekai_lai@brown.edu>"
      ); //Show this message
  }

  void MainWindow::onButton0Click(wxCommandEvent& event)
  {
      std::string text{ display_->GetValue().ToStdString() };
      if (text[0] == '0' && text.size() == 1)
      { 
          ResultFlag = false; //Reset this flag so that it can be deleted
          display_->ChangeValue('0');
      }
      else if (OperFlag == true)
      {//If there exists an operator, which can be indicated by operflag
          OperFlag = false; //Reset flag to false, so that it can append
          ValidOpe = true; //Set valid ope to true, which mainly to handle Operflag==true
          ResultFlag = false; //Reset this flag to avoid not being deleted
          display_->ChangeValue('0');
      }
      else
      {
          display_->AppendText('0');
      }
  }

  void MainWindow::onButton1Click(wxCommandEvent& event)
  {
      std::string text{ display_->GetValue().ToStdString() };
      if (text[0] == '0' && text.size() == 1)
      { 
          ResultFlag = false; //Reset this flag to avoid not being deleted
          display_->ChangeValue('1');
      }
      else if (OperFlag == true)
      {//If operation flag is true
          OperFlag = false; //Reset flag to false, so that it can append
          ValidOpe = true; //Set valid ope to true, which mainly to handle Operflag==true
          ResultFlag = false; //Reset this flag to avoid not being deleted
          display_->ChangeValue('1');
      }
      else
      {
          display_->AppendText('1');
      }
  }

  void MainWindow::onButton2Click(wxCommandEvent& event)
  {
      std::string text{ display_->GetValue().ToStdString() };
      if (text[0] == '0' && text.size() == 1)
      { 
          ResultFlag = false; //Reset this flag to avoid not being deleted
          display_->ChangeValue('2');
      }
      else if (OperFlag == true)
      { //If operation flag is true
          OperFlag = false; //Reset flag to false, so that it can append
          ValidOpe = true; //Set valid ope to true, which mainly to handle Operflag==true
          ResultFlag = false; //Reset this flag to avoid not being deleted
          display_->ChangeValue('2');
      }
      else
      {
          display_->AppendText('2');
      }
  }

  void MainWindow::onButton3Click(wxCommandEvent& event)
  {
      std::string text{ display_->GetValue().ToStdString() };
      if (text[0] == '0' && text.size() == 1)
      { 
          ResultFlag = false; //Reset this flag to avoid not being deleted
          display_->ChangeValue('3');
      }
      else if (OperFlag == true)
      {//If operation flag is true
          OperFlag = false; //Reset flag to false, so that it can append
          ValidOpe = true; //Set valid ope to true, which mainly to handle Operflag==true
          ResultFlag = false; //Reset this flag to avoid not being deleted
          display_->ChangeValue('3');
      }
      else
      {
          display_->AppendText('3');
      }
  }

  void MainWindow::onButton4Click(wxCommandEvent& event)
  {
      std::string text{ display_->GetValue().ToStdString() };
      if (text[0] == '0' && text.size() == 1)
      { 
          ResultFlag = false; //Reset this flag to avoid not being deleted
          display_->ChangeValue('4');
      }
      else if (OperFlag == true)
      {//If operation flag is true
          OperFlag = false; //Reset flag to false, so that it can append
          ValidOpe = true; //Set valid ope to true, which mainly to handle Operflag==true
          ResultFlag = false; //Reset this flag to avoid not being deleted
          display_->ChangeValue('4');
      }
      else
      {
          display_->AppendText('4');
      }
  }

  void MainWindow::onButton5Click(wxCommandEvent& event)
  {
      std::string text{ display_->GetValue().ToStdString() };
      if (text[0] == '0' && text.size() == 1)
      { 
          ResultFlag = false; //Reset this flag to avoid not being deleted
          display_->ChangeValue('5');
      }
      else if (OperFlag == true)
      {//If operation flag is true
          OperFlag = false; //Reset flag to false, so that it can append
          ValidOpe = true; //Set valid ope to true, which mainly to handle Operflag==true
          ResultFlag = false; //Reset this flag to avoid not being deleted
          display_->ChangeValue('5');
      }
      else
      {
          display_->AppendText('5');
      }
  }

  void MainWindow::onButton6Click(wxCommandEvent& event)
  {
      std::string text{ display_->GetValue().ToStdString() };
      if (text[0] == '0' && text.size() == 1)
      {
          ResultFlag = false; //Reset this flag to avoid not being deleted
          display_->ChangeValue('6');
      }
      else if (OperFlag == true)
      { //If operation flag is true
          OperFlag = false; //Reset flag to false, so that it can append
          ValidOpe = true; //Set valid ope to true, which mainly to handle Operflag==true
          ResultFlag = false; //Reset this flag to avoid not being deleted
          display_->ChangeValue('6');
      }
      else
      {
          display_->AppendText('6');
      }
  }
  void MainWindow::onButton7Click(wxCommandEvent& event)
  {    //number 7 pressed...
      std::string text{ display_->GetValue().ToStdString() };
      if (text[0] == '0' && text.size() == 1)
      { 
          ResultFlag = false; //Reset this flag to avoid not being deleted
          display_->ChangeValue('7');
      }
      else if (OperFlag == true)
      {//If operation flag is true
          OperFlag = false; //Reset flag to false, so that it can append
          ValidOpe = true; //Set valid ope to true, which mainly to handle Operflag==true
          ResultFlag = false; //Reset this flag to avoid not being deleted
          display_->ChangeValue('7');
      }
      else
      {
          display_->AppendText('7');
      }
  }

  void MainWindow::onButton8Click(wxCommandEvent& event)
  {    //number 8 pressed...
      std::string text{ display_->GetValue().ToStdString() };
      if (text[0] == '0' && text.size() == 1) 
      { 
          ResultFlag = false; //Reset this flag to avoid not being deleted
          display_->ChangeValue('8');
      }
      else if (OperFlag == true)
      {//If operation flag is true
          OperFlag = false; //Reset flag to false, so that it can append
          ValidOpe = true; //Set valid ope to true, which mainly to handle Operflag==true
          ResultFlag = false; //Reset this flag to avoid not being deleted
          display_->ChangeValue('8');
      }
      else
      {
          display_->AppendText('8'); 
      }
  }

  void MainWindow::onButton9Click(wxCommandEvent& event)
  {    //number 9 pressed...
      std::string text{ display_->GetValue().ToStdString() };
      if (text[0] == '0' && text.size() == 1)
      { 
          ResultFlag = false; //Reset this flag to avoid not being deleted
          display_->ChangeValue('9');
      }
      else if (OperFlag == true)
      {//If operation flag is true
          OperFlag = false; //Reset flag to false, so that it can append
          ValidOpe = true; //Set valid ope to true, which mainly to handle Operflag==true
          ResultFlag = false; //Reset this flag to avoid not being deleted
          display_->ChangeValue('9');
      }
      else
      {
          display_->AppendText('9');
      }
  }

  void MainWindow::onButtonClearClick(wxCommandEvent& event)
  {  //Clear the caculator to the start status
      display_->ChangeValue("0");
      operator_ = Operator::None;
      result_ = 0.0;
      NumOfDot = 0;
      OperFlag = false;
      ValidOpe = false;
      ResultFlag = false; 
      op1 = 0;
      op2 = 0;
  }

  void MainWindow::onButtonDelClick(wxCommandEvent& event)
  {
      if (ResultFlag == false&&operator_==Operator::None) //If it not the result(which is "=")
      {                                                   //And the operator is none
          std::string text{ display_->GetValue().ToStdString() };
          if (text.size() >= 2)
          {
              text.pop_back(); //Remove the last characters in text
              display_->ChangeValue(text);
          }
          else //When there are only one number in the screen
          {
              NumOfDot = 0; //Before enter the next number, reinitialize the number of dot
              display_->ChangeValue('0');
          }
      }
  }

  void MainWindow::onButtonDivClick(wxCommandEvent& event)
  {
      std::string text{ display_->GetValue().ToStdString() };
      if (operator_ == Operator::None)
      {
          op1 = std::stod(text);
          NumOfDot = 0; //Before enter the next number, reinitialize number of dot
          operator_ = Operator::Div;
          OperFlag = true;
          //ResultFlag = false; //Reset this flag to avoid not being deleted
          if (text.back() == '.' && text.empty() == false) //If the last character is "."
          {                                          //If so, we need to remove the dot
              text.pop_back(); //Remove the last character
              //ResultFlag = true; //To avoid deleting them
              display_->ChangeValue(text); //Then display
          }
      }
      else
      {
          if (ValidOpe == true) //Only in the valid condition, the caculation can be executed
          {
              op2 = std::stod(text);
              if (operator_ == Operator::Add)
              { //Add operation
                  result_ = op1 + op2;
              }
              else if (operator_ == Operator::Sub)
              { //Sub operation
                  result_ = op1 - op2;
              }
              else if (operator_ == Operator::Mul)
              { //Multiplication operation
                  result_ = op1 * op2;
              }
              else if (operator_ == Operator::Div)
              { //Division operation
                  result_ = op1 / op2;
              }
              op1 = result_; //Store the result in op1, which can be used in next caculation
              OperFlag = true; //There is a operator
              NumOfDot = 0; //Before enter the next number, reinitialize number of dot
              //ResultFlag = true; //Cannot delete
              std::stringstream OutResult; //Output the result
              OutResult << result_;
              wxString Out = OutResult.str();
              display_->ChangeValue(Out);
              ValidOpe = false; //Reset it to invalid
          }
          operator_ = Operator::Div; //Set the operator_ 
      }
  }

  void MainWindow::onButtonMulClick(wxCommandEvent& event)
  {
      std::string text{ display_->GetValue().ToStdString() };
      if (operator_ == Operator::None)
      {
          op1 = std::stod(text);
          NumOfDot = 0; //Before enter the next number, reinitialize number of dot
          operator_ = Operator::Mul;
          OperFlag = true;
          //ResultFlag = false; //Reset this flag to avoid not being deleted
          if (text.back() == '.' && text.empty() == false) //If the last character is "."
          {                                          //If so, we need to remove the dot
              text.pop_back();
             // ResultFlag = true; //To avoid deleting them
              display_->ChangeValue(text);
          }
      }
      else
      {
          if (ValidOpe == true)
          {
              op2 = std::stod(text);
              if (operator_ == Operator::Add)
              {
                  result_ = op1 + op2;
              }
              else if (operator_ == Operator::Sub)
              {
                  result_ = op1 - op2;
              }
              else if (operator_ == Operator::Mul)
              {
                  result_ = op1 * op2;
              }
              else if (operator_ == Operator::Div)
              {
                  result_ = op1 / op2;
              }
              op1 = result_;
              OperFlag = true;
              NumOfDot = 0; //Before enter the next number, reinitialize number of dot
             // ResultFlag = true; //Cannot delete
              std::stringstream OutResult;
              OutResult << result_;
              wxString Out = OutResult.str();
              display_->ChangeValue(Out);
              ValidOpe = false;
          }
          operator_ = Operator::Mul;
      }
  }

  void MainWindow::onButtonSubClick(wxCommandEvent& event)
  {
      std::string text{ display_->GetValue().ToStdString() };
      if (operator_ == Operator::None)
      {
          op1 = std::stod(text);
          NumOfDot = 0; //Before enter the next number, reinitialize number of dot
          operator_ = Operator::Sub;
          OperFlag = true;
          //ResultFlag = false; //Reset this flag to avoid not being deleted
          if (text.back() == '.' && text.empty() == false) //If the last character is "."
          {                                          //If so, we need to remove the dot
              text.pop_back();
              //ResultFlag = true; //To avoid deleting them
              display_->ChangeValue(text);
          }
      }
      else
      {
          if (ValidOpe == true) //If there are numbers previous to sub operator
          {
              op2 = std::stod(text);
              if (operator_ == Operator::Add)
              {
                  result_ = op1 + op2;
              }
              else if (operator_ == Operator::Sub)
              {
                  result_ = op1 - op2;
              }
              else if (operator_ == Operator::Mul)
              {
                  result_ = op1 * op2;
              }
              else if (operator_ == Operator::Div)
              {
                  result_ = op1 / op2;
              }
              op1 = result_;
              OperFlag = true;
              NumOfDot = 0; //Before enter the next number, reinitialize number of dot
              //ResultFlag = true; //Cannot delete
              std::stringstream OutResult;
              OutResult << result_;
              wxString Out = OutResult.str();
              display_->ChangeValue(Out);
              ValidOpe = false;
          }
          operator_ = Operator::Sub;
      }
  }

  void MainWindow::onButtonAddClick(wxCommandEvent& event)
  {
      std::string text{ display_->GetValue().ToStdString() };
      if (operator_==Operator::None)
      {          
          op1 = std::stod(text);
          NumOfDot = 0; //Before enter the next number, reinitialize number of dot
          operator_=Operator::Add;
          OperFlag = true;
          ResultFlag = false; //Reset this flag to avoid not being deleted
          if (text.back() == '.' && text.empty() == false) //If the last character is "."
          {                                          //If so, we need to remove the dot
              text.pop_back();
              ResultFlag = true; //To avoid deleting them
              display_->ChangeValue(text);
          }
      }
      else
      {
         if (ValidOpe == true)
          {
              op2 = std::stod(text);
              if (operator_ == Operator::Add)
              {
                  result_ = op1 + op2;
              }
              else if (operator_ == Operator::Sub)
              {
                  result_ = op1 - op2;
              }
              else if (operator_ == Operator::Mul)
              {
                  result_ = op1 * op2;
              }
              else if (operator_ == Operator::Div)
              {
                  result_ = op1 / op2;
              }
              op1 = result_;
              NumOfDot = 0; //Before enter the next number, reinitialize number of dot
              OperFlag = true;
             // ResultFlag = true; //Cannot delete
              std::stringstream OutResult; //Output the result
              OutResult << result_;
              wxString Out = OutResult.str();
              display_->ChangeValue(Out);
              ValidOpe = false;
          }
          operator_ = Operator::Add;
      }
  }

  void MainWindow::onButtonEqualClick(wxCommandEvent& event)
  {
      std::string text{ display_->GetValue().ToStdString() };
      if(operator_!=Operator::None) //Only when there exist an operator
      {
          if (ValidOpe == true) //When in the valid condition, execute the operation
          {
              op2 = std::stod(text);
              if (operator_ == Operator::Add)
              {
                  result_ = op1 + op2;
              }
              else if (operator_ == Operator::Sub)
              {
                  result_ = op1 - op2;
              }
              else if (operator_ == Operator::Mul)
              {
                  result_ = op1 * op2;
              }
              else if (operator_ == Operator::Div)
              {
                  result_ = op1 / op2;
              }
              op1 = 0; op2 = 0; //Reinitialize op1 and op2 to 0
              operator_ = Operator::None; //Set the operator to none
              ValidOpe = false;
              NumOfDot = 0;
              OperFlag = true; //Reinitialize other elements           
              std::stringstream OutResult; //Display the result
              OutResult << result_;
              wxString Out = OutResult.str();
              display_->ChangeValue(Out);
              result_ = 0; //Reinitialize result to 0
          }
      }
      ResultFlag = true; //Set the result flag to true, so that the delete can
                               //avoid this.
  }

 
  void MainWindow::onButtonDotClick(wxCommandEvent& event)
  {
      if (NumOfDot==0) //Only when number of dot is 0, we can append dot
      {
          display_->AppendText("."); 
          NumOfDot++;
      }
  }

  void MainWindow::onButtonSignClick(wxCommandEvent& event)
  {
      std::string text{ display_->GetValue().ToStdString() }; //Get the string
      if (text[0] != '0' || text.size() != 1) //Only when the text is not 0, it can be executed
      {
          if (text.front() == '-') //When the first character is "-"
          {
              text.erase(0, 1); //Remove the first character
          }
          else //When it is a positive number
          {
              text.insert(0, 1, '-'); //Insert "-" in front of the number
          }
          ResultFlag = true; //Reset this flag to avoid being deleted
          display_->ChangeValue(text);
      }
  }
}