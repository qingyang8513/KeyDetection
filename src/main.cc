// Copyright 2020
// Created by jin.ma on 2/1062020

#include <signal.h>
#include <stdlib.h>

#include <chrono>
#include <iostream>
#include <thread>

#include "./key_detection.h"

static volatile bool kExit = false;

void SignalHandler(int sig) {
  std::cout << "Receive exit signal: " << sig << std::endl;
  kExit = true;
}

void InitSignalHanler(void) {
  signal(SIGINT, SignalHandler);   // Ctrl + c
  signal(SIGTERM, SignalHandler);  // kill -15
#ifdef __linux__
  signal(SIGTSTP, SignalHandler);  // Ctrl + c (cannot be caught or ignored)
  signal(SIGKILL, SignalHandler);  // kill -9 (cannot be caught or ignored)
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

int main(int argc, char* argv[]) {
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
      if (static_cast<int>(key) == 3) {  // Ctrl + c
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
