#ifndef MULTI_GRAPH_H
#define MULTI_GRAPH_H

#include <vector>
#include <string>
#include "IntPair.h"
#include "Exceptions.h"
#include "IntPair.h"
#include <iostream>
#include <iomanip>
#include <fstream>

struct GraphEdge
{
    std::string name;       // Name of the vertex
    float       weight[2];  // Weights of the edge
                            // (used on shortest path)
    int         endVertexIndex;
};

struct GraphVertex
{
    std::vector<GraphEdge> edges; // Adjacency List
    std::string            name;  // Name of the vertex
};

class MultiGraph
{
    private:
    std::vector<GraphVertex>    vertexList;
    
    void        reverseVector(std::vector<int>& vec);

    static float Lerp(float w0, float w1, float alpha);

    protected:
    public:
    // Constructors & Destructor
                MultiGraph();
                MultiGraph(const std::string& filePath);

    // Connect Vertices
    void        InsertVertex(const std::string& vertexName);
    void        RemoveVertex(const std::string& vertexName);

    // Connect Vertices
    void        AddEdge(const std::string& edgeName,
                        const std::string& vertexFromName,
                        const std::string& vertexToName,
                        float weight0, float weight1);
    void        RemoveEdge(const std::string& edgeName,
                           const std::string& vertexFromName,
                           const std::string& vertexToName);

    //return w0 and w1 if its exist, else print error
    Pair<float,float> errorForFlight(const std::string& edgeName,
                        const std::string& vertexFromName,
                        const std::string& vertexToName);

    int indexOfVertex(const std::string& vertexName)const;
    
    int IndexOfNonUtilizedAirline(int VertexIndex,std::vector<int>& visited,std::vector<std::string>& usedAirlines)const;
    
    std::string NameOfAirline(int VertexIndex,int EdgeIndex)const;
    
    int Number()const;

    // Shortest Path Functions
    bool        HeuristicShortestPath(std::vector<int>& orderedVertexEdgeIndexList,
                                      const std::string& vertexNameFrom,
                                      const std::string& vertexNameTo,
                                      float heuristicWeight) const;
    bool        FilteredShortestPath(std::vector<int>& orderedVertexEdgeIndexList,
                                     const std::string& vertexNameFrom,
                                     const std::string& vertexNameTo,
                                     float heuristicWeight,
                                     const std::vector<std::string>& edgeNames) const;
    
    bool        FilteredShortestPathForCengFlight(std::vector<int>& orderedVertexEdgeIndexList,
                                      const std::string& vertexNameFrom,
                                      const std::string& vertexNameTo,
                                      float heuristicWeight,
                                      const std::vector<std::string>& edgeNames) const;

    // Other functions
    int         BiDirectionalEdgeCount() const;
    int         MaxVisitViaEdgeList(int startVertexIndex,
                                    std::vector<std::string>& edgeNames,
                                    std::vector<int>& visited) const;
    int         NumberOfNonVisitedNeighbor(int vertexIndex,std::vector<int>& visited)const;
    int         MaxDepthViaEdgeName(const std::string& vertexName,
                                    const std::string& edgeName) const;

    // Implemented Functions for Debugging
    void        PrintPath(const std::vector<int>& orderedVertexEdgeIndexList,
                          float heuristicWeight,
                          bool sameLine = false) const;
    void        PrintEntireGraph() const;
};

MultiGraph::MultiGraph()
{}

MultiGraph::MultiGraph(const std::string& filePath)
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    // Tokens
    std::string tokens[5];
    std::ifstream mapFile(filePath.c_str());

    if(!mapFile.is_open())
    {
        std::cout << "Unable to open " << filePath << std::endl;
        return;
    }

    // Read line by line
    std::string line;
    while (std::getline(mapFile, line))
    {
        // Empty Line Skip
        if(line.empty()) continue;
        // Comment Skip
        if(line[0] == '#') continue;

        // Tokenize the line
        int i = 0;
        std::istringstream stream(line);
        while(stream >> tokens[i]) i++;

        // Single token (Meaning it is a vertex)
        if(i == 1)
        {
            InsertVertex(tokens[0]);
        }
        // Exactly 5 tokens (Meaning it is an edge)
        else if(i == 5)
        {
            // Rename vars for readablity
            const std::string& vertexFromName = tokens[0];
            const std::string& vertexToName = tokens[1];
            const std::string& edgeName = tokens[2];
            float weight0 = static_cast<float>(std::atof(tokens[3].c_str()));
            float weight1 = static_cast<float>(std::atof(tokens[4].c_str()));
            AddEdge(edgeName, vertexFromName, vertexToName,
                    weight0, weight1);
        }
        else std::cerr << "Token Size Mismatch" << std::endl;
    }
}

