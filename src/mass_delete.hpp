//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

#ifndef MASS_DELETE_H
#define MASS_DELETE_H

#define HUGGLE_EXTENSION
#include <iextension.hpp>
#include <QAction>
#include <QDeclarativeItem>

namespace Huggle
{
    class WikiPage;
    class WikiEdit;
    class WikiSite;
}

class huggle_mass : public QDeclarativeItem, public Huggle::iExtension
{
    Q_OBJECT
#if QT_VERSION >= 0x050000
        Q_PLUGIN_METADATA(IID "org.huggle.extension.qt" FILE "mass_delete.json")
#endif
    Q_INTERFACES(Huggle::iExtension)
    public:
        huggle_mass();
        ~huggle_mass();
        bool Register();
        bool IsWorking();
        void Hook_MainWindowOnLoad(void *window);
        QString GetExtensionName() { return "Mass delete"; }
        QString GetExtensionAuthor() { return "Petr Bena"; }
        QString GetExtensionDescription() { return "Provides options to mass delete or revert many pages in few clicks"; }
        QString GetExtensionVersion() { return "1.0.0"; }
        QAction *menu;
        QAction *toggle;
        bool RequestCore() { return true; }
        bool RequestNetwork() { return true; }
        bool RequestConfiguration() { return true; }
    private slots:
        void ClickMenu();
};

QML_DECLARE_TYPE(huggle_mass)

#endif
