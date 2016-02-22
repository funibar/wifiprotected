#include "TarjetaRed.h"

// Constructors/Destructors
//  

TarjetaRed::TarjetaRed(string ifaceName) {
    initAttributes();
    int rtn = 0; //return code from libpcap functions

    //char *iface = pcap_lookupdev(_errMsg);
    _ifaceName = ifaceName;
    _network_device = pcap_create(ifaceName.c_str(), _errMsg);
    if (_network_device == NULL)
    {
        pcap_perror(_network_device, _errMsg);
        cerr << _errMsg << endl;
        throw new exception;
    }
    if (pcap_can_set_rfmon(_network_device))
    {
        setIsMonitor(true);
    }   
    rtn = pcap_activate(_network_device);
    if (rtn != 0)
    {
        cerr << "la interfaz seleccionada no es usable" << endl;
        cerr << "o bien el interfaz " << ifaceName << " no existe" << endl;
        cerr << _errMsg << endl;
        throw new exception;
        //TODO: hacer un switch de valores devueltos por la función
    }
    pcap_set_timeout(_network_device, 1000);
}

TarjetaRed::~TarjetaRed () {
    pcap_close(_network_device);
}

int contadorAPs=0;

struct classcomp {
  bool operator() (AccessPoint ap1, AccessPoint ap2) const
  {string bssid1 = ap1.getBSSID();
    string bssid2 = ap2.getBSSID();

    return bssid1.compare(bssid2);}
};

//  
// Methods
//  
void TarjetaRed::buscarAP()
{
    //Injection injection;

    int rtn = 0;
    int TIME_IN_MS = 1000;
    struct bpf_program fp;
    string EXPRESSION = "wlan type mgt subtype beacon";

    pcap_t *device = pcap_open_live(_ifaceName.c_str(), BUFSIZ, PROMISCUOUS, TIME_IN_MS, _errMsg);
    rtn = pcap_compile(_network_device, &fp, EXPRESSION.c_str(), OPTIMIZE_EXPRESSION, PCAP_NETMASK_UNKNOWN);
    if (rtn != 0)
    {
        cerr << pcap_geterr(_network_device) << endl;
    }
    rtn = pcap_setfilter(_network_device, &fp);
    if (rtn < 0)
    {
        cerr << pcap_geterr(_network_device) << endl;
    }
    int link_layer_type = pcap_datalink(_network_device);
    if (link_layer_type == DLT_IEEE802_11_RADIO) //where WPS information lives... :)
    {
	//int *ref_int=&asd;
	//SS=new set<AccessPoint, classcomp>;
        //cout << &listadoAPs << endl;
        
	pcap_loop(_network_device, -1, procesarPaquetes, reinterpret_cast<u_char*>(&listadoAPs));
        //pcap_loop(_network_device, 1, procesarPaquetes, NULL);
    }
}


// Accessor methods
// 


// Other methods
//  
void TarjetaRed::initAttributes () {
    isMonitor = false;
    memset(_errMsg, 0, PCAP_ERRBUF_SIZE);
}

void TarjetaRed::procesarPaquetes(u_char *args, const struct pcap_pkthdr *header, const u_char *packet)
{
    AccessPoint accessPoint(header, packet);
    set<AccessPoint, classcomp> *listadoAPs = reinterpret_cast< set<AccessPoint, classcomp> * > (args);
    listadoAPs->insert(accessPoint);

    ConsoleGUI gui;
    gui.clearGUI();
    std::set<AccessPoint, classcomp>::iterator it;
    int iColumn = 5;
    for ( it = listadoAPs->begin(); it != listadoAPs->end(); ++it)
    {
       AccessPoint ap = *it;
       gui.addLine(iColumn++, 1, ap);
    }
    gui.showGUI();
}
