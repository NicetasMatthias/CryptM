#ifndef KARATSUBA_H
#define KARATSUBA_H
#include <QString>
#include <vector>
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


long long karatsuba(long long a,long long b, std::vector <long*> *res);
long karatsuba_sub(long long a,long long b, size_t *i, std::vector <long*> *res);



#endif // KARATSUBA_H
