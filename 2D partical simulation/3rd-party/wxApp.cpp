
#include <wx/app.h>
#include <iostream>

namespace course
{
  class App : public wxApp
  {
  public:
    App() : wxApp{} {}
    virtual ~App() {}

    virtual bool OnInit() override
    {
      std::cout << "wxApp::OnInit called!\n";
      return true;
    }

    virtual int OnRun() override
    {
      ExitMainLoop();
      return 0;
    }
  };

  wxIMPLEMENT_APP_NO_MAIN(App);
}

//Allow to define a /SUBSYSTEM:CONSOLE application on Windows
int main(int argc, char* argv[])
{
  return wxEntry(argc, argv);
}