void MultiGraph::PrintPath(const std::vector<int>& orderedVertexEdgeIndexList,
                           float heuristicWeight,
                           bool sameLine) const
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this file !       //
    // ============================= //

    // Name is too long
    const std::vector<int>& ove = orderedVertexEdgeIndexList;
    // Invalid list
    // At least three items should be available
    if(ove.size() < 3) return;

    // Check vertex and an edge
    for(size_t i = 0; i < orderedVertexEdgeIndexList.size(); i += 2)
    {
        int vertexId = ove[i];
        if(vertexId >= static_cast<int>(vertexList.size()))
        {
            // Return if there is a bad vertex id
            std::cout << "VertexId " << vertexId
                      << " not found!" << std::endl;
            return;
        }


        const GraphVertex& vertex = vertexList[vertexId];
        std::cout << vertex.name;
        if(!sameLine) std::cout << "\n";
        // Only find and print the weight if next is available
        if(i == ove.size() - 1) break;
        int nextVertexId = ove[i + 2];
        if(nextVertexId >= static_cast<int>(vertexList.size()))
        {
            // Return if there is a bad vertex id
            std::cout << "VertexId " << vertexId
                    << " not found!" << std::endl;
            return;
        }

        // Find the edge between these two vertices
        int localEdgeId = ove[i + 1];
        if(localEdgeId >= static_cast<int>(vertex.edges.size()))
        {
            // Return if there is a bad vertex id
            std::cout << "EdgeId " << localEdgeId
                      << " not found in " << vertexId << "!" << std::endl;
            return;
        }

        const GraphEdge& edge = vertex.edges[localEdgeId];

        // Combine with heuristic (linear interpolation)
        float weight = Lerp(edge.weight[0], edge.weight[1],
                            heuristicWeight);

        std::cout << "-" << std::setfill('-')
                  << std::setw(4)
                  << weight << "->";
    }
    // Print endline on the last vertex if same line is set
    if(sameLine) std::cout << "\n";
    // Reset fill value because it "sticks" to the std out
    std::cout << std::setfill(' ');
    std::cout.flush();
}

void MultiGraph::PrintEntireGraph() const
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    for(size_t i = 0; i < vertexList.size(); i++)
    {
        const GraphVertex& v = vertexList[i];
        std::cout << v.name << "\n";
        for(size_t j = 0; j < v.edges.size(); j++)
        {
            const GraphEdge& edge = v.edges[j];

            // List the all vertex names and weight
            std::cout << "    -"
                      << std::setfill('-')
                      << std::setw(4) << edge.weight[0]
                      << "-"
                      << std::setw(4) << edge.weight[1]
                      << "-> ";
            std::cout << vertexList[edge.endVertexIndex].name;
            std::cout << " (" << edge.name << ")" << "\n";
        }
    }
    // Reset fill value because it "sticks" to the std out
    std::cout << std::setfill(' ');
    std::cout.flush();
}

//=======================//
//          TODO         //
//=======================//
float MultiGraph::Lerp(float w0, float w1, float alpha)
{
    /* TODO */
    float beta = w0*(1.0f-alpha)+w1*(alpha);
    return beta;
}

void MultiGraph::InsertVertex(const std::string& vertexName)
{
    /* TODO */
    for(size_t  i=0;i<vertexList.size();i++){
        if(vertexName == vertexList[i].name){
            throw DuplicateVertexException(vertexName);
        }
    }
    GraphVertex newVertex;
    newVertex.name = vertexName;
    vertexList.push_back(newVertex);
}

int MultiGraph::indexOfVertex(const std::string& vertexName)const{
    int Index=-1; //Index
    for(size_t  i=0;i<vertexList.size();i++){
        if(vertexName==vertexList[i].name){
            Index=static_cast<int>(i); //find the index
        }
    }
    return Index;
}

