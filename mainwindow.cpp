#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "config.h"

MainWindow::MainWindow(QWidget *parent, Regulador *regM, Regulador *regC,
                       VariablesCompartidas *varM, VariablesCompartidas *varC)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    regMot=regM;
    regCru=regC;
    varMot=varM;
    varCru=varC;

    // Inicializar a 0 los ultimos 5 valores del motor
    ui->LE_yk0m->setText("0");
    ui->LE_yk1m->setText("0");
    ui->LE_yk2m->setText("0");
    ui->LE_yk3m->setText("0");
    ui->LE_yk4m->setText("0");

    // Inicializar a 0 los ultimos 5 valores del crucero
    ui->LE_yk0c->setText("0");
    ui->LE_yk1c->setText("0");
    ui->LE_yk2c->setText("0");
    ui->LE_yk3c->setText("0");
    ui->LE_yk4c->setText("0");

    // Iniciaizar entradas de referencia a 1
    ui->DSB_refm->setValue(REFERENCIA_INIT);
    ui->DSB_refc->setValue(REFERENCIA_INIT);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_PB_ykm_clicked()
{
    QString text;
    ui->LE_yk0m->setText(text.setNum(varMot->Get_yk(0)));
    ui->LE_yk1m->setText(text.setNum(varMot->Get_yk(1)));
    ui->LE_yk2m->setText(text.setNum(varMot->Get_yk(2)));
    ui->LE_yk3m->setText(text.setNum(varMot->Get_yk(3)));
    ui->LE_yk4m->setText(text.setNum(varMot->Get_yk(4)));
}

void MainWindow::on_PB_ykc_clicked()
{
    QString text;
    ui->LE_yk0c->setText(text.setNum(varCru->Get_yk(0)));
    ui->LE_yk1c->setText(text.setNum(varCru->Get_yk(1)));
    ui->LE_yk2c->setText(text.setNum(varCru->Get_yk(2)));
    ui->LE_yk3c->setText(text.setNum(varCru->Get_yk(3)));
    ui->LE_yk4c->setText(text.setNum(varCru->Get_yk(4)));
}

void MainWindow::on_DSB_refm_valueChanged(double refm)
{
    if(refm>10)
    {
        refm=10;
        ui->DSB_refm->setValue(refm);
    }
    else if(refm<0)
    {
        refm=0;
        ui->DSB_refm->setValue(refm);
    }
    varMot->Set_r(refm);
}

void MainWindow::on_DSB_refc_valueChanged(double refc)
{
    if(refc>10)
    {
        refc=10;
        ui->DSB_refm->setValue(refc);
    }
    else if(refc<0)
    {
        refc=0;
        ui->DSB_refm->setValue(refc);
    }
    varCru->Set_r(refc);
}
