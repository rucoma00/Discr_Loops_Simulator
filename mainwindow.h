#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "variablescompartidas.h"
#include "regulador.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, Regulador *regM = nullptr, Regulador *regC = nullptr,
               VariablesCompartidas *varM = nullptr, VariablesCompartidas *varC = nullptr);
    ~MainWindow();

private slots:
    void on_PB_ykm_clicked();

    void on_PB_ykc_clicked();

private:
    Ui::MainWindow *ui;

    Regulador *regMot;
    Regulador *regCru;
    VariablesCompartidas *varMot;
    VariablesCompartidas *varCru;

};
#endif // MAINWINDOW_H
