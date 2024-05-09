    // exec.h
    // cpp Lang
    // Version 0.01
    // https://github.com/moehoshio/exec.h
    // MIT License
    // Welcome to  submit questions, light up star , error corrections (even just for better translations), and feature suggestions/construction.
    // :D
/*
Copyright (c) 2024 Hoshi

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once

#include <chrono>
#include <random>
#include <regex>
#include <string>

#if (__cplusplus >= 202002L)
    #define CONSTEXPR_ENABLE constexpr
#else 
    #define CONSTEXPR_ENABLE
#endif

CONSTEXPR_ENABLE inline decltype(auto) operator|(auto &&val, auto &&func) {
    return func(std::forward<decltype(val)>(val));
}

namespace exec {

    CONSTEXPR_ENABLE auto move = [](auto &&val) -> auto && { return std::move(val); };
    CONSTEXPR_ENABLE auto make_shared = [](auto &&val) -> decltype(auto) { return std::make_shared<std::remove_reference_t<decltype(val)>>(val); };
    CONSTEXPR_ENABLE inline  auto copy(const auto &d) {
        return d;
    };

    template <typename T = std::string>
    CONSTEXPR_ENABLE inline static T boolTo(bool v, const T &rTrue = "true", const T &rFalse = "false") {
        return ((v) ? rTrue : rFalse);
    };

    inline  std::string getTimeString(const char *Format = "%Y-%m-%d-%H-%M-%S") {
        auto currentTimePoint = std::chrono::system_clock::now();

        std::time_t currentTime = std::chrono::system_clock::to_time_t(currentTimePoint);
        std::tm *currentTm = std::localtime(&currentTime);

        char timeString[128];
        std::strftime(timeString, sizeof(timeString), Format, currentTm);
        return std::string(timeString);
    };
    inline  std::string generateUUID(int Digits = 32) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 15);

        const char *hex_chars = "0123456789abcdef";
        std::string uuid;

        for (int i = 0; i < Digits; ++i) {
            if (i == 8 || i == 12 || i == 16 || i == 20) {
                uuid += '-';
            } else {
                uuid += hex_chars[dis(gen)];
            }
        }

        return uuid;
    };

    // A random number , default with a maximum of 9 digits, it could be 0.
    inline  size_t randNums(std::pair<int,int> digits = {1,9}) {
        std::random_device rd;
        std::mt19937 rng(rd());

        std::uniform_int_distribution<int> distribution(0, 9);
        std::uniform_int_distribution<int> numsD2(digits.first,digits.second);
        std::string randomString;
        std::string numsList("0123456789");
        for (int i = 0; i < numsD2(rng); ++i) {
            randomString += numsList[distribution(rng)];
        }
        return std::stoull(randomString);
    }
    inline  std::string generateRandomString(int length, const std::string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789") {

        std::random_device rd;
        std::mt19937 rng(rd());

        std::uniform_int_distribution<int> distribution(0, characters.size() - 1);

        std::string randomString;
        for (int i = 0; i < length; ++i) {
            randomString += characters[distribution(rng)];
        }

        return randomString;
    };

    inline  bool isUrl(const std::string &str) {
        std::regex url_regex("(http|https)://[a-zA-Z0-9\\-\\.]+\\.[a-zA-Z]{2,3}(/\\S*)?");
        return std::regex_match(str, url_regex);
    };

    inline  bool isProxyAddress(const std::string &address) {
        std::regex proxyRegex(R"((http|https|socks5|socks4)://([\w.-]+)(:\d+))");
        return std::regex_match(address, proxyRegex);
    };
} // namespace exec
