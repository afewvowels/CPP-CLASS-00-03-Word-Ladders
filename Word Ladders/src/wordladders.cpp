//
//  wordladders.cpp
//  Word Ladders
//
//  Created by Keith Smith on 3/22/18.
//  Copyright © 2018 Keith Smith. All rights reserved.
//

#include "wordladders.h"

struct Word {
   char word[5];
};

//struct node {
//   string str;
//   vector<node *> children;
//   node(string s) {
//      str = s;
//      children.clear();
//   }
//};

int main(void) {
   map<string,LinearList<string>> dictionary;
   
   vector<string> d;
   
   string w1;
   string w2;
   
   fillD(d);
   
   while(w1 != "exit") {
      
      getWords(w1,w2,d);
//
//      node *root = new node(w1);
//      stack<node *> st;
//      st.push(root);
//
//      construct_tree(root, d);
//
//      vector<vector<string>> ladders;
//
//      cout << "Constructing ladders..." << endl;
//
//      construct_ladders(st, w2, ladders);
//
//      cout << "...construction complete.\n";
//
//      print(w1,w2,ladders);
//
//      delete root;
//      st.empty();
//
//      ladders.empty();
      
      node2 *root = new node2(w1);

      Queue<node2 *> *q = new Queue<node2 *>;
      
      q->enqueue(root);

      fillDictionary(dictionary);

//      createLinearLists(dictionary);

      buildConnections(root, dictionary);

      map<string,LinearList<string>> lld;
      
      buildLadders(*q, w2, lld);
   }
   
//   q = findWordLadder(w1,w2,dictionary);
   
//   cout << dictionary.at("trove")[0] << endl;
   
//   simpleWordLadder(w1,w2,dictionary);
   
//   cout << "Hello!\n";
   
   cout << "Program exited.\n";
   
   return 0;
}

bool isHammingOne(string a, string b) {
   int count = 0;
   
   for(int i = 0; i < a.length(); i++) {
      if(a[i] != b[i]) {
         count++;
      }
      if(count > 1) return false;
   }
   return count == 1 ? true : false;
}

void fillDictionary(map<string,LinearList<string>> &d) {
   string temp;
   
   ifstream wordList;
   wordList.open("/Users/bluebackdev/cpp/Class/CSIS 3700/06-Word_Ladders/xcode/Word Ladders/Word Ladders/sgb-words.txt");
   
   while(wordList >> temp) {
      LinearList<string> *list = new LinearList<string>;
      d.insert(pair<string,LinearList<string>>(temp,*list));
      list->clear();
   }
   
   wordList.close();
}

void fillD(vector<string> &d) {
   string temp;
   
   ifstream wordList;
   wordList.open("/Users/bluebackdev/cpp/Class/CSIS 3700/06-Word_Ladders/xcode/Word Ladders/Word Ladders/sgb-words.txt");
   
   while(wordList >> temp) {
      d.push_back(temp);
   }
   
   wordList.close();
}

void createLinearLists(map<string,LinearList<string>> &d) {
   map<string,LinearList<string>>::iterator it;
   
   string temp;
   
   cout << "Building word lists...\n";

   for(it=d.begin(); it != d.end(); ++it) {
      ifstream wordList;
      wordList.open("/Users/bluebackdev/cpp/Class/CSIS 3700/06-Word_Ladders/xcode/Word Ladders/Word Ladders/sgb-words.txt");
      
      string temp2 = it->first;
      
      while(wordList >> temp) {
         if(isHammingOne(temp, temp2)) {
            d[temp2].insert(d[temp2].size(),temp);
         }
      }
      
      wordList.close();
   }
   
   cout << "Build complete!\n";
}

void getWords(string &a, string &b, vector<string> d) {
   a = " ";
   b = " ";

   while(!isWordValid(a,d)) {
      cout << "Please enter word 1: ";
      cin >> a;
      
      if(isExit(a)) {
         
      }
      
      if(!isWordValid(a,d)) {
         cout << "That word is not in the dictionary.\n";
      }
   }
   while(!isWordValid(b,d)) {
      cout << "Please enter word 2: ";
      cin >> b;
      
      if(!isWordValid(b,d)) {
         cout << "That word is not in the dictionary.\n";
      }
   }
}

bool isWordValid(string s, vector<string> d) {
   for(int i = 0; i < d.size(); i++) {
      if(d[i] == s) {
         return true;
      }
   }
   return false;
}

bool isExit(string s) {
   if(s == "exit") {
      exit(0);
   }
   else {
      return false;
   }
}

