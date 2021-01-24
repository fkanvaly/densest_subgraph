#include <iostream>
#include <fstream>
#include "graph.cpp"
#include <unordered_map> 
#include <fstream>
#include <vector> 

using namespace std;
typedef unordered_map<int, unordered_map<int, bool> > edge_list;

Graph read_graph(string filename){
    Graph G = Graph();

    // Create a text string, which is used to output the text file
    string edge;

    // Read from the text file
    ifstream edgeFile(filename);
    // Use a while loop together with the getline() function to read the file line by line
    while (getline (edgeFile, edge)) {
        // Output the text from the file
        string src = edge.substr(0, edge.find(" ")); // source node
        string dst = edge.substr(edge.find(" ")+1, edge.size()); // destination node
        G.add_edge(stoi(src), stoi(dst));
    }

    // Close the file
    edgeFile.close();
    return G;
}

struct output_t{
    edge_list_t H;
    int nodes;
    int edges;
    float density;
};

output_t densest_graph(Graph G){
    // cout << "G at the beginning  -> edges: "<< G.n_edges<< " nodes: "<<G.nodes.size() << endl;


    // init H
    output_t out;
    out.H = G.edges;
    out.edges = G.n_edges;
    out.nodes = G.nodes.size();
    out.density = G.average_degree_density();

    vector<Edge> edge_to_delete_in_H;
    // while (G contains at least one edge)
    int i_max = G.nodes.size();
    int i=0;
    while (G.n_edges>0)
    {
        // G.print_lowest_degree();
        int node_id = G.lowest_node();
        // cout<<"node to remove: "<< node_id <<endl;
        vector<Edge> to_remove = G.remove_node(node_id);

        edge_to_delete_in_H.insert( edge_to_delete_in_H.end(), to_remove.begin(), to_remove.end() );
        if(G.average_degree_density() > out.density){
            // update
            out.edges = G.n_edges;
            out.nodes = G.nodes.size();
            out.density = G.average_degree_density();

            for (auto &&e : edge_to_delete_in_H){
                out.H[e.src].erase(e.dst);
                out.H[e.dst].erase(e.src);
            }
            edge_to_delete_in_H.clear();            
        }
        i++;
    }

    // cout << "G at the end  -> edges: "<< G.n_edges<< " nodes: "<<G.nodes.size() << endl;

    return out;
}


int main()
{   
    string dataset[] = {"email-Eu-core", "cit-HepPh", "email-EuAll", "com-DBLP", "com-Youtube"};
    string root = "../output/";
    string filename = dataset[4];
    Graph G = read_graph(root + filename +".txt");

    
    cout<<"nb of edge: "<<G.n_edges<<endl;
    cout<<"nb of nodes: "<<G.nodes.size()<<endl;

    // create metadata file
    ofstream metadata;
    metadata.open (root+"densest_subgraph/"+filename+"-meta.csv");
    metadata << "times,nodes,edges,density\n";

    // mesure execution time
    time_t start, end;
    time(&start);
    ios_base::sync_with_stdio(false);
    output_t out = densest_graph(G);
    time(&end); 

    // Calculating total time taken by the program. 
    double time_taken = double(end - start); 
    cout << "Time taken by program is : " << fixed 
         << time_taken << setprecision(5); 
    cout << " sec " << endl; 

    // write meta data
    metadata << time_taken << setprecision(5) << "," << out.nodes << "," << out.edges << "," << out.density << "\n";

    // write the resulting graph
    vector<Edge> edge_list;
    for (auto &&src : out.H)
    {
        for (auto &&elt : src.second)
        {
            edge_list.push_back(elt.second);
            if (out.H[elt.first].find(src.first) != out.H[elt.first].end()){
                out.H[elt.first].erase(src.first);
            }
        }
    }

    ofstream graph;
    graph.open (root+"densest_subgraph/"+filename+"-graph.txt");
    for (auto &&edge : edge_list){
        graph << edge.src << " " << edge.dst <<"\n";
    }
    graph.close();

    metadata.close();

}


// EXAMPLE
    // Graph G = Graph();
    // G.add_edge(8, 4);
    // G.add_edge(9, 4);
    // G.add_edge(10, 4);
    // G.add_edge(4, 7);
    // G.add_edge(4, 2);
    // G.add_edge(7, 5);
    // G.add_edge(5, 1);
    // G.add_edge(1, 3);
    // G.add_edge(3, 6);

    // G.add_edge(6, 2);
    // G.add_edge(2, 5);

    // G.add_edge(2, 3);
    // G.add_edge(2, 1);
    // G.add_edge(5, 6);
    // G.add_edge(1, 6);
    // G.add_edge(5, 3);