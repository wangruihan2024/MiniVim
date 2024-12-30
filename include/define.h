
#include <ncurses.h>
#include <unistd.h>
#include <signal.h>

#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <filesystem>

#define FILEWIN_COLOR_NUM 1;
#define INFOWIN_COLOR_NUM 2;

void readin(int argc, char *argv[]);                    // 读入模式和文件名
void initialize();                                      // 初始化窗口并读入文件
void output(std::string win);                           // 显示文件/命令窗口
void NORMAL();                                          // normal模式
void INSERT();                                          // insert模式
void COMMAND();                                         // command模式
void cursor(int keyin, char mode);                      // 箭头键移动光标
bool savefile();                                        // 保存文件
void show_row();                                        // 显示文件行号
void process_command();                                 // 处理command模式下的命令
void write(char ch_temp, std::string win);              // 读入对文件的修改
void substitute(std::string from, std::string to);      // 替换单词
void update_window_size();                              // 更新窗口大小
void handle_winch(int sig);                             // 传入窗口大小改变的信号
bool detectmode(std::string filename);                  // 判断传入的文件是CRLF还是LF格式
std::string extractfilename(std::string filename);      // 提取绝对路径中的文件名

struct COMMANDS
{
    std::string cmd;                                    // 记录当前的command
    std::string command_string[50];                     // 记录之前的command
    int command_count = 0;                              // 记录command_history里面记录的条数
    bool operator==(const COMMANDS &rhs) const {
    return (cmd == rhs.cmd) &&
           (command_count == rhs.command_count) &&
           (command_string == rhs.command_string);
    }
};
