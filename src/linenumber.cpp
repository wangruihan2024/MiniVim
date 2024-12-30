#include <define.h>
extern int filewin_column, rowwin_row, edge_row, rowwin_column, file_content_row, filewin_row;
extern WINDOW *rowwin;
extern bool scroll_mode;
extern std::vector<std::vector<char>> file_content;
void show_row() {
    for (int i = 0; i < rowwin_row; i++)
    {
        wmove(rowwin, i, 0);
        for (int k = 0; k < rowwin_column; k++)
            wprintw(rowwin, "%c", ' ');
    }
    int temp_line;
    for (int i = 0; i < rowwin_row; i++)
    {
        std::vector<char> line_output({});
        wmove(rowwin, i, 0);
        if (edge_row + i >= file_content_row)
        {
            for (int k = i; k < rowwin_row; k++)
            {
                wmove(rowwin, k, 0);
                wprintw(rowwin, "%c", '~');
            }
            break;
        }
        for (int i = 0; i < rowwin_row; i++) {
            wmove(rowwin, i, 0);
            wprintw(rowwin, "%d", i + edge_row + 1);
        }
    }
}