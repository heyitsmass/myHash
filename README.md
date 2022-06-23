# myHash

myHash is intended to demonstrate my ability to construct a hash map in c++. 


### Usage(s): 
```cpp
 int main(int argv, char** argc){ 
   unordered_map<int, std::string> map;
   
   const int n = 5; //Forces resize 
    
   for(int i=0; i <= n; ++i) 
     map.put(i, "test_" + to_string(i)); 
    
   std::cout << map.get(3) << std::endl; 
   
   map.remove(3); 
   
   std::cout << map.get(3) << std::endl; // Throws KeyError
   
   myHash<std::string, int> map2; 
   
   for(int i=0; i <= n; ++i){
     
     map2.put("test_" + to_string(i), i); 
   } 
   
   std::cout << map2.get("test_3") << std::endl; 
   
   map2.remove("test_3"); 
   
   std::cout << map2.get("test_3") << std::endl; // Throws KeyError
    
   return 0; 
 } 
 
```

### Anticipated Design Changes:

```cpp
  map.put(key, value); // Changes to map[key] = value; 
  
  map.get(key); // Changes to map[key]; 
  
  map.remove(key); // Method left, add map[key] = NULL/None 
  
  // Add rehash function
  
  // Optimize probing function (potentially modify to chaining) 

```