int MultiGraph::IndexOfNonUtilizedAirline(int VertexIndex,std::vector<int>& visited,std::vector<std::string>& usedAirlines)const{
    int IndexOfNonUtilizedAirline = -1;
    int num=vertexList[VertexIndex].edges.size();
    for(int i=num-1;i>=0;i--){
        bool isInUsedAirlines=false;
        for(int j=0;j<usedAirlines.size();j++){
            if(vertexList[VertexIndex].edges[i].name == usedAirlines[j]){
                isInUsedAirlines=true;
                break;
            }
        }
        if(!isInUsedAirlines && !visited[vertexList[VertexIndex].edges[i].endVertexIndex]){
            IndexOfNonUtilizedAirline=i;
        }
    }
    return IndexOfNonUtilizedAirline;
}

std::string MultiGraph::NameOfAirline(int VertexIndex,int EdgeIndex)const{
    return vertexList[VertexIndex].edges[EdgeIndex].name;
}


Pair<float,float> MultiGraph::errorForFlight(const std::string& edgeName,
                                            const std::string& vertexFromName,
                                            const std::string& vertexToName){
    int fromIndex=-1; //fromIndex
    int toIndex=-1; //toIndex
    Pair<float,float> W={-1,-1};
    for(size_t  i=0;i<vertexList.size();i++){
        if(vertexFromName==vertexList[i].name){
            fromIndex=static_cast<int>(i); //find the index
        }
        if(vertexToName==vertexList[i].name){
            toIndex=static_cast<int>(i); //find the index
        }
    }
    if(fromIndex== -1 || toIndex== -1){  // if one of them does not exist
        return W;
    }

    int rmvEdge= -1;
    for(size_t  k=0;k<vertexList[fromIndex].edges.size();k++){
        if(vertexList[fromIndex].edges[k].endVertexIndex==toIndex && edgeName==vertexList[fromIndex].edges[k].name){ // I found a edge btw A to B named edgeName.
                rmvEdge = static_cast<int>(k);  // if there is a conflict
        }
    }
    if(rmvEdge != -1){
        W.key= vertexList[fromIndex].edges[rmvEdge].weight[0];
        W.value=vertexList[fromIndex].edges[rmvEdge].weight[1];
    }
    return W;
}
void MultiGraph::RemoveVertex(const std::string& vertexName)
{
    /* TODO */
    int rmvIndex=-1; //rmvIndex
    for(size_t  i=0;i<vertexList.size();i++){
        if(vertexName==vertexList[i].name){
            rmvIndex=static_cast<int>(i); //find the index
        }
    }
    if(rmvIndex== -1 ){  // if it does not exist
        throw VertexNotFoundException(vertexName);
    }

    //when we remove a vertex, after the index of this deleted vertex,
    //others will be shifted to left
    //so we need to change the edges which toward to those shifted vertices.
    

    // we need to deal with edges

    for(size_t i=0;i < vertexList.size();i++){
        for(size_t j=0; j< vertexList[i].edges.size(); j++){
            if(vertexList[i].edges[j].endVertexIndex == rmvIndex){
                vertexList[i].edges.erase(vertexList[i].edges.begin()+j);
                j--;// since the edge-list shifted towards left
            }
            else if(vertexList[i].edges[j].endVertexIndex > rmvIndex){ 
                vertexList[i].edges[j].endVertexIndex--; //shift the edges to left
            }
        }
    }

    vertexList.erase(vertexList.begin() + rmvIndex); // erase the vertex
}

void MultiGraph::AddEdge(const std::string& edgeName,
                         const std::string& vertexFromName,
                         const std::string& vertexToName,
                         float weight0, float weight1)
{
    /* TODO */
    int fromIndex=-1; //fromIndex
    int toIndex=-1; //toIndex
    for(size_t  i=0;i<vertexList.size();i++){
        if(vertexFromName==vertexList[i].name){
            fromIndex=static_cast<int>(i); //find the index
        }
        if(vertexToName==vertexList[i].name){
            toIndex=static_cast<int>(i); //find the index
        }
    }
    if(toIndex== -1 ){  // if one of them does not exist
        throw VertexNotFoundException(vertexToName);
    }
    if(fromIndex== -1  ){  // if one of them does not exist
        throw VertexNotFoundException(vertexFromName);
    }
    
    for(size_t  k=0;k<vertexList[fromIndex].edges.size();k++){
        if(vertexList[fromIndex].edges[k].endVertexIndex==toIndex && edgeName==vertexList[fromIndex].edges[k].name){ // I found a edge btw A to B named edgeName.
                throw SameNamedEdgeException(edgeName,vertexFromName, vertexToName);  // if there is a conflict
        }
    }
    //Both A and B exist, and there is no edge btw AtoB named edgeName.
    //Let's add the directional edge btw them
    vertexList[fromIndex].edges.push_back({edgeName, {weight0, weight1}, toIndex});
}

