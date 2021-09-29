#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

#include <alg_math.h>

struct win_setup
{
    bool a;
    bool b;
    bool c;
    QString lb_a;
    QString lb_b;
    QString lb_c;
    win_setup(bool ai, bool bi, bool ci, QString ali, QString bli, QString cli)
    {
        a = ai;
        b = bi;
        c = ci;
        lb_a = ali;
        lb_b = bli;
        lb_c = cli;
    }
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

private:
    Ui::MainWindow *ui;
    QStringList alg_names;
    std::vector <win_setup> ws;
};
#endif // MAINWINDOW_H
