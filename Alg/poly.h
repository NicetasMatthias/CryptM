#ifndef POLY_H
#define POLY_H

#include <vector>
#include <alg_math.h>

class Poly
{
public:
    Poly();
    unsigned int degree;
    std::vector <int> coeff;

    Poly norm_deg();
    Poly norm_Z(int);
    Poly norm_ext(int,Poly);
    QString to_text();


    Poly operator-() const;
    friend Poly const operator* (Poly const&, Poly const&);
    friend Poly const operator* (int const&, Poly const&);
    friend Poly const operator+ (Poly const&, Poly const&);
    friend Poly const operator- (Poly const&, Poly const&);
    friend Poly const operator/ (Poly const&, Poly const&);
};

void poly_div(Poly, Poly, Poly*, Poly*, int);
Poly euclidP(Poly a, Poly b, std::vector<std::vector<Poly>> *res, unsigned int Z);
Poly rem_mulP(Poly a, Poly b, Poly m, std::vector <std::vector<Poly>> *res, unsigned int Z);

#endif // POLY_H
