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

    // Configuración de la gráfica del motor
    ui->QCP_m->addGraph(); // Referencia en azul
    ui->QCP_m->graph(0)->setPen(QPen(QColor(40, 110, 255)));
    ui->QCP_m->addGraph(); // Salida en rojo
    ui->QCP_m->graph(1)->setPen(QPen(QColor(255, 110, 40)));
    //ui->QCP_m->addGraph(); // Accion de control en amarillo
    //ui->QCP_m->graph(2)->setPen(QPen(QColor(255, 255, 0)));

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    ui->QCP_m->xAxis->setTicker(timeTicker);
    ui->QCP_m->axisRect()->setupFullAxesBox();
    ui->QCP_m->yAxis->setRange(-1.2, 1.2);

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui->QCP_m->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->QCP_m->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->QCP_m->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->QCP_m->yAxis2, SLOT(setRange(QCPRange)));

    // Configuración de la gráfica del crucero
    ui->QCP_c->addGraph(); // Referencia en azul
    ui->QCP_c->graph(0)->setPen(QPen(QColor(40, 110, 255)));
    ui->QCP_c->addGraph(); // Salida en rojo
    ui->QCP_c->graph(1)->setPen(QPen(QColor(255, 110, 40)));
    //ui->QCP_c->addGraph(); // Accion de control en amarillo
    //ui->QCP_c->graph(2)->setPen(QPen(QColor(255, 255, 0)));

    //QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    ui->QCP_c->xAxis->setTicker(timeTicker);
    ui->QCP_c->axisRect()->setupFullAxesBox();
    ui->QCP_c->yAxis->setRange(-1.2, 1.2);

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui->QCP_c->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->QCP_c->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->QCP_c->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->QCP_c->yAxis2, SLOT(setRange(QCPRange)));

    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
    connect(&dataTimer, SIGNAL(timeout()), this, SLOT(ActualizarGraficas()));
    dataTimer.start(0); // Interval 0 means to refresh as fast as possible
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

void MainWindow::ActualizarGraficas()
{
    static QTime timeStart = QTime::currentTime();
    // calculate two new data points:
    double key = timeStart.msecsTo(QTime::currentTime())/1000.0; // time elapsed since start of demo, in seconds
    static double lastPointKey = 0;
    if (key-lastPointKey > 0.002) // at most add point every 2 ms
    {
      // add data to lines:
      ui->QCP_m->graph(0)->addData(key, varMot->Get_r());
      ui->QCP_m->graph(1)->addData(key, varMot->Get_yk(0));
      // rescale value (vertical) axis to fit the current data:
      ui->QCP_m->graph(0)->rescaleValueAxis();
      ui->QCP_m->graph(1)->rescaleValueAxis(true);

      ui->QCP_c->graph(0)->addData(key, varCru->Get_r());
      ui->QCP_c->graph(1)->addData(key, varCru->Get_yk(0));
      // rescale value (vertical) axis to fit the current data:
      ui->QCP_c->graph(0)->rescaleValueAxis();
      ui->QCP_c->graph(1)->rescaleValueAxis(true);
      lastPointKey = key;
    }

    // make key axis range scroll with the data (at a constant range size of 8):
    ui->QCP_m->xAxis->setRange(key, 8, Qt::AlignRight);
    ui->QCP_m->replot();

    // make key axis range scroll with the data (at a constant range size of 8):
    ui->QCP_c->xAxis->setRange(key, 8, Qt::AlignRight);
    ui->QCP_c->replot();
}
