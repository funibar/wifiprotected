#ifndef TARJETARED_H
#define TARJETARED_H

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
  * class TarjetaRed
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
class TarjetaRed
{
public:

    // Constructors/Destructors
    //  


    /**
     * Empty Constructor
     */
    TarjetaRed (string ifaceName);

    /**
     * Empty Destructor
     */
    virtual ~TarjetaRed();

    // Static Public attributes
    //  

    // Public attributes
    //  


    // Public attribute accessor methods
    //  


    // Public attribute accessor methods
    //  



    /**
     */
    void buscarAP ();

protected:

    // Static Protected attributes
    //  

    // Protected attributes
    //  

public:


    // Protected attribute accessor methods
	//set<AccessPoint, AccessPointComparator> listadoAPs;
	set<AccessPoint> listadoAPs;

protected:

public:
    // Protected attribute accessor methods
    //  

protected:
    static const int PROMISCUOUS = 1;
    static const int OPTIMIZE_EXPRESSION = 1;

private:

    // Static Private attributes
    //  
    static void procesarPaquetes(u_char *args, const struct pcap_pkthdr *header, const u_char *packet);

    // Private attributes
    //  

    pcap_t *_network_device;
    char _errMsg[PCAP_ERRBUF_SIZE];
    string _ifaceName;
public:
    // Public attribute accessor methods
    //  
    bool isMonitor;


    /**
     * Set the value of isMonitor
     * @param new_var the new value of isMonitor
     */
    void setIsMonitor (bool new_var)     {
            isMonitor = new_var;
    }

    /**
     * Get the value of isMonitor
     * @return the value of isMonitor
     */
    bool getIsMonitor ()     {
        return isMonitor;
    }
private:
    void initAttributes () ;

};

#endif // TARJETARED_H
