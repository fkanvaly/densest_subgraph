#include <iostream>
#include <fstream>
#include "graph.cpp"
#include <unordered_map> 
#include <fstream>
#include <vector> 

using namespace std;

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

unordered_map<int, bool> densest_graph(Graph G){

    // init H
    unordered_map<int, bool> H;
    float H_density = G.average_degree_density();
    for (auto &&node : G.nodes)
        H[node.first] = true;

    vector<int> node_to_delete_in_H;
    // while (G contains at least one edge)
    int i_max = G.nodes.size();
    int i=0;
    while (G.n_edges>0 && i<i_max+1)
    {
        G.print_lowest_degree();
        int node_id = G.lowest_node();
        cout << "node_to_remove: "<<node_id<< endl;
        G.remove_node(node_id);

        node_to_delete_in_H.push_back(node_id);
        if(G.average_degree_density() > H_density){
            for (auto &&id : node_to_delete_in_H)
                H.erase(id);
            node_to_delete_in_H.clear();            
        }
        i++;
    }

    return H;
}


int main()
{
    Graph G = read_graph("../data/facebook_combined.txt");
    // Graph G = read_graph("../data/com-dblp.ungraph.txt");
    
    cout<<"nb of edge: "<<G.n_edges<<endl;
    cout<<"nb of nodes: "<<G.nodes.size()<<endl;

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

    unordered_map<int, bool> H = densest_graph(G);

    ofstream myfile;
    myfile.open ("densest.txt");
    for (auto &&node : H){
        cout<<node.first<<endl;
        myfile << node.first << "\n";
    }
    myfile.close();

}