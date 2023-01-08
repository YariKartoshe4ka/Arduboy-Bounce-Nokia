#pragma once

#include <Arduboy2.h>

typedef const __FlashStringHelper *FlashString;

class Menu {
 private:
  uint8_t prevChoice = -1;

  const uint8_t *n;
  const char *title, **text;
  const uint8_t *scenes;

  bool justPressedOnce(uint8_t button);
  int8_t centerFString(const char *str);

 protected:
  void checkEvents();
  void choiceCallback();
  void drawTitle();
  void drawOptions();

 public:
  uint8_t choice = 0;

  Menu() = default;
  Menu(const uint8_t *n, const char *title, const char **text, const uint8_t *scenes)
      : n(n), title(title), text(text), scenes(scenes){};

  void sceneInit();
  void sceneUpdate();
};
