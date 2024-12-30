#include <define.h>
extern bool if_close;
extern int row, column, cmd_top, command_size, cmdcur;
extern WINDOW *infowin, *cmdwin;
extern std::vector<char> command;
extern char mode;
void COMMAND() {
    wmove(infowin, 0, 0);
    cmdcur = 0;
    for (int k = 0; k < column; k++)
        wprintw(infowin, "%c", ' ');
    mvwprintw(cmdwin, 0, 0, "%c", '\:');
    for (int k = 1; k < column; k++)
        wprintw(cmdwin, "%c", ' ');
    cmd_top = command_size;
    command.clear();
    wmove(cmdwin, 0, 1);
    while (true)
    {
        mvwprintw(infowin, 0, 0, "[Command Mode]");
        wmove(cmdwin, 0, cmdcur + 1);
        wrefresh(infowin);
        wrefresh(cmdwin);
        int ch = getch();
        if (ch == 27)
        {
            mvwprintw(cmdwin, 0, 0, "%c", ' ');
            int k = column;
            while(k--)
                wprintw(cmdwin, "%c", ' ');
            mode = 'n';
            command.clear();
            output("cmd");
            wrefresh(cmdwin);
            break;
        }
        else if (ch == KEY_LEFT or ch == KEY_RIGHT or ch == KEY_UP or ch == KEY_DOWN)
        {
            cursor(ch, 'c');
        }
        else if (ch == KEY_BACKSPACE)
        {
            if (cmdcur > 0)
            {
                command.erase(command.begin() + cmdcur - 1);
                cmdcur--;
                output("cmd");
                wrefresh(cmdwin);
            }
        }
        else if (ch == '\n')
        {
            mvwprintw(cmdwin, 0, 0, "%c", ' ');
            for (int k = 1; k < column; k++)
                wprintw(cmdwin, "%c", ' ');
            if (command.size() != 0)
                process_command();

            mode = 'n';
            cmdcur = 0;
            command.clear();
            wrefresh(cmdwin);
            break;
        }
        else
        {
            write(ch, "cmd");
        }
    }
}