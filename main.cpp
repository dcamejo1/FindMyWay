#include<iostream>
#include<vector>
#include<map>
#include<iterator>
#include<queue>
#include<algorithm>
#include<random>
using namespace std;

struct Edge{
    pair<int,string> src; //Source vertex (From)
    pair<int,string> dest; //Destination vertex (To)
    int weight; //Weight of Edge (Price)
    Edge(pair<int,string> src_, pair<int,string> dest_, int weight_){ //Edge Constructor
        src = src_;
        dest = dest_;
        weight = weight_;
    }
};

class Graph {
    public:
        //Data Structures
        map<string,vector<pair<string,int>>> mapList; //Adjacency List Map 
        map<string,vector<pair<string,int>>>::iterator it; //Adjacency List Map Iterator
        map<string,int> keysLocation; //Map of location <"location", reference#>
        map<int,string> keysRefNum; //Map of location <reference#, "location">
    
        //Functions
        void insertEdge(string from, string to, int weight); 
        void print();
};

//Inserts Edges to Graph
void Graph::insertEdge(string from, string to, int weight) {
    mapList[from].push_back(make_pair(to,weight));
    if (mapList.find(to)==mapList.end()) {
        mapList[to] = {};
    }
}

//Traverses Graph and Prints Edges of Each Vertice
void Graph::print(){
    cout<< "Destinations & Prices-" << endl;
    for(it = mapList.begin(); it != mapList.end(); ++it) {
        cout << it->first << " ->";
        for(int j = 0; j < it->second.size(); j++)
            cout << " " << it->second[j].first << " $" << it->second[j].second << " |";
        cout<<"\n";
    }
}

//Dijkstra's Helper Function Used to Convert Adjacency List Map to Adjacency List Tuple
vector<vector<tuple<pair<int,string>,pair<int,string>,int>>> tupleListGen(Graph& graphObj){
    //Data Structures
    map<string,vector<pair<string,int>>>::iterator it; //Adjacency List Map Iterator
    vector<vector<tuple<pair<int,string>,pair<int,string>,int>>> tupleList; //Adjacency List Tuple
    vector<Edge> edges; //Vector of Edges

    //Assign Location to Reference Number & Store in Map -> "keys"
    int refNumber = 0;
    for(it = graphObj.mapList.begin(); it != graphObj.mapList.end(); ++it) {
        graphObj.keysLocation[it->first] = refNumber; 
        graphObj.keysRefNum[refNumber] = it->first;
        refNumber++;
    }

    //Inserting Edges to Edges Vector From Adjacency List Map
    for(it = graphObj.mapList.begin(); it != graphObj.mapList.end(); ++it) {
        for(int j = 0; j < it->second.size(); j++) {
            edges.push_back(Edge(make_pair(graphObj.keysLocation[it->first],it->first),make_pair(graphObj.keysLocation[it->second[j].first],it->second[j].first),it->second[j].second));
        }
    }

    //Dysecting Edges & Inserting in Adjacency List Tuple 
    tupleList.resize(graphObj.mapList.size());
    for(auto &edge : edges){
        tupleList[edge.src.first].push_back(make_tuple(edge.src,edge.dest,edge.weight));
    }

    return tupleList;
}

//Dijkstra's Algorithm Used to Calculate Shortest Path (Minimum Price) From Traveling From One Location to Another
void dijkstra(Graph& graphObj, string source) {
    int src = graphObj.keysLocation[source];
    vector<vector<tuple<pair<int,string>,pair<int,string>,int>>> adjList = tupleListGen(graphObj);
    int max = 2147483647;
    vector<int> distance(graphObj.mapList.size(), max);
    typedef pair<int, int> pairs;
    priority_queue<pairs, vector<pairs>, greater<pairs>> que;  
    que.push(make_pair(distance[src] = 0,src)); 
    while (!que.empty()) { 
        int sec = que.top().second; 
        que.pop(); 
        for (auto i : adjList[sec]) {  
            if (distance[get<1>(i).first] != distance[sec] + get<2>(i)) { 
                if(distance[get<1>(i).first] > distance[sec] + get<2>(i)) { 
                    distance[get<1>(i).first] = distance[sec] + get<2>(i); 
                    que.push(make_pair(distance[get<1>(i).first], get<1>(i).first));  
                }
                else{
                    continue;
                }
            }
        }
    }
    cout<< "COSTS FROM " << '"' << source << '"' << " TO THE FOLLOWING DESTINATIONS-" << endl;
    for(int i = 0; i < distance.size(); i++){
        cout << source << " to " << graphObj.keysRefNum[i] << ": $" << distance[i] << endl;
    }
    int minIndex = 1;
    int minValue = distance[1];
    for(int i = 1; i < distance.size();i++){
        if(minValue > distance[i]){
            minValue = distance[i];
            minIndex = i;
        }
    }
    cout << " " << endl;
    cout << "MINIMUM COST: $" << minValue << endl;
    cout << "FROM: " << source << " TO " << graphObj.keysRefNum[minIndex] << endl;
}

