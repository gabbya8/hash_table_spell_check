/* 
Name: Gabriella Alexis
Date: April 1, 2020
Class: Software Design & Analysis III

This is the class definition and implementation for double hashing.
*/


#ifndef DOUBLE_HASHING_H
#define DOUBLE_HASHING_H

#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include "quadratic_probing.h"

// Double Hashing implementation.
template <typename HashedObj>
class HashTableDouble {
 public:
  enum EntryType {ACTIVE, EMPTY, DELETED};

  explicit HashTableDouble(size_t size = 101) : array_(NextPrime(size)) //constructor
    { MakeEmpty(); }
  //if contains an object
  bool Contains(const HashedObj & x) const {
    return IsActive(FindPos(x)); //returns position of 
  }
  
  void MakeEmpty() {
    current_size_ = 0;
    for (auto &entry : array_)
      entry.info_ = EMPTY;
  }

  bool Insert(const HashedObj & x) {
    // Insert x as active
    size_t current_pos = FindPos(x);
    if (IsActive(current_pos))
      return false;
    
    array_[current_pos].element_ = x;
    array_[current_pos].info_ = ACTIVE;
   
    // Rehash
    if (++current_size_ > array_.size() / 2)
      Rehash();    
    return true;
  }
    
  bool Insert(HashedObj && x) {
    // Insert x as active
    size_t current_pos = FindPos(x);
    if (IsActive(current_pos))
      return false;
    
    array_[current_pos] = std::move(x);
    array_[current_pos].info_ = ACTIVE;

    // Rehash
    if (++current_size_ > array_.size() / 2)
      Rehash();

    return true;
  }

  bool Remove(const HashedObj & x) {
    size_t current_pos = FindPos(x);
    if (!IsActive(current_pos))
      return false;

    array_[current_pos].info_ = DELETED;
    return true;
  }

  /*gets the current size of hash table*/
  int tableSize()
  {
    return array_.size(); 
  }

  int num_of_elements()
  {
    return current_size_;
  }

  int num_of_collisions()
  {
    return collisions_;
  }

 void Search(HashedObj & x)
 {
     if(Contains(x))
     {
         if(InternalHash(x) == FindPos(x))
         {
            std::cout << x << " Found " << 1 << std::endl;
         }
         else
         {
            std::cout << x << " Found " << 1+ probes << std::endl;
         }
     }

     else{
         if(InternalHash(x) == FindPos(x))
         {
            std::cout << x << " Not_found " << 1 << std::endl;
         }
         else
         {
            std::cout << x << " Not_found " << 1 + probes << std::endl;
         }
     }
 }

void setRvalue(HashedObj & x)
{
  int r_value = std::stoi(x);
  std::cout << r_value << std::endl;
}

 private:        
  struct HashEntry {
    HashedObj element_;
    EntryType info_;
    
    HashEntry(const HashedObj& e = HashedObj{}, EntryType i = EMPTY)
    :element_{e}, info_{i} { }
    
    HashEntry(HashedObj && e, EntryType i = EMPTY)
    :element_{std::move(e)}, info_{ i } {}
  };
    
  std::vector<HashEntry> array_;
  size_t current_size_;

  mutable int collisions_ = 0;
  mutable int probes;
  int num;
  int r_value = 13;

  bool IsActive(size_t current_pos) const
  { return array_[current_pos].info_ == ACTIVE; } //returns position info as active

  /*collision resolution*/
  size_t FindPos(const HashedObj & x) const {
    size_t offset = 1;
    probes = 0;
    size_t current_pos = InternalHash(x); //element position after hash function

    /*while current positon is not empty and its element is not x (pos is taken)*/  
    while (array_[current_pos].info_ != EMPTY &&
	   array_[current_pos].element_ != x) {
      size_t new_position = InternalHash2(x);
      collisions_++; //we have a collision if statement is true
      probes++;
      current_pos += new_position;  // Compute ith probe. (pos = pos + offset)
      offset ++;
      if (current_pos >= array_.size()){
	      current_pos -= array_.size();
      }
    }
    return current_pos;
  }

  void Rehash() {
    std::vector<HashEntry> old_array = array_;

    // Create new double-sized, empty table.
    array_.resize(NextPrime(2 * old_array.size()));
    for (auto & entry : array_)
      entry.info_ = EMPTY;
    
    // Copy table over.
    current_size_ = 0;
    for (auto & entry :old_array)
      if (entry.info_ == ACTIVE)
	Insert(std::move(entry.element_));
  }

  /*hash function: hash(x) = x mod table_size; returns element position*/ 
  size_t InternalHash(const HashedObj & x) const {
    static std::hash<HashedObj> hf;
    return hf(x) % array_.size( );
  }

  size_t InternalHash2(const HashedObj & x) const {
    static std::hash<HashedObj> hf;
    return r_value - (hf(x) % r_value);
  }
};

#endif  // DOUBLE_HASHING_H
