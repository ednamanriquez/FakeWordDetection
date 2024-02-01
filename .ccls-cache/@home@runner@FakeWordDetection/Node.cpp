

#include "Node.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;



// Inserts node to bt, by taking the root and an input string
void insert(Node *&root, string input, bool found) {

  // base case, if no node creates a new one
  if (root == nullptr) {
    root = new Node(input, found);
  }

  // base case 2, if word is already in the tree, increases count
  if (input == root->word) {
    root->count++;
  }

  // recursion to find where input word belongs in the tree if less than current word then goes down the left brach, else goes down the right
  else {
    
    if (input < root->word) {
      insert(root->left, input, found);
    }

    else if (input > root->word) {
      insert(root->right, input, found);
    }
  }
}

// prints all nodes in tree in order
void printAll(Node *root, ofstream &outFile) {

  if (root == nullptr) {
    return;
  }

  else {
    // recursive call to print left branch before root
    printAll(root->left, outFile);

    //prints (fake word) if found == false for current root then prints root
    if (root->found == false) {
      outFile << "(Fake Word) ";
    }
    outFile << root->word << ": " << root->count << endl;

    // recursive call to print right branch after root
    printAll(root->right, outFile);
  }
}

// Binary search takes the vector containing dictionary, the left and right bounds and recursively searches for the matching word input, if its there returns true (not a fake word), if its not there returns false (fake word)
bool binary_search(vector<string> &dict, string word, int l, int r) {

  //base case word not found
  if(l > r){
    return false;
  }

  // base case word found
  int m = (l + r) / 2;
  
  if (dict[m] == word) {
    return true;
  }

  // recursive call to search on the right side
  if (word > dict[m]) {
    return binary_search(dict, word, m + 1, r);
  } 

  //recursive call to search the left side
  else {
  return binary_search(dict, word, l, m - 1);
  }
}


// takes freq vector and root of binary tree and pushes FAKE word nodes in the tree
void fake_insertVect(vector<Node*> &freq, Node*& root){

  // base case at the end of a branch
  if (root == nullptr){

    return;
  }

  // base case current node has a fake word pushes to vector
  if(root->found == false){
    
    freq.push_back(root);
  }

  // recursive call to go down the left of the root
  fake_insertVect(freq, root->left);

  //recursive call to go down the right of the root
  fake_insertVect(freq, root->right);

}


// sorts vector by frequency of the word, takes the vector and an int n (size of vecor) as inputs to perform insertion sort on the vector
void sort_Vector(vector<Node*> &freq, int n){

  // base case if the vector is less than 1 return
  if (n <= 1){
    
    return;
  }

  else {
//if it is more than one then it recursively calls itself to sort the vector
  sort_Vector(freq, n-1);

    Node * temp = freq[n-1];
    int i = n-2;
    
// while loop to swap the elements in the vector if the previous one is greater than the current one
    while (temp->count > freq[i]->count && i>=0){

      freq[i+1] = freq[i];
      i--;
    }

    freq[i+1] = temp;
    
  }

}

//print function for top 100 mistakes
void printMistakes(vector<Node*> &freq, ofstream& mistakes, int num){

  //while loop prints data from node at freq[i] 
  int i = 0;
  while (num > 0){

    mistakes << freq[i]->word << ": " << freq[i]->count<< endl;

    num --;
    i ++;
  }
  
}