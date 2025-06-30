#ifndef WAVEFUNCTION_H
#define WAVEFUNCTION_H

#include <vector>
#include <complex>

class WaveFunction {
private:
    float sigmaDist;
    int N;

public:
    std::vector<std::complex<double>> psi;

    WaveFunction(int tam_cristal, float sigma);

    std::vector<double> Psi2();
    double calcRetorno();
    double calcPart();
    double calcVar();
    double calcPM();
    void condInicial();
};

#endif
