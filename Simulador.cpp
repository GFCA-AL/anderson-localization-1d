#include "Simulador.h"
#include <fstream>
#include <iostream>
#include <format>
#include <ctime>

#define I std::complex<double>(0.0, 1.0)

using namespace std;

Simulador::Simulador(float sigma, int tam_cristal, double W_cristal)
    : Psi(WaveFunction(tam_cristal, sigma)), Cadeia(Cristal(tam_cristal, W_cristal)) {}

complex<double> Simulador::dpsi_dt(complex<double> psi_ant,
                                   complex<double> psi_post,
                                   complex<double> psi_atual,
                                   double pot_atual) {
    return -I * (psi_ant + psi_post + pot_atual * psi_atual);
}

void Simulador::condInicial() {
    Psi.condInicial();
}

void Simulador::gerarPotenciais() {
    Cadeia.gerarPotenciais();
}

void Simulador::RK4() {
    int N = Psi.psi.size();
    vector<complex<double>> k1(N), k2(N), k3(N), k4(N);
    double h = 0.01;

    for (int n = 1; n < N - 1; ++n)
        k1[n] = h * dpsi_dt(Psi.psi[n - 1], Psi.psi[n + 1], Psi.psi[n], Cadeia.potenciais_rede[n]);

    for (int n = 1; n < N - 1; ++n)
        k2[n] = h * dpsi_dt(Psi.psi[n - 1] + 0.5 * k1[n - 1],
                            Psi.psi[n + 1] + 0.5 * k1[n + 1],
                            Psi.psi[n] + k1[n],
                            Cadeia.potenciais_rede[n]);

    for (int n = 1; n < N - 1; ++n)
        k3[n] = h * dpsi_dt(Psi.psi[n - 1] + 0.5 * k2[n - 1],
                            Psi.psi[n + 1] + 0.5 * k2[n + 1],
                            Psi.psi[n] + k2[n],
                            Cadeia.potenciais_rede[n]);

    for (int n = 1; n < N - 1; ++n)
        k4[n] = h * dpsi_dt(Psi.psi[n - 1] + k3[n - 1],
                            Psi.psi[n + 1] + k3[n + 1],
                            Psi.psi[n] + k3[n],
                            Cadeia.potenciais_rede[n]);

    for (int n = 0; n < N; ++n)
        Psi.psi[n] += (1.0 / 6.0) * (k1[n] + 2.0 * k2[n] + 2.0 * k3[n] + k4[n]);
}

void Simulador::evoluir(double t_fotos[], float t_max) {
    condInicial();
    gerarPotenciais();

    string base = format("_w={:.2f}_{}.dat", Cadeia.W, time(0));
    string nome_r = "retorno" + base;
    string nome_pm = "posmedia" + base;
    string nome_pt = "part" + base;
    string nome_d = "variancia" + base;

    double t = 0.0, passo = 0.01;
    int t_foto = 0;

    while (t < t_max) {
        RK4();
        salvarResultado(t, Psi.calcRetorno(), nome_r);
        salvarResultado(t, Psi.calcPart(), nome_pt);
        salvarResultado(t, Psi.calcPM(), nome_pm);
        salvarResultado(t, Psi.calcVar(), nome_d);

        if (int(t) == t_fotos[t_foto]) {
            ofstream foto_arq(format("foto_t={:.2f}_w={:.2f}_ts={}.dat", t, Cadeia.W, time(0)));
            vector<double> psi2 = Psi.Psi2();
            for (size_t i = 0; i < psi2.size(); ++i)
                foto_arq << format("{} {:.5f}\n", i, psi2[i]);
            t_foto++;
        }

        t += passo;
    }
}

void Simulador::evoluir(double t_fotos[]) {
    evoluir(t_fotos, Psi.psi.size() / 5.0);
}

void Simulador::salvarResultado(const double t, const double dado, const string& nome_arquivo) {
    ofstream arquivo(nome_arquivo, ios::app);
    if (arquivo.is_open()) {
        arquivo << format("{:.6f} {:.6f}\n", t, dado);
    } else {
        cerr << "Erro ao abrir: " << nome_arquivo << endl;
    }
}
