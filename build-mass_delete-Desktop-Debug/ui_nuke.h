/********************************************************************************
** Form generated from reading UI file 'nuke.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NUKE_H
#define UI_NUKE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>
#include <QtWebKit/QWebView>

QT_BEGIN_NAMESPACE

class Ui_Nuke
{
public:
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_4;
    QComboBox *comboBox;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton;
    QLabel *label_2;
    QTableWidget *tableWidget;
    QLabel *label_4;
    QWebView *webView;
    QPushButton *pushButton_2;

    void setupUi(QDialog *Nuke)
    {
        if (Nuke->objectName().isEmpty())
            Nuke->setObjectName(QString::fromUtf8("Nuke"));
        Nuke->resize(1033, 657);
        verticalLayout_2 = new QVBoxLayout(Nuke);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox = new QGroupBox(Nuke);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        comboBox = new QComboBox(groupBox);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        horizontalLayout_4->addWidget(comboBox);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(groupBox);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout->addWidget(lineEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        radioButton = new QRadioButton(groupBox);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setChecked(true);

        horizontalLayout_2->addWidget(radioButton);

        radioButton_2 = new QRadioButton(groupBox);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));

        horizontalLayout_2->addWidget(radioButton_2);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        lineEdit_2 = new QLineEdit(groupBox);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        horizontalLayout_3->addWidget(lineEdit_2);


        verticalLayout->addLayout(horizontalLayout_3);

        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout->addWidget(pushButton);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setWordWrap(true);

        verticalLayout->addWidget(label_2);


        verticalLayout_2->addWidget(groupBox);

        tableWidget = new QTableWidget(Nuke);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setMinimumSize(QSize(0, 200));

        verticalLayout_2->addWidget(tableWidget);

        label_4 = new QLabel(Nuke);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout_2->addWidget(label_4);

        webView = new QWebView(Nuke);
        webView->setObjectName(QString::fromUtf8("webView"));
        webView->setUrl(QUrl(QString::fromUtf8("about:blank")));

        verticalLayout_2->addWidget(webView);

        pushButton_2 = new QPushButton(Nuke);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        verticalLayout_2->addWidget(pushButton_2);


        retranslateUi(Nuke);

        QMetaObject::connectSlotsByName(Nuke);
    } // setupUi

    void retranslateUi(QDialog *Nuke)
    {
        Nuke->setWindowTitle(QApplication::translate("Nuke", "Mass delete", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("Nuke", "Preferences", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Nuke", "Name of user", 0, QApplication::UnicodeUTF8));
        radioButton->setText(QApplication::translate("Nuke", "Revert", 0, QApplication::UnicodeUTF8));
        radioButton_2->setText(QApplication::translate("Nuke", "Delete", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Nuke", "Summary", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("Nuke", "Search contributions of this user", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Nuke", "Note: this function will revert or delete all edits made by this user, but it will not send any message to them. If you select Revert, only last revisions made by this user will be displayed in a list. If you pick delete, all pages this user ever contributed to will be displayed.", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("Nuke", "Preview of edit", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("Nuke", "Perform", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Nuke: public Ui_Nuke {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NUKE_H
