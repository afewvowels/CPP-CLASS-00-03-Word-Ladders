#include <iostream>
#include <fstream>
#include <string>
#include <map>
//#include <bits/stdc++>
#include "linearlist.h"
#include "queue.h"
#include <algorithm>
#include <vector>
#include <deque>
#include <stack>

using namespace std;

struct node {
    string str;
    vector<node *> children;
//    LinearList<node *> children;
    node(string s) {
        str = s;
        children.clear();
    }
};

struct node2 {
    string str;
    LinearList<node2 *> children;
    node2(string s) {
        str = s;
        children.clear();
    }
};

void fillDictionary(map<string,LinearList<string>> &);
bool isHammingOne(string, string);
void createLinearLists(map<string,LinearList<string>> &);
void getWords(string &, string &, vector<string>);
bool isExit(string);
Queue<string> *findWordLadder(string, string,const map<string,LinearList<string>> &);
void simpleWordLadder(string w1, string w2, map<string,LinearList<string>> &);

void fillD(vector<string> &);
void construct_ladders(stack<node *>, string, vector<vector <string>> &);
void construct_tree(node *, vector<string>);
void print(string, string, vector<vector<string>>);
bool isWordValid(string, vector<string>);

void buildConnections(node2 *, map<string,LinearList<string>>);
void buildLadders(Queue<node2 *>, string, map<string,LinearList<string>> &);
