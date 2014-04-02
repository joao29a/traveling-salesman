#ifndef KRUSKAL
#define KRUSKAL

#include "graph.hpp"
#include <algorithm>
#include <unordered_set>

template<typename T, typename C>
struct DisjointSet{
    static void union_set(Vertex<T,C>* x, Vertex<T,C>* y){
        Vertex<T,C>* xRoot = find(x);
        Vertex<T,C>* yRoot = find(y);
        if (xRoot == yRoot) return;

        if (xRoot->rank > yRoot->rank)
            yRoot->parent = xRoot;
        else if (yRoot->rank > xRoot->rank)
            xRoot->parent = yRoot;
        else{
            yRoot->parent = xRoot;
            xRoot->rank += 1;
        }
    }

    static Vertex<T,C>* find(Vertex<T,C>* vertex){
        if (vertex->parent != vertex)
            vertex->parent = find(vertex->parent);
        return vertex->parent;
    }

    static void make_set(Vertex<T,C>* vertex){
        vertex->parent = vertex;
        vertex->rank = 0;
    }
};

template<typename T, typename C>
struct Compare{
    bool operator()(const pair<pair<T,T>,C>& x, const pair<pair<T,T>,C>& y){
        return x.second > y.second;
    }
};

template<typename T, typename C>
vector<pair<T,T>> mst_kruskal(Graph<T,C>* graph){
    vector<pair<T,T>> A;
    vector<pair<pair<T,T>,C>> edges_c;
    unordered_set<T> visited;
    for (auto& x: graph->get_vertices()){
        DisjointSet<T,C>::make_set(x.second);
        visited.insert(x.first);
        for (auto& y: x.second->edges){
            if (visited.find(y.first) == visited.end()){
                pair<T,T> edge = {x.first, y.first};
                pair<pair<T,T>,C> edge_c = {edge, y.second};
                edges_c.push_back(edge_c);
            }
        }
    }
    sort(edges_c.begin(), edges_c.end(), Compare<T,C>());
    while (!edges_c.empty()){
        pair<pair<T,T>,C> edge_c = edges_c.back();
        edges_c.pop_back();
        Vertex<T,C>* x = graph->get_vertex(edge_c.first.first);
        Vertex<T,C>* y = graph->get_vertex(edge_c.first.second);
        if (DisjointSet<T,C>::find(x) != DisjointSet<T,C>::find(y)){
            A.push_back({x->id, y->id});
            DisjointSet<T,C>::union_set(x, y);
        }
    }
    return A;
}


#endif
