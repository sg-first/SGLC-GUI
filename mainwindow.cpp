#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "excep.h"
#include <QMessageBox>
#include "script.h"
#include "node.h"
#include "pos.h"
#include <QLabel>
#include <QSpinBox>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QLineEdit>
#include <QFileDialog>
#include <QTextStream>
#include <QGraphicsLineItem>
#include <QProcess>

#include <windows.h>
#include <string>
using namespace std;

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(QSize(1920,1080));
    this->scene=new QGraphicsScene(0,0,1920,1080);
    ui->Graph->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_setLine_triggered()
{
    if(loaded==false)
        QMessageBox::information(NULL, "提示", "未加载电路脚本");
    else
    {
        QDialog dialog(this);
        QFormLayout form(&dialog);
        form.addRow(new QLabel("设置线路变量:"));
        // Value1
        QLineEdit *spinbox1 = new QLineEdit(this);
        form.addRow("变量名: ", spinbox1);
        // Value2
        QSpinBox *spinbox2 = new QSpinBox(&dialog);
        form.addRow("变量值: ", spinbox2);
        // Add Cancel and OK button
        QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
            Qt::Horizontal, &dialog);
        form.addRow(&buttonBox);
        QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
        QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

        // Process when OK button is clicked
        if (dialog.exec() == QDialog::Accepted)
        {
            QString name=spinbox1->text();
            QString value=spinbox2->text();
            try
            {
                 s.set(name.toStdString(),value.toStdString());
            }
            catch(undefinedVariableExcep e)
            {
                QMessageBox::information(nullptr, "提示", "变量名不存在");
            }
        }
    }
}

void MainWindow::on_resetTrigger_triggered()
{
    if(loaded==false)
        QMessageBox::information(nullptr, "提示", "未加载电路脚本");
    else
    {
        s.getManager()->resetTri();
    }
}

void MainWindow::on_run_triggered()
{
    if(loaded==false)
        QMessageBox::information(nullptr, "提示", "未加载电路脚本");
    else
    {
        string result=s.getManager()->run();
        ui->textEdit->append(QString::fromStdString(result));
    }
}

void MainWindow::on_truthTable_triggered()
{
    if(loaded==false)
        QMessageBox::information(nullptr, "提示", "未加载电路脚本");
    else
    {
        string result=s.getManager()->trueTable();
        ui->textEdit->append(QString::fromStdString(result));
    }
}

void MainWindow::on_stateTruthTable_triggered()
{
    if(loaded==false)
        QMessageBox::information(nullptr, "提示", "未加载电路脚本");
    else
    {
       string result=s.getManager()->trueTable(0,true);
       ui->textEdit->append(QString::fromStdString(result));
    }
}

void MainWindow::on_run2_triggered()
{

    if(loaded==false)
        QMessageBox::information(nullptr, "提示", "未加载电路脚本");
    else
        s.getManager()->stru(scene);
}

void MainWindow::on_elementCount_triggered()
{
    if(loaded==false)
        QMessageBox::information(nullptr, "提示", "未加载电路脚本");
    else
    {
        string result=s.getManager()->gateNum();
        ui->textEdit->append(QString::fromStdString(result));
    }
}

void MainWindow::on_lineComplexity_triggered()
{
    if(loaded==false)
        QMessageBox::information(nullptr, "提示", "未加载电路脚本");
    else
    {
        string result=s.getManager()->multiplexing();
        ui->textEdit->append(QString::fromStdString(result));
    }
}

void MainWindow::on_closeCircuitScript_triggered()
{
    s.clear();
    ui->textEdit->clear();
    ui->Graph->scene()->clear();
    loaded=false;
}

QString ReadTXT(QString path)
{
    QFile f(path);
    f.open(QIODevice::ReadOnly);
    QTextStream text(&f);
    return text.readAll();
}

void MainWindow::on_load_triggered()
{
    QString filename = QFileDialog::getOpenFileName(
       this,
       "Open Script",
       QDir::currentPath(),
       "Circuit File(*.lc *.txt);;All files(*.*)");

    if (!filename.isNull())
    {
        this->on_closeCircuitScript_triggered();
        this->loaded=true; //选完了设true
        s.runFile(filename.toStdString());
    }
    else // 用户取消选择
       QMessageBox::information(nullptr, "提示", "未加载电路脚本");
}

void MainWindow::on_routerCmd_triggered()
{
    QString path=QDir::currentPath()+"/router.exe";
    string command="start "+path.toStdString();
    system(command.c_str());
}
