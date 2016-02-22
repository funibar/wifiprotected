#include "AccessPoint.h"

// Constructors/Destructors
//  

AccessPoint::AccessPoint( const struct pcap_pkthdr *header, const u_char *packet ) {
    initAttributes();
    
    struct ieee80211_radiotap_header *_radiotap_header;
    _radiotap_header = (struct ieee80211_radiotap_header *) packet;
   
    int iSizeIEEE80211Header = _radiotap_header->it_len;

    //setting the BSSID
    ostringstream strBssid;
    for (int i = iSizeIEEE80211Header, j = 0; i < iSizeIEEE80211Header + 24; i++)
    {
        if (i >= iSizeIEEE80211Header + 16 && i <= iSizeIEEE80211Header + 21) //el BSSID está desplazado 16 bytes y son 6 bytes
        {
            //cout << hex << uppercase << (unsigned short) packet[i];
            char separator = ( i < iSizeIEEE80211Header + 21 )? ':' : '\0'; //necesario para que el string de BSSID no termine con el caracter :
            strBssid << hex << setfill('0') << uppercase << setw(2) << static_cast<int>( packet[i] ) << separator;
        }
    }
    setBSSID( strBssid.str() );
    

    //setting ESSID
    int packetSize = header->len;
    ostringstream strEssid;
    for (int i = iSizeIEEE80211Header + 24; i < packetSize; i++)
    {
        int inicio = iSizeIEEE80211Header + 24 + 14;
        int fin = static_cast<int>( packet[iSizeIEEE80211Header + 24 + 13] ) - 1;
        if (i >= inicio &&  i <= inicio + fin )
            strEssid << static_cast<char>( packet[i] );

    }
    setESSID( strEssid.str() );

    //checking for WPS is active
    int iPosicionInfoWPS = header->len - 5;
    if (static_cast<int>(packet[iPosicionInfoWPS]) == 0x02)
    {
        setIsWPSActive(true);
    }
}

AccessPoint::~AccessPoint () { }

//  
// Methods
//  


// Accessor methods
//  

// Other methods
//  

void AccessPoint::initAttributes () {
    setIsWPSActive(false);
}

bool operator < (AccessPoint &ap1,  AccessPoint &ap2) {
    return strcmp(ap1.getBSSID().c_str(), ap2.getBSSID().c_str());
}

bool operator == (AccessPoint &ap1,  AccessPoint &ap2) {
    return strcmp(ap1.getBSSID().c_str(), ap2.getBSSID().c_str());
}
