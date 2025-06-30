#include "Simulador.h"

int main() {
    double t_fotos[] = {999};
    Simulador s(0.0, 200, 0.0);
    s.evoluir(t_fotos);
    return 0;
}