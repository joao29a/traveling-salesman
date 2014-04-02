#include "hdr/tester_hcp.hpp"

int main(int argc, char** argv){
    TesterHCP test(argv[1]);
    test.run_test(argv[1]);
    return 0;
}
