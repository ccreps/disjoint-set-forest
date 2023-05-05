// disjointSetForest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//implemented with reference to https://www.geeksforgeeks.org/disjoint-set-data-structures/

#include <iostream>
#include <vector>
#include <chrono>
using namespace std;

class DisjointSet {
    int* rank;
    int* rep;
    int n;

    public:

    DisjointSet(int n) {
        rank = new int[n];
        rep = new int[n];
        this->n = n;
    }

    void MakeSet(int x) {
        rep[x] = x;
        rank[x] = 0;
    }

    int FindSet(int x) {
        if (rep[x] != x) {
            rep[x] = FindSet(rep[x]);
        }
        return rep[x];
    }

    void Link(int x, int y) {
        if (rep[x] > rep[y]) {
            rep[y] = x;
        }
        else {
            rep[x] = y;
            if (rank[x] == rank[y]) {
                rank[y] = rank[y] + 1;
            }
        }
    }

    void SetUnion(int x, int y) {
        Link(FindSet(x), FindSet(y));
    }

    void NonHeuristicUnion(int n, int x, int y) {
        rep[x] = y;
        for (int i = 0; i < n; i++) {
            if (rep[i] == x)
                rep[i] = rep[y];
        }
    }
};

int main()
{
    const int N = 10000; //Number of elements to be tested on

    DisjointSet set(N);
    auto heuristicStart = std::chrono::system_clock::now();
    for (int i = 0; i < N; i++) {
        set.MakeSet(i);
    }
    for (int i = 1; i < N; i++) {
        set.SetUnion(i - 1, i);
    }
    std::chrono::duration<double> heuristicDuration = (std::chrono::system_clock::now() - heuristicStart);
 
    DisjointSet setTwo(N);
    auto nonHeuristicStart = std::chrono::system_clock::now();
    for (int i = 0; i < N; i++) {
        setTwo.MakeSet(i);
    }
    for (int i = 1; i < N; i++) {
        setTwo.NonHeuristicUnion(N, i-1, i);
    }
    std::chrono::duration<double> nonHeuristicDuration = (std::chrono::system_clock::now() - nonHeuristicStart);
    
    cout << "With Heuristics: " << heuristicDuration.count() << endl;
    cout << "Without Heuristics: " << nonHeuristicDuration.count() << endl;
}