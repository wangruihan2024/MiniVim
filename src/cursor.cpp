#include <define.h>
extern WINDOW *filewin, *cmdwin, *infowin;
extern int cursor_x, cursor_y, cmdcur, cmd_top, pos, edge_row, edge_column, file_content_row, filewin_column, filewin_row;
extern std::vector<char> command;
extern int command_size;
extern std::vector<std::vector<char>> file_content;
extern std::vector<COMMANDS> command_history;
void cursor(int keyin, char mode)
{
    if(mode == 'n' || mode == 'i') {
        if(keyin == KEY_UP) {
            pos = std::max(cursor_x, pos);
            if(cursor_y == edge_row)
                edge_row = std::max(edge_row - 1, 0);
            cursor_y = std::max(cursor_y - 1, 0);
            cursor_x = std::min(pos, (int)file_content[cursor_y].size());
            if(cursor_x < edge_column || cursor_x > (edge_column + filewin_column))
                edge_column = cursor_x;
            if(mode == 'n' && cursor_x == (int)file_content[cursor_y].size() && cursor_x != 0)
                cursor_x--;
            output("file");
        }
        else if (keyin == KEY_DOWN)
        {
            if(cursor_y + 1 < file_content_row) {
                pos = std::max(pos, cursor_x);
                cursor_y = std::min(file_content_row, cursor_y + 1);
                cursor_x = std::min(pos, (int)file_content[cursor_y].size());
                if(cursor_x < edge_column || cursor_x > edge_column + filewin_column)
                    edge_column = cursor_x;
                if(cursor_y == edge_row + filewin_row)
                    edge_row++;    
            }
            wrefresh(infowin);
            if(mode == 'n' && cursor_x == (int)file_content[cursor_y].size() && cursor_x != 0)
                cursor_x--;
            output("file");
        }
        else if (keyin == KEY_LEFT)
        {
            if(cursor_x != 0) {
                if(cursor_x - edge_column == 0)
                    edge_column--;
                else
                    cursor_x--;
                if(mode == 'n' && cursor_x == (int)file_content[cursor_y].size() && cursor_x != 0)
                    cursor_x--;
            }
            output("file");
            pos = cursor_x;
            wmove(filewin, cursor_y - edge_row, cursor_x - edge_column);
            wrefresh(filewin);
        }
        else if (keyin == KEY_RIGHT)
        {
            if(cursor_x != file_content[cursor_y].size()) {
                if(cursor_x - edge_column >= filewin_column)
                    edge_column++;
                else
                    cursor_x++;
            }
            if(mode == 'n' && cursor_x == (int)file_content[cursor_y].size() && cursor_x != 0)
                cursor_x--;
            output("file");
            pos = cursor_x;
            wmove(filewin, cursor_y - edge_row, cursor_x - edge_column);
        }
        wrefresh(filewin);
    }
    else if (mode == 'c')
    {
        if(keyin == KEY_LEFT) {
            cmdcur = std::max(0, cmdcur - 1);
            wmove(cmdwin, 0, cmdcur);
        }else if(keyin == KEY_RIGHT) {
            cmdcur = std::min((int)command.size(), cmdcur + 1);
            wmove(cmdwin, 0, cmdcur + 1);
        }
        else if(keyin == KEY_UP)
        {
            command.clear();
            if (command_history.size() == 0)
                return;
            cmd_top = std::max(0, cmd_top - 1);
            for (int i = 0; i < command_history[cmd_top].cmd.size(); i++)
            {
                command.push_back(command_history[cmd_top].cmd[i]);
            }
            for (int i = 0; i < command_history[cmd_top].command_count; i++)
            {
                command.push_back(' ');
                for (int k = 0; k < command_history[cmd_top].command_string[i].size(); k++)
                {
                    command.push_back(command_history[cmd_top].command_string[i][k]);
                }
            }
            cmdcur = command.size();
            output("cmd");
        }else if(keyin == KEY_DOWN) {
            command.clear();
            cmd_top = std::min(command_size, cmd_top + 1);
            if (cmd_top != command_size)
            {
                for (int i = 0; i < command_history[cmd_top].cmd.size(); i++)
                {
                    command.push_back(command_history[cmd_top].cmd[i]);
                }
                for (int i = 0; i < command_history[cmd_top].command_count; i++)
                {
                    command.push_back(' ');
                    for (int k = 0; k < command_history[cmd_top].command_string[i].size(); k++)
                    {
                        command.push_back(command_history[cmd_top].command_string[i][k]);
                    }
                }
            }
            else
            {
                command.clear();
            }
            cmdcur = command.size();
            output("cmd");
        }
    }
}