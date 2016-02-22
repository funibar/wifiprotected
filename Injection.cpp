#include "Injection.h"
#include <stdint.h>
#include <libnet.h>
#include <iostream>

// Constructors/Destructors
//  

Injection::Injection(string ifaceName) {
    int rtn = 0; //return code from libpcap functions
    cout << "creando Injection" << endl;
    _ifaceName = ifaceName;
    _network_device = pcap_create(ifaceName.c_str(), _errMsg);
    if (_network_device == NULL)
    {
        pcap_perror(_network_device, _errMsg);
        cerr << _errMsg << endl;
        throw new exception;
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

Injection::~Injection () {
    cout << "destruyendo Injection" << endl;
}

//  
// Methods
//  


void Injection::inyectar()
{
     cout << "vaginas" << endl;
     struct libnet_ethernet_hdr ethernet_header;
     u_int8_t ether_dhost[ETHER_ADDR_LEN] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05};
     u_int8_t ether_shost[ETHER_ADDR_LEN] = {0x48, 0x5d, 0x60, 0x95, 0x2d, 0xfd};
     //u_int8_t ether_shost[ETHER_ADDR_LEN] = {0x9c, 0x97, 0x26, 0xa0, 0x5e, 0x84};
     memcpy(ethernet_header.ether_dhost, ether_dhost, ETHER_ADDR_LEN);
     memcpy(ethernet_header.ether_shost, ether_shost, ETHER_ADDR_LEN);
     ethernet_header.ether_type = ETHERTYPE_EAP;

     struct libnet_802_1x_hdr eap_802_1x_header;
     u_int8_t dot1x_version = 0x01;
     u_int8_t dot1x_type = 0x01;
     u_int16_t dot1x_length = 0x00;
     eap_802_1x_header.dot1x_version = dot1x_version;
     eap_802_1x_header.dot1x_type = dot1x_type;
     eap_802_1x_header.dot1x_length = dot1x_length;

     u_int8_t frame[sizeof(ethernet_header) + sizeof(eap_802_1x_header)];
     memcpy(&frame[0], &ethernet_header, sizeof(ethernet_header));
     memcpy(&frame[sizeof(ethernet_header)], &eap_802_1x_header, sizeof(eap_802_1x_header));
     cout << "tam fram " << sizeof(frame) << endl;

     //libnet_ptag_t t = libnet_build_802_1x(dot1x_version, dot1x_type, dot1x_length, 0, 0, 0, 0);
     //eth.addr==00:01:02:03:04:05
     for (int i = 0; i < 1000; i++) {
         //pcap_inject(_network_device, static_cast<uint8_t *> (static_cast<void *>(&frame)), sizeof(ethernet_header) );
         pcap_inject(_network_device, reinterpret_cast<uint8_t *>(&frame), sizeof(frame) );
     }
}
