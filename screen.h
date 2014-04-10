#ifndef SCREEN_H_
#define SCREEN_H_

class Screen {
 public:
  Screen();
  Screen(char* memory);
  const int kScreenWidth = 80;
  const int kScreenHeight = 24;

  void PrintChar(char c);
  void Clear();
  void ScrollUp();

 private:
  char* memory_;
  int x_;
  int y_;
};

Screen* g_screen();

#endif  // SCREEN_H_
