#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

#include <QLineEdit>

#include <alg_math.h>

#include <poly.h>

struct win_setup
{
    bool a;
    bool b;
    bool c;
    bool ap;
    bool bp;
    bool cp;
    QString lb_a;
    QString lb_b;
    QString lb_c;
    QString lbp_a;
    QString lbp_b;
    QString lbp_c;
    win_setup(bool ai, bool bi, bool ci, bool api, bool bpi, bool cpi, QString ali, QString bli, QString cli, QString alpi, QString blpi, QString clpi)
    {
        a = ai;
        b = bi;
        c = ci;

        ap = api;
        bp = bpi;
        cp = cpi;

        lb_a = ali;
        lb_b = bli;
        lb_c = cli;

        lbp_a = alpi;
        lbp_b = blpi;
        lbp_c = clpi;


    }
};


enum alg_names
{
    KARATSUBA = 0,
    EUCLID,
    REM_MUL,
    REM_EXP,
    EUCLID_POLY,
    REM_MUL_POLY,
    TEST,

};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_comboBox_currentIndexChanged(int index);

    void on_spinBox_a_valueChanged(int arg1);

    void on_spinBox_b_valueChanged(int arg1);

    void on_spinBox_c_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
    QStringList alg_names;
    std::vector <win_setup> ws;

    std::vector <QLineEdit*> pa,pb,pc;
};

QString poly_vec_to_text(std::vector<std::vector<Poly>> *res, std::vector<QString> names, int size);
#endif // MAINWINDOW_H
