#include <iostream> 

using namespace std; 

template<class K, class V> 
struct hash_entry{ 
  K key; 
  V value; 
  size_t hash; 
  bool is_free; 

  hash_entry(): is_free(true) {}; 
  hash_entry(K k, V v): key(k), value(v), is_free(false) {};
  hash_entry(K k, V v, size_t h): key(k), value(v), hash(h), is_free(false) {};


};


template<class K, class V> 
class unordered_map{ 

  private: 
    int capacity; 
    int load;  
    
    hash_entry<K, V>* table; 

  public: 
    unordered_map(){ 
      this -> capacity = 8; 
      this -> load = 0; 

      this -> table = new hash_entry<K, V>[this -> capacity];  

    }

    V operator[](K key){ 
      cout << key << endl; 

      V tmp; 

      return tmp; 

    }

    ~unordered_map(){ 
      delete [] table;  
      table = nullptr; 
    }
}; 



int main(){ 

  unordered_map<string, string> map; 
   
  map["key"] = "something";  




  return 0; 
}