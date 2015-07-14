//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

#include "mass_delete.hpp"
#include <core.hpp>
#include <collectable_smartptr.hpp>
#include <localization.hpp>
#include <QMessageBox>
#include <query.hpp>
#include <querypool.hpp>
#include <mainwindow.hpp>
#include <generic.hpp>
#include <ui_mainwindow.h>
#include <wikiedit.hpp>
#include <wikisite.hpp>
#include <wikipage.hpp>
#include <wikiuser.hpp>
#include <syslog.hpp>
#include <configuration.hpp>
#include "nuke.hpp"

using namespace Huggle;

huggle_mass::huggle_mass()
{
    this->menu = nullptr;
}

huggle_mass::~huggle_mass()
{
    //delete this->menuThanks;
}

bool huggle_mass::Register()
{
    this->Init();
    return true;
}

bool huggle_mass::IsWorking()
{
    return true;
}

void huggle_mass::Hook_MainWindowOnLoad(void *window)
{
    Nuke::Window = (Huggle::MainWindow*)window;
    this->menu = new QAction("Mass actions", Nuke::Window->ui->menuFile);
    Nuke::Window->ui->menuFile->insertAction(Nuke::Window->ui->actionExit, this->menu);
    connect(this->menu, SIGNAL(triggered()), this, SLOT(ClickMenu()));
}

void huggle_mass::ClickMenu()
{
    Nuke *window = new Nuke(Nuke::Window);
    window->setAttribute(Qt::WA_DeleteOnClose);
    window->show();
}


#if QT_VERSION < 0x050000
    Q_EXPORT_PLUGIN2("org.huggle.extension.qt", huggle_mass)
#endif


