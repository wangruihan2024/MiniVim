#include <define.h>
extern WINDOW *cmdwin;
extern std::string filename;
extern bool read_mode, scroll_mode, file_exist, truncate_mode;
void readin(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        if(argv[i] == "-W") {
            if(argv[i + 1] == "scroll") {
                scroll_mode = true;
                i++;
            }
            else if (argv[i + 1] == "break")
            {
                scroll_mode = false;
                i++;
            }
        }else if(argv[i] == "-t") {
            truncate_mode = true;
        }
        else if (argv[i] == "-R")
        {
            read_mode = true;
        }else {
            filename = argv[i];
            file_exist = true;
        }
    }
}