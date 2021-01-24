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
    
    Node():id(-1){}
    Node(int id_)
        :id(id_){}
    Node(int id_, int deg)
        :id(id_), degree(deg){}
    ~Node(){} 
};

struct Edge
{
    int src;
    int dst;
    Edge(){};
    Edge(Edge const& e)
        :src(e.src), dst(e.dst){}
    Edge(int _src, int _dst)
        :src(_src), dst(_dst){}
};
typedef unordered_map<int, unordered_map<int, Edge> > edge_list_t;


struct Graph
{
    /* data */
    public:
        unordered_map<int, Node*> nodes; 
        edge_list_t edges; 
        map<int, unordered_map<int, bool> > track;
        int n_edges=0;
        int lowest_degree=0;

    Graph(){
    }

    Graph copy(){
        Graph G = Graph();
        for (auto &&elt : nodes)
            G.nodes[elt.first] = new Node(elt.second->id, elt.second->degree);
        
        for (auto &&id : edges)
            for (auto &&ed : id.second)
                G.edges[id.first][ed.first] = Edge(ed.second);

        for (auto &&id : track)
            for (auto &&ed : id.second)
                G.track[id.first][ed.first] = ed.second;

        G.n_edges = n_edges;
        G.lowest_degree = lowest_degree;
        return G;
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
        return n_edges/float(nodes.size());
    }

    void add_edge(int src, int dst){
        if(src==dst){
            return;
        }
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
        if(edges[src].find(dst)!=edges[src].end())
            return;

        // add connection in two directions
        edges[src][dst]=Edge(src, dst);
        edges[dst][src]=Edge(dst, src);

        // update nodelist
        change_degree(src, nodes[src]->degree+1);
        change_degree(dst, nodes[dst]->degree+1);

        // change edge count
        n_edges++;

        // cout<<"nb of edge: "<<n_edges << " nb of nodes: "<<nodes.size()<<endl;
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

    vector<Edge> remove_node(int id){
        vector<Edge> removed_edge;
        Node* node = nodes[id];

        // remove the node from its neighboors neighborhood
        for(auto&& elt: edges[id]){
            int neighb_id = elt.first;
            edges[neighb_id].erase(id); // remove the node in it's neigborhood

            int n_deg = nodes[neighb_id]->degree;
            change_degree(neighb_id, nodes[neighb_id]->degree - 1) ;
            n_edges--;

            removed_edge.push_back(Edge(id, neighb_id));
            // cout << "neigh: "<< neighb_id << " from: " << n_deg << " to: " << nodes[neighb_id]->degree<<endl;
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
        return removed_edge;
    }
};


