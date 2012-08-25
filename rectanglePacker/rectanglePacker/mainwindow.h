#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "SP/Layout.h"
#include "SP/SPPackingStrategy.h"
#include "SP/Rect.h"

#include "saparamsdialog.h"

#include <iostream>
using namespace RECTPACKING;

namespace Ui {
class MainWindow;
}

struct SAParams {
    double initTemp;
    double finalTemp;
    double alpha;
    double beta;
    int innerLoop;
    SAParams():initTemp(100.0),finalTemp(0.1),alpha(0.95),beta(1.0),innerLoop(100)
    {}
    friend std::ostream & operator << (std::ostream &out , const SAParams &pamas);
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    std::pair<float,float> getBorder(){return layout.compBorder();}
    std::vector<Rect> &getRects(){return layout.getRects();}
    
private slots:
    void on_actionOpen_triggered();

    void on_actionRandom_triggered();

    void on_actionSimulated_annealing_triggered();

    void on_actionSa_params_triggered();

    void on_actionAdd_rect_triggered();

    void removeRect(int);

private:
    Ui::MainWindow *ui;
    Layout layout;
    SPPackingStrategy *packingStrategy;

protected:
    SAParams params;
    void loadFile(const QString &filename);
    void simulated_annealing();
};

#endif // MAINWINDOW_H
