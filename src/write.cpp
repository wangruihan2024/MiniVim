#include <define.h>
extern WINDOW *filewin, *cmdwin;
extern std::vector<std::vector<char>> file_content;
extern std::vector<char> command;
extern int filewin_column, filewin_row, edge_row, edge_column;
extern int cursor_x, cursor_y, edtcur_x, edtcur_y, cmdcur;
extern bool scroll_mode;
extern char mode;

void write(char ch_temp, std::string win)
{
    if (win == "file")
    {
        file_content[cursor_y].insert(file_content[cursor_y].begin() + cursor_x, ch_temp);
        cursor_x++;
            if (edtcur_x >= filewin_column)
                edge_column++;
            output("file");
    }
    else if (win == "cmd")
    {
        command.insert(command.begin() + cmdcur, ch_temp);
        cmdcur++;
        output("cmd");
        wrefresh(cmdwin);
    }
}