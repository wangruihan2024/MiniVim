#include <define.h>
extern WINDOW *filewin, *infowin, *cmdwin, *rowwin;
extern std::vector<std::vector<char>> file_content;
extern std::vector<char> command;
extern std::string filename;
extern int filewin_row, filewin_column, file_content_row, edge_row, edge_column, column, cursor_x, cursor_y, row, column, edtcur_x, edtcur_y, cmdcur;
extern bool scroll_mode;
extern char mode;

void output(std::string win)
{

    if (win == "file" and scroll_mode)
    {
        for (int i = 0; i < filewin_row; i++)
        {
            wmove(filewin, i, 0);
            if (i + edge_row >= file_content_row)
            {
                for (int j = 0; j <= filewin_column; j++)
                {
                    wprintw(filewin, "%c", ' ');
                }
            }
            else
            {
                for (int j = 0; j <= filewin_column; j++)
                {
                    if (i + edge_row == cursor_y and j + edge_column == cursor_x)
                    {
                        edtcur_y = i;
                        edtcur_x = j;
                    }
                    if (edge_column + j < file_content[i + edge_row].size())
                        wprintw(filewin, "%c", file_content[i + edge_row][j + edge_column]);
                    else
                        wprintw(filewin, "%c", ' ');
                }
            }
        }
        wmove(filewin, edtcur_y, edtcur_x);
        wrefresh(filewin);
        show_row();
    }
    else if (win == "cmd")
    {
        wmove(cmdwin, 0, 1);
        for (int i = 0; i < command.size(); i++)
            wprintw(cmdwin, "%c", command[i]);
        for (int i = command.size(); i < column - 1; i++)
            wprintw(cmdwin, "%c", ' ');
        wmove(cmdwin, 0, cmdcur + 1);
        wrefresh(cmdwin);
    }
}
