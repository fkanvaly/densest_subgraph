#include <iostream>
#include <fstream>
#include "graph.cpp"
#include "linkedlist.cpp"

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

int main()
{
    // graph_t G = read_graph("../data/facebook_combined.txt");
    // vector<int> nodes = G.get_nodes();
    // cout<<"nb of edge: "<<G.nb_edges()<<endl;
    // cout<<"nb of nodes: "<<G.nb_nodes()<<endl;

    Graph G = Graph();

    G.add_edge(1,2);
    G.add_edge(2,3);
    G.add_edge(1,4);
    G.add_edge(4,2);

    G.remove_node(3);
    G.remove_node(4);

    for (auto &&elt : G.degrees)
    {
        cout<<"degree: "<<elt.first<<" size: "<< elt.second.size<<endl;

    }
    

    Linkedlist<node_t>& L= G.degrees[1];
    LNode<node_t>* elt = L.get_head();
    cout<<elt->node->id<<endl;
    cout<<elt->next->node->id<<endl;
    cout<<elt->next->next->node->id<<endl;
    // do
    // {
    //     cout<<elt->node->id<<endl;
    //     elt = elt->next;
    // } while(elt!=nullptr);
    


}