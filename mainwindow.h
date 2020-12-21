#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "script.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    script s;

private slots:

    void on_setLine_triggered();

    void on_resetTrigger_triggered();

    void on_run_triggered();


    void on_truthTable_triggered();

    void on_stateTruthTable_triggered();

    void on_run2_triggered();

    void on_elementCount_triggered();

    void on_lineComplexity_triggered();

    void on_closeCircuitScript_triggered();

    void on_load_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
