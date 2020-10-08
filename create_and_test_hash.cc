/* 
Name: Gabriella Alexis
Date: April 1, 2020
Class: Software Design & Analysis III

This is the code for creating and testing hash tables with linear probing, quadratic probing and double hashing.
*/

#include "quadratic_probing.h"
#include "linear_probing.h"
#include "double_hashing.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

template <typename HashTableType>
void TestFunctionForHashTable(HashTableType &hash_table, const string &words_filename, const string &query_filename) {
  // cout << "TestFunctionForHashTables..." << endl;
  // cout << "Words filename: " << words_filename << endl;
  // cout << "Query filename: " << query_filename << endl;
  hash_table.MakeEmpty();  
  //..Insert your own code 
  string line;
  ifstream file(words_filename); //reads words.txt
  if(!file.is_open())
  {
    cerr << "ERROR. Cannot open file." << endl;
  }

  while(getline(file, line))
  {
    hash_table.Insert(line);
  }

  string fline;
  ifstream q_file(query_filename); //reads query_filename
  if(!q_file.is_open())
  {
    cerr << "Error, cannot open file." << endl;
  }

  int total = hash_table.num_of_elements();
  int size = hash_table.tableSize();
  float load_factor = float(total)/ float(size);
  float avg_collisions = float(hash_table.num_of_collisions())/ float(total);  
  
  cout << "number_of_elements: " << total << endl; //25143
  cout << "size_of_table: " << size << endl; //55609
  cout << "load_factor: " << load_factor << endl;
  
  cout << "collisions: " << hash_table.num_of_collisions() << endl; //21214
  cout << "avg_collisions: " << avg_collisions << endl;
  cout << endl;

  vector<string> query_words;
  while(getline(q_file, fline))
  {
    query_words.push_back(fline); //put words into a vector 
  }

  for(int i = 0; i < query_words.size(); i++)
  {
    hash_table.Search(query_words[i]);
  }

}

template <typename HashTableType>
void TestFunctionForHashTable(HashTableType &hash_table, const string &words_filename, const string &query_filename, const string &r_value) {
  // cout << "TestFunctionForHashTables..." << endl;
  // cout << "Words filename: " << words_filename << endl;
  // cout << "Query filename: " << query_filename << endl;
  hash_table.MakeEmpty();  
  //..Insert your own code 
  string line;
  ifstream file(words_filename); //reads words.txt
  if(!file.is_open())
  {
    cerr << "ERROR. Cannot open file." << endl;
  }
 
  while(getline(file, line))
  {
    hash_table.Insert(line);
  }

  string fline;
  ifstream q_file(query_filename); //reads query_filename
  if(!q_file.is_open())
  {
    cerr << "Error, cannot open file." << endl;
  }

  int total = hash_table.num_of_elements();
  int size = hash_table.tableSize();
  float load_factor = float(total)/ float(size);
  float avg_collisions = float(hash_table.num_of_collisions())/ float(total);  
  string r_val = r_value; //assign to regular string instead of using the const string in param
  
  // hash_table.set_r_val(r_val);
  // cout << hash_table.get_r_val() << endl;
  cout << "r_value: ";
  hash_table.setRvalue(r_val);
  cout << "number_of_elements: " << total << endl; //25143
  cout << "size_of_table: " << size << endl; //55609
  cout << "load_factor: " << load_factor << endl;
  
  cout << "collisions: " << hash_table.num_of_collisions() << endl; //21214
  cout << "avg_collisions: " << avg_collisions << endl;

  cout << endl;
  vector<string> query_words;
  while(getline(q_file, fline))
  {
    query_words.push_back(fline); //put words into a vector 
  }

  for(int i = 0; i < query_words.size(); i++)
  {
    hash_table.Search(query_words[i]); //searches hash table for query words
  }

}

int testFunctionWrapper(int argument_count, char **argument_list) {
  const string words_filename(argument_list[1]);
  const string query_filename(argument_list[2]);
  const string param_flag(argument_list[3]);

  if (param_flag == "linear") {
    HashTableLinear<string> linear_probing_table;
    TestFunctionForHashTable(linear_probing_table, words_filename, query_filename);    
  } else if (param_flag == "quadratic") {
    HashTable<string> quadratic_probing_table;
    TestFunctionForHashTable(quadratic_probing_table, words_filename, query_filename);    
  } else if (param_flag == "double") {
    if(argument_count == 5)
    {
      const string r_value(argument_list[4]);
      HashTableDouble<string> double_probing_table;
      TestFunctionForHashTable(double_probing_table, words_filename, query_filename, r_value);   
    } 
  } else {
    cout << "Unknown tree type " << param_flag << " (User should provide linear, quadratic, or double)" << endl;
  }
  return 0;
}

// Sample main for program create_and_test_hash.
// WE WILL NOT USE YOUR MAIN IN TESTING. DO NOT CODE FUNCTIONALITY INTO THE MAIN.
// WE WILL DIRECTLY CALL testFunctionWrapper. ALL FUNCTIONALITY SHOULD BE THERE.
// This main is only here for your own testing purposes.
int main(int argc, char **argv) {

  //if(argc !=4 && argc !=5)
  if (argc != 4 && argc != 5) {
    cout << "you've entered " << argc << " arguments" << endl;
    for (int i = 0; i < argc; i++)
    {
      cout << argv[i] << endl;
    }
    cout << "Usage: " << argv[0] << " <wordsfilename> <queryfilename> <flag>" << endl;
    return 0;
  }
  
  testFunctionWrapper(argc, argv);
  return 0;
}
