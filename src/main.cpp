#include <iostream>
#include <memory>
#include <thread>
#include <functional>

#include <boost/asio.hpp>

#include <ncurses.h>

void listenKeyboard(boost::asio::io_context& ioService)
{
  bool run = true;
  while (run)
  {
    int key = getch();
    auto pkey = std::make_shared<int>(key);
    auto completion = [pkey, &ioService]() -> void {
      const char c[] = {static_cast<char>(*pkey), '\0'};
      printw(c);
      if (c[0] == 'q') ioService.stop();
    };
    ioService.dispatch(completion);
    run = (key != 'q');
  }
}

int main(int argc, char* argv[])
{
  initscr();
  noecho();
  printw("Hello World!");
  refresh();

  boost::asio::io_context ioService;
  std::thread t1(listenKeyboard, std::ref(ioService));

  auto work = std::make_shared<boost::asio::io_context::work>(ioService);
  ioService.run();
  t1.join();

  endwin();
  return 0;
}

