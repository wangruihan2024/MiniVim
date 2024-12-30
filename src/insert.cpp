#include <define.h>
extern bool if_close, if_change, scroll_mode;
extern int cursor_x, cursor_y, edge_row, edge_column, file_content_row, filewin_row, pos, filewin_column, column;
extern char mode;
extern WINDOW *filewin, *infowin, *cmdwin, *rowwin;
extern std::string filename;
extern std::string string_temp;
extern int edtcur_x, edtcur_y;
extern std::vector<std::vector<char>> file_content;
extern std::vector<char> blankline;
void INSERT()
{
    wmove(filewin, edtcur_y, edtcur_x);
    while (1)
    {
        wmove(infowin, 0, 0);
        for (int k = 0; k < column; k++)
            wprintw(infowin, "%c", ' ');
        getyx(filewin, edtcur_y, edtcur_x);
        wmove(infowin, 0, 0);
        wprintw(infowin, "%c", ' ');
        wprintw(infowin, string_temp.c_str());
        wprintw(infowin, "%c", ' ');
        wprintw(infowin, " LINE:%d COL:%d", cursor_y + 1, cursor_x + 1);
        wprintw(infowin, "%c", ' ');
        wprintw(infowin, "[Insert Mode]");
        wrefresh(infowin);
        wrefresh(cmdwin);
        wrefresh(rowwin);
        wrefresh(filewin);
        int ch = getch();
        if (ch == 27) // quit
        {
            mode = 'n';
            break;
        }
        else if (ch == KEY_UP or ch == KEY_DOWN or ch == KEY_LEFT or ch == KEY_RIGHT) // arrow keys
        {
            cursor(ch, 'i');
        }
        else if (ch == KEY_BACKSPACE) // delete
        {
            if (cursor_x == 0)
            {
                if (cursor_y != 0)
                {
                    if_change = true;
                    if (edtcur_y == 0)
                        edge_row--;
                    cursor_x = file_content[cursor_y - 1].size();
                    for (int i = 0; i < file_content[cursor_y].size(); i++)
                    {
                        file_content[cursor_y - 1].push_back(file_content[cursor_y][i]);
                    }
                    for (int i = 0; i < file_content[cursor_y].size(); i++)
                    {
                        file_content[cursor_y].pop_back();
                    }
                    file_content.erase(file_content.begin() + cursor_y);
                    file_content_row--;
                    cursor_y--;
                    if (cursor_x < edge_column || cursor_x > edge_column + filewin_column)
                        edge_column = cursor_x;
                }
            }
            else if (edtcur_x == 0)
                edge_column--;
            else
            {
                if_change = true;
                file_content[cursor_y].erase(file_content[cursor_y].begin() + cursor_x - 1);
                cursor_x--;
            }
            output("file");
        }
        else if (ch == '\t') // tab
        {
            for (int i = 1; i <= 4; i++)
                write(' ', "file");
        }
        else if (ch == '\n') // new line
        {
            if_change = true;
            pos = std::max(cursor_x, pos);
            file_content.insert(file_content.begin() + cursor_y + 1, blankline);
            int orgline_size = file_content[cursor_y].size();
            for (int i = cursor_x; i < orgline_size; i++)
            {
                file_content[cursor_y + 1].push_back(file_content[cursor_y][i]);
            }
            for (int i = cursor_x; i < orgline_size; i++)
            {
                file_content[cursor_y].pop_back();
            }
            cursor_y++, cursor_x = 0;
            file_content_row++;
            edtcur_y++;
            edtcur_x = 0;
            if (edtcur_y >= filewin_row)
            { 
                edge_row++;
                edtcur_y--;
            }
        
            edge_column = 0;
            output("file");
            wmove(filewin, edtcur_y, edtcur_x);
        }
        else 
        {
            write(ch, "file");
        }
    }
}