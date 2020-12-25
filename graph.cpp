#pragma once
#include <iostream>
#include <vector>
#include <unordered_map> 
#include "linkedlist.cpp"
using namespace std;

struct node_t
{
    /* data */
    int id;
    unordered_map<int, node_t* > neighboors;

    int degree=0;
    LNode<node_t>* degree_node;
    
    node_t():id(-1){}

    node_t(int id_)
        :id(id_){};

    void add_edge(int dst_id, node_t* dst_node){
        neighboors[dst_id] = dst_node;
    }

    bool has_edge(int dst_id){
        return neighboors.find(dst_id)!=neighboors.end();
    }
    ~node_t(){} 
};

struct Graph
{
    /* data */
    public:
                      //node_id 
        unordered_map<int, node_t*> nodes; 
        unordered_map<int, Linkedlist<node_t> > degrees;
                      //degree          //node_id        
        // unordered_map<int, unordered_map<int, bool> > degrees;
        int n_edges=0;
        int lowest_degree=0;

    Graph(){
    }

    vector<int> get_nodes(){
        vector<int> nodes_vec;
        for (auto elt: nodes) 
            nodes_vec.push_back(elt.first);

        return nodes_vec;
    }

    int nb_nodes(){
        return nodes.size();
    }

    int nb_edges(){
        return n_edges;
    }

    void add_edge(int src, int dst){
        // create new node if they doesn't exist yet
        if(nodes.find(src)==nodes.end()){
            nodes[src] = new node_t(src);
            degrees[0].push_back(nodes[src]);
        }

        if(nodes.find(dst)==nodes.end()){
            nodes[dst] = new node_t(dst);
            degrees[0].push_back(nodes[dst]);
        }

        // if edge already exist
        if(nodes[src]->has_edge(dst))
            return;

        // update nodelist
        node_t* src_node = nodes[src];
        node_t* dst_node = nodes[dst];

        // add connection in two directions
        src_node->add_edge(dst, dst_node);
        dst_node->add_edge(src, src_node);

        // // change degree node
        change_node_degree(src_node, src_node->degree+1);
        change_node_degree(dst_node, dst_node->degree+1);

        n_edges++;
    }

    void change_node_degree(node_t* node, int new_degree){

        degrees[new_degree].detach_and_push(node); 
        
        if(degrees[node->degree].size==1){
            degrees.erase(node->degree);
        }else{
            degrees[node->degree].size--;
        }

        node->degree = new_degree;
    }

    void remove_node(int id){
        node_t* node = nodes[id];

        // remove the node from its neighboors neighborhood
        for(auto& elt: node->neighboors){
            elt.second->neighboors.erase(id);
            change_node_degree(elt.second, elt.second->degree-1);
            n_edges--;
        }

        // remove from degree tracker
        degrees[node->degree].detach(node);
        if(degrees[node->degree].size==1){
            degrees.erase(node->degree);
        }else{
            degrees[node->degree].size--;
        }

        // remove from nodes
        nodes.erase(id);
    }

    // std::ostream& operator<<(std::ostream& out, const graph_t& G){
    //     return out << "my graph" << endl;
    // }

};


