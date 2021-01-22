#pragma once
#include <iostream>
#include <vector>
#include <unordered_map> 
#include <map> 

using namespace std;

struct Node
{
    /* data */
    int id;
    unordered_map<int, Node* > neighboors;

    int degree=0;
    
    Node():id(-1){}

    Node(int id_)
        :id(id_){};

    void add_edge(int dst_id, Node* dst_node){
        neighboors[dst_id] = dst_node;
    }

    bool has_edge(int dst_id){
        return neighboors.find(dst_id)!=neighboors.end();
    }
    ~Node(){} 
};

struct Graph
{
    /* data */
    public:
        unordered_map<int, Node*> nodes; 
        int n_edges=0;
        int lowest_degree=0;

    Graph(){
    }

    int nb_nodes(){
        return nodes.size();
    }

    int nb_edges(){
        return n_edges;
    }

    void print_nodes(){
        for (auto &&node : nodes)
            cout << node.second->id << endl;
    }

    void add_edge(int src, int dst){
        // create new node if they doesn't exist yet
        if(nodes.find(src)==nodes.end()){
            nodes[src] = new Node(src);
        }

        if(nodes.find(dst)==nodes.end()){
            nodes[dst] = new Node(dst);
        }

        // if edge already exist
        if(nodes[src]->has_edge(dst))
            return;

        // update nodelist
        Node* src_node = nodes[src];
        Node* dst_node = nodes[dst];

        // add connection in two directions
        src_node->add_edge(dst, dst_node);
        dst_node->add_edge(src, src_node);

        // // change degree node
        n_edges++;
    }


};


