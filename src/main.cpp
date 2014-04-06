#include "graph.hpp"
#include "nearest_neighbor.hpp"
#include "mst_prim.hpp"
#include "genetic.hpp"
#include "brute_force.hpp"
#include <limits>
#include <iostream>

#define KEY int
#define VALUE int

#define ALGORITHMS vector<KEY>*(*)\
    (Graph<KEY, VALUE>*, Vertex<KEY, VALUE>*)

unordered_map<string, ALGORITHMS> algs = {
    {"nn",  &nearest_neighbor},
    {"mst", &mst_prim},
    {"bf",  &brute_force}
};

template<typename T, typename C>
void print_path(Graph<T,C>* graph, vector<T>* path){
    for (int i = 0; i < path->size(); i++){
        cout << path->at(i) << " ";
    }
    cout << get_total_cost(graph, path) << endl;
}

int main(int argc, char** argv){
    Graph<KEY, VALUE>* graph = new Graph<KEY, VALUE>();
    graph->read_file(argv[2]);
    if (algs.find(string(argv[1])) != algs.end())
        print_path(graph, algs[argv[1]](graph, graph->get_first()));
    else {
        stringstream s;
        s << string(argv[3]) << " " << string(argv[4]) << " " << string(argv[5]);
        size_t pop_size, max_time;
        double mutation_rate;
        s >> pop_size >> mutation_rate >> max_time;
        print_path(graph, genetic_tsp(graph, pop_size, mutation_rate, max_time));
    }
    return 0;
}
