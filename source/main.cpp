// Copyright (c) [2023-2024] [Martin King][MT].
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
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


#include <signal.h>
#include <stdlib.h>

#include <chrono>
#include <iostream>
#include <thread>

#include "key-detector/key_detection.h"

static volatile bool kExit = false;

void SignalHandler(int sig) {
  std::cout << "Receive exit signal: " << sig << std::endl;
  kExit = true;
}

void InitSignalHanler(void) {
  signal(SIGINT, SignalHandler);  // Ctrl + c
  signal(SIGTERM, SignalHandler); // kill -15
#ifdef __linux__
  signal(SIGTSTP, SignalHandler); // Ctrl + z (cannot be caught or ignored)
  signal(SIGKILL, SignalHandler); // kill -9 (cannot be caught or ignored)
#endif
}

void ShowUsage(void) {
  std::cout << "========================================\n";
  std::cout << "Keyboard Detection\n";
  std::cout << "========================================\n";
  std::cout << "Usage:\n";
  std::cout << "      q/Q: Exit\n";
  std::cout << "      h/H: Show help\n";
  std::cout << "========================================\n";
}

int main(int argc, char *argv[]) {
  InitSignalHanler();
  KBDetect::InitKeyboard();
  while (!kExit) {
    if (KBDetect::IsKeyboardHit()) {
      char key = KBDetect::ReadCh();
      std::cout << "Input key: " << key << "\t Value: " << static_cast<int>(key)
                << std::endl;
      if (key == 'q' || key == 'Q') {
        break;
      }
      if (static_cast<int>(key) == 3) { // Ctrl + c
        break;
      }
      if (key == 'h' || key == 'H' ||
          static_cast<int>(key) < static_cast<int>('0')) {
        ShowUsage();
      }
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(30));
  }

  KBDetect::CloseKeyboard();
  std::cout << "======= Exit ========\n";
  exit(EXIT_SUCCESS);
}
