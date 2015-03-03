/* 
 * File:   main.cpp
 * Author: jdelatorre
 *
 * Created on 3 de marzo de 2015, 10:39
 */

//#include <cstdlib>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <algorithm>

struct Node {
    inline Node(const int i, const char v) : id(i), value(v) {}
    char value;
    int id;
    std::vector<Node> child;
};

const Node * find(const char value, std::vector<Node> &v) {
    for (auto it = v.begin(); it != v.end(); ++it) {
        const Node *n = &(*it);
        if(n->value == value) return n;
    }
    return nullptr;
}

void print(Node &root) {
    struct Track {
        inline Track (Node * n) : node(n), next_child(0){}
        Node * node;
        int next_child;
    };
    std::stack<Track> pile;
    
    pile.push(&root);
    while(!pile.empty()) {
        Track &actual = pile.top();
        size_t nr_childs = actual.node->child.size();
        if(nr_childs != 0 && // no termination node
           actual.next_child < nr_childs) {
            std::cout << actual.node->id 
                      << "->" << actual.node->child[actual.next_child].id 
                      << ":" << actual.node->child[actual.next_child].value
                      << "\n";
            pile.push(&actual.node->child[actual.next_child++]);
        } else {
            pile.pop();
        }
    }        
}

/*
 * 
 */
int main(int argc, char** argv) {
    int counter = 0;
    Node root(counter, ' ');
       
    std::string line;
    std::ifstream infile ("input.txt");

    if (infile.is_open()) {
        while ( std::getline (infile, line) ) {
            line.erase(std::remove_if( line.begin(), line.end(), 
                       [](char c) { return (c =='\r' || c == ' ' || c =='\t' || c == '\n');}), line.end() );
            Node * actual_node = &root;
            for(int i = 0; i < line.length(); i++) {
                const char c = line[i];                
                const Node *n = find(c, actual_node->child);
                if (n != nullptr) {
                    actual_node = (Node *) n;
                } else {
                    Node new_node(++counter, c);
                    actual_node->child.push_back(new_node);
                    actual_node = &(actual_node->child.back());
                }
            }
        }
        infile.close();
    } else std::cout << "Unable to open file";     
  
    print(root);
    
    return 0;
}

