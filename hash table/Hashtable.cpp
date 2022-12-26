#include "Hashtable.h"

//Purpose: Calculate the table index (int) for which the key (string) would be stored.
template<typename T>
int Hashtable<T>::hashFunction(string key, int power) {
    int idx = 0;

    for (auto ch : key) {
        idx = (idx + power*ch)%maximum_size;
        power = (power*29)%maximum_size; 
    }

    return idx;
}

//Purpose: Helper function for the rehashing function. 
//Returns true if n is prime.
//Function from GeeksForGeeks.org.
template<typename T>
bool Hashtable<T>::isPrime(int n) {
    // Corner cases
    if (n <= 1)  return false;
    if (n <= 3)  return true;

    // This is checked so that we can skip 
    // middle five numbers in below loop
    if (n%2 == 0 || n%3 == 0) return false;

    for (int i=5; i*i<=n; i=i+6) {
        if (n%i == 0 || n%(i+2) == 0) {
            return false;
        }
    }
    return true;
}

// Purpose: Helper function for the rehashing function.
//Returns the smallest prime number greater than N.
// Function from GeeksForGeeks.org.
template<typename T>
int Hashtable<T>::nextPrime(int N) {
    // Base case
    if (N <= 1) {
        return 2;
    }

    int prime = N;
    bool found = false;

    // Loop continuously until isPrime returns true for a number greater than n.
    while (!found) {
        prime++;

        if (isPrime(prime)) {
            found = true;
        }
    }

    return prime;
}

//Purpose: Rehash the table to a new maximum size.
//The new maximum-size will be the prime number after 2x the previous maximum-size.
template <typename T>
void Hashtable<T>::rehash() {
    cout << "Rehashing the table." << endl;

    //Save the pointer to the old table of node-pointers. Also save the size.
    Node<T>** oldtable = table; 
    int oldtable_size = maximum_size;

    //Calculate the new maximum size. Make it the smallest prime number bigger than twice the previous size.
    maximum_size = nextPrime(2*maximum_size);
    
    //Create a new dynamically-allocated array of pointers.
    table = new Node<T>*[maximum_size];
    
    //Update the current size to zero, since the insert function will update it during the next steps.
    current_size = 0;
    
    //Initialize the new table with null values.
    for (int i = 0; i < maximum_size; i++) {
        table[i] = nullptr;
    }

    //Copy all elements from the old table into the new table.

    //Iterate through all table indices in the OLD hash table.
    for (int i = 0; i < oldtable_size; i++) {
        
        //Temporary node starting at the head of the separate chaining (linked list) at this index.
        Node<T>* temp = oldtable[i]; 
        
        //Iterate through all the elements in the linked list at this index.
        
        //While you haven't reached the end of the linked list...
        while (temp != nullptr) {
            //The Insert function automatically adds into the new(current) table.
            insert(temp->key, temp->data);
            
            //Move to the next element in the old-table linked list.
            temp = temp->next;
        } 
    }

    //The new(current) table has all the values from the old table. 
    //Now, properly delete the old table.

    //Delete each of the linked lists in the old table.
    for (int i = 0; i < oldtable_size; i++) {
        //The Node Class Destructor recursively deletes the linked list in index i of old table. 
        delete oldtable[i];
    }
    
    //Delete the old table.
    delete [] oldtable;

    cout << "Table has been rehashed." << endl;
    cout << "current size: " << current_size << endl;
    cout << "maximum size: " << maximum_size << endl;
}

//Constructor
template<typename T>
Hashtable<T>::Hashtable(int max_size) {        
    current_size = 0;
    maximum_size = max_size;

    //Create a dynamically-allocated table of node pointers.
    table = new Node<T>*[maximum_size]; 

    for (int i = 0; i < maximum_size; i++) {
        table[i] = nullptr;
    }
}

//Destructor
template<typename T>
Hashtable<T>::~Hashtable() {
    //Delete each of the linked lists in the table.
    for (int i = 0; i < maximum_size; i++) {
        //Recursively deletes the linked list in ith index. 
        //The node destructor does the recursion.
        delete table[i];
        table[i] = nullptr;
    }

    //Delete the dynamically-allocated table of node pointers.
    delete table;
    table = nullptr;
}

