#include "Simulador.h"

int main() {
    double t_fotos[] = {0.0, 2.5, 5.0, 7.5, 10.0, 12.5, 15.0, 17.5, 20.0, 22.5, 25.0, 27.5, 30.0, 32.5, 35.0, 37.5, 39.0};
    Simulador s(0.0, 200, 5.0);
    s.evoluir(t_fotos);
    return 0;
}