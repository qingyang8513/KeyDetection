// Copyright 2020
// Created by jin.ma on 2/1062020

#include "./key_detection.h"

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
static struct termios kSettingsPre, kSettingsNew;
static int kPeekedCh = -1;
#endif

namespace KBDetect {

void InitKeyboard(void) {
#ifdef __linux__
  tcgetattr(0, &kSettingsPre);
  kSettingsNew = kSettingsPre;
  kSettingsNew.c_lflag &= ~ICANON;
  kSettingsNew.c_lflag &= ~ECHO;
  kSettingsNew.c_lflag &= ~ISIG;
  kSettingsNew.c_cc[VMIN] = 1;
  kSettingsNew.c_cc[VTIME] = 0;
  tcsetattr(0, TCSANOW, &kSettingsNew);
#endif
}

void CloseKeyboard(void) {
#ifdef __linux__
  tcsetattr(0, TCSANOW, &kSettingsPre);
#endif
}

bool IsKeyboardHit(void) {
#ifdef _WIN32
  return kbhit() > 0;

#elif defined __linux__
  if (kPeekedCh != -1) {
    return true;
  }

  char ch;
  int nread;
  kSettingsNew.c_cc[VMIN] = 0;
  tcsetattr(0, TCSANOW, &kSettingsNew);
  nread = read(0, &ch, 1);
  kSettingsNew.c_cc[VMIN] = 1;
  tcsetattr(0, TCSANOW, &kSettingsNew);

  if (nread == 1) {
    kPeekedCh = ch;
    return true;
  }
  return false;
#else
  return false;
#endif
}

int ReadCh(void) {
#ifdef _WIN32
  return getch();

#elif defined __linux__
  char ch;
  if (kPeekedCh != -1) {
    ch = kPeekedCh;
    kPeekedCh = -1;
    return ch;
  }
  read(0, &ch, 1);
  return ch;

#else
  return -1;
#endif
}

}  // namespace KBDetect
