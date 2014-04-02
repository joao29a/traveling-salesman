#ifndef PRIM
#define PRIM

#include <iostream>
#include <unordered_set>
#include <algorithm>
#include "graph.hpp"

using namespace std;

template<typename T, typename C>
struct Heap{
    struct Compare{
        bool operator()(const pair<T,C*>& p1, const pair<T,C*>& p2) const {
            return *p1.second > *p2.second;
        }
    };

    static void build(vector<pair<T,C*>>& vt){
        make_heap(vt.begin(), vt.end(), Compare());
    }
    
    static pair<T,C*> pop(vector<pair<T,C*>>& vt){
        pair<T,C*> node = vt.front();
        pop_heap(vt.begin(), vt.end(), Compare());
        vt.pop_back();
        return node;
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
    Heap<T,C>::build(Q);
    unordered_set<T> S;
    while (Q.size() != 0){
        pair<T,C*> node = Heap<T,C>::pop(Q);
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
        Heap<T,C>::build(Q);
    }
    path->push_back(root->id);
    return path;
}

#endif
