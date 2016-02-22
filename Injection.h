#ifndef INJECTION_H
#define INJECTION_H

#include <set>
#include <cstring>
#include <cstdint>
#include <iostream>
#include <pcap/pcap.h>
#include "Injection.h"
#include "ConsoleGUI.h"
#include "AccessPoint.h"

using namespace std;
using std::string;

/**
  * class Injection
  * 
  */

/*
Las funciones más interesantes de libpcap son:
	pcap_can_set_rfmon
	pcap_close
	pcap_compile
	pcap_create
	pcap_datalink
	pcap_findalldevs
	pcap_freealldevs
	pcap_lookupnet
	pcap_loop
	pcap_open_live
	pcap_setfilter
*/
class Injection
{
private:
    string _ifaceName;
    char _errMsg[PCAP_ERRBUF_SIZE];
    pcap_t *_network_device;

public:

    // Constructors/Destructors
    //  


    /**
     * Empty Constructor
     */
    Injection (string ifaceName);

    /**
     * Empty Destructor
     */
    virtual ~Injection();


public:
    void inyectar();

};

#endif // INJECTION_H
