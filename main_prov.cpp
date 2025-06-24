/**
 * @file main.cpp
 * @author Rafael Amorim (rafael.science.amorim@gmail.com)
 * @brief Solução da Eq. de Schrödinger linear, tight-binding, com RK4
 * @version 1.0
 * @date 2025-06-24
 *
 * @copyright Copyright (c) 2025
 */

// BIBLIOTECAS

#include <iostream> // entrada e saída (geral)
#include <fstream>  // entrada e saída (arquivos)
#include <complex>  // números complexos
#include <cmath>    // matemática geral
#include <time.h>   // funções temporais
#include <vector>   // vetores
#include <random>   // números aleatórios
#include <format>   // formatação de strings

// CONSTANTES

#define PI 3.1415926535             // PI
#define I complex<double>(0.0, 1.0) // Unidade Imaginária

using namespace std;

class WaveFunction
{
private:
    float sigmaDist;
    int N;

public:
    vector<complex<double>> psi_n;

    WaveFunction(int tam_cristal, float sigma)
        : psi_n(tam_cristal, complex<double>(0.0, 0.0)),
          sigmaDist(sigma)
    { }

    calcRetorno() {

    };

    calcPart() {

    };

    calcDP() {

    };

    calcPM() {

    };
}