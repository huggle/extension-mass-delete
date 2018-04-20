//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

#include "mass_delete.hpp"
#include "nuke.hpp"
#include <huggle_core/core.hpp>
#include <huggle_core/collectable_smartptr.hpp>
#include <huggle_core/localization.hpp>
#include <QMessageBox>
#include <huggle_core/query.hpp>
#include <huggle_core/querypool.hpp>
#include <huggle_ui/mainwindow.hpp>
#include <huggle_core/generic.hpp>
#include <huggle_core/wikiedit.hpp>
#include <huggle_core/wikisite.hpp>
#include <huggle_core/wikipage.hpp>
#include <huggle_core/wikiuser.hpp>
#include <huggle_core/syslog.hpp>
#include <huggle_core/configuration.hpp>
#include <QMenu>

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
    this->menu = new QAction("Mass actions", (QObject*)Nuke::Window->GetMenu(HUGGLE_MW_MENU_SYSTEM));
    Nuke::Window->GetMenu(HUGGLE_MW_MENU_SYSTEM)->insertAction(Nuke::Window->GetMenuItem(HUGGLE_MW_MENUITEM_EXIT), this->menu);
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


