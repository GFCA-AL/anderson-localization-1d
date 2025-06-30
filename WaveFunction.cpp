#include "WaveFunction.h"
#include <cmath>

#define PI 3.1415926535

using namespace std;

WaveFunction::WaveFunction(int tam_cristal, float sigma)
    :   sigmaDist(sigma), N(tam_cristal),
        psi(tam_cristal, complex<double>(0.0, 0.0))
        
    {}

vector<double> WaveFunction::Psi2() {
    vector<double> psi2;
    for (auto psi_n : psi)
        psi2.push_back(norm(psi_n));
    return psi2;
}

double WaveFunction::calcRetorno() {
    return norm(psi[N / 2]);
}

double WaveFunction::calcPart() {
    double sum_sq = 0.0, sum_quart = 0.0;
    for (auto p : psi) {
        double nrm = norm(p);
        sum_sq += nrm;
        sum_quart += nrm * nrm;
    }
    return sum_sq / sum_quart;
}

double WaveFunction::calcPM() {
    double media = 0.0;
    for (int i = 0; i < N; ++i)
        media += i * norm(psi[i]);
    return media;
}

double WaveFunction::calcVar() {
    double var = 0.0, media = calcPM();
    for (int i = 0; i < N; ++i)
        var += pow(i - media, 2.0) * norm(psi[i]);
    return var;
}

void WaveFunction::condInicial() {
    if (sigmaDist != 0) {
        for (size_t n = 0; n < N; n++)
        {
            double centro = N / 2.0;
            psi[n] = (1.0 / sqrt(2.0 * PI * pow(sigmaDist, 2.0))) * 
                    exp(-1.0 * pow(n - centro, 2.0) / (2.0 * pow(sigmaDist, 2.0)));
        }
    }
    else
    {
        psi[N / 2] = complex<double>(1.0, 0.0);
    }
}