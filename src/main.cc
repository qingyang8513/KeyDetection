// Copyright 2020
// Created by jin.ma on 2/1062020

#include <stdlib.h>

#include <chrono>
#include <iostream>
#include <thread>

#include "./key_detection.h"

int main(int argc, char* argv[]) {
  KBDetect::InitKeyboard();

  while (1) {
    if (KBDetect::IsKeyboardHit()) {
      char key = KBDetect::ReadCh();
      std::cout << "Input key value: " << key << std::endl;
      if (key == 'q') {
        break;
      }
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }

  KBDetect::CloseKeyboard();
  std::cout << "======= Exit ========\n";
  exit(EXIT_SUCCESS);
}
