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
    ws.push_back(win_setup(false,false,false,"test","test","test"));

    alg_names   << "Карацуба"
                << "Алгоритм Евклида"
                << "Остаток от умножения"
                << "Остаток от степени"
                << "test";
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
    case TEST:
    {
        Poly t1,t2,rez,rem,rez_d;


        t1.degree = 3;
        t1.coeff.push_back(2);
        t1.coeff.push_back(4);
        t1.coeff.push_back(0);
        t1.coeff.push_back(1);

        t2.degree = 2;

        t2.coeff.push_back(0);
        t2.coeff.push_back(0);
        t2.coeff.push_back(3);

        /*
        t1.degree = 4;
        t1.coeff.push_back(4);
        t1.coeff.push_back(2);
        t1.coeff.push_back(0);
        t1.coeff.push_back(5);
        t1.coeff.push_back(3);

        t2.degree = 2;

        t2.coeff.push_back(1);
        t2.coeff.push_back(2);
        t2.coeff.push_back(1);
        */
        /*
        t1.degree = 3;
        t1.coeff.push_back(0);
        t1.coeff.push_back(1);
        t1.coeff.push_back(0);
        t1.coeff.push_back(1);

        t2.degree = 4;

        t2.coeff.push_back(-4);
        t2.coeff.push_back(0);
        t2.coeff.push_back(5);
        t2.coeff.push_back(0);
        t2.coeff.push_back(3);
        */
        text += "\nP1:  " + t1.to_text();
        /*
        for (unsigned int i=0; i<=t1.degree; i++)
        {
            text += QString::number(t1.coeff[i]);
            text += " | ";
        }*/

        text += "\nP2:  " + t2.to_text();
        /*
        for (unsigned int i=0; i<=t2.degree; i++)
        {
            text += QString::number(t2.coeff[i]);
            text += " | ";
        }*/

        rez = t1+t2;
        text += "\nсложение:  " + rez.to_text();
        /*
        for (unsigned int i=0; i<=rez.degree; i++)
        {
            text += QString::number(rez.coeff[i]);
            text += " | ";
        }
*/
        rez = t1-t2;
        text += "\nвычитание:  " + rez.to_text();
        /*
        for (unsigned int i=0; i<=rez.degree; i++)
        {
            text += QString::number(rez.coeff[i]);
            text += " | ";
        }*/

        rez = t1*t2;
        text += "\nумножение:  " + rez.to_text();
        /*
        for (unsigned int i=0; i<=rez.degree; i++)
        {
            text += QString::number(rez.coeff[i]);
            text += " | ";
        }*/

        poly_div(t1,t2,&rez_d,&rem,7);
        text += "\nрезультат деления:  " + rez_d.to_text();
        /*
        for (unsigned int i=0; i<=rez_d.degree; i++)
        {
            text += QString::number(rez_d.coeff[i]);
            text += " | ";
        }*/
        text += "\nостаток от деления:  " + rem.to_text();
        /*
        for (unsigned int i=0; i<=rem.degree; i++)
        {
            text += QString::number(rem.coeff[i]);
            text += " | ";
        }
*/
        int Z = 7;
        std::vector<Poly *> res;
        std::vector<QString> names {"q","u","v","r"};
        text += "\n\nответ: " + euclidP(t1,t2,&res,Z).to_text();
        text += poly_vec_to_text(&res,names,4);

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

QString poly_vec_to_text(std::vector<Poly *> *res, std::vector<QString> names, int size) // size - количество строк не считая строку i
{
    QString buff;
    for (size_t i = 0; i < res->size(); i++)
    {
        buff += "\nШаг № " + QString::number((*res)[i][0].coeff[0]) + "\n";
        for (size_t j = 0; j < size; j++)
        {
            if (j<names.size())
            {
                buff += names[j] + ": ";
            }
            buff += (*res)[i][j+1].to_text() + "\n";
        }
    }
    return buff;
}










