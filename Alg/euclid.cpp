#include <euclid.h>

/*
 * 0 - i
 * 1 - q
 * 2 - u
 * 3 - v
 * 4 - r
 */

long euclid (long long a, long long b, std::vector<long *> *res)
{
    long *ta = new long[5];
    long *tb = new long[5];
    ta[0] = 0;
    ta[1] = 0;
    ta[2] = 1;
    ta[3] = 0;
    ta[4] = a;
    (*res).push_back(ta);
    tb[0] = 1;
    tb[1] = 0;
    tb[2] = 0;
    tb[3] = 1;
    tb[4] = b;
    (*res).push_back(tb);

    size_t i = 2;
    while (1)
    {
        long *tmp = new long[5];
        tmp[0] = i;
        tmp[1] = (*res)[i-2][4] / (*res)[i-1][4];
        tmp[2] = (*res)[i-2][2] - (*res)[i-1][2]*tmp[1];
        tmp[3] = (*res)[i-2][3] - (*res)[i-1][3]*tmp[1];
        tmp[4] = (*res)[i-2][4] % (*res)[i-1][4];



        if (tmp[4] == 0)
        {
            delete [] tmp;
            break;
        }
        else
        {
            res->push_back(tmp);
            i++;
        }
    }

    return (*res)[i-1][4];
}
