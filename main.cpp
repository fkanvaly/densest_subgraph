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

edge_list_t densest_graph(Graph G){

    // init H
    edge_list_t H = G.edges;
    float H_density = G.average_degree_density();

    vector<Edge> edge_to_delete_in_H;
    // while (G contains at least one edge)
    int i_max = G.nodes.size();
    int i=0;
    while (G.n_edges>0 && i<i_max+1)
    {
        // G.print_lowest_degree();
        int node_id = G.lowest_node();
        // cout << "node_to_remove: "<<node_id<< endl;
        vector<Edge> to_remove = G.remove_node(node_id);

        edge_to_delete_in_H.insert( edge_to_delete_in_H.end(), to_remove.begin(), to_remove.end() );
        // node_to_delete_in_H.push_back(node_id);
        if(G.average_degree_density() > H_density){
            for (auto &&e : edge_to_delete_in_H){
                H[e.src].erase(e.dst);
                H[e.dst].erase(e.src);
            }
            edge_to_delete_in_H.clear();            
        }
        i++;
    }

    return H;
}


int main()
{
    Graph G = read_graph("../data/facebook_combined.txt");
    // Graph G = read_graph("com-dblp.ungraph.txt");
    
    cout<<"nb of edge: "<<G.n_edges<<endl;
    cout<<"nb of nodes: "<<G.nodes.size()<<endl;

    time_t start, end;
    time(&start);
    ios_base::sync_with_stdio(false);

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

    edge_list_t H = densest_graph(G);

    time(&end); 
    // Calculating total time taken by the program. 
    double time_taken = double(end - start); 
    cout << "Time taken by program is : " << fixed 
         << time_taken << setprecision(5); 
    cout << " sec " << endl; 

    vector<Edge> edge_list;
    for (auto &&src : H)
    {
        for (auto &&elt : src.second)
        {
            edge_list.push_back(elt.second);
            if (H[elt.first].find(src.first) != H[elt.first].end()){
                H[elt.first].erase(src.first);
            }
        }
        
    }

    

    ofstream myfile;
    myfile.open ("densest.txt");
    for (auto &&edge : edge_list){
        cout << edge.src << " " << edge.dst <<endl;
        myfile << edge.src << " " << edge.dst <<"\n";
    }
    myfile.close();

}