void MultiGraph::RemoveEdge(const std::string& edgeName,
                            const std::string& vertexFromName,
                            const std::string& vertexToName)
{
    /* TODO */
    int fromIndex=-1; //fromIndex
    int toIndex=-1; //toIndex
    for(size_t  i=0;i<vertexList.size();i++){
        if(vertexFromName==vertexList[i].name){
            fromIndex=static_cast<int>(i); //find the index
        }
        if(vertexToName==vertexList[i].name){
            toIndex=static_cast<int>(i); //find the index
        }
    }
    if(fromIndex== -1  ){  // if one of them does not exist
        throw VertexNotFoundException(vertexFromName);
    }
    if(toIndex== -1 ){  // if one of them does not exist
        throw VertexNotFoundException(vertexToName);
    }
    int rmvEdge= -1;
    for(size_t  k=0;k<vertexList[fromIndex].edges.size();k++){
        if(vertexList[fromIndex].edges[k].endVertexIndex==toIndex && edgeName==vertexList[fromIndex].edges[k].name){ // I found a edge btw A to B named edgeName.
                rmvEdge = static_cast<int>(k);  // if there is a conflict
        }
    }
    if(rmvEdge == -1){
        throw EdgeNotFoundException(vertexFromName,edgeName);
    }
    
    vertexList[fromIndex].edges.erase(vertexList[fromIndex].edges.begin()+rmvEdge);

}

void MultiGraph::reverseVector(std::vector<int>& vec) {
    int n = static_cast<int>(vec.size());
    for (int i = 0; i < n / 2; ++i) {
        std::swap(vec[i], vec[n - i - 1]);
    }
}

bool MultiGraph::HeuristicShortestPath(std::vector<int>& orderedVertexEdgeIndexList,
                                       const std::string& vertexNameFrom,
                                       const std::string& vertexNameTo,
                                       float heuristicWeight) const
{
    /* TODO */
    MinPairHeap<float,int> pq; //our prioirty queue
    int V=static_cast<int>(vertexList.size());//num of vertices
    std::vector<float> distance(V,99999999); 
    std::vector<int> previous(V,-1);
    std::vector<int> edgeIndex(V,-1);

    int fromIndex=-1; //fromIndex
    int toIndex=-1; //toIndex
    for(size_t  i=0;i<vertexList.size();i++){
        if(vertexNameFrom==vertexList[i].name){
            fromIndex=static_cast<int>(i); //find the index
        }
        if(vertexNameTo==vertexList[i].name){
            toIndex=static_cast<int>(i); //find the index
        }
    }
    if(fromIndex==-1){  // if one of them does not exist
        throw VertexNotFoundException(vertexNameFrom);
    }
    if(toIndex== -1){  // if one of them does not exist
        throw VertexNotFoundException(vertexNameTo);
    }
    
    //std::cout<<"toIndex= "<<toIndex<<"fromIndex= "<<fromIndex<<std::endl;
    
    distance[fromIndex]=0; 

    for (int i = 0; i < V; ++i) { // Add all vertices to pq
        pq.push({distance[i], i});
    }
    while (!pq.empty()){
        Pair<float,int> curr = pq.top();
        //std::cout<<"curr= "<<curr.value<<" "<<curr.key<<std::endl;
        pq.pop();
        for(size_t  k=0;k<vertexList[curr.value].edges.size();k++){
            int v = vertexList[curr.value].edges[k].endVertexIndex;
            float beta = Lerp(vertexList[curr.value].edges[k].weight[0],vertexList[curr.value].edges[k].weight[1],heuristicWeight);
            float newDist = beta + distance[curr.value];
            if(newDist < distance[v]){
                distance[v] = newDist;
                previous[v] = curr.value;
                edgeIndex[v] = static_cast<int>(k);
                pq.push({newDist, v});
            }
        }
        if(curr.value==toIndex){ // we react to the target vertex
            //std::cout<<"vardık "<<curr.value<<" "<<curr.key<<std::endl;
            break;
        }
    }
    // Dijkstras algorith is done

    if(distance[toIndex]==99999999){
        //std::cout<<"MESAFE 99999999 ÇIKTI!"<<std::endl;
        return false;
    }
    int endIndex=toIndex;
    // Let's write the path itself.
    orderedVertexEdgeIndexList.clear();
    while (endIndex != -1 && previous[endIndex] != -1) {
        orderedVertexEdgeIndexList.push_back(endIndex);
        orderedVertexEdgeIndexList.push_back(edgeIndex[endIndex]);
        endIndex=previous[endIndex];
    }
    orderedVertexEdgeIndexList.push_back(endIndex);
    //reverseVector(orderedVertexEdgeIndexList);
    int n = static_cast<int>(orderedVertexEdgeIndexList.size());
    int temp;
    for (int i = 0; i < n / 2; ++i) {
        temp = orderedVertexEdgeIndexList[i];
        orderedVertexEdgeIndexList[i] = orderedVertexEdgeIndexList[n - i - 1];
        orderedVertexEdgeIndexList[n - i - 1] = temp;
    }
    if(orderedVertexEdgeIndexList.size()>1){
        return true;
    }else{
        return false;
    }
}

