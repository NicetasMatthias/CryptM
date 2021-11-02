#include <rem_mul.h>

/* 0 - i
 * 1 - a
 * 2 - b
 * 3 - c
 */

long long rem_mul(long a, long b, long c, std::vector <long*> *res)
{
    size_t i = 0;

    while (1)
    {
        long *tmp = new long[4];
        tmp[0] = i;
        if (i == 0)
        {
            tmp[1] = a;
            tmp[2] = b;
            tmp[3] = 0;
        }
        else
        {
            tmp[1] = (*res)[i-1][1]/2;
            tmp[2] = (*res)[i-1][2]*2 > c ? (*res)[i-1][2]*2-c : (*res)[i-1][2]*2;
            tmp[3] = (*res)[i-1][3]+(*res)[i-1][1]%2*(*res)[i-1][2] > c ? (*res)[i-1][3]+(*res)[i-1][1]%2*(*res)[i-1][2]-c : (*res)[i-1][3]+(*res)[i-1][1]%2*(*res)[i-1][2];
        }
        res->push_back(tmp);
        if (tmp[1] == 1)
        {
            break;
        }
        else
        {
            i++;
        }
    }

    return (*res)[i][2]+(*res)[i][3]>c?(*res)[i][2]+(*res)[i][3]-c:(*res)[i][2]+(*res)[i][3];

}
