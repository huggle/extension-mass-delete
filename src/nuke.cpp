//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

#include "nuke.hpp"
#include <huggle_core/apiqueryresult.hpp>
#include <huggle_core/configuration.hpp>
#include <huggle_core/generic.hpp>
#include <huggle_ui/history.hpp>
#include <huggle_core/historyitem.hpp>
#include <huggle_core/localization.hpp>
#ifdef HUGGLE_WEBEN
    #include <huggle_ui/web_engine/huggleweb.hpp>
#else
    #include <huggle_ui/webkit/huggleweb.hpp>
#endif
#include <huggle_ui/mainwindow.hpp>
#include <huggle_core/syslog.hpp>
#include <QTimer>
#include <huggle_core/wikisite.hpp>
#include <huggle_ui/uigeneric.hpp>
#include "ui_nuke.h"

using namespace Huggle;

MainWindow *Nuke::Window = NULL;

Nuke::Nuke(QWidget *parent) : QDialog(parent), ui(new Ui::Nuke)
{
    this->ui->setupUi(this);

    QStringList header;
    header << "Revision" << "Page name" << "Date" << "Summary" << "Link" << "Pick";
    this->ui->tableWidget->setColumnCount(6);
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
    this->timer = new QTimer(this);
    QObject::connect(this->timer, SIGNAL(timeout()), this, SLOT(OnTick()));
    foreach(Huggle::WikiSite *sx, hcfg->Projects)
    {
        this->ui->comboBox->addItem(sx->Name);
    }
    this->ui->comboBox->setCurrentIndex(0);
    this->web = new HuggleWeb(this);
    this->ui->wxLayout->addWidget(this->web);
}

Nuke::~Nuke()
{
    delete this->ui;
    delete this->web;
    while (this->CheckBoxes.count())
    {
        delete this->CheckBoxes.at(0);
        this->CheckBoxes.removeFirst();
    }
}

WikiSite *Nuke::Site()
{
    return hcfg->Projects.at(this->ui->comboBox->currentIndex());
}

void Nuke::Reload()
{
    this->ui->pushButton->setEnabled(true);
    this->ui->pushButton_2->setEnabled(true);
}

void Nuke::InsertRevision(QString type, QString title, QString time, QString summary, QString diff)
{
    int row = this->ui->tableWidget->rowCount();
    this->ui->tableWidget->insertRow(row);
    this->ui->tableWidget->setItem(row, 0, new QTableWidgetItem(diff));
    QCheckBox *xx = new QCheckBox();
    this->ui->tableWidget->setItem(row, 1, new QTableWidgetItem(title));
    QString link = Configuration::GetProjectScriptURL(Site()) + "index.php?title=" + QUrl::toPercentEncoding(title) + "&diff=" + diff;
    this->ui->tableWidget->setItem(row, 2, new QTableWidgetItem(time));
    this->ui->tableWidget->setItem(row, 3, new QTableWidgetItem(summary));
    this->ui->tableWidget->setItem(row, 4, new QTableWidgetItem(link));
    this->CheckBoxes.append(xx);
    xx->setChecked(false);
    this->ui->tableWidget->setCellWidget(row, 5, xx);
}

static void qEdits_fail(Query *result)
{
    UiGeneric::MessageBox("Error", "Unable to retrieve a list of contributions for this user, reason: " + result->GetFailureReason());
    HUGGLE_DEBUG1(result->Result->Data);
    ((Nuke*)result->CallbackOwner)->Reload();
}

static void qEdits_finish(Query *result)
{
    ApiQuery *qx = (ApiQuery*)result;
    QList<ApiQueryResultNode*> list = qx->GetApiQueryResult()->GetNodes("item");
    if (list.count() == 0)
    {
        UiGeneric::MessageBox("No edits", "There were no edits found made by this user");
        ((Nuke*)result->CallbackOwner)->Reload();
        return;
    }
    //////HUGGLE_DEBUG(qx->GetApiQueryResult()->Data, 1);
    foreach(ApiQueryResultNode *xx, list)
    {
        QString page = xx->GetAttribute("title", "Unknown page");
        QString time = xx->GetAttribute("timestamp", "Unknown time");
        QString diff = xx->GetAttribute("revid");
        ((Nuke*)result->CallbackOwner)->InsertRevision("0", page, time, xx->GetAttribute("comment"), diff);
    }
    ((Nuke*)result->CallbackOwner)->Reload();
}

