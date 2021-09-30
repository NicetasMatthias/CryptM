#include <karatsuba.h>


/* 0 - a
 * 1 - b
 * 2 - n
 * 3 - A1
 * 4 - B1
 * 5 - A
 * 6 - A0
 * 7 - B0
 * 8 - B
 * 9 - tA
 * 10 - tB
 * 11 - C
 */


long karatsuba_sub(long long a,long long b, size_t *i, std::vector <long*> *res)
{
    size_t tmp_i = *i;
    long ans;
    long *tmp = new long[12];
    (*res).push_back(tmp);
    int na = QString::number(a).length();
    int nb = QString::number(b).length();
    (*res)[tmp_i][0] = a;
    (*res)[tmp_i][1] = b;
    (*res)[tmp_i][2] = na>nb?na:nb;
    if ((*res)[tmp_i][2]%2==1)
    {
        (*res)[tmp_i][2]++;
    }
    (*res)[tmp_i][2]/=2;
    (*res)[tmp_i][3] = a / static_cast<long>(pow(10,(*res)[tmp_i][2]));
    (*res)[tmp_i][4] = b / static_cast<long>(pow(10,(*res)[tmp_i][2]));

    if (((*res)[tmp_i][3]>10)||((*res)[tmp_i][4]>10))
    {
        *i = *i+1;
        (*res)[tmp_i][5] = karatsuba_sub((*res)[tmp_i][3],(*res)[tmp_i][4],i,res);//рекурсия шагает в коммунизм
    }
    else
    {
        (*res)[tmp_i][5] = (*res)[tmp_i][3] * (*res)[tmp_i][4];
    }

    (*res)[tmp_i][6] = a % static_cast<long>(pow(10,(*res)[tmp_i][2]));
    (*res)[tmp_i][7] = b % static_cast<long>(pow(10,(*res)[tmp_i][2]));

    if (((*res)[tmp_i][6]>10)||((*res)[tmp_i][7]>10))
    {
        *i = *i+1;
        (*res)[tmp_i][8] = karatsuba_sub((*res)[tmp_i][6],(*res)[tmp_i][7],i,res);//рекурсия опять шагает в коммунизм
    }
    else
    {
        (*res)[tmp_i][8] = (*res)[tmp_i][6] * (*res)[tmp_i][7];
    }

    (*res)[tmp_i][9] = (*res)[tmp_i][3] + (*res)[tmp_i][6];
    (*res)[tmp_i][10] = (*res)[tmp_i][4] + (*res)[tmp_i][7];

    if (((*res)[tmp_i][9]>10)||((*res)[tmp_i][10]>10))
    {
        *i = *i+1;
        (*res)[tmp_i][11] = karatsuba_sub((*res)[tmp_i][9],(*res)[tmp_i][10],i,res);//финальный шаг в коммунизм (перестройка)
    }
    else
    {
        (*res)[tmp_i][11] = (*res)[tmp_i][9] * (*res)[tmp_i][10];
    }

    ans =   pow(10,(*res)[tmp_i][2]*2) * ( (*res)[tmp_i][5] ) +
            pow(10,(*res)[tmp_i][2]) * ( (*res)[tmp_i][11] - (*res)[tmp_i][5] - (*res)[tmp_i][8]) +
            (*res)[tmp_i][8];



    return ans;
}


long long karatsuba(long long a,long long b, std::vector <long*> *res)
{
    size_t *i= new size_t;
    *i = 0;
    long ans = karatsuba_sub(a,b,i,res);
    delete i;
    return ans;
}
