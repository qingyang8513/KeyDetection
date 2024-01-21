// Copyright (c) [2023-2024] [Martin King][MT].
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
// @author MT
// @date   2024-01-21

#include "key-detector/key_detection.h"

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

} // namespace KBDetect
