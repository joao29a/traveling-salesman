#ifndef TESTER_HCP
#define TESTER_HCP

#include <unordered_map>
#include <unordered_set>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

//typedef pair<string, string> pair_t;

//struct KeyHash{
//    size_t hash_string(string s) const {
//        size_t hash = 5381;
//        size_t i;
//        for (i = 0; i < s.size(); i++){    
//            hash = ((hash << 5) + hash) + s[i];
//        }   
//        return hash;
//    }
//
//    size_t operator()(const pair_t& p) const {
//        size_t first = hash_string(p.first);
//        size_t second = hash_string(p.second);
//        return second + 0x9e3779b9 + (first << 6) + (first >> 2);
//    }
//};

//typedef unordered_map<pair_t, int, KeyHash> edge_set_t;

typedef unordered_map<string, pair<float, float>> vertex_set_t;

class TesterHCP{
    private:
        float cost;
        int total_vt;
        vertex_set_t vertices;
        vector<string> path;

    public:
        TesterHCP(){};
        TesterHCP(const char*);
        TesterHCP(vertex_set_t&);
        void set_vertices(const char*);
        void set_vertices(vertex_set_t&);
        void set_path(vector<string>&);
        void set_cost(float);
        vertex_set_t get_vertices() const;
        bool test_result();
        void run_test(const char*);
        void read_output();
        bool test_cost();
        float get_cost(string, string);
};

ostream& operator<<(ostream&, const TesterHCP&);
ostream& operator<<(ostream&, const vector<string>&);
bool operator==(const TesterHCP&, const TesterHCP&);

#endif