bool MultiGraph::FilteredShortestPath(std::vector<int>& orderedVertexEdgeIndexList,
                                      const std::string& vertexNameFrom,
                                      const std::string& vertexNameTo,
                                      float heuristicWeight,
                                      const std::vector<std::string>& edgeNames) const
{
    /* TODO */
    MinPairHeap<float,int> pq; //our prioirty queue
    int V=static_cast<int>(vertexList.size());//num of vertices
    std::vector<float> distance(V,99999999); 
    std::vector<int> previous(V,-1);
    std::vector<int> edgeIndex(V,-1);

    int fromIndex=-1; //fromIndex
    int toIndex=-1; //toIndex
    for(size_t  i=0;i<vertexList.size();i++){
        if(vertexNameFrom==vertexList[i].name){
            fromIndex=static_cast<int>(i); //find the index
        }
        if(vertexNameTo==vertexList[i].name){
            toIndex=static_cast<int>(i); //find the index
        }
    }
    if(fromIndex==-1){  // if one of them does not exist
        throw VertexNotFoundException(vertexNameFrom);
    }
    if(toIndex== -1){  // if one of them does not exist
        throw VertexNotFoundException(vertexNameTo);
    }
    
    //std::cout<<"toIndex= "<<toIndex<<"fromIndex= "<<fromIndex<<std::endl;
    
    distance[fromIndex]=0; 

    for (int i = 0; i < V; ++i) { // Add all vertices to pq
        pq.push({distance[i], i});
    }
    while (!pq.empty()){
        Pair<float,int> curr = pq.top();
        //std::cout<<"curr= "<<curr.value<<" "<<curr.key<<std::endl;
        pq.pop();
        for(size_t  k=0;k<vertexList[curr.value].edges.size();k++){
            int v = vertexList[curr.value].edges[k].endVertexIndex;
            bool isAllowed=true;
            for(size_t i=0;i<edgeNames.size();i++){
                if(vertexList[curr.value].edges[k].name == edgeNames[i]){
                    isAllowed = false;
                }
            }
            if(isAllowed){
                float beta = Lerp(vertexList[curr.value].edges[k].weight[0],vertexList[curr.value].edges[k].weight[1],heuristicWeight);
                float newDist = beta + distance[curr.value];
                if(newDist < distance[v]){
                    distance[v] = newDist;
                    previous[v] = curr.value;
                    edgeIndex[v] = static_cast<int>(k);
                    pq.push({newDist, v});
                }
            }
        }
        if(curr.value==toIndex){ // we react to the target vertex
            //std::cout<<"vardık "<<curr.value<<" "<<curr.key<<std::endl;
            break;
        }
    }
    // Dijkstras algorith is done

    if(distance[toIndex]==99999999){
        //std::cout<<"MESAFE 99999999 ÇIKTI!"<<std::endl;
        return false;
    }
    int endIndex=toIndex;
    // Let's write the path itself.
    orderedVertexEdgeIndexList.clear();
    while (endIndex != -1 && previous[endIndex] != -1) {
        orderedVertexEdgeIndexList.push_back(endIndex);
        orderedVertexEdgeIndexList.push_back(edgeIndex[endIndex]);
        endIndex=previous[endIndex];
    }
    orderedVertexEdgeIndexList.push_back(endIndex);
    //reverseVector(orderedVertexEdgeIndexList);
    int n = static_cast<int>(orderedVertexEdgeIndexList.size());
    for (int i = 0; i < n / 2; ++i) {
        std::swap(orderedVertexEdgeIndexList[i], orderedVertexEdgeIndexList[n - i - 1]);
    }

    return !orderedVertexEdgeIndexList.empty();
}

