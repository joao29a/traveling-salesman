#include "graph.hpp"
#include "nearest_neighbor.hpp"
#include "mst_prim.hpp"
#include "genetic.hpp"
#include <limits>
#include <iostream>

#define KEY int
#define VALUE float

#define HEURISTIC vector<KEY>*(*)\
    (Graph<KEY, VALUE>*, Vertex<KEY, VALUE>*)

unordered_map<string, HEURISTIC> algs = {
    {"nn",  &nearest_neighbor},
    {"mst", &mst_prim}
};

template<typename T, typename C>
void print_path(Graph<T,C>* graph, vector<T>* path){
    VALUE cost = 0;
    for (int i = 0; i < (int) (path->size() - 1); i++){
        cost += graph->get_cost(path->at(i), path->at(i + 1));
    }
    for (int i = 0; i < path->size(); i++){
        cout << path->at(i) << " ";
    }
    cout << cost << endl;
}

int main(int argc, char** argv){
    Graph<KEY, VALUE>* graph = new Graph<KEY, VALUE>();
    graph->read_file(argv[2]);
    if (algs.find(string(argv[1])) != algs.end())
        print_path(graph, algs[argv[1]](graph, graph->get_first()));
    else{
        stringstream s;
        s << string(argv[3]) << " " << string(argv[4]);
        size_t pop_size;
        double mutation_rate;
        s >> pop_size >> mutation_rate;
        print_path(graph, genetic_tsp(graph, pop_size, mutation_rate));
    }
    return 0;
}
