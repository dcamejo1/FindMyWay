#include<iostream>
#include<vector>
#include<map>
#include<iterator>
#include<queue>
using namespace std;


class Graph {
    private:
        map<string,vector<pair<string,int>>> graph;
        map<string,vector<pair<string,int>>>::iterator it;
    public:
        void insertEdge(string from, string to, int weight); 
        map<string,vector<pair<string,int>>> returnMap();
        int numVertices();
        void print();
};

void Graph::insertEdge(string from, string to, int weight) {
    graph[from].push_back(make_pair(to,weight));
    if (graph.find(to)==graph.end()) {
        graph[to] = {};
    }
}

map<string,vector<pair<string,int>>> Graph::returnMap(){
    return graph;
}

int Graph::numVertices(){
    return graph.size();
}

void Graph::print(){
    for(it = graph.begin(); it != graph.end(); ++it) {
        cout << it->first << " ->";
        for(int j = 0; j < it->second.size(); j++)
            cout << " " << it->second[j].first << " " << it->second[j].second << " |";
        cout<<"\n";
    }
}

// void dijkstra(Graph& graphObj, string source) {//??????????
//     int max = 2147483647;
//     vector<int> distance(graphObj.numVertices(), max);
//     //Priority Queue of pairs
//     typedef pair<int, int> pairs;
//     priority_queue<pairs, vector<pairs>, greater<pairs>> que;  
//     que.push(make_pair(distance[source] = 0,source)); 
//     while (!que.empty()) { 
//         string sec = que.top().second; 
//         que.pop(); 
//         for (auto i : graph[sec]) {  
//             if (distance[i.first] != distance[sec] + i.second) { 
//                 if(distance[i.first] > distance[sec] + i.second) { 
//                     distance[i.first] = distance[sec] + i.second; 
//                     que.push(make_pair(distance[i.first],i.first));  
//                 }
//                 else{
//                     continue;
//                 }
//             }
//         }
//     }
//     // for(auto i : distance){
//     //     cout << i.first << " " << i.second << endl;
//     // }
// }

int main(){
    Graph graphObj;
    graphObj.insertEdge("A","B",4);
    graphObj.insertEdge("B","C",1);
    graphObj.insertEdge("C","D",8);
    graphObj.insertEdge("D","E",9);
    graphObj.insertEdge("D","F",5);
    graphObj.insertEdge("F","E",12);
    graphObj.insertEdge("G","F",7);
    graphObj.insertEdge("A","G",10);
    graphObj.insertEdge("B","G",2);
    graphObj.insertEdge("G","C",6);
    
    graphObj.print();
    //dijkstra(graphObj,"A");

    return 0;
}