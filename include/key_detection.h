// Copyright 2020
// Created by jin.ma on 2/1062020

#ifndef KEY_DETECTION_H_
#define KEY_DETECTION_H_

namespace KBDetect {

void InitKeyboard(void);

void CloseKeyboard(void);

bool IsKeyboardHit(void);

int ReadCh(void);

}  // namespace KBDetect

#endif  // KEY_DETECTION_H_
