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
        navigationMap.RemoveEdge    (airlineName,airportFrom,airportTo);
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
    if(fromIndex == -1 || toIndex == -1){
        PrintPathDontExist(startAirportName,endAirportName);
    }
    bool incLRU = ((alpha==0 || alpha==1) ? true : false);
    if(lruTable.Find(intArray,fromIndex,toIndex,true,incLRU)){ //why trueee ?????
        PrintFlightFoundInCache(startAirportName,endAirportName,true); //why ture?????
        navigationMap.PrintPath(intArray,alpha,true);
        return;
    }
    if(navigationMap.HeuristicShortestPath(intArray,startAirportName,endAirportName,alpha)){
        //add to cache
        if(incLRU){
            PrintFlightCalculated(startAirportName,endAirportName,true); //why ture?
            lruTable.Insert(intArray,true);
        }
        navigationMap.PrintPath(intArray,alpha,true);    
    }else{
        PrintPathDontExist(startAirportName,endAirportName);
    }
    
}

void CENGFlight::FindSpecificFlight(const std::string& startAirportName,
                                    const std::string& endAirportName,
                                    float alpha,
                                    const std::vector<std::string>& unwantedAirlineNames) const
{
    /* TODO */
    std::vector<int> intArray;
    if(navigationMap.FilteredShortestPathForCengFlight(intArray,startAirportName,endAirportName,alpha,unwantedAirlineNames)){
        navigationMap.PrintPath(intArray,alpha,true);
    }else{
        PrintPathDontExist(startAirportName,endAirportName);
    }
    //PrintFlightCalculated ???
}

void CENGFlight::FindSisterAirlines(std::vector<std::string>& airlineNames,
                               const std::string& startAirlineName,
                               const std::string& airportName) const
{
    /* TODO */
    int num = navigationMap.Number();
    //std::cout<<num<<"\n";
    std::vector<int> visited(num,0);
    std::vector<int> oldvisited(num,0);
    std::vector<std::string> usedAirlines;
    
    bool AllVisited = false;
    usedAirlines.push_back(startAirlineName);
    if(navigationMap.indexOfVertex(airportName)==-1){
        PrintSisterAirlinesDontCover(airportName);
    }
    if(navigationMap.MaxVisitViaEdgeList(navigationMap.indexOfVertex(airportName),usedAirlines,visited)== 0){
        PrintSisterAirlinesDontCover(airportName);
        return;
    }
    while(!AllVisited){
        bool visitchanged=true;
        for(int i=0;i<num;i++){
            if(visited[i]!=oldvisited[i]){
                visitchanged=false;
            }
        }
        if(visitchanged){ //until our visted airports did not change from the last iteration.
            PrintSisterAirlinesDontCover(airportName);
            return;
        }
        int nextAirPort;
        int maxNonVisitedNum=-1;
        for(int i=num-1;i>=0;i--){
            if(visited[i]==1 && maxNonVisitedNum<navigationMap.NumberOfNonVisitedNeighbor(i,visited)){
                maxNonVisitedNum = navigationMap.NumberOfNonVisitedNeighbor(i,visited);
                nextAirPort = i;
            }
        }//Select a visited airport 
        //std::cout<<"nextairport "<<nextAirPort<<std::endl;
        
        int newAirlineIndex = navigationMap.IndexOfNonUtilizedAirline(nextAirPort,visited,usedAirlines);
        if(newAirlineIndex==-1){
            PrintSisterAirlinesDontCover(airportName);
            return;
        }
        std::string newAirline = navigationMap.NameOfAirline(nextAirPort,newAirlineIndex);
        usedAirlines.push_back(newAirline);
        
        navigationMap.MaxVisitViaEdgeList(nextAirPort,usedAirlines,visited);
        
        
        AllVisited=true;
        for(int i=0;i<num;i++){   //check AllVisited
            if(visited[i]==0){
                AllVisited=false;
            }
        }
        oldvisited=visited;
    }
    /*for(int i=0;i<num;i++){
        std::cout<<visited[i];
        
    }*/
    for(int i=1;i<usedAirlines.size();i++){
        //std::cout<<usedAirlines[i];
        airlineNames.push_back(usedAirlines[i]);
        
    }
    //std::cout<<"\n";

}

int CENGFlight::FurthestTransferViaAirline(const std::string& airportName,
                                           const std::string& airlineName) const
{
    /* TODO */
    if(navigationMap.indexOfVertex(airportName)==-1){
        return -1;
    }
    return navigationMap.MaxDepthViaEdgeName(airportName,airlineName);
}