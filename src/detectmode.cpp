#include <define.h>
extern bool if_CRLF;
extern std::string filename;
bool detectmode(std::string filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    char prev = '\0', curr;
    while (file.get(curr)) {
        if (prev == '\r' && curr == '\n') 
            return true; 
        prev = curr;
    }
    return false;  
}