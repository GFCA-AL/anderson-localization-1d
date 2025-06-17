/**
 * @file main.cpp
 * @author Rafael Amorim (rafael.science.amorim@gmail.com)
 * @brief
 * @version 0.1
 * @date 2025-06-17
 **/

#include <iostream> // biblioteca padrão de entrada e saída
#include <complex>  // números complexos
#include <cmath>    // artifícios matemáticos
#include <time.h>   // biblioteca temporal
#include <vector>   // vetores
#include <random>   // números aleatórios

#define PI 3.1415926535 // PI

using namespace std;

/**
 * @class WaveFunction
 * @brief Representa a função de onda psi da partícula
 *
 * O objetivo dessa classe é gerenciar tudo o que for relacionado a
 * simulação da difusão da função de onda pelo cristal desordenado,
 * incluindo resolução numérica da Eq. de Schrödinger e a escrita dos
 * dados medidos em arquivos.
 */
class WaveFunction
{
public:
    vector<complex<double>> psi; // vetor função de onda (ket psi)
    vector<double> pot;          // vetor de potenciais do cristal (on-site energy)
    float W;                     // largura de desordem do sistema

    /**
     * @brief Inicializa um novo objeto WaveFunction
     *
     * @param tam_cristal tamanho da cadeia cristalina desejado
     * @param W_param largura da desordem desejada no sistema
     */
    WaveFunction(int tam_cristal, float W_param)
        :   psi(tam_cristal, complex<double>(0.0, 0.0)), // função de onda zerada
            pot(tam_cristal, 0.0),                       // potenciais zerados
            W(W_param)                                   // largura da desordem
    { }


    /**
     * @brief Overloading do método "evoluir()" -- possibilita a definição de um valor padrão para t_max;
     *
     * @param t_fotos Vetor com instantes de tempo para serem realizadas as "fotografias" de psi
     */
    void evoluir(vector<float> t_fotos)
    {
        float t_max = psi.size() / 5.0; // maior tempo possível que não gera efeitos de borda
        evoluir(t_fotos, t_max);        // executa a versão principal com o t_max recém definido
    };

    /**
     * @brief Resolve por Runge-Kutta de 4ª ordem a eq. de Schrödinger do sistema
     *
     * @param t_fotos Vetor com instantes de tempo para serem realizadas as "fotografias" de psi
     * @param t_max Tempo máximo de execução da simulação.
     */
    void evoluir(vector<float> t_fotos, float t_max) {

    };

    /**
     * @brief Povoa o cristal com os potenciais retirados do intervalo preestabelecido (W)
     * 
     * O método abaixo realiza um experimento aleatório para cada sítio do cristal, estabelecendo 
     * um valor de potencial on-site dentro da largura de desordem, W, previamente estabelecida.
     * 
     */
    void gerarPotenciais()
    {
        mt19937 rng(random_device{}());     // gera uma semente aleatória pelo algoritmo Mersenne Twister
 
        float W_inf = ((W * -1.0) / 2.0);   // limite inferior do intervalo de desordens possíveis
        float W_sup = W / 2.0;              // limite superior do intervalo de desordens possíveis

        // estabelece que o RNG deve ter uma distribuição uniforme limitada por W_inf e W_sup
        uniform_real_distribution<> dist(W_inf, W_sup);     

        // atribuição aleatória de potenciais aos átomos da cadeia de acordo com o W escolhido
        for (int i = 0; i < psi.size(); i++)
        {
            // gera e atribui ao i-ésimo sítio um determinado potencial on-site 
            pot[i] = dist(rng);
        }
    };

    /**
     * @brief Equação diferencial a ser resolvida pelo Runge-Kutta
     * 
     * @param psi_anterior 
     * @param psi_posterior 
     * @param psi_atual 
     * @param pot_atual 
     * @return Retorna o valor da derivada num determinado ponto, para sua integração
     */
    complex<double> dpsi_dt(
        const complex<double> psi_anterior,
        const complex<double> psi_posterior,
        const complex<double> psi_atual,
        const double pot_atual)

    {
        // TODO: Implementar a equação 
    };
};

int main()
{
    // TODO: Montar o main com o compacto algoritmo de execução
}