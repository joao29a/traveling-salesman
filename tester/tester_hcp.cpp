#include "hdr/tester_hcp.hpp"
#include <unistd.h>

TesterHCP::TesterHCP(const char* filename){
    set_vertices(filename);
}

TesterHCP::TesterHCP(vertex_set_t& vertices){
    set_vertices(vertices);
}

void TesterHCP::set_vertices(const char* filename){
    ifstream f;
    f.open(filename);

    string line;
    while (getline(f, line)){
        stringstream s(line);
        string vt;
        float pos_x, pos_y;
        s >> vt >> pos_x >> pos_y;
        pair<float, float> coord = {pos_x, pos_y};
        vertices[vt] = coord;
    }

    total_vt = vertices.size();

    f.close();
}

bool TesterHCP::test_result(){
    if (path.empty()){
        cout << "Fail: No path" << endl;
        return false;
    }
    else if (total_vt > path.size() - 1){
        cout << "Fail: Missing vertex " << path << endl;
        return false;
    }
    else if (total_vt < path.size() - 1){
        cout << "Fail: Repeated vertex " << path << endl;
        return false;
    }
    if (path[0] != path.back()){
        cout << "Fail: Init != End " << endl;
        return false;
    }
    unordered_set<string> visited_vt;
    for (int i = 0; i < path.size() - 1; i++){
        if (visited_vt.find(path[i]) != visited_vt.end()){
            cout << "Fail: Vertex already visisted\n";
            return false;
        }
        else if (vertices.find(path[i]) == vertices.end()){
            cout << "Fail: Inexistent vertex: " << path[i] << endl;
            return false;
        }
        visited_vt.insert(path[i]);
    }
    return true;
}

float TesterHCP::get_cost(string vt1, string vt2){
    pair<float, float> coord_vt1 = vertices[vt1];
    pair<float, float> coord_vt2 = vertices[vt2];
    float coord = pow(coord_vt1.first - coord_vt2.first, 2);
    coord += pow(coord_vt1.second - coord_vt2.second, 2);
    return sqrt(coord);
}

bool TesterHCP::test_cost(){
    float cost = 0;
    for (int i = 0; i < path.size() - 1; i++){
        cost += get_cost(path[i], path[i + 1]);
    }
    int final_cost = (int)this->cost - (int)cost;
    if (final_cost != 0){
        cout << "Fail: Wrong cost " << this->cost << " != " << cost << endl;
        return false;
    }
    return true;
}

void TesterHCP::read_output(){
    string word;
    while (getline(cin, word, ' ')){
        path.push_back(word);
    }
    cost = atof(path.back().c_str());
    path.pop_back();
}

void TesterHCP::run_test(const char* file){
    read_output();
    if (test_result())
            cout << "OK cost: " << this->cost << " ";
}
void TesterHCP::set_cost(float cost){
    this->cost = cost;
}

void TesterHCP::set_path(vector<string>& path){
    this->path = path;
}

void TesterHCP::set_vertices(vertex_set_t& vertices){
    this->vertices = vertices;
}

vertex_set_t TesterHCP::get_vertices() const {
    return vertices;
}

ostream& operator<<(ostream& os, const TesterHCP& obj){
    os << "{ ";
    for (auto& vertex: obj.get_vertices()){
        os << vertex.first << " ";
    }
    os << "}";
    return os;
}

ostream& operator<<(ostream& os, const vector<string>& p){
    for (int i = 0; i < p.size(); i++){
        os << p[i] << " ";
    }
    return os;
}

bool operator==(const TesterHCP& obj1, const TesterHCP& obj2){
    vertex_set_t obj2_vt = obj2.get_vertices();
    for (auto& elem: obj1.get_vertices()){
        if (obj2_vt.find(elem.first) == obj2_vt.end())
            return false;
    }
    return true;
}
