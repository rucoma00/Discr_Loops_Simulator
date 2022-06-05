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
    ui->LCDN_refm->display(REFERENCIA_INIT);
    ui->VS_refm->setValue(REFERENCIA_INIT*100);
    ui->LCDN_refc->display(REFERENCIA_INIT);
    ui->VS_refc->setValue(REFERENCIA_INIT*100);

    // Inicilaizar entradas de Kp
    ui->DSP_Kpm->setValue(KP_INIT_REGULADOR_MOTOR);
    ui->DSP_Kpc->setValue(KP_INIT_REGULADOR_CRUCERO);
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

void MainWindow::on_VS_refm_sliderMoved(int position)
{
    double ref=position/100.0;
    varMot->Set_r(ref);
    ui->LCDN_refm->display(ref);
}

void MainWindow::on_VS_refc_sliderMoved(int position)
{
    double ref=position/100.0;
    varCru->Set_r(ref);
    ui->LCDN_refc->display(ref);
}

void MainWindow::on_DSP_Kpm_valueChanged(double Kp)
{
    regMot->Set_Kp(Kp);
}

void MainWindow::on_DSP_Kpc_valueChanged(double Kp)
{
    regCru->Set_Kp(Kp);
}
