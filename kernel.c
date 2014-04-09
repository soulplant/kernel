char* video = (char*) 0xb8000;
void kmain() {
  video[0] = 'x';
  video[2] = 'y';
  video[4] = 'z';
  while (1);
}
