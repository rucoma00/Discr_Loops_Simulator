#include "mainwindow.h"
#include "ui_mainwindow.h"

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
}

MainWindow::~MainWindow()
{
    delete ui;
}