Queue<string> *findWordLadder(string w1, string w2,const map<string,LinearList<string>> &dictionary) {
   LinearList<string> *w = new LinearList<string>;
   
   Queue<string> *q = new Queue<string>;
   
   string s;
   
   q->enqueue(w2);
   
   cout << "Generating word ladder:\n";
   
   while(!q->isEmpty()) {
      s = q->dequeue();
      
      w->insert(w->size(),s);
      
      for(int i = 0; i < w->size(); i++) {
         
//         if(w->operator[](i) == NULL) {
//            cout << w->operator[](0) << endl;
//            string v;
//            v = w->operator[](0);
//            q->enqueue(v);
//         }
      }
   }
   
   w->clear();
   
   return q;
}

void simpleWordLadder(string w1, string w2, map<string,LinearList<string>> &d) {
   Queue<string> *q = new Queue<string>;
   
   cout << "From " << w2 << " to " << w1 << ":" << endl;
   
   q->enqueue(w2);
   
   d.erase(w2);
   
   while(!q->isEmpty()) {
      
      string first = q->dequeue();
      
      for(map<string,LinearList<string>>::iterator it = d.begin(); it != d.end(); it++) {
         string second = it->first;
         
         if(isHammingOne(first, second)) {
            
            cout << first << "," << second << endl;

            q->enqueue(second);

            d.erase(second);

            first = second;

            if(second == w1) {
               while(!q->isEmpty()) {
                  cout << q->dequeue() << endl;
               }
               return;
            }
         }
      }
   }
}

void construct_tree(node *root, vector<string> dict) {
   cout << "Building trees..." << endl;
   
   deque<node *> q;
   q.push_back(root);
   while (!q.empty()) {
      node *curr = q.front();
      q.pop_front();
      if (dict.size() == 0)
         return;
      for (int i = 0; i < dict.size(); i++) {
         if (isHammingOne(dict[i], curr->str)) {
            string n = dict[i];
            dict.erase(dict.begin()+i);
            i--;
            node *nnode = new node(n);
            q.push_back(nnode);
            curr->children.push_back(nnode);
         }
      }
   }
   
   q.empty();
   
   cout << "...building complete." << endl;
}

void construct_ladders(stack<node *> st, string w2, vector<vector <string> > &ladders) {
   node *top = st.top();
   if (isHammingOne(top->str,w2)) {
      stack<node *> t = st;
      vector<string> n;
      while (!t.empty()) {
         n.push_back(t.top()->str);
         t.pop();
      }
      ladders.push_back(n);
   }
   for (int i = 0; i < top->children.size(); i++) {
      st.push(top->children[i]);
      construct_ladders(st,w2,ladders);
      st.pop();
   }
   top->children.clear();
}

void print(string w1, string w2, vector<vector<string> > ladders) {
   if(ladders.size() == 0) {
      cout << "There is no ladder between " << w1 << " and " << w2 << ".\n";
      return;
   }
   
   cout << "The following ladders were found from " << w1 << " to " << w2 << endl;
   
   for (int i = 0; i < ladders.size(); i++) {
      for (int j = ladders[i].size()-1; j >= 0; j--) {
         cout<<ladders[i][j]<<" ";
      }
      cout << w2 << endl;
   }
}

void buildConnections(node2 *root, map<string,LinearList<string>> d) {
   Queue<node2 *> q;
   q.enqueue(root);
   while(!q.isEmpty()) {
      node2 *current = q.dequeue();
      if(d.size() == 0) {
         return;
      }
      for (map<string,LinearList<string>>::iterator it = d.begin(); it != d.end(); it++) {
         if (isHammingOne(it->first, current->str)) {
            string n = it->first;
            d[it->first].clear();
            d.erase(it->first);
            it--;
            node2 *newNode = new node2(n);
            q.enqueue(newNode);
            current->children.insert(current->children.size(), newNode);
         }
      }
   }
}

void buildLadders(Queue<node2 *> queue, string w2, map<string,LinearList<string>> &lld) {
   cout << "Ladders" << endl;
   
   node2 *top = queue.peek();
   if(isHammingOne(top->str, w2)) {
      Queue<node2 *> results = queue;
      LinearList<string> *list = new LinearList<string>;
      while(!results.isEmpty()) {
         cout << "While loop" << endl;
         list->insert(list->size(), results.dequeue()->str);
      }
      cout << "Insert" << endl;
      lld.insert(std::pair<string,LinearList<string>>(top->str, *list));
      cout << "Post-insert" << endl;
   }
   cout << "Pre-for loop" << endl;
   for (int i = 0; i < top->children.size(); i++) {
      cout << "Recursive call" << endl;
      queue.enqueue(top->children.operator[](i));
      buildLadders(queue, w2, lld);
      queue.dequeue();
   }
   
   top->children.clear();
}