//Purpose: Insert a new key and value in O(1).
template<typename T>
void Hashtable<T>::insert(string key, T value) {
    //Check load factor and rehash if it is over the limit.
    float load_factor = current_size/float(maximum_size);
    if (load_factor > loadfactormax) {
        rehash();
    }
    
    //Calculate the index by using the string.
    int index = hashFunction(key);

    //Create a new node.
    Node<T>* n = new Node<T>(key, value);

    //Insertion as a linked list in O(1).
    n->next = table[index]; //Make the new node point to the existing node at this index.
    table[index] = n; //Update this new node as the new head

    current_size++;
}

//Purpose: Print where each key is stored in which bucket.
template <typename T>
void Hashtable<T>::printHashTable() {
    for (int i = 0; i < maximum_size; i++) {
        Node<T>* temp = table[i];
        cout << "index " << i << ": ";
        while (temp != nullptr) {
            cout << temp->key << ", " << temp->data << "\t";
            temp = temp->next;
        }
        cout << endl;
    }
}

//Purpose: Search the hashtable for a specific key and return a pointer to its value.
//It returns pointers so that, when not found, it can return a nullptr for any data type.
template <typename T>
T* Hashtable<T>::search(string target) {
    //The hash function returns which index the key would be located in.
    int index = hashFunction(target);

    //Search the linked list at this location.

    //Start from the head of the linked list.
    Node<T>* temp = table[index];

    //While you haven't reached the end of the linked list...
    while (temp != nullptr) {
        //Compare each node's value to the target.
        if (temp->key == target) {
            //If found, return the address of where the value is stored.
            return &(temp->data);
        }

        //Move to next node in this linked list.
        temp = temp->next;
    }

    //You made it here because the linked list did not contain the key you wanted.
    return nullptr;
}

//Purpose: Erases a key of the hashtable in approximate O(1) steps.
template <typename T>   
void Hashtable<T>::erase(string target) {
    //The hash function returns which index the key would be located in.
    int index = hashFunction(target);

    //Search the linked list at this location.

    //Go to the head of the linked list.
    Node<T>* cnode = table[index];

    //Search the head of the linked list.
    //This step is done separately so that we can reroute the table (array of pointers).
    if (cnode->key == target) {
        //Make a temporary node so that you can delete it.
        Node<T>* temp = cnode;

        //Make the pointer in the table point to the next object.
        table[index] = cnode->next;
        
        //Delete the node,
        //but first make it point to null so that you do not recursively delete the whole linked list.
        temp->next = nullptr;
        delete temp;
        return;
    }

    //If it was not the head of the linked list...
    while (cnode->next != nullptr) {
        //Check the next element.
        if (cnode->next->key == target) {
            //Make a temporary node so that you can delete it.
            Node<T>* temp = cnode->next;

            //Make the current node point to the next-next element
            cnode->next = cnode->next->next;

            //Delete the node and return.
            temp->next = nullptr;
            delete temp;
            return;
        }
        cnode = cnode->next;
    }

    //You are here because the target was not found
    cout << "Erase function message: \"" << target << "\" was not found." << endl;
}

//Purpose: Overload the [] operator so that it takes the key and returns the value by reference.
//When the key exists: map[key] = x would update the value.
//When the key does not exist: map[key] = x would result in creating the <key,value>.
template <typename T>   
T& Hashtable<T>::operator[] (string key) {
    //Declare a pointer to variable object T.
    T* valuepointer;

    //Search for the key in the hashtable. 
    //Returns a pointer to the value of the key if found, a nullptr if not found.
    valuepointer = search(key);

    //If the key exists in the hashtable, return the value object by reference.
    //The purpose of returing by reference is that using the [] operator will allow to update the value.
    if (valuepointer != nullptr) {
        return *valuepointer;
    }        
    
    //The key did not exist in the hashtable. You must add the key.
    
    //Create an empty object (of unspecified typename).
    T object; 
    
    //Create a node in the hashtable that contains this key and its object (object as a garbage value).
    insert(key, object);
        
    //You don't know where this object was inserted.
    //So you must search the key again.
    valuepointer = search(key);

    return *valuepointer;
}
