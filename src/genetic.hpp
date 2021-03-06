#ifndef GA
#define GA

#include "graph.hpp"
#include "heap.hpp"
#include <vector>
#include <deque>

template<typename T, typename C>
using pair_t = pair<vector<T>*, C>;

template<typename T, typename C>
struct CompareGenetic{
    bool operator()(pair_t<T,C>* p1, pair_t<T,C>* p2){
        return p1->second > p2->second;
    }
};

template<typename T, typename C>
using deque_pair = deque<pair_t<T,C>*>;

/* This is faster than the erase function from vector/deque */
template<typename T, typename D>
void swap(D& vt, int pos1, int pos2){
    T tmp = vt[pos1];
    vt[pos1] = vt[pos2];
    vt[pos2] = tmp;
}

template<typename T, typename D>
void remove(D& vt, int pos){
    swap<T, D>(vt, pos, vt.size() - 1);
    vt.pop_back();
}

template<typename T, typename C>
deque_pair<T,C>* generate_population(Graph<T,C>* graph, size_t population_size){
    deque_pair<T,C>* population = new deque_pair<T,C>();
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
            remove<T, vector<T>>(vertices_left, pos);
        }
        individual->push_back(*individual->begin());
        pair_t<T,C>* individual_cost = new pair_t<T,C>();
        *individual_cost = make_pair(individual, get_total_cost(graph, individual));
        population->push_back(individual_cost);
    }
    return population;
}

/* only works if C is an int type */
template<typename T, typename C>
bool is_population_improving(deque_pair<T,C>* population){
    for (int i = 1; i < population->size(); i++){
        if (population->at(0)->second != population->at(i)->second)
            return true;
    }
    return false;
}

template<typename T, typename C>
pair_t<T,C>* crossover(Graph<T,C>* graph, pair_t<T,C>* parent1, 
        pair_t<T,C>* parent2){
    pair_t<T,C>* individual = new pair_t<T,C>();
    unordered_set<T> visited;
    vector<T>* path = new vector<T>();
    int part = rand() % 2 + 1;
    int init = 0;
    if (part == 1) init = parent1->first->size() / 2;
    for (int i = init; i < parent1->first->size() / part; i++){
        path->push_back(parent1->first->at(i));
        visited.insert(parent1->first->at(i));
    }
    for (auto& elem: (*parent2->first)){
        if (visited.find(elem) == visited.end()){
            path->push_back(elem);
            visited.insert(elem);
        }
    }
    path->push_back(path->front());
    *individual = make_pair(path, get_total_cost(graph, path));
    return individual;
}

template<typename T, typename C>
void mutation(Graph<T,C>* graph, pair_t<T,C>* individual, 
        double mutation_rate){
    if (((double) rand() / RAND_MAX) < mutation_rate){
        int pos1 = (rand() % (individual->first->size() - 2)) + 1;
        int pos2 = pos1;
        while (pos2 == pos1)
            pos2 = (rand() % (individual->first->size() - 2)) + 1;
        swap<T, vector<T>>(*individual->first, pos1, pos2);
        individual->second = get_total_cost(graph, individual->first);
    }
}

template<typename T, typename C>
void update_population(deque_pair<T,C>* population, pair_t<T,C>* individual){
    delete population->back()->first;
    delete population->back();
    population->pop_back();
}

template<typename T, typename C>
vector<T>* genetic_tsp(Graph<T,C>* graph, size_t population_size, 
        double mutation_rate, size_t max_time){
    srand(time(NULL));
    deque_pair<T,C>* population = generate_population(graph, population_size);
    Heap<pair_t<T,C>*, deque, CompareGenetic<T,C>> heap;
    heap.build(*population);
    size_t init_time = time(NULL);
    while (is_population_improving(population) && 
            (time(NULL) - init_time) < max_time){
        int pos = rand() % (population_size - 1) + 1;
        pair_t<T,C>* individual = crossover(graph, population->at(0), 
                population->at(pos));
        mutation(graph, individual, mutation_rate);
        update_population(population, individual);
        heap.push(*population, individual);
    }
    return population->front()->first;
}

#endif
