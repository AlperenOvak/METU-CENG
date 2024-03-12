#include "CENGFlight.h"
#include "MultiGraph.h"
#include "HashTable.h"
#include <iostream>

int main(int argc, const char* argv[])
{
    
    CENGFlight newMap("test_izmir.txt");
    //newMap.FindFlight("Kutahya(KTY)","Ankara(ESB)",0);
    std::vector<std::string> airlines;
    newMap.FindSisterAirlines(airlines,"Metro","BUCA");
    for(int i=0;i<airlines.size();i++){
        std::cout<<airlines[i]<<"--";
    }
    std::cout<<"\n";
    //newMap.FindFlight("BUCA","GUZELBAHCE",0);
    /*std::vector<std::string> airlines = {"Dolmus"};
    newMap.FindSpecificFlight("BUCA","GUZELBAHCE",0,airlines);*/
    //std::cout<<newMap.FurthestTransferViaAirline("BUCA","Taksi");
    //newMap.HaltFlight("URLA","KONAK","Dolmus");
    //std::cout<<newMap.FurthestTransferViaAirline("URLA","Dolmus");
    //newMap.ContinueFlight("URLA","KONAK","Dolmus");
    //std::cout<<newMap.FurthestTransferViaAirline("URLA","Dolmus");

    return 0;
}