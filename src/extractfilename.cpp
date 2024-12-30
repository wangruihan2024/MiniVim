#include <define.h>
extern std::string fileanme;
std::string extractfilename(std::string path) {
    int lastSlashPos = path.find_last_of('/');
    if (lastSlashPos != std::string::npos) {
        return path.substr(lastSlashPos + 1);
    }
    return path;
}