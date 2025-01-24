# exec.hpp

This is a an extremely concise header-only C++ library that provides some practical features and encapsulation.

- Cross-platform and dependency-free (only relies on the standard library).
- Header-only.
- Modern C++.

Look at these again:

- [one.h](https://github.com/moehoshio/one.h)

For example:

- `boolTo`: Converts a boolean value to a specified type.

```cpp
auto boolS2 = exec::boolTo<const char *>(true,"true","false");//"true"
```

A suitable scenario might be logging, indicating whether a certain option is enabled.

- `copy`: Avoids dangling references caused by passing temporary objects when a function accepts `const T &` and returns `T &`.

```cpp
// Without using exec::copy here, it would lead to a dangling reference.
decltype(auto) minStr = exec::copy(std::min(std::string("1"),std::string("02"))); // std::string "1"
```

And, using the pipe operator (`|`) for chaining and enhancing the readability of function calls:

```cpp
decltype(auto) strShadPtr = std::string("str") | exec::move | exec::make_shared; //std::shared_ptr<std::string>
```

It's worth noting that for non-static member functions and template functions, encapsulation is typically required (e.g., using lambda, specific examples are provided later).

C++ Standard:
Requires C++20 or above.
Currently, mainly due to the use of constexpr and simplified function templates. If you modify them, there should be no issues.

here are some more examples:

- `boolTo` : T(bool,T,T)

```cpp
    std::string boolStr = exec::boolTo(false);// std::string "false"

    auto boolS2 = exec::boolTo<const char *>(true,"t","f");// "t"
```

- `getTimeString`: std::string(const char *)

```cpp
auto/*std::string*/ strTime = exec::getTimeString("%Y-%m-%d-%H-%M-%S");//2024-01-01-00-01-01 or custom format 
```

```cpp

#include "exec.hpp"
  

    
  
    decltype(auto) minStr = exec::copy(std::min(std::string("1"),std::string("02")) );// string "1"

    using namespace exec::op;
    decltype(auto) strShadPtr = std::string("str") | exec::move | exec::make_shared; //std::shared_ptr<std::string>



    
  
    auto/*std::string*/ uuid = exec::generateUUID(32);//32 digits uuid

    auto/*std::string*/ strRand = exec::generateRandomString(10); // 10 digits a-Z and 0-9  or custom format

    size_t nums = exec::randNums({1,9});// default 0-999999999 (9 digits)



    bool isUrl =  exec::isUrl("https://example.com"); // true
    bool isProxy = exec::isProxyAddress("http://example.com"); //false


    // Encapsulation of template functions:
    auto boolTo = [](bool v) -> decltype(auto) { return exec::boolTo(v); };
    // Encapsulation for non-static member functions:
    auto memberFunc = [this](auto&& v)->decltype(auto) { return this->func(v);};

    // Sometimes, operator precedence might be an issue. Use () to ensure the order of operations:
    std::cout<< (std::string("http://example.com:1082") | exec::isProxyAddress | boolTo) ; // cout std::string "true"



     // use initializer list
    auto CustomListFunc = [] <typename T> (const std::initializer_list<T>& v){ std::vector vec{v}; for(const auto & it : vec) std::cout<<it;  return v;};

    auto strList = {std::string("01"),std::string("02")};

    // Must use this approach, cannot directly construct an anonymous entity
    (void) resList =  strList | move | CustomListFunc ;// cout std::string "0102"
    //Equivalent to
    // resList = CustomListFunc(  move(  strList )   );

    using namespace exec::op::range;
    // For types that satisfy the iterator requirements, the container traversal version will be selected.
    auto/*vector<std::string>*/ vec = it | make_vector | [](auto&&v){std::cout<<v;} ;      
    // Iterate over the vector container and call the function with the values. Similar to : 
    // func(strList,func){
    // for( auto it : strList )
    //{ func(it);}
    // return it;
    //}
  

  

    constexpr int i = exec::sum(1,2,3,4); //10 (1+2+3+4)

    constexpr int i2 = exec::product(1,2,3,4); //24 (1*2*3*4)


    auto strs = exec::sum(std::string("str1 "),std::string("str2 "),std::string("str3\n"));
    //"str1 str2 str3\n"

    
    bool res = exec::allTrue(true,true,true,false);//false

    bool res2 = exec::anyTrue(false,true,false);//true

    bool res3 = exec::matchExtName("/home/main.cpp","txt");//false
    bool res4 = exec::matchExtNames("/home/main.cpp",{"txt","cpp","hpp"});//true


    auto res5 = exec::matchSizesV("1920x1080");
    // res5[0] = "1920x1080"
    // res5[1] = "1920"
    // res5[2] = "1080"

```

Welcome to  submit questions, light up star , error corrections (even just for better translations), and feature suggestions/construction.
More content will continue to be added in the future. :D
