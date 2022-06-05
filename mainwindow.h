#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "variablescompartidas.h"
#include "regulador.h"
#include "qcustomplot.h"

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

    void on_VS_refm_sliderMoved(int position);

    void on_VS_refc_sliderMoved(int position);

    void on_DSP_Kpm_valueChanged(double Kp);

    void on_DSP_Kpc_valueChanged(double Kp);

    void ActualizarGraficas();

private:
    Ui::MainWindow *ui;

    Regulador *regMot;
    Regulador *regCru;
    VariablesCompartidas *varMot;
    VariablesCompartidas *varCru;

    QTimer dataTimer;
};
#endif // MAINWINDOW_H
