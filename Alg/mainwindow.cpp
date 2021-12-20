#include "mainwindow.h"
#include "ui_mainwindow.h"




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
        //и добавить реакцию на изменение значения спинбокса
    ws.push_back(win_setup(true,true,false,false,false,false,"a = ","b = ","","","",""));
    ws.push_back(win_setup(true,true,false,false,false,false,"a = ","b = ","","","",""));
    ws.push_back(win_setup(true,true,true,false,false,false,"a = ","b = ","модуль","","",""));
    ws.push_back(win_setup(true,true,true,false,false,false,"показатель","основание","модуль","","",""));
    ws.push_back(win_setup(false,false,false,true,true,false,"","","","P1","P2",""));//евклид для полиномов
    ws.push_back(win_setup(false,false,false,true,true,true,"","","","модуль m(x)","P1","P2"));//евклид для полиномов
    ws.push_back(win_setup(false,false,false,false,false,false,"test","test","test","test","test","test"));

    pa.push_back(ui->lineEdit_pc_a_0);
    pa.push_back(ui->lineEdit_pc_a_1);
    pa.push_back(ui->lineEdit_pc_a_2);
    pa.push_back(ui->lineEdit_pc_a_3);
    pa.push_back(ui->lineEdit_pc_a_4);
    pa.push_back(ui->lineEdit_pc_a_5);
    pa.push_back(ui->lineEdit_pc_a_6);
    pa.push_back(ui->lineEdit_pc_a_7);
    pa.push_back(ui->lineEdit_pc_a_8);
    pa.push_back(ui->lineEdit_pc_a_9);

    pb.push_back(ui->lineEdit_pc_b_0);
    pb.push_back(ui->lineEdit_pc_b_1);
    pb.push_back(ui->lineEdit_pc_b_2);
    pb.push_back(ui->lineEdit_pc_b_3);
    pb.push_back(ui->lineEdit_pc_b_4);
    pb.push_back(ui->lineEdit_pc_b_5);
    pb.push_back(ui->lineEdit_pc_b_6);
    pb.push_back(ui->lineEdit_pc_b_7);
    pb.push_back(ui->lineEdit_pc_b_8);
    pb.push_back(ui->lineEdit_pc_b_9);

    pc.push_back(ui->lineEdit_pc_c_0);
    pc.push_back(ui->lineEdit_pc_c_1);
    pc.push_back(ui->lineEdit_pc_c_2);
    pc.push_back(ui->lineEdit_pc_c_3);
    pc.push_back(ui->lineEdit_pc_c_4);
    pc.push_back(ui->lineEdit_pc_c_5);
    pc.push_back(ui->lineEdit_pc_c_6);
    pc.push_back(ui->lineEdit_pc_c_7);
    pc.push_back(ui->lineEdit_pc_c_8);
    pc.push_back(ui->lineEdit_pc_c_9);

    alg_names   << "Карацуба"
                << "Алгоритм Евклида"
                << "Остаток от умножения"
                << "Остаток от степени"
                << "Алгоритм Евклида (полиномы)"
                << "Остаток от умножения (полиномы)"
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
    case EUCLID_POLY:
    {
        //тут почитаем и закинем в функцию все что нужно
        Poly t1,t2;
        int Z = ui->lineEdit_z->text().toInt();
        t1.degree = ui->spinBox_a->value();
        for (size_t i = 0; i<= t1.degree; i++)
        {
            t1.coeff.push_back(pa[i]->text().toInt());
        }
        t2.degree = ui->spinBox_b->value();
        for (size_t i = 0; i<= t2.degree; i++)
        {
            t2.coeff.push_back(pb[i]->text().toInt());
        }
        std::vector<std::vector<Poly>> res;
        std::vector<QString> names {"q","u","v","r"};
        text += "ответ: " + euclidP(t1,t2,&res,Z).to_text() + "\n";
        text += poly_vec_to_text(&res,names,4);


        break;
    }
    case REM_MUL_POLY:
    {
        Poly t1,t2,m;
        int Z = ui->lineEdit_z->text().toInt();


        m.degree = ui->spinBox_a->value();
        for (size_t i = 0; i<= m.degree; i++)
        {
            m.coeff.push_back(pa[i]->text().toInt());
        }
        t1.degree = ui->spinBox_b->value();
        for (size_t i = 0; i<= t1.degree; i++)
        {
            t1.coeff.push_back(pb[i]->text().toInt());
        }
        t2.degree = ui->spinBox_c->value();
        for (size_t i = 0; i<= t2.degree; i++)
        {
            t2.coeff.push_back(pc[i]->text().toInt());
        }
        std::vector<std::vector<Poly>> res;
        std::vector<QString> names {"a","b","b'","c"};
        text += "ответ: " + rem_mulP(t1,t2,m,&res,Z).to_text() + "\n";
        text += poly_vec_to_text(&res,names,4);

        Poly tmp = t1*t2;
        tmp = tmp.norm_ext(Z,m);
        text += "\n" + tmp.to_text();

        break;

    }
    case TEST:
    {
        Poly t1,t2,rez,rem,rez_d;

/*        t1.degree = 1;
        t1.coeff.push_back(3);
        t1.coeff.push_back(4);

        t2.degree = 0;

        t2.coeff.push_back(2);    */

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

//        rez = t1+t2;
//        text += "\nсложение:  " + rez.to_text();
        /*
        for (unsigned int i=0; i<=rez.degree; i++)
        {
            text += QString::number(rez.coeff[i]);
            text += " | ";
        }
*/
//        rez = t1-t2;
//        text += "\nвычитание:  " + rez.to_text();
        /*
        for (unsigned int i=0; i<=rez.degree; i++)
        {
            text += QString::number(rez.coeff[i]);
            text += " | ";
        }*/

//        rez = t1*t2;
//        text += "\nумножение:  " + rez.to_text();
        /*
        for (unsigned int i=0; i<=rez.degree; i++)
        {
            text += QString::number(rez.coeff[i]);
            text += " | ";
        }*/

//        poly_div(t1,t2,&rez_d,&rem,5);
//        text += "\nрезультат деления:  " + rez_d.to_text();
        /*
        for (unsigned int i=0; i<=rez_d.degree; i++)
        {
            text += QString::number(rez_d.coeff[i]);
            text += " | ";
        }*/
//        text += "\nостаток от деления:  " + rem.to_text();
        /*
        for (unsigned int i=0; i<=rem.degree; i++)
        {
            text += QString::number(rem.coeff[i]);
            text += " | ";
        }
*/

        int Z = 5;
        std::vector<std::vector<Poly>> res;
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
    for (size_t i = 0; i<10; i++)
    {
        pa[i]->setText("");
        pb[i]->setText("");
        pc[i]->setText("");
        if (i<=ui->spinBox_a->value()) pa[i]->setEnabled(ws[index].ap);
        else pa[i]->setEnabled(false);
        if (i<=ui->spinBox_b->value()) pb[i]->setEnabled(ws[index].bp);
        else pb[i]->setEnabled(false);
        if (i<=ui->spinBox_c->value()) pc[i]->setEnabled(ws[index].cp);
        else pc[i]->setEnabled(false);
    }
    ui->spinBox_a->setEnabled(ws[index].ap);
    ui->spinBox_b->setEnabled(ws[index].bp);
    ui->spinBox_c->setEnabled(ws[index].cp);

    ui->lineEdit_z->setEnabled(ws[index].ap || ws[index].bp || ws[index].cp);

    if (ws[index].ap || ws[index].bp || ws[index].cp)
    {
        ui->label_z->setText("Z = ");
    }
    else
    {
        ui->label_z->setText("");
    }

    ui->plainTextEdit_res->setPlainText("");
    ui->lineEdit_a->setEnabled(ws[index].a);
    ui->lineEdit_b->setEnabled(ws[index].b);
    ui->lineEdit_c->setEnabled(ws[index].c);
    ui->label_a->setText(ws[index].lb_a);
    ui->label_b->setText(ws[index].lb_b);
    ui->label_c->setText(ws[index].lb_c);
    ui->label_pa->setText(ws[index].lbp_a);
    ui->label_pb->setText(ws[index].lbp_b);
    ui->label_pc->setText(ws[index].lbp_c);
}

QString poly_vec_to_text(std::vector<std::vector<Poly>> *res, std::vector<QString> names, int size) // size - количество строк не считая строку с i
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


void MainWindow::on_spinBox_a_valueChanged(int arg1)
{
    for (int i = 0; i < 10; i++)
    {
        if (i <=arg1)
        {
            pa[i]->setEnabled(true);
        }
        else
        {
            pa[i]->setEnabled(false);
        }
    }
}

void MainWindow::on_spinBox_b_valueChanged(int arg1)
{
    for (int i = 0; i < 10; i++)
    {
        if (i <=arg1)
        {
            pb[i]->setEnabled(true);
        }
        else
        {
            pb[i]->setEnabled(false);
        }
    }
}

void MainWindow::on_spinBox_c_valueChanged(int arg1)
{
    for (int i = 0; i < 10; i++)
    {
        if (i <=arg1)
        {
            pc[i]->setEnabled(true);
        }
        else
        {
            pc[i]->setEnabled(false);
        }
    }
}
