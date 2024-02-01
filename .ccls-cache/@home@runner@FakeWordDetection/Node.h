#ifndef Node_H
#define Node_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

// Declares class node 
class Node {
  public:

  // node constructor
  Node(string wrd, bool fnd) {
		this -> word = wrd;
    this -> found = fnd;
		count = 0; 
		left = right = nullptr;
	}

  // members of class node
	string word; 
	int count;
  bool found;
	Node* left;
	Node* right;

};

// other functions that will interact with the members of class Node
  void printAll(Node* root, ofstream& outFile);
  void insert(Node*& root, string input, bool found);
  bool binary_search(vector<string> &dict, string word, int l, int r);

  void fake_insertVect(vector<Node*> &freq, Node*& root);
  void sort_Vector(vector<Node*> &freq, int n);
  void printMistakes(vector<Node*> &freq, ofstream& mistakes, int num);

#endif

