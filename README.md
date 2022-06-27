# myHash

myHash is intended to demonstrate my ability to construct a hash map in c++. 


### Usage(s): 
```cpp
 int main(int argv, char** argc){ 
 
   /* Tested type combinations (limited by hashable types):
      <string, string> 
      <int, string> 
      <string, int> 
   */ 
   
   unordered_map<std::string, std::string> map; 
   
   map["key"] = "value"; 
   
   cout << map["key"] << endl; 
   auto value = map["key"]; 
   
   map.remove("key"); 
   
   cout << map["key"] << endl; //Throws KeyError

   return 0; 
 } 
 
```

### Anticipated Design Changes:

```cpp

  map.remove(key); // Method left, add map[key] = NULL/None 
  
  // Add rehash function
  
  // Optimize probing function (potentially modify to chaining) 
  
  // Move classes into header / .cpp files 

```

### Changes: 
```cpp
  map.put(key, value) //Deprecated replaced with:
  map[key] = value; 
  
  auto value = map.get(key); //Deprecated replaced with: 
  auto value = map[key]; 
  
  //Added functionality to support stream output 
  cout << map[key] << endl; // Output: value 
  
  //Added _get helper function to assist get and set 
 
  //Added proxy class as intermediary for [] operations 
  
```
### Valgrind Summary 
![a3129ea6304a4869b88fc66ad1b88c3d](https://user-images.githubusercontent.com/58617118/175980331-57fbbfb4-3e39-48ac-acf9-34f01b465a10.png)
