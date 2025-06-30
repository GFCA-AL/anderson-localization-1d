#ifndef CRISTAL_H
#define CRISTAL_H

#include <vector>

class Cristal {
public:
    std::vector<double> potenciais_rede;
    double W;
    int N;

    Cristal(int tam_cristal, double W_cristal);
    void gerarPotenciais();
};

#endif
