#include "pieceTable.h"
#include <string>
#include <vector>

void pieceTable::append(vector<char> &vec, string str) {
    for (char i : str) {
        vec.push_back(i);
    }
}

pieceTable::pieceTable() {
    vector<int> temp = {0,0,0};
    pieces.push_back(temp);
}

void pieceTable::insert(int pos, std::string str) {
    int key = 0;
    int count = 0;
    vector<int> temp = {0,0,0};
    for (int i=0; i<pieces.size(); i++) {
        if (pos<(count + pieces[i][1])) {
            key = i;
            break;
        }
        else {
            count += pieces[i][1];
        }
    }
    if (count == pos) {
        temp[0] = add.size();
        temp[1] = str.length();
        temp[2] = 1;
        pieces.insert(pieces.begin() + key, temp);
        append(add, str);
    }
    else {
        temp[0] = add.size();
        temp[1] = str.length();
        temp[2] = 1;
        pieces.insert(pieces.begin() + key, temp);

        temp[0] = pieces[key+1][0];
        temp[1] = pos - count;
        temp[2] = pieces[key+1][2];
        pieces.insert(pieces.begin() + key, temp);

        append(add, str);
        pieces[key+2][0] += pieces[key][1];
        pieces[key+2][1] -= pieces[key][1];
    }
}

void pieceTable::remove(int pos, int length) {
    int toRemove = length;
    int count = 0;
    vector<int> temp = {0,0,0};
    for (int i=0; i<pieces.size(); i++) {
        if (count<=pos && pos<count+pieces[i][1] && pos+length>count+pieces[i][1]) {
            int buffer = pieces[i][1];
            pieces[i][1] -= (pos-count);
            count += buffer;
        }
        else if (count<=pos && pos<count+pieces[i][1] && pos+length<count+pieces[i][1]) {
            int buffer = pieces[i][1];
            temp[0] = pieces[i][0];
            temp[1] = pieces[i][0] + (pos-count);
            temp[2] = pieces[i][2];
            pieces[i][0] += temp[1] + length;
            pieces[i][1] -= temp[1] + length;
            pieces.insert(pieces.begin() + i, temp);
            count += buffer;
            i++;
        }
        else if (pos<count && count<pos+length && pos+length<count+pieces[i][1]) {
            int buffer = pieces[i][1];
            pieces[i][0] += pos+length-count;
            pieces[i][1] -= pos+length-count;
            count += buffer;
        }
        else if (pos<count && pos+length>count+pieces[i][1]) {
            count += pieces[i][1];
            pieces.erase(pieces.begin()+i);
            i--;
        }
        else {
            count += pieces[i][1];
        }
    }
}

void pieceTable::printTable() {
    for (int i=0; i<pieces.size(); i++) {
        if (pieces[i][2] == 0) {
            //cout << pieces[i][0] << "'" << pieces[i][1] << "'" << pieces[i][2] << endl;
            for (int x=pieces[i][0]; x<pieces[i][0]+pieces[i][1]; x++) {
                cout << orig[x];
            }
        }
        else {
            //cout << pieces[i][0] << "'" << pieces[i][1] << "'" << pieces[i][2] << endl;
            for (int x=pieces[i][0]; x<pieces[i][0]+pieces[i][1]; x++) {
                cout << add[x];
            }
        }
        //cout << endl;
    }
    cout << endl;
}