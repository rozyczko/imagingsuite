#include <cmath>

#include <QListWidgetItem>


#include <base/timage.h>
#include <generators/Sine2D.h>

#include <buildfilelist.h>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    logger("MainWindow"),
    ui(new Ui::MainWindow),
    m_fScale(1.0)
{
    ui->setupUi(this);
    kipl::logging::Logger::AddLogTarget(*ui->LogView);
    connect(ui->TestButton,SIGNAL(clicked()),this,SLOT(TestClicked()));
    connect(ui->PlotButton,SIGNAL(clicked()),this,SLOT(PlotClicked()));
    connect(ui->GetModulesButton,SIGNAL(clicked()),this,SLOT(GetModulesClicked()));

    ui->singlemodule->Configure("muhrec");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::TestClicked()
{
    logger(kipl::logging::Logger::LogMessage,"Testing");
}

void MainWindow::PlotClicked()
{
    logger(kipl::logging::Logger::LogMessage,"Plotting");
    QVector<QPointF> data;

    int N=10;
    for (int i=0; i<N; i++) {
        float x=i/float(N-1);
        data.append(QPointF(x,sin(2*3.1415*x)));
    }

    ui->CurvePlotter->setCurveData(0,data);
    ui->CurvePlotter->setPlotCursor(0,QtAddons::PlotCursor(0.5,QColor("blue"),QtAddons::PlotCursor::Vertical));
    ui->CurvePlotter->setPlotCursor(1,QtAddons::PlotCursor(0.25,QColor("red"),QtAddons::PlotCursor::Horizontal));
}

void MainWindow::on_ShowImageButton_clicked()
{
    m_fScale=fmod(m_fScale+1.0,10.0);
    kipl::base::TImage<float,2> img=kipl::generators::Sine2D::JaehneRings(100,m_fScale);

    ui->ImageView->set_image(img.GetDataPtr(),img.Dims());
    ui->ImageView_2->set_image(img.GetDataPtr(),img.Dims());
    int flip=static_cast<int>(m_fScale) & 1;
    if (flip) {
        ui->ImageView->set_rectangle(QRect(10,10,30,40),QColor(Qt::red),0);
    }
    else {
        QVector<QPointF> data;

        for (int i=0;i<static_cast<int>(img.Size(0)); i++)
            data.append(QPointF(i,20+50*sin(2*3.14*i/100.0f)));
        ui->ImageView->set_plot(data,QColor(Qt::green),0);
    }

}

void MainWindow::GetModulesClicked()
{
    std::list<ModuleConfig> modules=ui->ModuleConf->GetModules();

    std::list<ModuleConfig>::iterator it;
    std::ostringstream msg;
    msg<<"Got "<<modules.size()<<" modules from the widget\n";
    for (it=modules.begin(); it!=modules.end(); it++) {
        msg<<(it->m_sModule)<<"("<<(it->m_bActive ? "Active": "Disabled")<<"), has "<<(it->parameters.size())<<" parameters\n";
    }

    logger(kipl::logging::Logger::LogMessage,msg.str());
}

void MainWindow::on_GetROIButton_clicked()
{
    QRect rect=ui->ImageView->get_marked_roi();

    ui->roi_x0->setValue(rect.x());
    ui->roi_y0->setValue(rect.y());
    ui->roi_x1->setValue(rect.x()+rect.width());
    ui->roi_y1->setValue(rect.x()+rect.height());
}

void MainWindow::on_check_linkimages_toggled(bool checked)
{
    QtAddons::ImageViewerWidget *v1=dynamic_cast<QtAddons::ImageViewerWidget *>(ui->ImageView);
    QtAddons::ImageViewerWidget *v2=dynamic_cast<QtAddons::ImageViewerWidget *>(ui->ImageView_2);

    if (checked)
        v1->LinkImageViewer(v2);
    else
       v1->ClearLinkedImageViewers();
}

void MainWindow::on_pushButton_listdata_clicked()
{
    std::list<ImageLoader> loaderlist;

    loaderlist=ui->ImageLoaders->GetList();
    for (auto it=loaderlist.begin(); it!=loaderlist.end(); it++) {
        std::cout<<*it<<std::endl;
    }

    std::list<std::string> flist=BuildFileList(loaderlist);

    for (auto it=flist.begin(); it!=flist.end(); it++) {
        std::cout<<*it<<std::endl;
    }


}
