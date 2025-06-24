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

#define PI 3.1415926535                 // PI
#define I complex<double>(0.0, 1.0)     // Unidade imaginária (I)

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
    vector<complex<double>> k1;     // vetor para os valores de k1 do runge kutta
    vector<complex<double>> k2;     // vetor para os valores de k2 do runge kutta 
    vector<complex<double>> k3;     // vetor para os valores de k3 do runge kutta 
    vector<complex<double>> k4;     // vetor para os valores de k4 do runge kutta 
    vector<double> pot;             // vetor de potenciais do cristal (on-site energy)
    float W;                        // largura de desordem do sistema
    int N;                        // tamanho da cadeia cristalina
    float sigmaDist;                // sigma inicial da distribuição (gaussiana)

    /**
     * @brief Inicializa um novo objeto Cristal
     *
     * @param tam_cristal tamanho da cadeia cristalina desejado
     * @param W_param largura da desordem desejada no sistema
     */
    Cristal(int tam_cristal, float W_param, float sigma)
        :   psi_n(tam_cristal, complex<double>(0.0, 0.0)),  // função de onda zerada
            k1(tam_cristal, complex<double>(0.0, 0.0)),     // k1 zerado 
            k2(tam_cristal, complex<double>(0.0, 0.0)),     // k2 zerado 
            k3(tam_cristal, complex<double>(0.0, 0.0)),     // k3 zerado 
            k4(tam_cristal, complex<double>(0.0, 0.0)),     // k4 zerado
            pot(tam_cristal, 0.0),                          // potenciais zerados
            W(W_param),                                     // largura da desordem
            N(tam_cristal),                                 // tam. do cristal
            sigmaDist(sigma)

    { }


    /**
     * @brief Overloading do método "evoluir()" -- possibilita a definição de um valor padrão para t_max;
     *
     * @param t_fotos Array com instantes de tempo para serem realizadas as "fotografias" de psi
     */
    void evoluir(double t_fotos[])
    {
        float t_max = N / 5.0; // maior tempo possível que não gera efeitos de borda
        evoluir(t_fotos, t_max);        // executa a versão principal com o t_max recém definido
    };

    /**
     * @brief Resolve por Runge-Kutta de 4ª ordem a eq. de Schrödinger do sistema
     *
     * @param t_fotos Array com instantes de tempo para serem realizadas as "fotografias" de psi
     * @param t_max Tempo máximo de execução da simulação.
     */
    void evoluir(double t_fotos[], float t_max) {
        // TODO: Implementar as fotografias nos tempos específicos

        // passo runge-kutta
        const double h = 10E-3;

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
        pt.open(nome_pt);
        pm.open(nome_pm);
        d.open(nome_d);

        float t = 0.0; 

        while (t <= t_max)
        {
            RK4(h);
            r << format("{:.5f}    {:.5f}\n", t, calcRetorno());
            pt << format("{:.5f}    {:.5f}\n", t, calcPart());
            pm << format("{:.5f}    {:.5f}\n", t, calcPM());
            d << format("{:.5f}    {:.5f}\n", t, calcDP());

            t += h;
        };

        // Fecha os arquivos e salva os dados

        r.close();
        pm.close();
        pt.close();
        d.close();
    };

    void condInicial()
    {
        if (sigmaDist != 0)
        {
            for (size_t n = 0; n <= N; n++)
            {
                k1[n] = exp((-(pow(fabs(n - N/2), 2.0))) / 2.0 * sigmaDist) / (sqrt(2.0 * PI)) + 0.0 * I;
                k2[n] = exp((-(pow(fabs(n - N/2), 2.0))) / 2.0 * sigmaDist) / (sqrt(2.0 * PI)) + 0.0 * I;
                k3[n] = exp((-(pow(fabs(n - N/2), 2.0))) / 2.0 * sigmaDist) / (sqrt(2.0 * PI)) + 0.0 * I;
                k4[n] = exp((-(pow(fabs(n - N/2), 2.0))) / 2.0 * sigmaDist) / (sqrt(2.0 * PI)) + 0.0 * I;
                psi_n[n] = exp((-(pow(fabs(n - N/2), 2.0))) / 2.0 * sigmaDist) / (sqrt(2.0 * PI)) + 0.0 * I;
            }
        }
        else
        {
            psi_n[N/2] = complex<double>(1.0, 0.0);
        }
    }

    void RK4(double h)
    {

        for (size_t n = 1; n < N; n++)
        {
            k1[n] = h * dpsi_dt(psi_n[n+1],
                                psi_n[n-1],
                                psi_n[n],
                                pot[n]);
        }
        for (size_t n = 1; n < N; n++)
        {
            k2[n] = h * dpsi_dt(psi_n[n+1] + 0.5 * k1[n+1],
                                psi_n[n-1] + 0.5 * k1[n-1],
                                psi_n[n] + k1[n],
                                pot[n]);
        }
        for (size_t n = 1; n < N; n++)
        {
            k3[n] = h * dpsi_dt(psi_n[n+1] + 0.5 * k2[n+1],
                                psi_n[n-1] + 0.5 * k2[n-1],
                                psi_n[n] + 0.5 * k2[n],
                                pot[n]);
        }
        for (size_t n = 1; n < N; n++)
        {
            k4[n] = h * dpsi_dt(psi_n[n+1] + k3[n+1],
                                psi_n[n-1] + k3[n-1],
                                psi_n[n] + k3[n],
                                pot[n]);
        }
        for (size_t n = 0; n < N; n++)
        {
            psi_n[n] = psi_n[n] + (1.0/6.0) * (k1[n] + 2.0 * k2[n] + 2.0 * k3[n] + k4[n]);
        }
    }

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
        for (size_t n = 0; n < N; n++)
        {
            // gera e atribui ao i-ésimo sítio um determinado potencial on-site 
            pot[n] = dist(rng);
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

    float calcRetorno()
    {
        return norm(psi_n[N/2]);
    };

    float calcPart()
    {
        double acm_mod_quad = 0.0;
        double acm_mod_qutr = 0.0;

        for (int n = 0; n < N; n++)
        {
            acm_mod_quad = acm_mod_quad + norm(psi_n[n]);
            acm_mod_qutr = acm_mod_qutr + pow(norm(psi_n[n]), 2.0);
        }
        
        return acm_mod_quad / acm_mod_qutr;
    };

    float calcDP()
    {
        float desvio = 0.0;
        float media = calcPM();

        for (int n = 0; n < N; n++)
        {
            desvio = desvio + (pow(n - media, 2.0)) * norm(psi_n[n]); 
        }

        return desvio; 
    };

    float calcPM()
    {
        float media = 0.0; 

        for (int n = 0; n < N; n++)
        {
            media = media + n * norm(psi_n[n]);
        }

        return media; 
    };
};

class WaveFunction
{

};

class Simulador
{

};

int main()
{
    // Inicializa o contador temporal 
    double timecont1 = time(NULL), timecont2; 
    double t_fotos[] = {0.0, 10.0, 20.0, 30.0, 40.0};

    Cristal cristal(100, 0.0, 0.0);

    cristal.condInicial();
    cristal.gerarPotenciais();
    cristal.evoluir(t_fotos);
}