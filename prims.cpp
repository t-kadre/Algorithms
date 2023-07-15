#include <bits/stdc++.h>
using namespace std;
//prim's algo for finding MST of unconnected, weighted, connected graph
//both kruskals and prim's are greedy algorithms for finding MST of a given graph
//greedy algo=algo in which if we have multiple options, we pick the option which is currently best for us (in this case picking the edge with min weights)
//pick one vertex as source for example 0
int main(){
    int n,e;
    cin>>n>>e;
    int** edges=new int*[n];//weighted adjacency matrix
    for(int i=0;i<n;i++){
        edges[i]=new int[n];
        for(int j=0;j<n;j++){
            edges[i][j]=0; 
        }
    }
    for(int i=0;i<e;i++){
        int f,s,weight;
        cin>>f>>s>>weight;
        edges[f][s]=weight;
        edges[s][f]=weight;
    }
    cout<<endl;
    int*parent=new int[n];//parent array to store parent of every vertex
    int*weight=new int[n];//weight array to store weights of edges of every vertex 
    bool*visited=new bool[n];
    for(int i=0;i<n;i++){
        visited[i]=false;
        weight[i]=INT_MAX;
    }
    parent[0]=-1;//as 0 is source vertex it doesnt have a parent and weight as reaching 0 from 0 requires 0 weight
    weight[0]=0;
    for(int i=0;i<n;i++){//O(n^2)
        int minWeightVertex=-1;//finding vertex which is unvisited and has minimum weight
        for(int i=0;i<n;i++){
            if(visited[i]==false && (weight[i]<weight[minWeightVertex] || minWeightVertex==-1)){
                minWeightVertex=i;
            }
        }
        //exploring unvisited adjacent vertices of minWeightVertex
        visited[minWeightVertex]=true;
        for(int j=0;j<n;j++){
            if(edges[minWeightVertex][j]!=0 && visited[j]==false){
                if(edges[minWeightVertex][j]<weight[j]){
                    weight[j]=edges[minWeightVertex][j];
                    parent[j]=minWeightVertex;
                }
            }
        }
    }
    //O(n^2) time so to improve we can use adjacency list instead of matrix so that we directly go to the neighbours of a vertex to check if their weights can be changed instead of checking it for all vertices and PQ to find minWeightVertex -> O(nlogn)
    for(int i=1;i<n;i++){
        if(i<parent[i]){
            cout<<i<<" "<<parent[i]<<" "<<weight[i]<<endl;
        }else{
            cout<<parent[i]<<" "<<i<<" "<<weight[i]<<endl;
        }
    }
    return 0;
}