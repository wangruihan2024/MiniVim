#include <define.h>
extern WINDOW *cmdwin;
extern std::vector<std::vector<char>> file_content;
extern int file_content_row;
void substitute(std::string from, std::string to)
{
    wmove(cmdwin, 0, 0);
    wrefresh(cmdwin);
    for (int i = 0; i < file_content_row; i++)
    {
        int pos_x = 0; // 记录读入光标的位置
        while (pos_x <= (int)file_content[i].size() - (int)from.size())
        {
            for (int j = pos_x; j < pos_x + (int)from.size(); j++)
            {
                if (file_content[i][j] != from[j - pos_x])
                {
                    pos_x++;
                    break;
                }
                if (j == pos_x + (int)from.size() - 1)
                {
                    for (int k = 0; k < (int)from.size(); k++)
                        file_content[i].erase(file_content[i].begin() + pos_x);
                    for (int k = 0; k < (int)to.size(); k++)
                        file_content[i].insert(file_content[i].begin() + pos_x + k, to[k]);
                    pos_x += to.size();
                    break;
                }
            }
        }
    }
    output("file");
}