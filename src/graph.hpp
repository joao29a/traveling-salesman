#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <unordered_map>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <limits>

using namespace std;

template<typename T, typename C>
struct Vertex{
    T id;
    string color = "white";
    C key;
    Vertex<T,C>* parent;
    unordered_map<T, C> edges;
    Vertex(T id){ this->id = id; };
};

template<typename T, typename C>
using map_vertex_t = unordered_map<T, Vertex<T, C>*>;

template<typename T, typename C>
class Graph{
    public:
        Graph(){};
        ~Graph();
        void set_vertex(T);
        map_vertex_t<T,C>& get_vertices();
        void set_edge(T, T, C);
        Vertex<T,C>* get_vertex(T);
        void read_file(const char*);
        C get_cost(T, T);
        Vertex<T,C>* get_first();

    private:
        map_vertex_t<T,C> adj_list;
};

template<typename T, typename C>
Graph<T,C>::~Graph(){
    for (auto& vet: adj_list){
        delete vet.second;
    }
}

template<typename T, typename C>
map_vertex_t<T,C>& Graph<T,C>::get_vertices(){
    return adj_list;
}

template<typename T, typename C>
void Graph<T,C>::read_file(const char* filename){
    ifstream file;
    file.open(filename);

    string line;
    unordered_map<T, pair<C, C>> vt_coord;
    while (getline(file, line)){
        stringstream s(line);
        T vt;
        C pos_x, pos_y;
        s >> vt >> pos_x >> pos_y;
        pair<C, C> coord = {pos_x, pos_y};
        vt_coord[vt] = coord;
    }
    for (auto& elem1: vt_coord){
        for (auto& elem2: vt_coord){
            if (elem1.first == elem2.first) continue;
            C coord = pow(elem1.second.first - elem2.second.first, 2);
            coord += pow(elem1.second.second - elem2.second.second, 2);
            coord = sqrt(coord);
            set_vertex(elem1.first);
            set_edge(elem1.first, elem2.first, coord);
            set_vertex(elem2.first);
            set_edge(elem2.first, elem1.first, coord);
        }
    }
}

template<typename T, typename C>
void Graph<T,C>::set_vertex(T id){
    if (adj_list[id] == NULL){
        adj_list[id] = new Vertex<T,C>(id);
    }
}

template<typename T, typename C>
void Graph<T,C>::set_edge(T id, T id_edge, C weight){
    adj_list[id]->edges[id_edge] = weight;
}

template<typename T, typename C>
Vertex<T,C>* Graph<T,C>::get_vertex(T id){
    return adj_list[id];
}

template<typename T, typename C>
Vertex<T,C>* Graph<T,C>::get_first(){
    return adj_list.begin()->second;
}

template<typename T, typename C>
C Graph<T,C>::get_cost(T vt1, T vt2){
    if (adj_list[vt1]->edges.find(vt2) == adj_list[vt1]->edges.end())
        return adj_list[vt2]->edges[vt1];
    return adj_list[vt1]->edges[vt2];
}


template<typename T, typename C>
C get_total_cost(Graph<T,C>* graph, vector<T>* path){
    C cost = 0;
    for (int i = 0; i < path->size() - 1; i++){
        cost += graph->get_cost(path->at(i), path->at(i + 1));
    }
    return cost;
}

#endif
