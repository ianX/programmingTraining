#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>

#include <ctime>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <iterator>

#include "SP/Rect.h"

#include "addrectdialog.h"

std::ostream & operator << (std::ostream &out ,const SAParams &pamas)
{
    out<<"innerloop:\t"<<pamas.innerLoop<<'\n'
      <<"inittemp:\t"<<pamas.initTemp<<'\n'
     <<"finaltemp:\t"<<pamas.finalTemp<<'\n'
    <<"alpha:\t"<<pamas.alpha<<'\n'
    <<"beta:\t"<<pamas.beta<<std::endl;
    return out;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    layout()
{
    ui->setupUi(this);
    packingStrategy = new SPPackingStrategy;
    connect(ui->centralWidget,SIGNAL(removeRect(int)),this,SLOT(removeRect(int)));
    connect(ui->centralWidget, SIGNAL(updated()),this,SLOT(updateStatus()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::removeRect(int i)
{
    layout.removeRect(i);
    packingStrategy->initialPacking(layout);
    ui->centralWidget->updateStage(layout);
}

void MainWindow::updateStatus()
{
    pair<float,float> b = layout.compBorder();
    int w = b.first;
    int h = b.second;
    int area = w*h;
    vector<int> s1 ,s2;
    packingStrategy->getCommand(s1,s2);
    QString mess = tr("Area: ")+QString::number(area)+tr(";  width: ")+QString::number(w)+
            tr(";  height: ")+QString::number(h)+tr(";  ");
    mess += tr("s1: ");
    for(int i = 0;i<(int)s1.size();++i)
    {
        mess+=QString::number(s1[i])+tr(",");
    }
    mess +=tr(" s2: ");
    for(int i = 0;i< (int)s2.size();++i)
    {
        mess+=QString::number(s2[i])+tr(",");
    }
    ui->statusBar->showMessage(mess);
}

void MainWindow::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("rectanglePacker"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()) , QMessageBox::Ok);
        return;
    }

    QTextStream in(&file);
    int num = in.readLine().toInt();
    bool good = true;

    vector<Rect> rects;

    for(int i = 0;i<num && !in.atEnd();i++)
    {
        QString line = in.readLine();
        QStringList list = line.split(QChar(' '),QString::SkipEmptyParts);
        if(list.size() != 2)
        {
            good = false;
            break;
        }
        Rect rect;
        rect.width = list.at(0).toInt();
        rect.height = list.at(1).toInt();
        if(rect.width == 0 || rect.height == 0)
        {
            good = false;
            break;
        }

        rects.push_back(rect);
    }

    if((int)rects.size() != num)
        good = false;
    if(!good)
    {
        QMessageBox::warning(this, tr("rectanglePacker"),
                             tr("file format error %1.\n")
                             .arg(fileName) , QMessageBox::Ok);
        return;
    }

    layout.clear();
    for(vector<Rect>::iterator itr = rects.begin();itr != rects.end();++itr)
    {
        layout.addRect(*itr);
    }
}

double nextRand()
{
    int rnd = rand() % 65535;
    std::cout<<"rand:"<<rnd/65535.0<<std::endl;
    return rnd/65535.0;
}

void MainWindow::simulated_annealing()
{
    double ctemp = params.initTemp;
    int loop = params.innerLoop;
    srand(time(0));
    while(ctemp > params.finalTemp)
    {
        float carea = layout.compArea();
        for(int i = 0; i < loop; ++i)
        {
            this->packingStrategy->nextPackingCommand();
            this->packingStrategy->compPackingLayout(layout);
            float narea = layout.compArea();
            if(carea < narea && nextRand() > exp((carea-narea)/ctemp))
            {
                this->packingStrategy->fallBack(layout);
                continue;
            }
            ui->centralWidget->updateStage(layout);
        }
        ctemp *= params.alpha;
        loop *= params.beta;
    }
}

void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this);
    if(filename.size() == 0)
        return;
    loadFile(filename);
    packingStrategy->initialPacking(layout);
    ui->centralWidget->updateStage(layout);
}

void MainWindow::on_actionRandom_triggered()
{
    packingStrategy->initialPacking(layout);
    ui->centralWidget->updateStage(layout);
}

void MainWindow::on_actionSimulated_annealing_triggered()
{
    if(layout.getRectNum() == 0)
        return;
    this->setEnabled(false);
    this->simulated_annealing();
    this->setEnabled(true);
}

void MainWindow::on_actionSa_params_triggered()
{
    SAParamsDialog *dialog = new SAParamsDialog(this);
    dialog->show();
    this->setEnabled(false);

    dialog->setEnabled(true);
    dialog->exec();

    this->setEnabled(true);

    if(!dialog->isAccepted())
        return;

    params.innerLoop = dialog->getInnerLoop(params.innerLoop);
    params.alpha = dialog->getAlpha(params.alpha);
    params.beta = dialog->getBeta(params.beta);
    params.initTemp = dialog->getInitTemp(params.initTemp);
    params.finalTemp = dialog->getFinalTemp(params.finalTemp);
    cout<<params;
}

void MainWindow::on_actionAdd_rect_triggered()
{
    AddRectDialog *dialog = new AddRectDialog(this);
    dialog->show();

    this->setEnabled(false);

    dialog->setEnabled(true);
    dialog->exec();

    this->setEnabled(true);
    if(!dialog->isAccepted())
        return;
    Rect r;
    r.width = dialog->getWidth();
    r.height = dialog->getHeight();
    layout.addRect(r);
    packingStrategy->initialPacking(layout);
    ui->centralWidget->updateStage(layout);
}
