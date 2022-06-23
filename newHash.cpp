#include <iostream> 

using namespace std; 


template<class Key, class Value>
struct hashTable{ 
  Key key; 
  Value value;  
  bool isFree; 
  int hash; 

  hashTable(){ 
    isFree = true; 
  }

  hashTable(Key k, Value v){ 
    key = k; 
    value = v; 
    isFree = false; 
    hash = -1; 
  }

  hashTable(Key k, Value v, int h){ 
    key = k; 
    value = v; 
    isFree = false; 
    hash = h; 
  }

}; 

class keyError : public std::exception { 
  public: 
    std::string what(){ 
      return "Error: Key does not exist in map";
    }
};

template<class Key, class Value> 
class unordered_map{ 
  int capacity; 
  int load; 
  hashTable<Key, Value>* table; 

  static_assert(is_same<Key, int>::value || is_same<Key, string>::value || is_same<Key, bool>::value,
                "Error: input type for key is not hashable"); 

  public: 

    unordered_map(){ 
      this -> capacity = 16; 
      this -> load = 0; 

      this -> table = new hashTable<Key, Value>[this -> capacity];

      cout << "Allocated Array" << endl; 
    }

    bool put(Key key, Value value){ 
      if(this -> load >= this -> capacity) this -> resize(); 

      size_t hash = this -> hash_code(key);  
      int index = this -> hash_index(hash);  

      cout << hash << ' ' << index << endl; 

      if(!table[index].isFree)

    }

    Value get(Key key){ 
      return table[0].value; 

    }

    int hash_index(int val, int offset = 0){ 
      return (val + offset) % this -> capacity;
    }

    size_t hash_code(Key key){ 
      return hash<Key>{}(key); 
    }

    void resize(){ 
      ; 
    }

    ~unordered_map(){ 
      delete [] table; 
      table = nullptr; 
      cout << "Deallocated Array" << endl; 
    }
}; 

int main(){ 

  unordered_map<string, string> map; 

  map.put("brandon", "cannon"); 
  
  cout << map.get("cannon") << endl; 



  return 0; 
}
