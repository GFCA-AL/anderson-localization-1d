#ifndef SIMULADOR_H
#define SIMULADOR_H

#include "WaveFunction.h"
#include "Cristal.h"
#include <string>
#include <complex>

class Simulador {
public:
    WaveFunction Psi;
    Cristal Cadeia;

    Simulador(float sigma, int tam_cristal, double W_cristal);

    void condInicial();
    void gerarPotenciais();
    void RK4();
    void evoluir(double t_fotos[], float t_max);
    void evoluir(double t_fotos[]);
    void salvarResultado(const double t, const double dado, const std::string& nome_arquivo);

private:
    std::complex<double> dpsi_dt(std::complex<double> psi_ant,
                                 std::complex<double> psi_post,
                                 std::complex<double> psi_atual,
                                 double pot_atual);
};

#endif
