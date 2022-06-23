#include <iostream>

//using namespace std; 

struct hashTable{ 
  bool isFree; 
  int key; 
  std::string value;  

  hashTable(){ 
    this -> isFree = true; 
    this -> key = 0; 
    this -> value = ""; 
  }

  hashTable(int k, std::string v){ 
    this -> isFree = false; 
    this -> key = k; 
    this -> value = v;  
  }
}; 

class keyError : public std::exception { 
  public: 
    std::string what(){ 
      return "Error: Key does not exist in map";
    }
};

class unordered_map{ 
  int capacity; 
  int load; 
  hashTable* table; 

  int hashIndex(int key, int i = 0){ 
    return 0; 
  }

  void resize(){ 
    this -> capacity = capacity += (capacity*2)/3; 

    hashTable* newTable = new hashTable[capacity]; 

    for(int i = 0; i < load; i++){ 
      int index = hashIndex(table[i].key); 

      if(!newTable[index].isFree) 
        index = probeIndex(table[i].key);

      newTable[index] = table[i]; 
    }

    delete(table); 
    table = newTable; 
  }

  int probeIndex(int key){ 
    int index = -1; 
    for(int i = 0; i < capacity; i++){ 
      index = hashIndex(key, i); 
      if(table[index].isFree or table[index].key == key)
        break; 
    }
    return index; 
  }

  public: 

    unordered_map(){ 
      this -> capacity = 16; 
      this -> load = 0;

      this -> table = new hashTable[capacity];  

    }

    void print(){ 
      if (load > 0){ 
        std::cout << '{'; 
        for(int i =0; i < load; i++){ 
          std::cout << '(' << table[i].key
              << ":'" << table[i].value
              << "')"; 
          if (i < load-1){ 
            std::cout << ','; 
          }
        }
        std::cout << '}' << std::endl; 
      } 
      return; 
    }

    bool put(int key, std::string value){ 
      if(load >= capacity) this -> resize(); 

      int index = hashIndex(key); 

      if(!table[index].isFree)
        if(table[index].key == key){ 
          table[index].value = value; 
          return true;  
        }
        index = probeIndex(key); 
        if(index < 0) return false; 
      
      table[index] = hashTable(key, value);  
      ++load;  
      return true; 
    }

    std::string get(int key){ 
      int index = hashIndex(key); 

      if(table[index].key == key and !table[index].isFree) 
        return table[index].value;  
      
      index = probeIndex(key); 

      if(index > 0)
        return table[index].value; 
      
      throw keyError(); 
    }

    /* 
    int hashCode(int key, std::string value){ 
      std::size_t hash = std::hash<std::string>{}(value); 

      std::cout << hash << ' ' << hash % capacity << std::endl; 

      return hash; 
    }
    */ 

    void remove(int key){ 
      int index = hashIndex(key); 

      if(table[index].key == key and !table[index].isFree)
        table[index] = hashTable(); 
        --load;  
      
      index = probeIndex(key); 

      if(index > 0) 
        table[index] = hashTable(); 

      return; 
    }

    ~unordered_map(){ 
      delete [] table; 
      table = nullptr; 
    }

}; 

int main(){ 

  unordered_map map; 

  map.print(); 

  map.put(53, "test"); 

  map.put(53, "a");

  std::cout << map.get(53) << std::endl; 

  map.remove(53); 

  map.print(); 
 

  return 0; 
}