#include <bits/stdc++.h>
using namespace std;
//Tree=connected graph with no cycle
//Spanning tree=given an undirected connected graph G(V,E), this means any tree with ALL the vertices, it spans V
//ST has n vertices and n-1 edges
//minimum spanning tree (MST) = the given graph is weighted as well, then MST is a ST with minimum sum of all weights of edges 

//kruskals algo helps to find MST of a given weighted, undirected, connected graph
//steps: pick the edges one by one starting from min weight edge till n-1 edges are reached
//if a cycle is formed by selecting that edge, skip it

//cycle detection = if there exist a path between the end vertices of an edge which we are about to add, then cycle will be formed after adding that edge
//because if there isnt a path that means the two end vertices are in separate connected components or at least one of them is not in the MST built till now
//introducing one edge = the hasPath(v1,v2) function has complexity O(V+E)=O(V+V^2)=O(V^2) in worst case which is bad

//union find algo for cycle detection=maintain a parents array where we store the parent of every vertex, initially each vertex is its own parent
//introducing first edge in graph (min weight wala) is valid as the top most parents of both end vertices are different so no cycle
//after introducing that in MST, change parent of top most parent of any end vertex of the edge to the top most parent of the other end vertex of the edge
//top most parent=if 0 ka parent isnt 0 but 1, then 0 ka parent 1, 1 ka parent 2, 2 ka parent 2 so 0 ka parent 2
//MST is formed by introducing edges and a separate parent array wala tree is also formed
//continue this until n-1 edges are reached 
//introducing one edge = worst case to find top most parent of a vertex when skew parent tree formed, going through every vertex to find top most parent = O(V) 
//hence O(ElogE+EV)=time complexity of kruskals, E=V^2 worst case
//cant improve ElogE sorting part but can improve cycle detection part by using "union by rank & path compression" instead of "union find" method, which avoids skew parent tree formation and maintains balanced parent tree so that cycle detection takes O(logV) instead of O(V) 
//O(ElogE+ElogV)
class edge{
    public:
    int source;
    int dest;
    int weight;
};
bool compare(const edge& a,const edge& b){
    return a.weight<=b.weight;
}
int main(){
    int n,e;
    cin>>n>>e;
    edge*input=new edge[e];//input array with all the weighted edges of the given graph
    for(int i=0;i<e;i++){
        int source,dest,weight;
        cin>>source>>dest>>weight;
        input[i].source=source;
        input[i].dest=dest;
        input[i].weight=weight;
    }
    sort(input,input+e,compare);//O(ElogE)
    edge*output=new edge[n-1];
    int*parent=new int[n];
    for(int i=0;i<n;i++){
        parent[i]=i;
    }
    int count=0;
    for(int i=0;i<e;i++){//O(EV)
        if(count>n-2){
            break;
        }
        int p1=parent[input[i].source];
        int p2=parent[input[i].dest];
        int s=input[i].source;
        int d=input[i].dest;
        while(s!=p1){//cycle detection->worst case to find top most parent of a vertex when skew parent tree formed, going through every vertex to find top most parent = O(V)
            s=p1;
            p1=parent[s];
        }
        while(d!=p2){
            d=p2;
            p2=parent[d];
        }
        if(p1!=p2){
            output[count].source=input[i].source;
            output[count].dest=input[i].dest;
            output[count].weight=input[i].weight;
            parent[p2]=p1;
            count++;
        }else{
            continue;
        }
    }
    for(int i=0;i<n-1;i++){
        if(output[i].source<output[i].dest){ 
            cout<<output[i].source<<" "<<output[i].dest<<" "<<output[i].weight<<endl;
        }else{
            cout<<output[i].dest<<" "<<output[i].source<<" "<<output[i].weight<<endl;
        }
    }
    return 0;
}