#include <unistd.h>

#include <chrono>
#include <iostream>
#include <thread>

using namespace std::chrono_literals;

enum colors { RED = 31, GREEN = 32, YELLOW = 33, NO_COLOR = 0 };

void set_color(int textColor) { std::cout << "\033[" << textColor << "m"; }

void out() { std::cout << "0" << std::endl; }

void change_state_pedestrian(bool is_cur_red, int seconds) {
  system("clear");
  set_color(NO_COLOR);
  std::cout << "pedestrian:\ntime: " << seconds << std::endl;
  if (is_cur_red) {
    set_color(NO_COLOR);
    out();
    set_color(GREEN);
    out();

  } else {
    set_color(RED);
    out();
    set_color(NO_COLOR);
    out();
  }
}

/**
 *@param cur_color  переменная отвеччает за цвет светофора 1 - red, 2 - yellow,
 *3 - red+yellow, 0 - green
 *
 */
void change_state_auto(int cur_color, int seconds) {
  set_color(NO_COLOR);
  std::cout << "auto:\ntime: " << seconds << std::endl;
  if (cur_color == 1) {
    set_color(RED);
    out();
    set_color(NO_COLOR);
    out();
    out();

  } else if (cur_color == 2) {
    set_color(NO_COLOR);
    out();
    set_color(YELLOW);
    out();
    set_color(NO_COLOR);
    out();
  } else if (cur_color == 3) {
    set_color(RED);
    out();
    set_color(YELLOW);
    out();
    set_color(NO_COLOR);
    out();
  } else if (cur_color == 0) {
    set_color(NO_COLOR);
    out();
    set_color(NO_COLOR);
    out();
    set_color(GREEN);
    out();
  }
  set_color(NO_COLOR);
}

bool is_cur_red(int var) { return var % 2; }

void timer(int seconds, int state) {
  for (int i = 0; i < seconds; i++) {
    change_state_pedestrian(state, i);
    change_state_auto(state, i);
    std::this_thread::sleep_for(1000ms);
  }
  state += 2;
  change_state_pedestrian(0, seconds + 1);
  change_state_auto(state, 1);
  std::this_thread::sleep_for(1000ms);
  change_state_pedestrian(0, seconds + 2);
  change_state_auto(state, 2);
  std::this_thread::sleep_for(1000ms);
  change_state_pedestrian(0, seconds + 3);
  change_state_auto(state, 3);
  std::this_thread::sleep_for(1000ms);
}

int main() {
  long long helper = 0;  // разное время на зелёный и красный
  while (1) {
    if (is_cur_red(helper)) {
      timer(5, 1);
    } else {
      timer(10, 0);
    }
    helper++;
  }
  return 0;
}