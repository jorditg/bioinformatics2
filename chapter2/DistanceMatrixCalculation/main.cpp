/* 
 * File:   main.cpp
 * Author: jordi
 *
 * Created on April 3, 2015, 8:26 AM
 */

#include <cstdlib>

#include "graph.hpp"

/*
 * 
 */
int main(int argc, char** argv) {
    adjacency_list g(62);
    
    g.read("input.txt");
    
    g.print();
    g.get_distance_matrix();
    g.print_distance_matrix();
    return 0;
}

