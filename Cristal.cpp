#include "Cristal.h"
#include <random>

using namespace std;

Cristal::Cristal(int tam_cristal, double W_cristal)
    :   potenciais_rede(tam_cristal, 0.0), W(W_cristal),
        N(tam_cristal) 
        
    {}

void Cristal::gerarPotenciais() {
    mt19937 rng(random_device{}());
    uniform_real_distribution<> dist(-W / 2.0, W / 2.0);

    for (int i = 0; i < N; ++i)
        potenciais_rede[i] = dist(rng);
}
