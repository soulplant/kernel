#ifndef SCREEN_H_
#define SCREEN_H_

class Screen {
 public:
  Screen();
  Screen(char* memory);

  void PrintChar(char c);
  void Clear();

 private:
  char* memory_;
  int x_;
};

Screen* g_screen();

#endif  // SCREEN_H_
