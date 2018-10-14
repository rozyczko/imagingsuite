#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLineSeries>
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) ,
    cnt(0)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QtCharts::QLineSeries *series=new QtCharts::QLineSeries();

    for (int i=0; i<10; ++i)
        series->append(qreal(i),qreal(std::rand() ));

    QString name;
    name.sprintf("Data %d", cnt);

    series->setName(name);
    ui->widget->setCurveData(cnt++,series);
}

void MainWindow::on_pushButton_3_clicked()
{
    if (cnt<=0) return;
    cnt--;
    ui->widget->clearCurve(cnt);
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->widget->clearAllCurves();
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->widget->showLegend();
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->widget->hideLegend();
}
