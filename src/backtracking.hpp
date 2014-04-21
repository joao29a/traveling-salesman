#ifndef BACKTRACKING
#define BACKTRACKING

#include <vector>
#include "graph.hpp"

template<typename T, typename C>
vector<T>* backtracking_search(Graph<T,C>* graph, Vertex<T,C>* root){
    vector<T>* path = new vector<T>();
    if (backtracking(graph, root, path)){
        path->push_back(root->id);
        return path;
    }
    return NULL;
}

template<typename T, typename C>
bool backtracking(Graph<T,C>* graph, Vertex<T,C>* root, vector<T>* path){
    if (path->size() == graph->get_vertices().size())
        return true;
    if (root->color != "white")
        return false;
    root->color = "black";
    path->push_back(root->id);
    for (auto& edge: root->edges){
        Vertex<T,C>* vertex = graph->get_vertex(edge.first);
        if (backtracking(graph, vertex, path))
            return true;
    }
    return false;
}

#endif
