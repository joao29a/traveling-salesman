#ifndef AG
#define AG

#include "graph.hpp"
#include <vector>

template<typename T, typename C>
using pair_t = pair<vector<T>*, C>;

template<typename T, typename C>
using vector_list = vector<pair_t<T,C>*>;

template<typename T, typename C>
C get_cost(Graph<T,C>* graph, vector<T>* path){
    C cost = 0;
    for (int i = 0; i < path->size() - 1; i++){
        cost += graph->get_cost(path->at(i), path->at(i + 1));
    }
    return cost;
}

/* This is faster than the erase function from vector */
template<typename T>
void remove(vector<T>& vt, int pos){
    T tmp = vt[pos];
    vt[pos] = vt.back();
    vt[vt.size() - 1] = tmp;
    vt.pop_back();
}

template<typename T, typename C>
vector_list<T,C>* generate_population(Graph<T,C>* graph, size_t population_size){
    vector_list<T,C>* population = new vector_list<T,C>();
    vector<T> vertices;
    for (auto& vertex: graph->get_vertices()){
        vertices.push_back(vertex.first);
    }
    while (population->size() < population_size){
        vector<T> vertices_left(vertices);
        vector<T>* individual = new vector<T>();
        while (!vertices_left.empty()){
            int pos = rand() % vertices_left.size();
            individual->push_back(vertices_left[pos]);
            remove<T>(vertices_left, pos);
        }
        individual->push_back(*individual->begin());
        pair_t<T,C>* individual_cost = new pair_t<T,C>();
        *individual_cost = make_pair(individual, get_cost(graph, individual));
        population->push_back(individual_cost);
    }
    return population;
}

template<typename T, typename C>
struct Compare{
    bool operator()(pair_t<T,C>* x, pair_t<T,C>* y) const {
        return x->second < y->second;
    }
};

template<typename T, typename C>
vector<T>* genetic_tsp(Graph<T,C>* graph, size_t population_size, 
        double mutation_rate){
    srand(time(NULL));
    vector<T>* best = new vector<T>();
    vector_list<T,C>* population = generate_population(graph, population_size);
    sort(population->begin(), population->end(), Compare<T,C>());
    //TODO sex, mutation, population update
    return best;
}

#endif
