#include <iostream>
#include <stdlib.h>
#include "Injection.h"

using namespace std;
using std::string;

int main() {
    //const char *ifaceName[] = {"mon0"};
    string ifaceName = "wlan0";
    Injection inject(ifaceName);
    inject.inyectar();

    return EXIT_SUCCESS;
}
