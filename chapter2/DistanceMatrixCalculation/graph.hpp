/* 
 * File:   edge.hpp
 * Author: jordi
 *
 * Created on April 3, 2015, 8:29 AM
 */

#ifndef EDGE_HPP
#define	EDGE_HPP

#include <vector>
#include <list>
#include <iostream>
#include <fstream>
#include <string>

class edge {
private:
    int wt;
    int to;

public:
    edge(int w, int id){
        wt = w;
        to = id;
    }

    int getWeight() const {
        return wt;
    }
    
    int getTo() const {
        return to;
    }
};


class adjacency_list {
private:
    const int N;
    std::vector <std::list<edge> > ad_lst;
    std::vector<std::vector<int> > dist_mat;

public:
    inline adjacency_list(int N) : N(N), ad_lst(N) {};
    
    inline void add(int from, int to, int weight) {
        ad_lst[from].push_back(edge(weight, to));
    }
    
    inline void print() {
        int c = 0;
        for (auto it = ad_lst.begin(); it != ad_lst.end(); it++) {
            const std::list<edge> &li = *it;
            if(li.size() > 0) {
                std::cout << c << " -> ";
                for(auto iter = li.begin(); iter != li.end(); ++iter)
                    std::cout << "( V= " << iter->getTo() << " wt= " << iter->getWeight() << " )";
                std::cout << std::endl;
            }
            c++;
        }
    }
    
    inline void read(const std::string file) {
        // reading a text file
        std::string line;
        std::ifstream myfile (file);
        if (myfile.is_open()) {
            while ( getline (myfile, line) ) {
                const int len1 = line.find("-");
                const int from = std::stoi(line.substr(0, len1));
                const int len2 = line.find(":") - len1 - 2;
                const int to = std::stoi(line.substr(len1 + 2, len2));
                const int wt = std::stoi(line.substr(len1+ len2 + 3));
                this->add(from, to, wt);
            }
            myfile.close();
        } else std::cout << "Unable to open file"; 
    }
    
    inline void get_distance_matrix() {
        dist_mat.resize(N);
        for(int i = 0; i < N; i++) {
            dist_mat[i].resize(N, 0);
            for(auto it = ad_lst[i].begin(); it != ad_lst[i].end(); it++) {
                dist_mat[i][it->getTo()] = it->getWeight();
            }
        }
        bool updated = false;
        do {
            updated = false;
            for(int i = 0; i < N; i++) {
                for(int j = 0; j < N; j++) {
                    if(dist_mat[i][j] != 0) {
                        for(int k = 0; k < N; k++) {
                            if(k != i && k != j && dist_mat[j][k] != 0) {
                                const int n = dist_mat[i][k]==0?
                                              dist_mat[j][k] + dist_mat[i][j] :
                                              std::min(dist_mat[i][k], dist_mat[j][k] + dist_mat[i][j]);
                                if(dist_mat[i][k] != n) {
                                    dist_mat[i][k] = n;                                
                                    updated = true;
                                }
                            }
                        }
                    }
                }
            }
        } while(updated);
    }
    
    inline void print_distance_matrix() {
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                if(ad_lst[i].size() == 1 && ad_lst[j].size() == 1)
                  std::cout << dist_mat[i][j] << " ";
            }
            if(ad_lst[i].size() == 1)
                std::cout << std::endl;
        }
    }
};

#endif	/* EDGE_HPP */

