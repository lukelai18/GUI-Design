//  Copyright (c) 2022 Daniel Moreno. All rights reserved.
//

#pragma once

#include <wx/app.h>

#include <memory>

#include "MainWindow.hpp"
#include "Simulation.hpp"

namespace course
{
    class App : public wxApp
    {
        MainWindow* window_;
        Simulation* simulation_;
    public:
        App();
        virtual ~App();

        virtual bool OnInit() override;

        const Simulation& simulation() const;
        Simulation& simulation();

        const MainWindow& mainWindow() const;
        MainWindow& mainWindow();
    };

    wxDECLARE_APP(App); //declares: wxGetApp()
}