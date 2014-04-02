#include "../tester/hdr/tester_hcp.hpp"
#define BOOST_TEST_MODULE tester_hcp
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_vertices){
    vertex_set_t expected_vertices = {{"1", {0, 0}}, {"2", {0, 0}}, {"3", {0, 0}}};
    TesterHCP expected_result(expected_vertices);
    TesterHCP result("../testcases/1.g");
    BOOST_CHECK_EQUAL(result, expected_result);
}

BOOST_AUTO_TEST_CASE(test_hcp){
    TesterHCP result("../testcases/1.g");
    vector<string> path = {"1", "2", "3", "1"};
    result.set_path(path);
    BOOST_CHECK_EQUAL(result.test_result(), true);
    
    path = {"2", "3", "1", "2"};
    result.set_path(path);
    BOOST_CHECK_EQUAL(result.test_result(), true);
    
    path = {"1", "2"};
    result.set_path(path);
    BOOST_CHECK_EQUAL(result.test_result(), false);
    
    path = {"1", "2", "1"};
    result.set_path(path);
    BOOST_CHECK_EQUAL(result.test_result(), false);
    
    path = {"1", "2", "1", "3", "1"};
    result.set_path(path);
    BOOST_CHECK_EQUAL(result.test_result(), false);
    
    path = {"1", "2", "4"};
    result.set_path(path);
    BOOST_CHECK_EQUAL(result.test_result(), false);
    
    path = {"1", "2", "3", "2"};
    result.set_path(path);
    BOOST_CHECK_EQUAL(result.test_result(), false);
 
    path = {};
    result.set_path(path);
    BOOST_CHECK_EQUAL(result.test_result(), false);

    
    result.set_vertices("../testcases/1a.g");
    path = {"10", "9", "8", "10", "3", "2", "8", "7", "6", "5", "10"};
    result.set_path(path);
    BOOST_CHECK_EQUAL(result.test_result(), false);
}

BOOST_AUTO_TEST_CASE(test_cost){
    TesterHCP result("../testcases/1.g");
    vector<string> path = {"1", "2", "3", "1"};
    result.set_path(path);
    result.set_cost(17.2486);
    BOOST_CHECK_EQUAL(result.test_cost(), true);

    path = {"1", "2", "3", "1"};
    result.set_path(path);
    result.set_cost(16);
    BOOST_CHECK_EQUAL(result.test_cost(), false);
}
