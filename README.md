# exec.h

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

```cpp
#include "exec.h"

    std::string boolStr = exec::boolTo(false);// std::string "false"

    auto boolS2 = exec::boolTo<const char *>(true,"t","f");// "t"
    
    decltype(auto) minStr = exec::copy(std::min(std::string("1"),std::string("02")) );// string "1"

    decltype(auto) strShadPtr = std::string("str") | exec::move | exec::make_shared; //std::shared_ptr<std::string>



    auto/*std::string*/ strTime = exec::getTimeString("%Y-%m-%d-%H-%M-%S");//2024-01-01-00-01-01 or custom format 
    
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

    
    
    constexpr int i = exec::sum(1,2,3,4); //10 (1+2+3+4)

    constexpr int i2 = exec::product(1,2,3,4); //24 (1*2*3*4)

    auto it = exec::sum(std::string("str1 "),std::string("str2 "),std::string("str3\n"));//"str1 str2 str3\n"

    bool res = exec::allTrue(true,true,true,false);//false

    bool res2 = exec::anyTrue(false,true,false);//true

```

Welcome to  submit questions, light up star , error corrections (even just for better translations), and feature suggestions/construction.  
More content will continue to be added in the future. :D
