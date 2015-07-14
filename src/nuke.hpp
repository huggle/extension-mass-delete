//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

#ifndef NUKE_HPP
#define NUKE_HPP

#include <iextension.hpp>
#include <apiquery.hpp>
#include <collectable_smartptr.hpp>
#include <QCheckBox>
#include <QModelIndex>
#include <QDialog>

class QTimer;

namespace Ui
{
    class Nuke;
}

namespace Huggle
{
    class MainWindow;
    class WikiPage;
    class WikiUser;
    class WikiSite;
}

class Nuke : public QDialog
{
    Q_OBJECT

    public:
        static Huggle::MainWindow *Window;

        explicit Nuke(QWidget *parent = 0);
        ~Nuke();
        Huggle::WikiSite *Site();
        void Reload();
        void InsertRevision(QString type, QString title, QString time, QString summary, QString diff);
        int CurrentEdit;
        int Edits;

    private slots:
        void on_pushButton_clicked();
        void on_pushButton_2_clicked();
        void OnTick();
        void on_tableWidget_clicked(const QModelIndex &index);
        void on_pushButton_3_clicked();

    private:
        Huggle::Collectable_SmartPtr<Huggle::ApiQuery> qEdits;
        QTimer *timer;
        Huggle::Collectable_SmartPtr<Huggle::ApiQuery> Delete;
        QList<QCheckBox*> CheckBoxes;
        Ui::Nuke *ui;
};

#endif // NUKE_HPP
