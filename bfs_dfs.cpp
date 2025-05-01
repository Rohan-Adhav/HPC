#include<iostream>
#include<vector>
#include<queue>
#include<omp.h>
using namespace std;

struct Graph{
    vector<vector<int>>adj;
    int V;
    Graph(int V){
        this->V=V;
        adj.resize(V);
    }
    void addEdge(int u,int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void BFS(int start){
        vector<bool>visited(V,false);
        queue<int>q;
        visited[start]=true;
        q.push(start);
        while(!q.empty()){
            int u = q.front();
            q.pop();
            cout<<u<<" ";
            #pragma omp parallel for
            for(int i=0;i<adj[u].size();i++){
                int v =  adj[u][i];
                if(!visited[v]){
                #pragma omp critical
                    {
                    
                        visited[v]=true;
                        q.push(v);
                    }
                }
            }
        }
        cout<<endl;
    }
    void DFS(int start){
        vector<bool>visited(V,false);
        #pragma omp parallel
        {
            #pragma omp single nowait
            {
                DFSutil(start,visited);
            }
        }
        cout<<endl;
    }
    void DFSutil(int u,vector<bool>&visited){
        visited[u]=true;
        cout<<u<<" ";
        #pragma omp parallel for
        for(int i=0;i<adj[u].size();i++){
            int v=adj[u][i];
            if(!visited[v]){
                visited[v]=true;
                DFSutil(v,visited);
            }
        }
    }
};
int main(){
    int  V;
    cout<<"Enter the number of  Edges\n";
    cin>>V;
    Graph g(V);
    int  edgecount;
    cout<<"Enter the  number of edges\n";
    cin>>edgecount;
    vector<int>adj;
    cout<<"Enter the edges  in the format of source to destination\n";
    for(int  i=0;i<edgecount;i++){
        int u,v;
        cin>>u>>v;
        g.addEdge(u,v);
    }
    cout<<"BFS of graph starting from node 0\n";
    g.BFS(0);
    cout<<"DFS of graph starting from node 0\n";
    g.DFS(0);
    
    return 0;
}
