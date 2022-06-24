#include <iostream> 

template<class Key, class Value>
struct hashTable{ 
  Key key; 
  Value value;  
  bool isFree; 
  int hash; 

  hashTable(): isFree(true) {}; 
  hashTable(Key k, Value v): key(k), value(v), isFree(false) {}; 
  hashTable(Key k, Value v, int h): key(k), value(v), isFree(false), hash(h) {}; 

}; 

class KeyError : public std::exception { 
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
  
  /*
  static_assert(is_same<Key, int>::value || 
                is_same<Key, string>::value || 
                is_same<Key, bool>::value,

                "Error: input type for key is not hashable"); 
  */ 

    int hash_index(size_t val, int offset = 0){ 
      return (val + offset) % this -> capacity;
    }

    size_t hash_code(Key key){ 
      return std::hash<Key>()(key); 
    }

    void resize(){ 

      hashTable<Key, Value>* old = this -> table; 
      int old_size = this -> capacity; 

      this -> capacity = capacity += (capacity*2)/3; 

      delete [] this -> table; 

      this -> table = new hashTable<Key, Value>[this -> capacity];  
      this -> load = 0; 

      for(int i = 0; i < old_size; i++)
        this -> put(old[i].key, old[i].value); 

    }

  public: 

    unordered_map(){ 
      this -> capacity = 8; 
      this -> load = 0; 

      this -> table = new hashTable<Key, Value>[this -> capacity];  
    }

    void put(Key key, Value value){ 
      //Resize if necessary
      if(this -> load >= this -> capacity) this -> resize(); 

      size_t hash = this -> hash_code(key);  
      int index = this -> hash_index(hash);  

      if(!table[index].isFree){
        //Update the value if the key matches
        if(table[index].key == key){ 
          table[index].value = value; 
          return; 
        }

        //Probe for available index
        for(int i =0; i < this -> capacity; ++i)
          if(table[this -> hash_index(hash, i)].isFree){ 
            index = this -> hash_index(hash, i); 
            break;
          }
      }
      
      table[index] = hashTable<Key, Value>(key, value, hash); 
      ++load; 
    }

    Value get(Key key){ 
      size_t hash = this -> hash_code(key); 
      int index = this -> hash_index(hash); 

      if(table[index].key != key){
        //Probe for matching key
        for(int i = 0; i < this -> capacity; ++i)
          if(table[this -> hash_index(hash, i)].key == key)
            return table[this -> hash_index(hash, i)].value; 

        delete [] table; 
        table = nullptr; 
        throw KeyError(); 
      }
      return table[index].value; 
    }

    void remove(int key){ 
      size_t hash = hash_code(key); 
      int index = hash_index(hash); 

      if(table[index].key != key){ 
        //Probe for matching key 
        for(int i =0; i < this -> capacity; ++i)
          if(table[i].key == key){ 
            index = i;
            break; 
          }
        delete[] table; 
        table = nullptr; 
        throw KeyError(); 
      }

      table[index] = hashTable<Key, Value>(); 
      --load; 
    }

    ~unordered_map(){ 
      delete [] table; 
      table = nullptr; 
    }
}; 

int main(){ 

  unordered_map<int, int> map; 

  for(int i =0; i <=5; i++){ 
    map.put(i, i); 
  }

  std::cout << map.get(1) << std::endl; 

  map.remove(1); 

  //std::cout << map.get(1) << std::endl; 

  return 0; 
}