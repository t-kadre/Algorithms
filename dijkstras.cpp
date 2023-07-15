#include <bits/stdc++.h>
using namespace std;
//given a graph, directed or undirected, can have cycles, NO NEGATIVE WEIGHTS, this algo is used to find the shortest distance between any two nodes
//another version of this algo is used to find the shortest distance of every other vertex from a given vertex, which we will implement
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
    int*distance=new int[n];
    bool*visited=new bool[n];
    for(int i=0;i<n;i++){
        distance[i]=INT_MAX;
        visited[i]=false;
    }
    distance[0]=0;
    for(int i=0;i<n;i++){//O(n^2) time, optimization->adjacency list & PQ -> O((V+E)logV), same as prims
        int minDistanceVertex=-1;//finding unvisited vertex with min distance
        for(int i=0;i<n;i++){
            if(visited[i]==false && (distance[i]<distance[minDistanceVertex] || minDistanceVertex==-1)){
                minDistanceVertex=i;
            }
        }
        visited[minDistanceVertex]=true;
        for(int j=0;j<n;j++){
            if(edges[minDistanceVertex][j]!=0 && visited[j]==false){
                if(distance[minDistanceVertex]+edges[minDistanceVertex][j]<distance[j]){
                    distance[j]=distance[minDistanceVertex]+edges[minDistanceVertex][j];
                }
            }
        }
    }
    for(int i=0;i<n;i++){
        cout<<i<<" "<<distance[i]<<endl;
    }
    return 0;
}