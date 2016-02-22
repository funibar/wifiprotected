#include <iostream>
#include <stdlib.h>
#include "TarjetaRed.h"

using namespace std;
using std::string;

int main() {
    //const char *ifaceName[] = {"mon0"};
    string ifaceName = "mon0";
    TarjetaRed tarjeta(ifaceName);
    tarjeta.buscarAP();

    return EXIT_SUCCESS;
}
