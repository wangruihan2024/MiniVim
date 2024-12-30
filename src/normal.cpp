#include <define.h>
extern std::vector<std::vector<char>> file_content;
extern std::vector<char> blankline;
extern int cursor_x, cursor_y, filewin_row, edge_row, edge_column, column, file_content_row, filewin_column;
extern bool if_close, read_mode, scroll_mode;
extern char mode;
extern int edtcur_x, edtcur_y;
extern WINDOW *infowin, *filewin, *rowwin, *cmdwin;
extern std::string filename;
extern std::string string_temp;
void NORMAL()
{
    if (cursor_x == (int)file_content[cursor_y].size() && cursor_x != 0)
        cursor_x--;
    output("file"); 
    bool if_dd = false;
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
        wprintw(infowin, "[NORMAL MODE]");

        wrefresh(infowin);
        wrefresh(cmdwin);
        wrefresh(rowwin);
        wrefresh(filewin);

        int ch = getch();
        if (ch == ':') 
        {
            if_dd = false;
            mode = 'c';
            break;
        }
        else if (ch == 'i' && !read_mode) 
        {
            if_dd = false;
            mode = 'i';
            break;
        }
        else if (ch == 27)
        {
            if_dd = false;
            if_close = true;
            break;
        }
        else if (ch == KEY_UP or ch == KEY_DOWN or ch == KEY_LEFT or ch == KEY_RIGHT)
        {
            if_dd = false;
            cursor(ch, 'n');
        }
        else if (ch == '0')
        {
            if_dd = false;
            while (cursor_x != 0)
            {
                cursor(KEY_LEFT, 'n');
            }
            output("file");
        }
        else if (ch == '$')
        {
            if_dd = false;
            int end = std::max((int)file_content[cursor_y].size() - 1, 0);
            while (cursor_x != end)
                cursor(KEY_RIGHT, 'n');
            output("file");
        }
        else if (ch == 'b')
        {
            if_dd = false;
            if (cursor_x == 0 && cursor_y != 0 && ! scroll_mode)
            {
                cursor_y--;
                cursor_x = std::max((int)file_content[cursor_y].size() - 1, 0);
                if (edtcur_y == 0)
                    edge_row--;
                output("file");
            }
            else
            {
                if (scroll_mode && cursor_y != 0 && cursor_x == 0)
                {
                    cursor_x = file_content[cursor_y - 1].size();
                    if (cursor_x < edge_column or cursor_x > edge_column + filewin_column)
                        edge_column = cursor_x;
                    cursor_y--;
                }
                bool start_word = false;
                while (true)
                {
                    if (cursor_x == 0)
                        break;
                    if (!start_word && file_content[cursor_y][cursor_x - 1] != ' ')
                        start_word = true;
                    else if (start_word && file_content[cursor_y][cursor_x - 1] == ' ')
                        break;
                    cursor(KEY_LEFT, 'n');
                }
            }
        }
        else if (ch == 'w')
        {
            if_dd = false;
            bool start_word = false;
            if (file_content[cursor_y].size() == 0 && cursor_x == 0)
            {
                cursor_y++, cursor_x = 0;
                if (edtcur_y == filewin_row - 1)
                    edge_row++;
                output("file");
            }
            else
            {
                while (true)
                {
                    if (cursor_x == file_content[cursor_y].size() - 1)
                    {
                        if (cursor_y != file_content_row - 1)
                        {
                            cursor_y++, cursor_x = 0;
                            edge_column = 0;
                        }
                        output("file");
                        break;
                    }
                    if (!start_word && file_content[cursor_y][cursor_x] == ' ')
                        start_word = true;
                    else if (start_word && file_content[cursor_y][cursor_x] != ' ')
                        break;
                    cursor(KEY_RIGHT, 'n');
                }
            }
        }
        else if (ch == 'd' && !read_mode)
        {
            if (if_dd == false)
                if_dd = true;
            else
            {
                if_dd = false;
                if (cursor_y == edge_row)
                {
                    edge_column = 0;
                    cursor_x = 0;
                }
                if (cursor_y == file_content_row - 1)
                {
                    if (!! scroll_mode)
                    {
                        edge_column = 0;
                    }
                    if (cursor_y == edge_row)
                        edge_row = std::max(0, cursor_y - 1);
                    file_content.erase(file_content.begin() + cursor_y);
                    file_content_row--;
                    cursor_y--;
                    if (file_content_row == 0)
                        file_content.push_back(blankline), cursor_y = 0, cursor_x = 0, file_content_row++;
                    output("file");
                }
                else
                {
                    if (scroll_mode)
                        edge_column = 0;
                    file_content.erase(file_content.begin() + cursor_y);
                    file_content_row--;
                    cursor_x = 0;
                    output("file");
                }
            }
        }
    }
}
