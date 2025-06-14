# Simulação da Equação de Schrödinger Dependente do Tempo

**Grupo de Física Computacional Aplicada (GFCA)**  
Instituto Federal de Alagoas - Campus Maceió

---

## 📌 Visão Geral

Este repositório contém a base para uma simulação numérica da equação de Schrödinger dependente do tempo em uma dimensão, aplicada ao estudo da dinâmica eletrônica em redes cristalinas com desordem. Trata-se de uma iniciativa de pesquisa conduzida pelo Grupo de Física Computacional Aplicada (GFCA) com um aluno do ensino médio, Rafael Amorim (PIBIC), durante os anos de 2023-2025.

O objetivo principal é modelar e analisar o comportamento de um elétron único evoluindo sob um Hamiltoniano de tight-binding com desordem diagonal, utilizando métodos de integração numérica.

---

## 🔬 Contexto Físico

O sistema simulado representa uma cadeia cristalina unidimensional com desordem aleatória entre os sítios. A função de onda inicial do elétron pode ser distribuída de forma delta ou gaussiana, dependendo dos parâmetros definidos. Ao longo da simulação, são extraídas grandezas físicas relevantes como:

- Probabilidade de retorno
- Posição média (centróide)
- Participação
- Desvio quadrático

---

## 🧮 Metodologia

- A evolução temporal é realizada utilizando o método de **Runge-Kutta de quarta ordem**.
- A desordem nos potenciais dos sítios é gerada a partir de uma distribuição uniforme em um intervalo pré-definido.
- A função de onda do sistema é representada por arrays complexos e atualizada iterativamente ao longo do tempo.

---

## 📊 Saídas e Análise

A simulação produz arquivos de dados com resolução temporal contendo:

- Probabilidade de retorno
- Centrôide da função de onda
- Participação eletrônica
- Desvio quadrático

Esses dados serão utilizados para análise posterior, com foco em fenômenos de localização e transporte quântico em sistemas desordenados.

---

## ⚙️ Compilação e Execução

Instruções de compilação e uso serão incluídas assim que o código for finalizado. Um `Makefile` ou configuração em CMake será disponibilizado para facilitar o processo de construção.

---

## 📚 Licença

Este projeto está licenciado sob os termos da **Licença MIT**, salvo disposição em contrário. Consulte o arquivo `LICENSE` para mais informações.

---

## 🧠 Contato

Para dúvidas, contribuições ou propostas de colaboração, entre em contato com a coordenação do GFCA.

---

**Status:** Projeto em desenvolvimento ativo  
