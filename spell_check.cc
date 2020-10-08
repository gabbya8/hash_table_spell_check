/* 
Name: Gabriella Alexis
Date: April 6, 2020
Class: Software Design & Analysis III

This is the code for spell checker implemented using quadratic probing.
*/

#include "quadratic_probing.h"
#include "linear_probing.h"
#include "double_hashing.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

void SpellCheck(const string &document_filename, const string &dictionary_filename)
{
  HashTable<string> hash_table;
  string line;
  ifstream file(dictionary_filename);
  
  if(!file.is_open())
  {
    cerr << "ERROR. Cannot open file." << endl;
  }

  while(getline(file, line))
  {
    hash_table.Insert(line); //inserts dictionary words into table
  }
  
  file.close();

  string word;
  ifstream doc_file(document_filename);
  vector<string> spell_check;

  if(!doc_file.is_open())
  {
    cerr << "Error. Cannot open file." << endl;
  }

  while(doc_file >> word) //reads file
  {
    for(int i = 0; i < word.length(); i++) //go through words
    {
      if(ispunct(word.front())) //if first char is a punctuation
      {
        word = word.substr(1); //remove
      }
      else if(ispunct(word.back())) //if last char is punctuation
      {
        word.pop_back(); //remove
        if(ispunct(word.back())) //double check for last char being punctuation
        {
          word.pop_back();
        }
      }
        word[i] = tolower(word[i]); //converts to lowercase
    }
    if(hash_table.Contains(word)) //if word is in dictionary
    {
      cout << word << " is CORRECT" << endl;
      //   correct = true;
    } 
        
    else
    {
      string incorrect_word = word;  
      cout << incorrect_word << " is INCORRECT" << endl;
      string new_word = incorrect_word;
      /*CASE A- missing letter.  Fix: add a letter*/
      for(int i = 0; i < incorrect_word.length() + 1; i++) //goes through each letter in incorrect word
      {
        for(char letter = 'a'; letter <= 'z'; letter++)
        {
          new_word.insert(i,1,letter); //insert a letter for every space in new_word
          if(hash_table.Contains(new_word)) //check if it's in the dictionary
          {
            cout << "** " << incorrect_word << " -> " << new_word << " ** " <<"case A"<< endl;
          }
          new_word = incorrect_word;
        }
      }
      /*CASE B- added letter.  Fix: remove a letter*/
      new_word = incorrect_word;
      for(int i = 0; i < incorrect_word.length(); i++)
      {
        new_word.erase(i,1); //removes a letter in new_word
        if(hash_table.Contains(new_word)) //check if it's in the dictionary
        {
          cout << "** " << incorrect_word << " -> " << new_word << " ** " << "case B"<< endl;
        }
        new_word = incorrect_word;    
      }

      /*CASE C- swapped letter.  Fix: swap letters into correct positions*/
      new_word = incorrect_word;
      for(int i = 0; i < incorrect_word.length()-1; i++)
      {
        std::swap(new_word[i], new_word[i+1]);
        if(hash_table.Contains(new_word))
        {
          cout << "** " << incorrect_word << " -> " << new_word << " ** " << "case C"<< endl;
        }
        new_word = incorrect_word;
      }
    }
  }
  doc_file.close();

}
int testSpellingWrapper(int argument_count, char** argument_list) 
{

  const string document_filename(argument_list[1]);
  const string dictionary_filename(argument_list[2]);
  // Call functions implementing the assignment requirements.
  
  SpellCheck(document_filename, dictionary_filename);
  // cout << "Input document filename is " << document_filename << endl;
  // cout << "Input dictionary filename is " << dictionary_filename << endl;


  return 0;
}

int main(int argc, char **argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <document-file> <dictionary-file>" << endl;
    return 0;
  }
  
  testSpellingWrapper(argc, argv);

  return 0;
}
