#ifndef PROJECT3_PIECETABLE_H
#define PROJECT3_PIECETABLE_H
#include <iostream>
#include <vector>

using namespace std;

class pieceTable {
private:
    vector<vector<int>> pieces;
    vector<char> orig;
    vector<char> add;
    void append(vector<char> &vec, string str);
public:
    pieceTable();
    void insert(int pos, string str);
    void remove(int pos, int length);
    void printTable();
};


#endif //PROJECT3_PIECETABLE_H
