#include "Node.h"
#include <iostream>  
#include <string>    
#include <fstream>   
#include <vector>

vector<string> dict;
vector<Node*> freq;

using namespace std; 

int main() {
  
  string word;

  // opens dictionary
  ifstream dictionary;
  dictionary.open("largedictionary.txt");

  // if dictionary cannot open returns error
    if (!dictionary){
    cout << "File cannot open";
    
    return 1;
  }
  
  //feed dictionary to vector
  while (dictionary >> word){

    dict.push_back(word);
  }


  // Opens whale.txt 
	ifstream myfile; 
  myfile.open("whale.txt");

  // if whale.txt cannot open returns error
  if (!myfile){
    cout << "File cannot open";
    
    return 1;
  }

  
  // declares root as nullptr since there is no tree curretly
  Node * root = nullptr;


  //declares vars needed for binary search 
  
  int l = 0;
  int r = dict.size();

  //reads whale.txt into word which is passed to insert to make tree also calls binary search to determine if word is fake or not
  while (myfile >> word){
    
    insert(root, word, binary_search(dict, word, l, r));
  }

  // opens outfile wordCounts.txt
  ofstream outFile;
  outFile.open("wordCounts.txt");

  //calls print function to print tree nodes to wordCounts.txt
  printAll(root, outFile);


  // Calls fake_insert to push all fake words in the tree to vector freq
  fake_insertVect(freq, root);

  // passes the vector and size of vector to sort by frequency (decending)
  int n = freq.size();
  sort_Vector(freq, n);

  // Opens topMistakes.txt
	ofstream mistakes; 
  mistakes.open("topMistakes.txt");

  // if topMistakes.txt cannot open returns error
  if (!mistakes){
    cout << "File cannot open";
    
    return 1;
  }

  // prints the top num of mistakes from vector freq
  int num = 100;
  printMistakes(freq, mistakes, num);


  //closes files
  outFile.close();
  myfile.close();
  dictionary.close();
  mistakes.close();

  // lets user know program has completed successfully
  cout << "Analysis Complete!" << endl;

	return 0; 
}