void Nuke::on_pushButton_clicked()
{
    if (this->ui->lineEdit->text() == "")
    {
        UiGeneric::MessageBox("No user", "You didn't provide any user name I could look for");
        return;
    }

    while(this->ui->tableWidget->rowCount() > 0)
        this->ui->tableWidget->removeRow(0);

    this->ui->pushButton_2->setEnabled(false);
    this->ui->pushButton->setEnabled(false);

    HUGGLE_CLEAR_PQ_LIST(this->CheckBoxes);

    this->qEdits = new Huggle::ApiQuery(Huggle::ActionQuery, this->Site());
    this->qEdits->Parameters = "list=usercontribs&uclimit=500&ucuser=" + QUrl::toPercentEncoding(this->ui->lineEdit->text()) +
            "&ucprop=comment%7Ctimestamp%7Ctitle%7Cids%7Csize";
    this->qEdits->callback = (Callback) qEdits_finish;
    this->qEdits->FailureCallback = (Callback) qEdits_fail;
    this->qEdits->CallbackOwner = this;
    this->qEdits->Process();
}

void Nuke::on_pushButton_2_clicked()
{
    if (!this->CheckBoxes.count())
    {
        UiGeneric::MessageBox("Edit list", "You didn't select any edits to revert or delete");
        return;
    }

    if (!this->ui->radioButton_2->isChecked())
    {
        UiGeneric::MessageBox("", "This feature is not implemented yet");
        return;
    }

    this->ui->pushButton_2->setEnabled(false);
    this->ui->pushButton->setEnabled(false);
    this->ui->tableWidget->setEnabled(false);
    // Get list of checked edits
    this->CurrentEdit = 0;
    this->timer->start(10);
    this->Edits = 0;
    int edit = 0;
    while (edit < this->CheckBoxes.size())
    {
        if (!this->CheckBoxes.at(edit)->isChecked())
        {
            edit++;
            continue;
        }
        // Delete this page
        this->Edits++;
        edit++;
    }
}

void Nuke::OnTick()
{
    if (this->CurrentEdit >= this->CheckBoxes.count())
    {
        // We are done
        this->ui->pushButton_2->setText("Done");
        this->timer->stop();
        return;
    }
    if (this->Delete == nullptr)
    {
        // let's process next edit
        if (!this->CheckBoxes.at(this->CurrentEdit)->isChecked())
        {
            this->CurrentEdit++;
            return;
        }
        this->Delete = new ApiQuery(ActionDelete, this->Site());
        this->Delete->UsingPOST = true;
        this->Delete->Parameters = "title=" + QUrl::toPercentEncoding(this->ui->tableWidget->item(this->CurrentEdit, 1)->text())
                + "&reason=" + QUrl::toPercentEncoding(this->ui->lineEdit_2->text())
                + "&token=" + QUrl::toPercentEncoding(this->Site()->GetProjectConfig()->Token_Csrf);
        this->Delete->Process();
    } else
    {
        if (!this->Delete->IsProcessed())
            return;
        QString page = this->ui->tableWidget->item(this->CurrentEdit, 1)->text();
        if (this->Delete->IsFailed())
        {
            Syslog::HuggleLogs->ErrorLog("MassAction: Failed to delete page " + page + " reason " +
                                         this->Delete->GetFailureReason());
        } else
        {
            HistoryItem *hi = new HistoryItem();
            hi->IsRevertable = false;
            hi->Result = _l("successful");
            hi->Target = page;
            hi->Type = HistoryDelete;
            Nuke::Window->_History->Prepend(hi);
            Syslog::HuggleLogs->Log("MassAction: Successfuly deleted " + this->ui->tableWidget->item(this->CurrentEdit, 1)->text());
        }
        this->CurrentEdit++;
        this->Delete = nullptr;
    }
    if (this->Edits >= this->CurrentEdit)
        this->ui->pushButton_2->setText("Deleting edit " + QString::number(this->CurrentEdit + 1) + " of " + QString::number(this->Edits));
}

void Nuke::on_tableWidget_clicked(const QModelIndex &index)
{
    //this->ui->webView->setHtml(_l("wait"));
    this->web->RenderHtml("This feature is not implemented yet");
}

void Nuke::on_pushButton_3_clicked()
{
    foreach (QCheckBox *xx, this->CheckBoxes)
        xx->setChecked(true);
}
