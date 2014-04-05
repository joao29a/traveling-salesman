#ifndef BRUTE
#define BRUTE

#include "graph.hpp"
#include <vector>
#include <iostream>

/* heap's algorithm */
template<typename T>
void generate_permutations(size_t N, vector<T>& vertices, 
        vector<vector<T>>& permutations){
    if (N == 1)
        permutations.push_back(vertices);
    else{
        for (int i = 0; i < N; i++){
            generate_permutations(N - 1, vertices, permutations);
            int index = i;
            if (N % 2 != 0)
                index = 0;
            T tmp = vertices[N-1];
            vertices[N-1] = vertices[index];
            vertices[index] = tmp;
        }
    }
}

template<typename T, typename C>
vector<T> get_best_path(Graph<T,C>*graph, vector<vector<T>>& permutations, 
        Vertex<T,C>* root){
    C best_cost = numeric_limits<C>::max();
    vector<T> best_path;
    for (auto& tour: permutations){
        if (tour[0] == root->id){
            tour.push_back(root->id);
            C cost = get_total_cost(graph, &tour);
            if (cost < best_cost){
                best_path = tour;
                best_cost = cost;
            }
        }
    }
    return best_path;
}

template<typename T, typename C>
vector<T>* brute_force(Graph<T,C>* graph, Vertex<T,C>* root){
    vector<T>* path = new vector<T>();
    vector<T> vertices;
    vector<vector<T>> permutations;
    for (auto& vt: graph->get_vertices()) vertices.push_back(vt.first);
    generate_permutations(vertices.size(), vertices, permutations);
    for (auto& vertex: get_best_path(graph, permutations, root)) path->push_back(vertex);
    return path;
}

#endif
