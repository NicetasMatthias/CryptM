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
            tmp += "(" + QString::number(this->coeff[i]) + ")" + "x^" + QString::number(i) + " + ";
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
        while (tmp.coeff[i]<=0)
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
    return rm.norm_Z(Z);
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
    while (tmp.degree >= t2.degree && tmp.degree!=0)
    {
        std::vector <long*> *res = new std::vector <long*>;
        euclid(Z,t2.coeff[t2.degree],res);


        Poly tmp_del = (tmp.coeff[tmp.degree] * (*res)[(*res).size()-1][3]) *t2;
        int dif = tmp.degree-tmp_del.degree;
        tmp_del.degree += dif;
        r.coeff.insert(r.coeff.begin(), tmp.coeff[tmp.degree] * (*res)[(*res).size()-1][3]);
        for (unsigned int i = 0; i < (dif); i++)
        {
            tmp_del.coeff.insert(tmp_del.coeff.begin(),0);
        }
        tmp = (tmp-tmp_del);
        tmp.coeff[tmp.degree] %= Z;
        if (tmp.coeff[tmp.degree] == 0 && tmp.degree!=0)
        {
            tmp.coeff.erase(tmp.coeff.begin()+tmp.degree);
            tmp.degree--;
        }
    }
    if (tmp.degree == 0 && (r.coeff.size()-1)!=r.degree)
    {
        r.coeff.insert(r.coeff.begin(),tmp.coeff[0]/t2.coeff[0]);
        tmp.coeff[0] = tmp.coeff[0]%t2.coeff[0];
    }
    *rem = tmp.norm_Z(Z);
    *rez = r.norm_Z(Z);

}

Poly euclidP(Poly a, Poly b, std::vector<std::vector<Poly>> *res, unsigned int Z)
{
    std::vector <Poly> ta,tb;
    //Poly *tb = new Poly[5];

    Poly tmp;

    tmp.coeff.push_back(0);
    tmp.degree = 0;
    ta.push_back(tmp);
    tmp.coeff.clear();

    tmp.coeff.push_back(0);
    tmp.degree = 0;
    ta.push_back(tmp);
    tmp.coeff.clear();


    tmp.coeff.push_back(1);
    tmp.degree = 0;
    ta.push_back(tmp);
    tmp.coeff.clear();

    tmp.coeff.push_back(0);
    tmp.degree = 0;
    ta.push_back(tmp);
    tmp.coeff.clear();

    ta.push_back(a);
    (*res).push_back(ta);



    tmp.coeff.push_back(1);
    tmp.degree = 0;
    tb.push_back(tmp);
    tmp.coeff.clear();

    tmp.coeff.push_back(0);
    tmp.degree = 0;
    tb.push_back(tmp);
    tmp.coeff.clear();

    tmp.coeff.push_back(0);
    tmp.degree = 0;
    tb.push_back(tmp);
    tmp.coeff.clear();

    tmp.coeff.push_back(1);
    tmp.degree = 0;
    tb.push_back(tmp);
    tmp.coeff.clear();

    tb.push_back(b);
    (*res).push_back(tb);

    size_t i = 2;
    while (1)
    {
        std::vector <Poly> tmpv;
        tmpv.resize(5);
        Poly rz,rm;
        poly_div((*res)[i-2][4],(*res)[i-1][4],&rz,&rm,Z);
        tmpv[0].coeff.push_back(i);
        tmpv[0].degree = 0;
        tmpv[1] = rz;
        tmpv[2] = (*res)[i-2][2] - (*res)[i-1][2]*tmpv[1];
        tmpv[2] = tmpv[2].norm_Z(Z);
        tmpv[3] = (*res)[i-2][3] - (*res)[i-1][3]*tmpv[1];
        tmpv[3] = tmpv[3].norm_Z(Z);
        tmpv[4] = rm;



        if (tmpv[4].degree == 0 && tmpv[4].coeff[0] == 0)
        {
            tmpv.clear();
            break;
        }
        else
        {
            res->push_back(tmpv);
            i++;
        }
    }

    return (*res)[i-1][4];
}


Poly rem_mulP(Poly a, Poly b, Poly m, std::vector <std::vector<Poly>> *res, unsigned int Z)
{
    size_t i = 0;

    while (1)
    {
        std::vector<Poly> tmp;
        tmp.resize(5);
        tmp[0].degree = 0;
        tmp[0].coeff.push_back(i);
        if (i == 0)
        {
            tmp[1] = a.norm_Z(Z);
            tmp[2] = b.norm_Z(Z);
            tmp[3] = tmp[2];
            tmp[3].coeff.insert(tmp[3].coeff.begin(),0);
            tmp[3].degree++;
            tmp[4].degree = 0;
            tmp[4].coeff.push_back(0);
        }
        else
        {
            tmp[1] = (*res)[i-1][1];
            tmp[1].coeff.erase(tmp[1].coeff.begin());
            tmp[1].degree--;
            tmp[2] = (*res)[i-1][3].norm_ext(Z,m);
            tmp[3] = tmp[2];
            tmp[3].coeff.insert(tmp[3].coeff.begin(),0);
            tmp[3].degree++;
            if((*res)[i-1][1].coeff[0] != 0)
            {
                tmp[4] = ((*res)[i-1][4] +   ((*res)[i-1][1].coeff[0]*(*res)[i-1][2]));
                tmp[4] = tmp[4].norm_ext(Z,m);
            }
            else
            {
                tmp[4] = (*res)[i-1][4].norm_Z(Z);
            }
        }
        res->push_back(tmp);
        if (tmp[1].degree == 0)
        {
            break;
        }
        else
        {
            i++;
        }
    }

    Poly ans = ((*res)[i][1].coeff[0]*(*res)[i][2]+(*res)[i][4]);
    return ans.norm_Z(Z);


}
