#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Node.h"

//Purpose: A hash table that can hold variable-type values. 
//Explicitly instantiated in hashtable.cpp for int, float, double, string.
template<typename T>
class Hashtable {

private:
    //PRIVATE MEMBER VARIABLES

    Node<T>** table; //A pointer to an array of Node pointers.
    int current_size; //Current amount of entered keys
    int maximum_size; //Size of the array holding the data.
    float loadfactormax = 2; //Maximum allowed load factor. If increased, the table will be rehashed.

    //PRIVATE METHODS

    int hashFunction(string key, int power = 29);
    bool isPrime(int n);
    int nextPrime(int N);
    void rehash(); 
  
public:

    //Constructor, destructor.

    Hashtable(int max_size);
    ~Hashtable();

    //PUBLIC METHODS

    void insert(string key, T value);
    void printHashTable();
    T* search(string target);
    void erase(string target);
    
    //OPERATORS OVERLOADS

    T& operator[] (string key);
};

//EXPLICIT INSTANTIATIONS
template class Hashtable<int>;
template class Hashtable<float>;
template class Hashtable<double>;
template class Hashtable<string>;
template class Hashtable<bool>;


#endif