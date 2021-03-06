
//name: Eduardo Roman
// Assignment: Lab10
// File: Lab10.cpp

#include <cctype>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <string>
#include "BinarySearch.h"
#include <time.h>
using namespace std;

int CreateBinaryTree (ifstream & input, BinarySearchTree<string>& BST);
  
int main (int argc,char * argv [])
{
  clock_t start_t, end_t;
  
  if (argc < 2)
    {
      cout << "Usage: " << argv [0] << " <input-file> <output-file>\n";
      exit (1);
    }
  
  ifstream IndexFile (argv[1]);
  if (IndexFile.fail())
    {
      cout << "File: " << argv [1] << " not found\n";
      exit (2);
    }
  
  start_t = clock();
  BinarySearchTree<string>  BST;
  int numwords =CreateBinaryTree(IndexFile, BST);
  end_t = clock();
  double total_t = (double)(end_t -start_t) / CLOCKS_PER_SEC;
  cout << endl;
  int Totalcomparisons = BST.getKeyComparisons();
  cout << "Total number of words: "<< numwords << endl;
  cout << "Total number of distinct words: " << BST.size()<<endl;
  cout << "Time taken to build index using AVL is: " << total_t << endl;
  cout << "Height of the AVL Tree is: " << BST.depth()<< endl;
  cout << "Total number of key comparisons: " << Totalcomparisons<< endl<<endl;;
  int options;
  while(options)
    {
      cout << "Options: (1) display index, (2) search, (3) save index, (4) quit\n";
      cin >> options;

      if (options == 1)
	{
	  string underscores(40,'_');
	  cout << "Binary Search Tree Index:\n"<< underscores<< endl;
	  BST.printTree();
	  cout << endl;
	}
      else if (options == 2)
	{
	  string SearchWord;
	  cout << "Enter search word: ";
	  cin >> SearchWord;
	  int KeyComparisons= 0;
	  if (BST.contains(SearchWord, KeyComparisons)== true)
	    {
	      cout << "Line numbers<BST>: ";
	      vector<int> rows = BST.getLines(SearchWord);
	      for (int i = 0; i<rows.size()-1; i++)
		{
		  cout << rows[i]<< ',';
		}
	      cout << rows[rows.size()-1]<<endl;
	      cout << "Search Key Comparisons: "<< KeyComparisons<<endl;//KeyComparisons<<"\t";
	      cout << endl;
	    }
	  else
	    cout << "The word is not in the document\n";
	}
      
      else if (options == 3)
	{
	  string outputfile;
	  cout<< "Please state the name of the file to create: ";
	  cin >> outputfile;
	  outputfile += ".txt";
	  ofstream file(outputfile.c_str());
	  string underscore(25,'_');
	  string header = "Binary Search Tree Index:\n"+ underscore+"\n";
	  file << header;
	  BST.outputTree(file);
	  file.close();
	}

     else if (options == 4)
	{
	  exit(1);
	}
      // else
      //{
      // cout << "Enter a valid option\n";
      // continue;
      // }
    }

      

  return 0;
}
int  CreateBinaryTree (ifstream & input, BinarySearchTree<string> & BST)
{
  int totalwords =0;
  string Line;
  int LineNum = 0;
  while(getline(input,Line))
    {
      LineNum++;
      stringstream stream(Line);
      string Word;
      while( stream >> Word)
	{
	  int TEMP = 0;
	  //totalwords++;
	  string FirstWord;
	  string SecondWord;
	  for(int w = 0; w < Word.size(); w++)
	    {
	      if (Word[w]== '-' && Word[w+1] == '-')
		{
		  TEMP = w;
		}
	    }
	  if (TEMP != 0)
	    {
	      for(int  F= 0; F < TEMP; F++)
		{
		  FirstWord += Word[F];
		}
	      for(int S = TEMP+2; S < Word.size(); S++)
		{
		  SecondWord += Word[S];
		}
	      totalwords +=2;
	      BST.insert(FirstWord, LineNum);
	      BST.insert(SecondWord, LineNum);
	    }
	  else if (Word[Word.size()-1]!= '\'' && Word[Word.size()-1]!= '.' && !isalpha(Word[Word.size()-1]))
	    {
	      Word.erase(Word.size()-1,1);
	      if(Word[Word.size()-1]== ',' )
		{
		  Word.erase(Word.end()-1);
		}
	      BST.insert(Word,LineNum);
	    }
	  else if (ispunct(Word[Word.size()-1]))
	    {
	      Word.erase(Word.size()-1,1);
	      BST.insert(Word,LineNum);
	    }
	  else if (ispunct(Word[0]))
	    {
	      Word.erase(Word.begin());
	      BST.insert(Word,LineNum);
	    }
	  else BST.insert(Word,LineNum);
	  totalwords++;
	}
    }
  return totalwords;
}

	  
	  /*
	  else if(ispunct(Word[Word.size()-1]))
	    { 
	      Word.erase(Word.size()-1,1);
	      BST.insert(Word, LineNum);
	    }
	  else if (ispunct(Word[0]))
	    {
	      Word.erase(Word.begin());
	      BST.insert(Word, LineNum);
	    }
	  else BST.insert(Word, LineNum);
	  totalwords++;
	  // BST.insert(Word, LineNum);
	}
    }
      return totalwords;
}
	  */
   
 
		 
	 
	       
	  
	  
	  
      
