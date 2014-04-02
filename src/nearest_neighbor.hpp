#ifndef NN
#define NN

#include <vector>
#include <limits>
#include "graph.hpp"

template<typename T, typename C>
vector<T>* nearest_neighbor(Graph<T,C>* graph, Vertex<T,C>* root){
    vector<T>* path = new vector<T>();
    vector<T> Q = {root->id};
    while (!Q.empty()){
        T node = Q.back();
        Q.pop_back();
        Vertex<T,C>* vertex = graph->get_vertex(node);
        vertex->color = "gray";
        pair<T*, C> lowest = make_pair(nullptr, numeric_limits<C>::max());
        for (auto& edge: vertex->edges){
            if (graph->get_vertex(edge.first)->color == "white" 
                    && edge.second < lowest.second)
                lowest = make_pair((T*)&edge.first, edge.second);
        }
        if (lowest.first != nullptr){
            graph->get_vertex(*lowest.first)->color = "gray";
            vertex->color = "black";
            path->push_back(node);
            Q.push_back(*lowest.first);
        }
        else path->push_back(node);
    }
    path->push_back(root->id);
    return path;
}

#endif
