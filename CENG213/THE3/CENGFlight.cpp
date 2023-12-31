#include "CENGFlight.h"
#include <iostream>
#include "IntPair.h"

//=======================//
// Implemented Functions //
//=======================//
void CENGFlight::PrintCanNotHalt(const std::string& airportFrom,
                                 const std::string& airportTo,
                                 const std::string& airlineName)
{
    std::cout << "A flight path between \""
              << airportFrom << "\" and \""
              << airportTo << "\" via "
              << airlineName
              << " airlines is not found and cannot be halted"
              << std::endl;
}

void CENGFlight::PrintCanNotResumeFlight(const std::string& airportFrom,
                                         const std::string& airportTo,
                                         const std::string& airlineName)
{
    std::cout << "A flight path between \""
              << airportFrom << "\" and \""
              << airportTo << "\" via "
              << airlineName
              << " airlines cannot be resumed"
              << std::endl;
}

void CENGFlight::PrintFlightFoundInCache(const std::string& airportFrom,
                                         const std::string& airportTo,
                                         bool isCostWeighted)
{
    std::cout << "A flight path between \""
              << airportFrom << "\" and \""
              << airportTo << "\" using "
              << ((isCostWeighted) ? "cost" : "price")
              <<  " is found in cache." << std::endl;
}

void CENGFlight::PrintFlightCalculated(const std::string& airportFrom,
                                       const std::string& airportTo,
                                       bool isCostWeighted)
{
    std::cout << "A flight path is calculated between \""
              << airportFrom << "\" and \""
              << airportTo << "\" using "
              << ((isCostWeighted) ? "cost" : "price")
              <<  "." << std::endl;
}

void CENGFlight::PrintPathDontExist(const std::string& airportFrom,
                                    const std::string& airportTo)
{
    std::cout << "A flight path does not exists between \""
              << airportFrom << "\" and \""
              << airportTo <<"\"." << std::endl;
}

void CENGFlight::PrintSisterAirlinesDontCover(const std::string& airportFrom)
{
    std::cout << "Could not able to generate sister airline list from \""
              << airportFrom <<"\"." << std::endl;
}

void CENGFlight::PrintMap()
{
    navigationMap.PrintEntireGraph();
}

void CENGFlight::PrintCache()
{
    lruTable.PrintTable();
}

CENGFlight::CENGFlight(const std::string& flightMapPath)
    : navigationMap(flightMapPath)
{}

//=======================//
//          TODO         //
//=======================//
void CENGFlight::HaltFlight(const std::string& airportFrom,
                            const std::string& airportTo,
                            const std::string& airlineName)
{
    /* TODO */
    Pair<float,float> W;
    W = navigationMap.errorForFlight(airlineName,airportFrom,airportTo);
    if(W.key == -1 || W.value == -1){
        PrintCanNotHalt(airportFrom,airportTo,airlineName);
    }else{
        navigationMap.RemoveEdge(airlineName,airportFrom,airportTo);
    }
    HaltedFlight halted;
    halted.w0 = W.key;
    halted.w1 = W.value;
    halted.airline = airlineName;
    halted.airportFrom = airportFrom;
    halted.airportTo = airportTo;

    haltedFlights.push_back(halted);
}

    // (Direct Function call)
void CENGFlight::ContinueFlight(const std::string& airportFrom,
                                const std::string& airportTo,
                                const std::string& airlineName)
{
    /* TODO */
    bool cont = false;
    for(size_t i=0;i<haltedFlights.size();i++){
        if(haltedFlights[i].airportFrom == airportFrom && haltedFlights[i].airportTo == airportTo && haltedFlights[i].airline == airlineName){
            std::string edge = haltedFlights[i].airline;
            std::string from = haltedFlights[i].airportFrom;
            std::string to = haltedFlights[i].airportTo;
            float w0 = haltedFlights[i].w0;
            float w1 = haltedFlights[i].w1;
            navigationMap.AddEdge(edge,from,to,w0,w1);
            cont = true;
            haltedFlights.erase(haltedFlights.begin()+i);
        }
    }
    if(!cont){
        PrintCanNotResumeFlight(airportFrom,airportTo,airlineName);
    }
}

void CENGFlight::FindFlight(const std::string& startAirportName,
                            const std::string& endAirportName,
                            float alpha)
{
    /* TODO */
    int fromIndex= navigationMap.indexOfVertex(startAirportName);
    int toIndex=navigationMap.indexOfVertex(endAirportName);
    std::vector<int> intArray;
    if(lruTable.Find(intArray,fromIndex,toIndex,true,false)){ //why trueee ?????
        PrintFlightFoundInCache(startAirportName,endAirportName,true); //why ture?????
        navigationMap.PrintPath(intArray,alpha,true);
        return;
    }
    navigationMap.HeuristicShortestPath(intArray,startAirportName,endAirportName,alpha);
    PrintFlightCalculated(startAirportName,endAirportName,true); //why ture?
    //add to cache
    lruTable.Insert(intArray,true);
    navigationMap.PrintPath(intArray,alpha,true);
}

void CENGFlight::FindSpecificFlight(const std::string& startAirportName,
                                    const std::string& endAirportName,
                                    float alpha,
                                    const std::vector<std::string>& unwantedAirlineNames) const
{
    /* TODO */
}

void CENGFlight::FindSisterAirlines(std::vector<std::string>& airlineNames,
                               const std::string& startAirlineName,
                               const std::string& airportName) const
{
    /* TODO */
}

int CENGFlight::FurthestTransferViaAirline(const std::string& airportName,
                                           const std::string& airlineName) const
{
    /* TODO */
    return -1;
}