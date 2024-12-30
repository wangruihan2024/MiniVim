#include <define.h>
extern std::vector<COMMANDS> command_history;
extern std::vector<std::vector<char>> file_content;
extern int command_size, file_content_row;
extern WINDOW *cmdwin;
extern bool scroll_mode, file_exist, read_mode, if_change, if_CRLF;
extern std::string filename;
bool savefile()
{
    COMMANDS command_temp = command_history[command_size - 1];
    if(read_mode && if_change) {
        wmove(cmdwin, 0, 0);
        wprintw(cmdwin, "read-only file cannot be revised");
        return false;
    }else {
        if_change = false;
        std::ofstream fwriter(filename);
        for (int i = 0; i < file_content_row; i++) {
            if(i != 0 && !if_CRLF)
                fwriter << '\n';
            else if(i != 0 && if_CRLF)
                fwriter << '\r\n';
            for (int j = 0; j < file_content[i].size(); j++)
            {
                fwriter << file_content[i][j];
            }
        }
        fwriter.close();
        wmove(cmdwin, 0, 0);
        wprintw(cmdwin, "the file is saved");
        return true;
    }
}