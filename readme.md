<img src="https://miro.medium.com/max/2978/1*rmq7bd3GFjcwfXtkrBQaPQ.png" align="right" width="150"/>

# Finding densest subgraphs in linear time
Author: Kanvaly Fadiga

This repo implement a 2-approximation algorithm for the densest subgraph problem

# Installation

- I c++ for the algoithm so we just need g++ to compile the code.
- We use python to plot our data. install the necessary package by using this command:
    ```sh
    pip install -r requirements.txt
    ```


# Usage

create a new folder `../input/` and paste the data by renaming them as follow:

```
../input
└── email-Eu-core.txt
└── com-DBLP.txt 
└── com-Youtube.txt
└── email-EuAll.txt
└── cit-HepPh.txt
```

then create a output folder `../output/` that contains a subfolder `densest_subgraph/`: 

```
../output
└── densest_subgraph/
```

> - use `python3 convert.py` to convert all dataset into a write format for the c++ code and put them in `../output/`.
> - in `main.cpp` use `idx` to choose a dataset and `runs` to choose the number of runs to do. `write_edge` to choose if whether or we cant to output the densest graph edges.
```c++
// parameter
bool write_edge = true;
int runs = 1;
int idx = 0;

vector<string> dataset = {"email-Eu-core", "cit-HepPh", 
                          "email-EuAll", "com-DBLP", 
                          "com-Youtube"};

string root = "../output/";
string filename = dataset[idx];
Graph G = read_graph(root + filename +".txt");
```
> - then compile the c++ code and runs. this will generate data a `$dataset_name.csv` file which give the densest graph density, number of nodes and edges. 
```
g++ -std=c++11 main.cpp -w
./a.out
```



This repo contains the notebook I use to plot the running time as a function of the input size.
