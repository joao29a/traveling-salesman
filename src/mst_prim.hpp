#ifndef PRIM
#define PRIM

#include <iostream>
#include <unordered_set>
#include <algorithm>
#include "graph.hpp"
#include "heap.hpp"

template<typename T, typename C>
struct ComparePrim {
    bool operator()(const pair<T,C*>& p1, const pair<T,C*>& p2){
        return *p1.second > *p2.second;
    }
};

template<typename T, typename C>
vector<T>* mst_prim(Graph<T,C>* graph, Vertex<T,C>* root){
    vector<T>* path = new vector<T>();
    vector<pair<T,C*>> Q;
    for (auto& vertex: graph->get_vertices()){
        vertex.second->key = numeric_limits<C>::max();
        vertex.second->parent = nullptr;
        pair<T,C*> pair_vt = {vertex.first, &vertex.second->key};
        Q.push_back(pair_vt);
    }
    root->key = 0;
    Heap<pair<T,C*>, vector, ComparePrim<T,C>> heap;
    unordered_set<T> S;
    while (Q.size() != 0){
        pair<T,C*> node = heap.pop(Q);
        S.insert(node.first);
        path->push_back(node.first);
        Vertex<T,C>* vertex = graph->get_vertex(node.first);
        for (auto& edge: vertex->edges){
            Vertex<T,C>* adj_vertex = graph->get_vertex(edge.first);
            if (S.find(adj_vertex->id) == S.end() &&
                    adj_vertex->key > edge.second){
                adj_vertex->key = edge.second;
                adj_vertex->parent = vertex;
            }
        }
        heap.build(Q);
    }
    path->push_back(root->id);
    return path;
}

#endif
