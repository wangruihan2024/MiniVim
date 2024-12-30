#include <define.h>

int row = 15;//总行数
int column = 50;//总列数
int filewin_row;//filewin的行数
int filewin_column;  // filewin的列数
int rowwin_column = 3;//行号列的列数
int rowwin_row;//行号列的行数

int file_content_row = 0; // 文件里面的内容占的行数
int command_size = 0;//一共有多少个指令行

int edge_row = 0, edge_column = 0; // 记录边框从哪一行列开始显示

int cursor_x, cursor_y, edtcur_x, edtcur_y, cmdcur;
int pos = 0, cmd_top;

char mode = 'n'; // i, n, c
char ch = 0;

bool read_mode = false;
bool truncate_mode = false;
bool scroll_mode = true;//scroll_mode=true时scroll false=break
bool file_exist = false; // if the file exists
bool if_close = false;//true->end the process
bool if_change = false;//是否做出了修改
bool if_CRLF = false;//是否要用\r\n换行

std::vector<COMMANDS> command_history;
std::vector<std::vector<char>> file_content; // 储存打开的文件的内容
std::vector<char> blankline = {};//空行
std::vector<char> command;//在cmdwin中的命令行


WINDOW *filewin;
WINDOW *infowin;
WINDOW *cmdwin;
WINDOW *rowwin;

std::string filename;
std::string string_temp;

int main(int argc, char *argv[])
{
    readin(argc, argv);
    initscr(); 
    // if(filename[0] = 'b')
    //     if_CRLF = true;
    initialize();
    signal(SIGWINCH, handle_winch);
    wmove(infowin, 0, 0);
    wrefresh(infowin);
    output("file");
    int ch = 0;
    while (!if_close)
    {
        if (mode == 'n')
        {
            NORMAL();
        }
        else if (mode == 'c')
        {
            COMMAND();
        }
        else if (mode == 'i')
        {
            INSERT();
        }
    }

    delwin(filewin);
    delwin(rowwin);
    delwin(infowin);
    delwin(cmdwin);
    endwin(); 
    return 0;
}