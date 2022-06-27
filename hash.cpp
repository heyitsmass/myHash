#include <iostream> 

using namespace std; 

class KeyError : public std::exception {}; 

template<class Key, class Value> 
struct hash_entry{ 

  size_t hash_code; 
  Key key; 
  Value value; 
  bool is_free; 

  hash_entry(): is_free(true){}; 
  hash_entry(Key k, Value v): key(k), value(v), is_free(false){}; 
  hash_entry(Key k, Value v, size_t h): key(k), value(v), hash_code(h), is_free(false){}; 

}; 

template<class Key, class Value> 
class unordered_map{ 

  hash_entry<Key, Value>* table; 
  int capacity; 
  int load; 

  int _get(Key key){ 
    size_t hash_code = std::hash<Key>()(key); 
    int index;

    for(int i =0; i < capacity; ++i){ 
      index = hash_index(hash_code, i); 
      if(table[index].is_free || table[index].key == key)
        return index; 
    }
    return -1; 
  }

  void _resize(){ 
    hash_entry<Key, Value>* old = this -> table; 
    int old_size = this -> capacity; 

    this -> capacity = capacity += (capacity*2)/3; 

    delete[] this -> table; 

    this -> table = new hash_entry<Key, Value>[this -> capacity]; 
    this -> load = 0; 

    for(int i =0; i < old_size; ++i) 
      this -> set(old[i].key, old[i].value); 
  }

  public: 
    class proxy{ 

      /*
      public: 
      void operator=(Value value){ 
        ;
      }
      */ 

    };

    unordered_map(){ 
      this -> capacity = 8; 
      this -> load = 0; 
      this -> table = new hash_entry<Key, Value>[capacity];
    }

    Value get(Key key){ 
      int index = _get(key); 
      if(table[index].key == key)
        return table[index].value;
      //delete[] table; 
      //table = nullptr; 
      throw KeyError(); 
    }

    void set(Key key, Value value){ 
      if(load >= capacity) _resize(); 

      int index = _get(key); 

      if(table[index].is_free)
        table[index] = hash_entry<Key, Value>(key, value); 
      else 
        table[index].value = value; 

    }

    void remove(Key key){ 
      int index = _get(key); 
      if(table[index].key != key){ 
        //delete[] table; 
        //table = nullptr;
        throw KeyError(); 
      } 
      table[index] = hash_entry<Key, Value>(); 
      --load; 
    }

    int hash_index(size_t hash_code, int offset = 0){ 
      return (hash_code + offset) % capacity; 
    }

    /* 
    proxy operator[](Key key){ 
      return proxy(*this, key); 
    } */ 

    ~unordered_map(){ 
      delete[] table; 
      table = nullptr; 
    }
}; 

int main(){ 

  unordered_map<string, string> map; 
  
  //map["string"] = "value"; 

  //cout << map["string"] << endl; 

  return 0; 
}