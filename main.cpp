// OBJETIVO DO PROGRAMA: resolver a Equação de Schrödinger para múltiplos sítios, simulando comportamento de um elétron dentro de um cristal
// Essa simulação calculará as medições de retorno, participação, desvio quadrático e o centróide da função de onda,
// se utilizando de uma largura de desordem previamente escrita no código.

#include <iostream>
#include <complex>
#include <math.h>
#include <time.h>
#include <vector>
#include <random>

#define PI 3.1415926535

using namespace std;

class WaveFunction
{
public:
    vector<complex<double>> psi;
    vector<double> pot;
    float W;

    WaveFunction(int tam_cristal, float W)
    {
        for (int i=0; i<tam_cristal; i++)
        {
            psi[i] = 0;
            pot[i] = 0;
        }
    };

    void evoluir(vector<float> t_fotos)
    {
        float t_max = psi.size() / 5.0; 
        evoluir(t_fotos, t_max); 
    };

    void evoluir(vector<float> t_fotos, float t_max)
    {

    }

    void gerarPotenciais()
    {
        srand(time(NULL));
        
        float W_inf = ((W * -1.0) / 2.0);
        float W_sup = W / 2.0; 

        for (int i=0; i<psi.size(); i++)
        {
            pot[i] = W_inf + (W_sup - W_inf) * ((double)rand() / RAND_MAX);
        }        
    };

    complex<double> dpsi_dt(
        complex<double> psi_anterior,
        complex<double> psi_posterior,
        complex<double> psi_atual,
        double pot_atual)

    {

    };
};

int main()
{
}