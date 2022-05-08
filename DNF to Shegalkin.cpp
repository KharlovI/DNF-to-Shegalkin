#include <iostream>

#include "BoolAlgebra.h"

int main()
{
    BoolVar x = { "x", false }, nx = { "x", true }, y = { "y", false }, ny = { "y", true }, z = { "z", false }, nz = { "z", true };

    EK ek1, ek2, ek3;
    ek1.append(&x); ek1.append(&ny); ek1.append(&z);
    ek2.append(&nx); ek2.append(&ny); ek2.append(&z);
    ek3.append(&x); ek3.append(&ny); ek3.append(&nz);
    DNF dnf1;
    dnf1.append(&ek1); dnf1.append(&ek2); dnf1.append(&ek3);

    PolinomShehalkina resultDnf = genPolinom(dnf1);
    for (u_int64 i = 0; i < resultDnf.size(); i++)
    {
        for (u_int64 j = 0; j < resultDnf[i].size(); j++)
            std::cout << resultDnf[i][j];
        std::cout << " ";
    }
    std::cout << std::endl;

    ED ed1, ed2;
    ed1.append(&x); ed1.append(&ny); ed1.append(&nz);
    ed2.append(&x); ed2.append(&ny);
    KNF knf1;
    knf1.append(&ed1); knf1.append(&ed2);

    PolinomShehalkina resultKnf = genPolinom(knf1);
    for (u_int64 i = 0; i < resultKnf.size(); i++)
    {
        for (u_int64 j = 0; j < resultKnf[i].size(); j++)
            std::cout << resultKnf[i][j];
        std::cout << " ";
    }
    std::cout << std::endl;
}

