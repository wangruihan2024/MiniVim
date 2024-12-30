#include <define.h>
extern int filewin_row, row, column, rowwin_column, filewin_column, rowwin_row;
extern WINDOW *filewin, *infowin, *cmdwin, *rowwin;
extern bool truncate_mode, file_exist, if_CRLF;
extern std::string filename;
extern std::string string_temp;
extern std::vector<std::vector<char>> file_content;
extern int file_content_row;
extern std::vector<char> blankline;
void initialize()
{
    filewin_row = row - 2;
    filewin_column = column - 3;
    rowwin_row = row - 2;
    rowwin_column = 3;

    initscr();
    raw();
    noecho(); 
    curs_set(2);
    keypad(stdscr, true);

    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_BLACK,COLOR_CYAN);

    filewin = newwin(filewin_row, filewin_column, 0, rowwin_column + 1);
    infowin = newwin(1, column, rowwin_row + 1, 0);
    cmdwin = newwin(1, column, rowwin_row + 2, 0);
    rowwin = newwin(rowwin_row, rowwin_column, 0, 0);

    wbkgd(filewin, COLOR_PAIR(1));
    wbkgd(infowin, COLOR_PAIR(2));
    wbkgd(cmdwin, COLOR_PAIR(1));
    wbkgd(rowwin, COLOR_PAIR(1));
    wbkgd(stdscr, COLOR_PAIR(1));
    
    refresh();
    wrefresh(filewin);
    wrefresh(infowin);
    wrefresh(cmdwin);
    wrefresh(rowwin);
    
    keypad(filewin, true);
    keypad(infowin, true);
    keypad(cmdwin, true);
    keypad(rowwin, true);

    if_CRLF = detectmode(filename);
   

    file_content.push_back(blankline);
    file_content_row++;
    if (truncate_mode || !file_exist)
        return;
    std::ifstream freader(filename);
    if(freader.fail())
        return;
    char c = 0;
    while(!freader.eof()) {
        freader.get(c);
        if(!freader)
            break;
        if(c == '\t') {
            for (int k = 0; k < 4; k++)
                file_content[file_content_row - 1].push_back(' ');
        }else if(c == '\n' && !if_CRLF) {
            file_content_row++;
            file_content.push_back(blankline);
        }else if(c == '\r' && if_CRLF) {
            if (freader.peek() == '\n') {
            freader.get(); 
            file_content_row++;
            file_content.push_back(blankline);
            } else {
            file_content[file_content_row - 1].push_back(c);
            }
        }else {
            file_content[file_content_row - 1].push_back(c);
        }
    }
    freader.close();
    string_temp = extractfilename(filename);
    wmove(infowin, 0, 0);
    wprintw(infowin, "the information has been recorded");
    wrefresh(infowin);
    output("file");
}
