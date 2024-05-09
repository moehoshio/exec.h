# exec.h

This is also an extremely concise header-only C++ library that provides some practical features and encapsulation.

For example:

- `boolTo`: Converts a boolean value to a specified type.

```cpp
auto boolS2 = exec::boolTo<const char *>(true,"true","false");//"true"
```

A suitable scenario might be logging, indicating whether a certain option is enabled.

- `copy`: Avoids dangling references caused by passing temporary objects when a function accepts `const T &` and returns `T &`.

```cpp
decltype(auto) minStr = exec::copy(std::min(std::string("1"),std::string("02"))); // std::string "1"
```

And, using the pipe operator (`|`) for chaining and enhancing the readability of function calls:

```cpp
decltype(auto) strShadPtr = std::string("str") | exec::move | exec::make_shared; //std::shared_ptr<std::string>
```

- Cross-platform and dependency-free (only relies on the standard library).
- Header-only.
- Modern C++.

here are some more examples:

```cpp
#include "exec.h"
    std::string boolStr = exec::boolTo(false);// std::string "false"
    auto boolS2 = exec::boolTo<const char *>(true,"t","f");// "t"
    decltype(auto) it = exec::copy(std::min(std::string("1"),std::string("02")) );// string "1"

    decltype(auto) strShadPtr = std::string("str") | exec::move | exec::make_shared; //std::shared_ptr<std::string>

    auto/*std::string*/ strTime = exec::getTimeString();//2024-01-01-00-01-01 or custom format 
    
    auto/*std::string*/ uuid = exec::generateUUID();//32 digits uuid

    auto/*std::string*/ strRand = exec::generateRandomString(10); // 10 digits a-Z and 0-9  or custom format

    size_t nums = exec::randNums();// default 0-999999999 (9 digits)

    bool isUrl =  exec::isUrl("https://example.com"); // true
    bool isProxy = exec::isProxyAddress("http://example.com"); //false

    auto boolTo = [](bool v) -> decltype(auto) { return exec::boolTo(v); };

    std::cout<< (std::string("http://example.com:1082") | exec::isProxyAddress | boolTo) ; // std::string "true"
```

Welcome to  submit questions, light up star , error corrections (even just for better translations), and feature suggestions/construction.  
More content will continue to be added in the future. :D
