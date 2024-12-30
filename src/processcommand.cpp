#include <define.h>
extern int cmd_top, command_size;
extern WINDOW *cmdwin, *filewin;
extern std::vector<COMMANDS> command_history;
extern std::vector<char> command;
extern int cursor_x, cursor_y, edge_row, edge_column, file_content_row;
extern bool if_change, if_close, read_mode, scroll_mode;
void process_command()
{
    COMMANDS new_cmd;
    bool cmd_start = false;
    int k = 0;
    while (command[k] != ' ' && k < command.size())
    {
        new_cmd.cmd.append(std::string(1, command[k]));
        k++;
    }
    for (; k < command.size(); k++)
    {
        if (new_cmd.cmd == "sub")
        {
            if (command[k] == ' ' && !cmd_start)
                continue;
            if (!cmd_start && command[k] == '\"')
                new_cmd.command_count++, cmd_start = true;
            else if (cmd_start && command[k] == '\"')
                cmd_start = false;
        }
        else if (command[k] == ' ')
        {
            new_cmd.command_count++;
            continue;
        }
        new_cmd.command_string[new_cmd.command_count - 1].append(std::string(1, command[k]));
    }
    if (command_size == 0 || (!command.empty() && !(new_cmd == command_history[command_size - 1])))
    {
        command_history.push_back(new_cmd);
        command_size++;
        cmd_top = command_size;
    }
    command.clear();
    wmove(cmdwin, 0, 1);
    output("cmd");

    if (new_cmd.cmd == "w")
    {
        savefile();
    }
    else if (new_cmd.cmd == "q")
    {
        if (!if_change)
            if_close = true;
        else
        {
            wmove(cmdwin, 0, 0);
            wprintw(cmdwin, "the file isn't saved");
        }
    }
    else if (new_cmd.cmd == "q!")
        if_close = true;
    else if (new_cmd.cmd == "wq")
    {
        if (savefile() && !if_change)
            if_close = true;
    }
    else if (new_cmd.cmd == "jmp")
    {
        if (new_cmd.command_count >= 1)
        {
            int linenum = 0;
            for (int i = 0; i < new_cmd.command_string[0].size(); i++)
            {
                linenum *= 10;
                linenum += new_cmd.command_string[0][i] - '0';
            }
            linenum--;
            if (linenum >= 0 && linenum <= file_content_row - 1)
            {
                edge_row = linenum;
                cursor_y = edge_row, cursor_x = 0;
                if (scroll_mode)
                    edge_column = 0;
                output("file");
            }
            else
            {
                wmove(cmdwin, 0, 0);
                wprintw(cmdwin, "the linenumber is invalid");
            }
        }
    }
    else if (new_cmd.cmd == "sub")
    {
        if (new_cmd.command_count >= 2 && new_cmd.command_string[0].size() >= 2 && new_cmd.command_string[1].size() >= 2)
        {
            if (new_cmd.command_string[0][0] == '\"' && new_cmd.command_string[0][new_cmd.command_string[0].size() - 1] == '\"' && new_cmd.command_string[1][0] == '\"' && new_cmd.command_string[1][new_cmd.command_string[1].size() - 1] == '\"')
            {
                std::string str_from, str_to;
                str_from = new_cmd.command_string[0].substr(1, new_cmd.command_string[0].size() - 2);
                str_to = new_cmd.command_string[1].substr(1, new_cmd.command_string[1].size() - 2);
                if (str_from.size() == 0)
                {
                    wmove(cmdwin, 0, 0);
                    wprintw(cmdwin, "the input is invalid");
                }
                else if (!read_mode)
                {
                    if_change = true;
                    substitute(str_from, str_to);
                    wmove(filewin, 0, 0);
                    wmove(cmdwin, 0, 0);
                    wprintw(cmdwin, "substitute successfully");
                    wrefresh(cmdwin);
                    wrefresh(filewin);
                }
                else
                {
                    wmove(cmdwin, 0, 0);
                    wprintw(cmdwin, "file cannot be modified in readonly mode");
                }
            }
            else
            {
                wmove(cmdwin, 0, 0);
                wprintw(cmdwin, "the input is invalid");
            }
        }
        else
        {
            wmove(cmdwin, 0, 0);
            wprintw(cmdwin, "the input is invalid");
        }
    }
}