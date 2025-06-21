/**
 * @file main.cpp
 * @author Rafael Amorim (rafael.science.amorim@gmail.com)
 * @brief
 * @version 0.1
 * @date 2025-06-17
 **/

#include <iostream> // biblioteca padrão de entrada e saída
#include <fstream>  // escrita em arquivos
#include <complex>  // números complexos
#include <cmath>    // artifícios matemáticos
#include <time.h>   // biblioteca temporal
#include <vector>   // vetores
#include <random>   // números aleatórios
#include <format>   // formatação de strings

#define PI 3.1415926535 // PI
#define I complex<double>(0.0, 1.0)

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
class Cristal
{
public:
    vector<complex<double>> psi_n;  // vetor representativo do valor da função de onda em cada sítio
    vector<double> pot;             // vetor de potenciais do cristal (on-site energy)
    float W;                        // largura de desordem do sistema
    float N;                        // tamanho da cadeia cristalina
    float sigmaDist;                // sigma inicial da distribuição (gaussiana)

    /**
     * @brief Inicializa um novo objeto Cristal
     *
     * @param tam_cristal tamanho da cadeia cristalina desejado
     * @param W_param largura da desordem desejada no sistema
     */
    Cristal(int tam_cristal, float W_param, float sigma)
        :   psi_n(tam_cristal, complex<double>(0.0, 0.0)),  // função de onda zerada
            pot(tam_cristal, 0.0),                          // potenciais zerados
            W(W_param),                                     // largura da desordem
            N(tam_cristal),                                 // tam. do cristal
            sigmaDist(sigma)

    { }


    /**
     * @brief Overloading do método "evoluir()" -- possibilita a definição de um valor padrão para t_max;
     *
     * @param t_fotos Vetor com instantes de tempo para serem realizadas as "fotografias" de psi
     */
    void evoluir(vector<float> t_fotos)
    {
        float t_max = N / 5.0; // maior tempo possível que não gera efeitos de borda
        evoluir(t_fotos, t_max);        // executa a versão principal com o t_max recém definido
    };

    /**
     * @brief Resolve por Runge-Kutta de 4ª ordem a eq. de Schrödinger do sistema
     *
     * @param t_fotos Vetor com instantes de tempo para serem realizadas as "fotografias" de psi
     * @param t_max Tempo máximo de execução da simulação.
     */
    void evoluir(vector<float> t_fotos, float t_max) {
        // Inicializa arquivos para escrita de resultados 
        ofstream r;     // Retorno
        ofstream pm;    // Centróide / Posição média 
        ofstream pt;    // Participação
        ofstream d;     // Desvio quadrático

        // Criação do nome dos arquivos

        string nome_r;
        string nome_pm;
        string nome_pt;
        string nome_d;

        // Formatação das strings de acordo com o timestamp de criação e a desordem da cadeia 

        nome_r = format("rschr_r_w={}_{}.dat", W, time(0));
        nome_pm = format("rschr_pm_w={}_{}.dat", W, time(0));
        nome_pt = format("rschr_pt_w={}_{}.dat", W, time(0));
        nome_d = format("rschr_d_w={}_{}.dat", W, time(0));

        // Abre os arquivos com os nomes predefinidos

        r.open(nome_r);
        pm.open(nome_pm);
        pt.open(nome_pt);
        d.open(nome_d);

        // TODO: Adicionar método de distribuição inicial (cond. gaussiana vs delta) aqui

        // TODO: Adicionar método do Runge-Kutta aqui

        // Fecha os arquivos e salva os dados

        r.close();
        pm.close();
        pt.close();
        d.close();


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
        for (int i = 0; i < N; i++)
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
    complex<double> dpsi_dt(const complex<double> psi_anterior,
                            const complex<double> psi_posterior,
                            const complex<double> psi_atual,
                            const double pot_atual)
    {
        return -I * (psi_anterior + psi_posterior + pot_atual * psi_atual);
    };

    float calcRetorno(const complex<double> psi_n2)
    {

    };

    float calcPart(const complex<double> psi_n)
    {

    };

    float calcDP(const complex<double> psi_n)
    {

    };

    float calcPM(const complex<double> psi_n)
    {

    };
};

int main()
{
    // TODO: Montar o main com o compacto algoritmo de execução
}