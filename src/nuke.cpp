//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

#include "nuke.hpp"
#include <configuration.hpp>
#include <wikisite.hpp>
#include "ui_nuke.h"

using namespace Huggle;

Nuke::Nuke(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Nuke)
{
    this->ui->setupUi(this);

    QStringList header;
    header << "Revision" << "Page name" << "Date" << "Summary" << "Pick";
    this->ui->tableWidget->setColumnCount(5);
    this->ui->tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    this->ui->tableWidget->setHorizontalHeaderLabels(header);
    this->ui->tableWidget->verticalHeader()->setVisible(false);
    this->ui->tableWidget->horizontalHeader()->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    if (Configuration::HuggleConfiguration->SystemConfig_DynamicColsInList)
    {
#if QT_VERSION >= 0x050000
        // Qt5 code
        this->ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
#else
        // Qt4 code
        this->ui->tableWidget->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
#endif
    } else
    {
        this->ui->tableWidget->setColumnWidth(0, 60);
        this->ui->tableWidget->setColumnWidth(1, 200);
        this->ui->tableWidget->setColumnWidth(2, 200);
        this->ui->tableWidget->setColumnWidth(3, 80);
    }
    this->ui->tableWidget->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    this->ui->tableWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    this->ui->tableWidget->setShowGrid(false);
    this->ui->lineEdit_2->setText(Configuration::GenerateSuffix("Mass action", hcfg->Project->GetProjectConfig()));
    foreach(Huggle::WikiSite *sx, hcfg->Projects)
    {
        this->ui->comboBox->addItem(sx->Name);
    }
    this->ui->comboBox->setCurrentIndex(0);
}

Nuke::~Nuke()
{
    delete this->ui;
}

void Nuke::on_pushButton_clicked()
{

}
