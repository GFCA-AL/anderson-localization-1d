# Simulação da Equação de Schrödinger Dependente do Tempo

**Grupo de Física Computacional Aplicada (GFCA)**
Instituto Federal de Alagoas — Campus Maceió

## 📌 Visão Geral

Este repositório contém uma simulação numérica da equação de Schrödinger dependente do tempo em uma dimensão, aplicada ao estudo da dinâmica eletrônica em redes cristalinas com desordem. O projeto é desenvolvido pelo Grupo de Física Computacional Aplicada (GFCA) em parceria com o aluno Rafael Amorim (PIBIC), durante os anos de 2023–2025.

O objetivo principal é modelar e analisar o comportamento quântico de um elétron sob um Hamiltoniano do tipo **tight-binding com desordem estática**, utilizando métodos de integração numérica (Runge-Kutta de quarta ordem).

## 🔬 Contexto Físico

O sistema consiste em uma cadeia unidimensional com desordem aleatória nos potenciais on-site. A função de onda do elétron é inicialmente localizada ou distribuída de forma gaussiana, e sua evolução temporal é computada numericamente.

Durante a simulação, são extraídas grandezas físicas de interesse como:

* 📍 **Probabilidade de retorno** (em relação ao sítio inicial);
* 🎯 **Posição média** (centróide da função de onda);
* 📏 **Participação** (medida de espalhamento espacial);
* 📈 **Desvio quadrático** (variância da posição);
* 📷 **Densidade de Probabilidade** da função de onda num dado instante temporal ("fotografia").


## 🧮 Metodologia

* A equação diferencial é integrada com o método **Runge-Kutta de quarta ordem (RK4)**;
* Os potenciais de cada sítio são sorteados a partir de uma **distribuição uniforme** dentro de uma largura $W$;
* A função de onda é armazenada como um vetor de números complexos e atualizada iterativamente;
* A condição inicial pode ser uma **distribuição delta** (localizada) ou **gaussiana**.


## 📁 Estrutura

O código-fonte é modularizado em três classes principais, separadas em arquivos `.cpp` e `.h`:

* `WaveFunction`: representa a função de onda e calcula observáveis físicos;
* `Cristal`: gera e armazena os potenciais desordenados da cadeia;
* `Simulador`: integra a equação de Schrödinger no tempo e organiza as saídas.

O arquivo `main.cpp` é responsável por configurar e iniciar a simulação.

## 📊 Saídas da Simulação

Os dados são gravados em arquivos `.dat` com nomes que incluem a largura da desordem e um timestamp da execução. As principais saídas incluem:

* `rschr_r_w=...`: retorno $R(t)$
* `rschr_pm_w=...`: posição média $\langle x(t) \rangle$
* `rschr_pt_w=...`: participação $P(t)$
* `rschr_d_w=...`: desvio quadrático $D(t)$
* `foto_t=...`: distribuição $|\psi(x,t)|^2$ em tempos específicos

Esses dados podem ser analisados com ferramentas como Python, GNUPlot ou MATLAB.


## ⚙️ Compilação e Execução

### 🛠️ Compilação com `Makefile`

O repositório já inclui um `Makefile`. Para compilar o projeto, basta rodar:

```bash
make
```

Isso gera um executável chamado `simulador`.

### 🧼 Limpeza

Para remover os arquivos objeto e o executável:

```bash
make clean
```

### ▶️ Execução

Execute o simulador com:

```bash
./simulador
```

O comportamento padrão pode ser alterado dentro do `main.cpp`, como o tamanho da cadeia, desvio inicial, e tempos para captura de "fotos".


## 🧪 Exemplo de Parâmetros

```cpp
int tamanho = 500;
float sigma = 1.0;
double largura_desordem = 1.0;

Simulador sistema(sigma, tamanho, largura_desordem);
double tempos[] = {1, 2, 5, 10, 20};
sistema.evoluir(tempos);
```

## 📚 Licença

Este projeto está licenciado sob a **Licença MIT**, salvo disposição em contrário. Veja o arquivo `LICENSE` para mais detalhes.


## 🧠 Contato

Para dúvidas, sugestões ou colaborações, entre em contato com a coordenação do GFCA ou diretamente com o autor do projeto:

📧 **[rafael.science.amorim@gmail.com](mailto:rafael.science.amorim@gmail.com)**

## 🛠️ Perspectivas

- Adição de uma função de normalização para a função de onda gaussiana; 
- Integração com Python para plotagem automática;
- Modificação para execução do código por meio de argumentos de linha de comando para maior praticidade.

---

**Status do projeto:** Em desenvolvimento ativo 🛠️