bool MultiGraph::FilteredShortestPathForCengFlight(std::vector<int>& orderedVertexEdgeIndexList,
                                      const std::string& vertexNameFrom,
                                      const std::string& vertexNameTo,
                                      float heuristicWeight,
                                      const std::vector<std::string>& edgeNames) const
{
    /* TODO */
    MinPairHeap<float,int> pq; //our prioirty queue
    int V=static_cast<int>(vertexList.size());//num of vertices
    std::vector<float> distance(V,99999999); 
    std::vector<int> previous(V,-1);
    std::vector<int> edgeIndex(V,-1);

    int fromIndex=-1; //fromIndex
    int toIndex=-1; //toIndex
    for(size_t  i=0;i<vertexList.size();i++){
        if(vertexNameFrom==vertexList[i].name){
            fromIndex=static_cast<int>(i); //find the index
        }
        if(vertexNameTo==vertexList[i].name){
            toIndex=static_cast<int>(i); //find the index
        }
    }
    if(fromIndex==-1){  // if one of them does not exist
        return false;
    }
    if(toIndex== -1){  // if one of them does not exist
        return false;
    }
    
    //std::cout<<"toIndex= "<<toIndex<<"fromIndex= "<<fromIndex<<std::endl;
    
    distance[fromIndex]=0; 

    for (int i = 0; i < V; ++i) { // Add all vertices to pq
        pq.push({distance[i], i});
    }
    while (!pq.empty()){
        Pair<float,int> curr = pq.top();
        //std::cout<<"curr= "<<curr.value<<" "<<curr.key<<std::endl;
        pq.pop();
        for(size_t  k=0;k<vertexList[curr.value].edges.size();k++){
            int v = vertexList[curr.value].edges[k].endVertexIndex;
            bool isAllowed=true;
            for(size_t i=0;i<edgeNames.size();i++){
                if(vertexList[curr.value].edges[k].name == edgeNames[i]){
                    isAllowed = false;
                }
            }
            if(isAllowed){
                float beta = Lerp(vertexList[curr.value].edges[k].weight[0],vertexList[curr.value].edges[k].weight[1],heuristicWeight);
                float newDist = beta + distance[curr.value];
                if(newDist < distance[v]){
                    distance[v] = newDist;
                    previous[v] = curr.value;
                    edgeIndex[v] = static_cast<int>(k);
                    pq.push({newDist, v});
                }
            }
        }
        if(curr.value==toIndex){ // we react to the target vertex
            //std::cout<<"vardık "<<curr.value<<" "<<curr.key<<std::endl;
            break;
        }
    }
    // Dijkstras algorith is done

    if(distance[toIndex]==99999999){
        //std::cout<<"MESAFE 99999999 ÇIKTI!"<<std::endl;
        return false;
    }
    int endIndex=toIndex;
    // Let's write the path itself.
    orderedVertexEdgeIndexList.clear();
    while (endIndex != -1 && previous[endIndex] != -1) {
        orderedVertexEdgeIndexList.push_back(endIndex);
        orderedVertexEdgeIndexList.push_back(edgeIndex[endIndex]);
        endIndex=previous[endIndex];
    }
    orderedVertexEdgeIndexList.push_back(endIndex);
    //reverseVector(orderedVertexEdgeIndexList);
    int n = static_cast<int>(orderedVertexEdgeIndexList.size());
    for (int i = 0; i < n / 2; ++i) {
        std::swap(orderedVertexEdgeIndexList[i], orderedVertexEdgeIndexList[n - i - 1]);
    }

    return !orderedVertexEdgeIndexList.empty();
}

