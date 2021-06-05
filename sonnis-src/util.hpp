#include <string>
#include <sstream>
#include <vector>

using std::string;
using std::vector;
using std::set;

#ifndef UTIL_HPP
#define UTIL_HPP
class util {
    public:
    static vector<string> split(string &input, char delimiter) {
        vector<string> result;
        std::stringstream ss(input);
        string temp;
    
        while (getline(ss, temp, delimiter)) {
            result.push_back(temp);
        }
        return result;
    }

    static vector<string> split(string input, string delimiter) {
        size_t pos = 0;
        vector<string> result;
        string token;
        while ((pos = input.find(delimiter)) != string::npos) {
            token = input.substr(0, pos);
            result.push_back(token);
            input.erase(0, pos + delimiter.length());
        }
        result.push_back(input);
        return result;
    }

    static inline void trim_whitespace(string &str) {
        str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char ch) {
            return !std::isspace(ch);
        }));

        str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char ch) {
            return !std::isspace(ch);
        }).base(), str.end());
    }
};
#endif