#include "menu.h"

#include <Arduboy2Ex.h>

#include "../constants.h"
#include "../scenes.h"

extern Arduboy2Ex arduboy;

bool MenuBase::justPressedOnce(uint8_t button) {
  bool pressed = arduboy.justPressed(button);
  if (pressed) arduboy.previousButtonState |= button;
  return pressed;
};

int8_t MenuBase::centerFString(const char *str) {
  uint8_t length = strlen_P(str), width = CHAR_WIDTH * length + CHAR_SPACING * (length - 1);

  return (SCREEN_W - width) / 2;
};

void MenuBase::checkEvents() {
  arduboy.pollButtons();

  if (justPressedOnce(B_BUTTON)) scene = (Scene)pgm_read_byte(scenes);
};

void MenuBase::drawTitle() {
  arduboy.setTextColor(WHITE);

  arduboy.fillRect(0, 0, SCREEN_W, CHAR_HEIGHT + LINE_SPACING * 3, BLACK);

  int8_t x = centerFString(pgm_read_word(text));
  arduboy.setCursor(x, 2);

  arduboy.print((FlashString)pgm_read_word(text));
  arduboy.drawFastHLine(0, CHAR_HEIGHT + LINE_SPACING * 2, SCREEN_W);
};

void MenuBase::sceneInit() {
  drawTitle();
};
void MenuBase::sceneUpdate() {
  checkEvents();
};

void MenuOptions::checkEvents() {
  MenuBase::checkEvents();

  if (justPressedOnce(DOWN_BUTTON)) {
    choice = (choice == n - 1 ? 1 : choice + 1);
  } else if (justPressedOnce(UP_BUTTON)) {
    choice = (choice == 1 ? n - 1 : choice - 1);
  }

  if (justPressedOnce(A_BUTTON)) choiceCallback();
};

void MenuOptions::choiceCallback() {
  scene = (Scene)pgm_read_byte(scenes + choice);
};

void MenuOptions::drawOptions() {
  for (uint8_t i = 1; i < n; ++i) {
    arduboy.setTextColor(WHITE);

    int8_t x = centerFString(pgm_read_word(text + i)),
           y = TITLE_OFFSET_Y + (LINE_SPACING + CHAR_HEIGHT) * (i - 1);

    if (i == choice) {
      arduboy.setTextColor(BLACK);
      arduboy.fillRect(0, y - LINE_SPACING / 2, SCREEN_W, CHAR_HEIGHT + LINE_SPACING);
    }

    arduboy.setCursor(x, y);
    arduboy.print((FlashString)pgm_read_word(text + i));
  }
};

void MenuOptions::sceneInit() {
  choice = 1;
  prevChoice = 0;
};

void MenuOptions::sceneUpdate() {
  checkEvents();

  if (prevChoice == choice) return;
  prevChoice = choice;

  arduboy.clear();

  drawTitle();
  drawOptions();

  arduboy.display();
};
