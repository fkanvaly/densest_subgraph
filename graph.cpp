#pragma once
#include <iostream>
#include <vector>
#include <unordered_map> 
#include <map> 
#include "degree_tracker.cpp" 


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
typedef unordered_map<int, unordered_map<int, bool> > degree_set_t;

struct Graph
{
    /* data */
    public:
        unordered_map<int, Node*> nodes; 
        edge_list_t edges; 
        int n_edges=0;

        // degree tracking datastructure
        degree_set_t degree_set;
        unordered_map<int, node_t*> degree_order;
        node_t* start = NULL;

    Graph(){
    }

    Graph copy(){
        Graph G = Graph();
        for (auto &&elt : nodes)
            G.nodes[elt.first] = new Node(elt.second->id, elt.second->degree);
        
        for (auto &&id : edges)
            for (auto &&ed : id.second)
                G.edges[id.first][ed.first] = Edge(ed.second);

        for (auto &&id : degree_set)
            for (auto &&ed : id.second)
                G.degree_set[id.first][ed.first] = ed.second;

        G.n_edges = n_edges;
        G.start = copy_linkedlist(&start, G.degree_order);
        return G;
    }

    node_t* copy_linkedlist(node_t** head, unordered_map<int, node_t*>& new_degree_order){
        if(*head==NULL){
            return NULL;
        }
        
        node_t* new_start = NULL;
        node_t* iter = *head;
        while (iter->next != *head)
        {
            new_degree_order[iter->data] = insertEnd(&new_start, iter->data);
            iter = iter->next;
        }
        new_degree_order[iter->data] = insertEnd(&new_start, iter->data);
        return new_start;
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
        display(start);
    }

    void print_lowest_degree(){
        display(start);
        cout<< "lowest degree : " << start->data << endl;
        for (auto &&node : degree_set[start->data])
        {
            cout<< "-> node: " << node.first << endl;
        }
    }

    void print_track(){
        // printf("degree_set:\n");
        for (auto &&node : degree_set)
        {
            cout<< node.first << " - ";
        }
        cout<<endl;
    }

    int lowest_node(){
        int lowest_degree = start->data;
        return degree_set[lowest_degree].begin()->first;
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
            node_t* deg0 = insertEnd(&start, 0);
            degree_order[0] = deg0;
        }
        // create new node if they doesn't exist yet
        if(nodes.find(src)==nodes.end()){
            nodes[src] = new Node(src);
            degree_set[0][src] = true;

            if(degree_order.find(0)==degree_order.end()){
                degree_order[0] = insertBegin(&start, 0);
            }
        }

        if(nodes.find(dst)==nodes.end()){
            nodes[dst] = new Node(dst);
            degree_set[0][dst] = true;

            if(degree_order.find(0)==degree_order.end()){
                degree_order[0] = insertBegin(&start, 0);
            }
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

    void change_degree(int id, int new_deg){
        // printf("------change degree of : %i--------\n", id);
        Node* node = nodes[id];
        int old_deg = node->degree;
        // move the neigboor to new degree 
        assert (new_deg!=old_deg);        

        // cout << "node: "<< id << " from: " << old_deg << " to: " << new_deg<<endl;

        node->degree = new_deg;
        degree_set[old_deg].erase(id);
        
        //update
        bool is_increase = new_deg>old_deg;
        if(degree_set.find(new_deg)==degree_set.end()){
            // printf("degree %i not found\n", new_deg);
            degree_set[new_deg][id] = true;

            // add on order degree_seter
            node_t* old_node = degree_order[old_deg];
            if(is_increase){
                if(old_node->next->data!=new_deg){
                    if(degree_order.size()==1 || old_node==start->prev ) // one elt or node is the last
                        degree_order[new_deg] = insertEnd(&start, new_deg);
                    else
                        degree_order[new_deg] = insertAfter(&start, new_deg, old_node);
                }
            }else{// decrease
                if(old_node->prev->data!=new_deg){
                    if(degree_order.size()==1 || old_node==start) // one elt or node is the start
                        degree_order[new_deg] = insertBegin(&start, new_deg);
                    else
                        degree_order[new_deg] = insertAfter(&start, new_deg, old_node->prev);
                }
            }
        }else{
            degree_set[new_deg][id] = true;
        }
        // display(start);
        // print_track();


        if(degree_set.find(old_deg)!=degree_set.end()){
            // printf("deg %i exist!\n", old_deg);
            if(degree_set[old_deg].size()==0){
            degree_set.erase(old_deg);
            node_t* to_delete = degree_order[old_deg];

            // printf("deg %i is empty| delation\n", old_deg);
            deletenode(&start, to_delete);
            // display(start);

            degree_order.erase(old_deg);}
        }

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

        // remove from degree degree_seter
        if(degree_set[node->degree].size()==1){
            degree_set.erase(node->degree);
            node_t* to_delete = degree_order[node->degree];
            deletenode(&start, to_delete);
            degree_order.erase(node->degree);
        }
        else
        {
            degree_set[node->degree].erase(id);
        }
        
        // remove from nodes
        nodes.erase(id);
        return removed_edge;
    }
};


