#ifndef ACTIVITY_H
#define ACTIVITY_H

// =========================================================
// File: actitivy.h
// Author: Gaddiel Lara Roldán
// Date: 16/11/2022
// =========================================================

#include "ugraph.h"
using namespace std;

template <class Vertex>
int getVIndex(vector<Vertex> a1, typename set<Vertex>::iterator j1){
    int index;
    for (int i=0;i<a1.size();i++){
        if (a1[i]==*j1){
            index=i;
        }
    }
    return index;
}

template <class Vertex>
void dfs2(int i, Vertex v, const UnweightedGraph<Vertex>* g, bool visited[],stack<Vertex> &TS){
    visited[i] = true;
    vector<Vertex> a=g->getVertexes();
    typename set<Vertex>::iterator j;
    set<Vertex> adj=g->getConnectionFrom(v);
    int k;
    for (j = adj.begin(); j != adj.end();j++){
        k=getVIndex(a,j);
        if (visited[k]==false){
            dfs2(k, a[k], g, visited, TS);
        }
    }
    TS.push(v);
}

template <class Vertex>
string topologicalSort(const UnweightedGraph<Vertex>* graph) {
    stack<Vertex> TS;
    stringstream aux;
    aux<<"[";
    vector<Vertex> a=graph->getVertexes();
    int n=a.size();
    bool* visited = new bool[n];
    for (int i = 0; i < n; i++){
        visited[i] = false;
    }
    for (int i = 0; i < n; i++){
        if (visited[i] == false){
            dfs2(i, a[i], graph, visited, TS);
        }
    }
    while (TS.empty() == false){
        aux << TS.top() << " ";
        TS.pop();
    }
    delete [] visited;
    aux<<"]";
    return aux.str();
}

template <class Vertex>
bool isBipartite(const UnweightedGraph<Vertex>* graph) {
    vector<Vertex> v=graph->getVertexes();
    typename set<Vertex>::iterator itr;
    set<Vertex> s;
    vector<Vertex> aux;
    for (int i=0;i<v.size();i++){
        s=graph->getConnectionFrom(v[i]);
        for (itr=s.begin();itr!=s.end();itr++){
            aux.push_back(v[i]);
            aux.push_back(*itr);
        }
    }
    int k=aux.size()/2;
    vector<Vertex> adj[k];
    for (int j=0;j<k;j++){
        adj[j]={aux[2*j],aux[2*j+1]};
    }
    vector<Vertex> gpoA;
    vector<Vertex> gpoB;
    bool UinA;
    bool UinB;
    bool VinA;
    bool VinB;
    for (int l=0;l<k;l++){
        UinA=find(gpoA.begin(),gpoA.end(),adj[l][0])!=gpoA.end();
        UinB=find(gpoB.begin(),gpoB.end(),adj[l][0])!=gpoB.end();
        VinA=find(gpoA.begin(),gpoA.end(),adj[l][1])!=gpoA.end();
        VinB=find(gpoB.begin(),gpoB.end(),adj[l][1])!=gpoB.end();
        if (!UinA&&!UinB&&!VinA&&!VinB){
            gpoA.push_back(adj[l][0]);
            gpoB.push_back(adj[l][1]);
        }
        if (UinA&&!VinA&&!VinB){
            gpoB.push_back(adj[l][1]);
        }
        if (UinB&&!VinA&&!VinB){
            gpoA.push_back(adj[l][1]);
        }
        if (VinA&&!UinA&&!UinB){
            gpoB.push_back(adj[l][0]);
        }
        if (VinA&&!UinA&&!UinB){
            gpoB.push_back(adj[l][0]);
        }
        if (UinA&&VinA||UinB&&VinB){
            return 0;
        }
    }
    return 1;
}

template <class Vertex>
bool isCyclic(int i, Vertex v, const UnweightedGraph<Vertex>* g, bool visited[], Vertex parent){
    visited[i] = true;
    vector<Vertex> a=g->getVertexes();
    typename set<Vertex>::iterator j;
    set<Vertex> adj=g->getConnectionFrom(v);
    int k;
    for (j = adj.begin(); j != adj.end(); j++){
        k=getVIndex(a,j);
        if (!visited[k]){
           if (isCyclic(k, a[k], g, visited, parent)){
              return true;
           }
        }
        else if (v != parent){
           return true;
        }
    }
    return false;
}
template <class Vertex>
bool isTree(const UnweightedGraph<Vertex>* graph) {
    Vertex parent;
    vector<Vertex> a=graph->getVertexes();
    int n=a.size();
    bool* visited = new bool[n];
    for (int i = 0; i < n; i++){
        visited[i] = false;
    }
    if (isCyclic(0, a[0], graph, visited, parent)){
        return false;
    }
    for (int u = 0; u < n; u++){
        if (!visited[u]){
           return false;
        }
    }
    return true;
}

#endif /* ACTIVITY_H */
