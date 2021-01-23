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
    int degree=0;
    unordered_map<int, bool > neighboors;

    
    Node():id(-1){}

    Node(int id_)
        :id(id_){};

    void add_edge(int dst_id, Node* dst_node){
        neighboors[dst_id] = true;
    }

    bool has_edge(int dst_id){
        return neighboors.find(dst_id)!=neighboors.end();
    }
    ~Node(){} 
};

struct Edge
{
    int src;
    int dst;
};


struct Graph
{
    /* data */
    public:
        unordered_map<int, Node*> nodes; 
        unordered_map<int, unordered_map<int, bool> > edges; 
        map<int, unordered_map<int, bool> > track;
        int n_edges=0;
        int lowest_degree=0;

    Graph(){
    }

    Graph copy(){
        Graph g = Graph();
    }

    int nb_nodes(){
        return nodes.size();
    }

    int nb_edges(){
        return n_edges;
    }

    void print_nodes(){
        for (auto &&node : nodes)
            cout << node.second->id << " degree: "<< node.second->degree << endl;
    }

    void print_degree(){
        cout << "size: " << track.size() <<endl;
        for (auto &&deg : track)
        {
            cout<< "degree : " << deg.first << endl;
            for (auto &&node : deg.second)
            {
                cout<< "-> node: " << node.first << endl;
            }
        }
        
    }

    void print_lowest_degree(){
        cout<< "lowest degree : " << lowest_degree << endl;
        if( track.find(lowest_degree) != track.end() ){
            for (auto &&node : track[lowest_degree])
            {
                cout<< "-> node: " << node.first << endl;
            }
        }
    }

    int lowest_node(){
        if( track.find(lowest_degree) != track.end() )
            for (auto &&node : track[lowest_degree])
                return node.first;
    }

    float average_degree_density(){
        return n_edges/nodes.size();
    }

    void add_edge(int src, int dst){
        // cout<<"src: "<<src<<" dst: "<<dst<<endl;
        if(nodes.size()==0){
            lowest_degree = 1;
        }
        // create new node if they doesn't exist yet
        if(nodes.find(src)==nodes.end()){
            nodes[src] = new Node(src);
            track[1][src] = true;
        }

        if(nodes.find(dst)==nodes.end()){
            nodes[dst] = new Node(dst);
            track[1][dst] = true;
        }

        // if edge already exist
        if(nodes[src]->has_edge(dst))
            return;

        // update nodelist
        Node* src_node = nodes[src];
        Node* dst_node = nodes[dst];

        change_degree(src, src_node->degree+1);
        change_degree(dst, dst_node->degree+1);

        // add connection in two directions
        src_node->add_edge(dst, dst_node);
        dst_node->add_edge(src, src_node);

        // change degree node
        n_edges++;

    }

    void change_degree(int id, int deg){
        Node* node = nodes[id];
        int old_deg = node->degree;
        // move the neigboor to new degree 
        if (deg==old_deg)
            return;        

        track[old_deg].erase(id);
        node->degree = deg;
        track[deg][id] = true;
        // cout << "node: "<< id << " from: " << old_deg << " to: " << deg<<endl;

        if(lowest_degree>deg)
            lowest_degree = deg;

        if(track[old_deg].size()==0)
            track.erase(old_deg);

    }

    void remove_node(int id, ){
        Node* node = nodes[id];

        // remove the node from its neighboors neighborhood
        for(auto& elt: node->neighboors){
            // remove the node in it's neigborhood
            int n_id = elt.first;
            Node* n_node = nodes[n_id];
            n_node->neighboors.erase(id);

            // move the neigboor to new degree
            int n_deg = n_node->degree;
            change_degree(n_id, n_deg-1) ;
            n_edges--;
            // cout << "neigh: "<< n_id << " from: " << n_deg << " to: " << n_node->degree<<endl;
        }

        // remove from degree tracker
        if(track[node->degree].size()==1){
            track.erase(node->degree);
            if(node->degree == lowest_degree)
                lowest_degree = track.begin()->first;
        }
        else
        {
            track[node->degree].erase(id);
        }
        
        // remove from nodes
        nodes.erase(id);
    }
};


