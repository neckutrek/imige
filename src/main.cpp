#include <iostream>
#include <boost/asio.hpp>
#include <ncurses.h>

int main(int argc, char* argv[])
{
   initscr();
   noecho();
   printw("Hello World!");
   refresh();
   getch();
   endwin();
   return 0;
}