//Randomly Insert Edges to Graph
void randomInsertions(Graph& graphObj,int insertions){
    //Random Price and Location Generator
    random_device rand;
    mt19937 rng(rand());
    uniform_int_distribution<int> uniPrice(0,500); //Random Price Between 0 and 500
    uniform_int_distribution<int> uniLocation(0,15); //Random Index Between 0 and 9 for Location Array
    string locations[16] = {"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P"}; //Locations
    for(int i = 0; i < insertions; i++){
        int randomPrice = uniPrice(rng); 
        int randomLocation1 = uniLocation(rng);
        int randomLocation2 = uniLocation(rng);
        graphObj.insertEdge(locations[randomLocation1],locations[randomLocation2],randomPrice); //Insert Edges to Graph
    }
    graphObj.print(); //Print Graph
    //dijkstra(graphObj,locations[uniLocation(rng)]);//Dijkstra's From Random Location
}

//User Interface (Menu Options)
void menu(Graph& graphObj){
    //Menu    
    while(true){
        cout << " " << endl;
        cout << "------------" << endl;
        cout << "FIND MY WAY" << endl;
        cout << "------------" << endl;
        cout << " " << endl;
        int feature;
        cout << "1. Load Destinations & Prices" << endl;
        cout << "2. Display Minimum Costs From Starting Destination" << endl;
        cout << "3. Display Possible Round Trips" << endl;
        cout << "4. Display All Destinations and Prices" << endl;
        cout << "5. Exit" << endl;
        cout << "Option#: ";
        cin >> feature;
        cout << " " << endl;

        //Features
        if(feature == 1){ //Load Destinations & Prices Manually
            int option;
            cout << "1. Load Manually" <<endl;
            cout << "2. Generate Random Insertions" << endl;
            cout << "Option#: ";
            cin >> option;
            if(option == 1) { //Load Locations & Prices Manually
                int numDestinations = 0;
                cout << "Enter Number of Destinations: ";
                cin >> numDestinations;
                cout << " " << endl;
                string to, from;
                int price;
                for(int i = 0; i < numDestinations; i++){
                    cout << "Enter Destinations-" << endl;
                    cout << "From To Price (A B 5): ";
                    cin >> from >> to >> price;
                    graphObj.insertEdge(from,to,price);
                }
                cout << " " << endl;
            }
            else if(option == 2){ //Randomly Generate Locations & Prices
                int numInsertions;
                cout << "Enter Number of Random Insertions: ";
                cin>>numInsertions;
                cout << " " << endl;
                randomInsertions(graphObj, numInsertions);
                cout << " " << endl;
            }
        }
        else if(feature == 2){ //Dijkstra's Minimum Price
            string from;
            cout << "Find Minimum Cost From: ";
            cin >> from;
            cout << " " << endl;
            dijkstra(graphObj,from);
        }
        else if(feature == 3){ //Cycle Detection Round Trips
            //Function that Displays Round Trips!
        }
        else if(feature == 4){ //Display Destinations & Prices
            graphObj.print();
        }
        else if(feature == 5){ //Exit
            break;
        }
    }
}

int main(){
    Graph graphObj;
    // graphObj.insertEdge("A","B",4);
    // graphObj.insertEdge("B","C",1);
    // graphObj.insertEdge("C","D",8);
    // graphObj.insertEdge("D","E",9);
    // graphObj.insertEdge("D","F",5);
    // graphObj.insertEdge("F","E",12);
    // graphObj.insertEdge("G","F",7);
    // graphObj.insertEdge("A","G",10);
    // graphObj.insertEdge("B","G",2);
    // graphObj.insertEdge("G","C",6);
    
    // graphObj.print();
    // dijkstra(graphObj,"A");

    menu(graphObj);

    return 0;
}