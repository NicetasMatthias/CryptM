#ifndef KARATSUBA_H
#define KARATSUBA_H
#include <QString>
#include <vector>

long long karatsuba(long long a,long long b, std::vector <long*> *res);
long karatsuba_sub(long long a,long long b, size_t *i, std::vector <long*> *res);



#endif // KARATSUBA_H
