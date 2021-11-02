#include "mainwindow.h"
#include "ui_mainwindow.h"




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ws.push_back(win_setup(true,true,false,"a = ","b = ",""));
    ws.push_back(win_setup(true,true,false,"a = ","b = ",""));
    ws.push_back(win_setup(true,true,true,"a = ","b = ","модуль"));
    ws.push_back(win_setup(true,true,true,"показатель","основание","модуль"));

    alg_names   << "Карацуба"
                << "Алгоритм Евклида"
                << "Остаток от умножения"
                << "Остаток от степени";
    ui->comboBox->addItems(alg_names);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString text;
    switch (ui->comboBox->currentIndex())
    {
    case KARATSUBA:
    {
        std::vector <long*> *res = new std::vector <long*>;
        long long mul = karatsuba(ui->lineEdit_a->text().toLongLong(),ui->lineEdit_b->text().toLongLong(),res);
        text += "Результат: " + QString::number(mul) + "\n";
        text += "a\tb\tn\tA1\tB1\tA\tA0\tB0\tB\tta\ttb\tC\n\n";
        for (size_t i = 0; i<res->size(); i++)
        {
            for (int j = 0; j < 12; j++)
            {
                text +=  QString::number((*res)[i][j]) + "\t";
            }
            text += "\n";
        }
        break;
    }
    case EUCLID:
    {
        std::vector <long*> *res = new std::vector <long*>;
        long long nod = euclid(ui->lineEdit_a->text().toLongLong(),ui->lineEdit_b->text().toLongLong(),res);

        text += "НОД: " + QString::number(nod) + " = " +
                QString::number((*res)[0][4]) + " * (" + QString::number((*res)[res->size()-2][2]) + ") + " +
                QString::number((*res)[1][4]) + " * (" + QString::number((*res)[res->size()-2][3]) + ")\n\n";
        text += "i\tq\tu\tv\tr\n";
        for (size_t i = 0; i<res->size(); i++)
        {
            for (int j = 0; j < 5; j++)
            {
                text +=  QString::number((*res)[i][j]) + "\t";
            }
            text += "\n";
        }
        break;
    }
    case REM_MUL:
    {
        std::vector <long*> *res = new std::vector <long*>;
        long long mul = rem_mul(ui->lineEdit_a->text().toLongLong(),ui->lineEdit_b->text().toLongLong(),ui->lineEdit_c->text().toLongLong(),res);
        text += "Результат: " + QString::number(mul) + "\n";
        text += "i\ta\tb\tc\n";
        for (size_t i = 0; i<res->size(); i++)
        {
            for (int j = 0; j < 4; j++)
            {
                text +=  QString::number((*res)[i][j]) + "\t";
            }
            text += "\n";
        }

        break;
    }
    case REM_EXP:
    {
        std::vector <long*> *res = new std::vector <long*>;
        long long mul = rem_exp(ui->lineEdit_a->text().toLongLong(),ui->lineEdit_b->text().toLongLong(),ui->lineEdit_c->text().toLongLong(),res);
        text += "Результат: " + QString::number(mul) + "\n";
        text += "i\ta\tb\tc\n";
        for (size_t i = 0; i<res->size(); i++)
        {
            for (int j = 0; j < 4; j++)
            {
                text +=  QString::number((*res)[i][j]) + "\t";
            }
            text += "\n";
        }

        break;
    }
    default:
        text += "Ошибка при выборе алгоритма";
        break;
    }


    ui->plainTextEdit_res->setPlainText(text);
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    ui->lineEdit_a->setText("");
    ui->lineEdit_b->setText("");
    ui->lineEdit_c->setText("");
    ui->plainTextEdit_res->setPlainText("");
    ui->lineEdit_a->setEnabled(ws[index].a);
    ui->lineEdit_b->setEnabled(ws[index].b);
    ui->lineEdit_c->setEnabled(ws[index].c);
    ui->label_a->setText(ws[index].lb_a);
    ui->label_b->setText(ws[index].lb_b);
    ui->label_c->setText(ws[index].lb_c);
}
