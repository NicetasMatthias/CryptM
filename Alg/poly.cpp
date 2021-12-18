#include "poly.h"

Poly::Poly()
{
}

QString Poly::to_text()
{
    QString tmp;
    for (int i = this->degree; i >= 0; i--)
    {
        if (i != 0)
        {
            tmp += "x^" + QString::number(i) + "*(" + QString::number(this->coeff[i]) + ")" + " + ";
        }
        else
        {
            tmp += "(" + QString::number(this->coeff[i]) + ")";
        }
    }
    return tmp;
}

Poly Poly::norm_deg()
{
    Poly tmp = *this;
    for (int i = tmp.degree; i > 0; i--)
    {
        if (tmp.coeff[i] == 0 && i != 0)
        {
            tmp.coeff.pop_back();
            tmp.degree--;
        }
        else
        {
            break;
        }
    }
    return tmp;
}

Poly Poly::norm_Z(int Z)
{
    Poly tmp = *this;
    for(size_t i = 0; i <= tmp.degree; i++)
    {
        while (tmp.coeff[i]<0)
        {
            tmp.coeff[i] += Z;
        }
        tmp.coeff[i] = tmp.coeff[i]%Z;
    }
    return tmp.norm_deg();
}

Poly Poly::norm_ext(int Z, Poly P)
{
    Poly rm,rz;
    poly_div(*this,P,&rz,&rm,Z);
    return rm;
}

Poly Poly::operator-() const
{
    return -1*(*this);
}
Poly const operator* (Poly const& left, Poly const& right)
{
    Poly t1=left, t2=right, rez;
    rez.degree = t1.degree + t2.degree;

    for (size_t i=0; i<=rez.degree; i++)
    {
        rez.coeff.push_back(0);
    }

    for (size_t i=0; i<=t1.degree; i++)
    {
        for (size_t j=0; j<=t2.degree; j++)
        {
            rez.coeff[i+j]+=t1.coeff[i]*t2.coeff[j];
        }
    }
    return rez;
}
Poly const operator* (int const& left, Poly const& right)
{
    Poly t = right;
    for (size_t i = 0; i <= t.degree; i++)
    {
        t.coeff[i]*=left;
    }
    return t;
}
Poly const operator+ (Poly const& left, Poly const& right)
{
    Poly t1, t2, rez;
    if (left.degree >= right.degree)
    {
        t1 = left;
        t2 = right;
    }
    else
    {
        t1 = right;
        t2 = left;
    }

    rez.degree = t1.degree;

    for (size_t i=0; i<=t1.degree; i++)
    {
        if (i>t2.degree)
        {
            rez.coeff.push_back(t1.coeff[i]);
        }
        else
        {
            rez.coeff.push_back(t1.coeff[i]+t2.coeff[i]);
        }
    }
    return rez.norm_deg();

}
Poly const operator- (Poly const& left, Poly const& right)
{
    return left + (-right);
}
/*Poly const operator/ (Poly const& left, Poly const& right)
{
    Poly t1 = left, t2 = right, rez;
    rez.degree = t1.degree;
}*/

void poly_div(Poly t1, Poly t2, Poly *rez, Poly *rem, int Z)
{
    Poly r;
    if (t1.degree<t2.degree)
    {
        *rem = t1;
        r.degree = 0;
        r.coeff.push_back(0);
        *rez = r;
        return;
    }
    r.degree = t1.degree - t2.degree;
    Poly tmp = t1;
    while (tmp.degree >= t2.degree)
    {
        std::vector <long*> *res = new std::vector <long*>;
        euclid(Z,t2.coeff[t2.degree],res);

//        Poly tmp_del = (tmp.coeff[tmp.degree] * ((*res)[(*res).size()-1][3])  ) *t2;
        //int temp_int = (*res)[(*res).size()-1][3];
        Poly tmp_del = (tmp.coeff[tmp.degree] * (*res)[(*res).size()-1][3]) *t2;
        int dif = tmp.degree-tmp_del.degree;
        tmp_del.degree += dif;
        r.coeff.insert(r.coeff.begin(),tmp.coeff[tmp.degree]* (*res)[(*res).size()-1][3]);
        for (unsigned int i = 0; i < (dif); i++)
        {
            tmp_del.coeff.insert(tmp_del.coeff.begin(),0);
        }
        tmp = (tmp-tmp_del);
        tmp = tmp.norm_Z(Z);
    }
    *rem = tmp.norm_Z(Z);
    *rez = r.norm_Z(Z);

}

Poly euclidP(Poly a, Poly b, std::vector<Poly *> *res, unsigned int Z)
{
    Poly *ta = new Poly[5];
    Poly *tb = new Poly[5];

    ta[0].coeff.push_back(0);
    ta[0].degree = 0;

    ta[1].coeff.push_back(0);
    ta[1].degree = 0;


    ta[2].coeff.push_back(1);
    ta[2].degree = 0;

    ta[3].coeff.push_back(0);
    ta[3].degree = 0;

    ta[4] = a;
    (*res).push_back(ta);

    tb[0].coeff.push_back(1);
    tb[0].degree = 0;

    tb[1].coeff.push_back(0);
    tb[1].degree = 0;

    tb[2].coeff.push_back(0);
    tb[2].degree = 0;

    tb[3].coeff.push_back(1);
    tb[3].degree = 0;

    tb[4] = b;
    (*res).push_back(tb);

    size_t i = 2;
    while (1)
    {
        Poly *tmp = new Poly[5];
        Poly rz,rm;
        poly_div((*res)[i-2][4],(*res)[i-1][4],&rz,&rm,Z);
        tmp[0].coeff.push_back(i);
        tmp[0].degree = 0;
        tmp[1] = rz;
        tmp[2] = (*res)[i-2][2] - (*res)[i-1][2]*tmp[1];
        tmp[3] = (*res)[i-2][3] - (*res)[i-1][3]*tmp[1];
        tmp[4] = rm;



        if (tmp[4].degree < b.degree)
        {
            res->push_back(tmp);
            break;
        }
        else
        {
            res->push_back(tmp);
            i++;
        }
    }

    return (*res)[i][4];
}