int MultiGraph::BiDirectionalEdgeCount() const
{
    /* TODO */
    int biCount = 0;
    std::vector<int> seenVertex(vertexList.size(),0); //we will mark them as seen
    for(size_t  i=0;i<vertexList.size();i++){
        for(size_t  j=0;j<vertexList[i].edges.size();j++){
            int endVertexIndex = vertexList[i].edges[j].endVertexIndex;
            if(seenVertex[endVertexIndex] == 0){
                std::string edgeName = vertexList[i].edges[j].name;
                for(size_t  k=0; k<vertexList[endVertexIndex].edges.size();k++){
                    if(vertexList[endVertexIndex].edges[k].name == edgeName && vertexList[endVertexIndex].edges[k].endVertexIndex == static_cast<int>(i)){
                        biCount++;
                    }
                }
            }
        }
        seenVertex[i]=1;
        
    }    
    return biCount;
}

int MultiGraph::Number() const{
    return vertexList.size();
}

int MultiGraph::NumberOfNonVisitedNeighbor(int vertexIndex,std::vector<int>& visited)const{
    int num=0;
    for(int i=0;i<vertexList[vertexIndex].edges.size();i++){
        if(visited[vertexList[vertexIndex].edges[i].endVertexIndex]==0){
            num++;
        }
    }
    return num;
}

int MultiGraph::MaxVisitViaEdgeList(int startVertexIndex,
                                    std::vector<std::string>& edgeNames,
                                    std::vector<int>& visited) const{
    
    int error=0;
    int maxDepth = 0;
    MinPairHeap<int, int> q;  // Pair: depth, vertex index
    //visited[startVertexIndex]=1;

    q.push({0,startVertexIndex });  // Start vertex with depth 0

    while (!q.empty()) {
        Pair<int,int> curr = q.top();
        int currIndex = curr.value;
        int depth = curr.key;
        q.pop();
        
        
        visited[currIndex] = 1;
        for(size_t  i=0;i<vertexList[currIndex].edges.size();i++){
            for(int j=0;j<edgeNames.size();j++){
                if (vertexList[currIndex].edges[i].name == edgeNames[j]) {
                    error=1;
                    int nextVertexIndex = vertexList[currIndex].edges[i].endVertexIndex;
                    if (!visited[nextVertexIndex]) {
                        q.push({depth + 1, nextVertexIndex});
                        maxDepth = depth + 1;
                    }
                }
            }
        }
    }    
    return error;
}


int MultiGraph::MaxDepthViaEdgeName(const std::string& vertexName,
                                    const std::string& edgeName) const
{
    /* TODO */
    int startVertexIndex = -1;
    for (size_t i = 0; i < vertexList.size(); ++i) {
        if (vertexList[i].name == vertexName) {
            startVertexIndex = static_cast<int>(i);
            break;
        }
    }
    if (startVertexIndex == -1) {
        throw VertexNotFoundException(vertexName);
    }
    int maxDepth = 0;
    MinPairHeap<int, int> q;  // Pair: depth, vertex index
    std::vector<bool> visited(vertexList.size(), false);
    

    q.push({0,startVertexIndex });  // Start vertex with depth 0

    while (!q.empty()) {
        Pair<int,int> curr = q.top();
        int currIndex = curr.value;
        int depth = curr.key;
        q.pop();
        

        visited[currIndex] = true;
        for(size_t  i=0;i<vertexList[currIndex].edges.size();i++){
            if (vertexList[currIndex].edges[i].name == edgeName) {
                int nextVertexIndex = vertexList[currIndex].edges[i].endVertexIndex;
                if (!visited[nextVertexIndex]) {
                    q.push({depth + 1, nextVertexIndex});
                    if(maxDepth < depth + 1){
                        maxDepth = depth + 1;
                    }
                }
            }
        }
    }
    return maxDepth;
}



#endif // MULTI_GRAPH_H