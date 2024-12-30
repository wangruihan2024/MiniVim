#include <define.h>
extern int row, column;
extern int filewin_row, filewin_column, rowwin_row, rowwin_column;
extern int cursor_x, cursor_y, edge_row;
extern std::vector<std::vector<char>> file_content; 
extern WINDOW *filewin, *rowwin, *infowin, *cmdwin;
void update_window_size()
{
    endwin();
    refresh();
    clear();
    int new_row, new_column;
    getmaxyx(stdscr, new_row, new_column);
    row = new_row;
    column = new_column;
    filewin_row = row - 2;
    filewin_column = column - 3;
    rowwin_row = row - 2;
    rowwin_column = 3;

    wresize(filewin, filewin_row, filewin_column);
    wresize(rowwin, rowwin_row, rowwin_column);
    wresize(infowin, 1, column);
    wresize(cmdwin, 1, column);

    mvwin(filewin, 0, rowwin_column + 1);
    mvwin(rowwin, 0, 0);
    mvwin(infowin, rowwin_row + 1, 0);
    mvwin(cmdwin, rowwin_row + 2, 0);

    if(cursor_y < edge_row)
        edge_row = cursor_y;
    else if(cursor_y >= edge_row + filewin_row)
        edge_row = cursor_y - filewin_row + 1;
    edge_row = std::max(0, std::min(edge_row, (int)file_content.size() - filewin_row));

    output("file");
    wrefresh(filewin);
    wrefresh(rowwin);
    wrefresh(infowin);
    wrefresh(cmdwin);
}
void handle_winch(int sig) {
    update_window_size();
}
