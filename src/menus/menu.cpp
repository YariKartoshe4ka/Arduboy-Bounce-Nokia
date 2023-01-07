#include "menu.h"

#include <Arduboy2.h>

#include "../constants.h"
#include "../scenes.h"

extern Arduboy2 arduboy;

/* Font constants */
#define CHAR_WIDTH 5
#define CHAR_HEIGHT 8
#define CHAR_SPACING 1
#define LINE_SPACING 2

#define N pgm_read_byte(n)

bool Menu::justPressedOnce(uint8_t button) {
  bool pressed = arduboy.justPressed(button);
  if (pressed) arduboy.previousButtonState |= button;
  return pressed;
};

int8_t Menu::centerFString(const char *str) {
  uint8_t length = strlen_P(str), width = CHAR_WIDTH * length + CHAR_SPACING * (length - 1);

  return (SCREEN_W - width) / 2;
};

void Menu::checkEvents() {
  arduboy.pollButtons();

  if (justPressedOnce(DOWN_BUTTON)) {
    choice = (choice == N - 1 ? 0 : choice + 1);
  } else if (justPressedOnce(UP_BUTTON)) {
    choice = (choice == 0 ? N : choice) - 1;
  } else if (justPressedOnce(A_BUTTON)) choiceCallback();
};

void Menu::choiceCallback() {
  scene = pgm_read_byte(scenes + choice);
};

void Menu::drawTitle() {
  arduboy.setTextColor(WHITE);

  arduboy.fillRect(0, 0, SCREEN_W, CHAR_HEIGHT + LINE_SPACING * 3, BLACK);

  int8_t x = centerFString(title);
  arduboy.setCursor(x, 2);

  arduboy.print((FlashString)title);
  arduboy.drawFastHLine(0, CHAR_HEIGHT + LINE_SPACING * 2, SCREEN_W);
};

void Menu::drawOptions() {
  int8_t TITLE_OFFSET_Y = CHAR_HEIGHT + LINE_SPACING * 3 + 1;

  for (uint8_t i = 0; i < N; ++i) {
    arduboy.setTextColor(WHITE);

    int8_t x = centerFString(pgm_read_word(text + i)),
           y = TITLE_OFFSET_Y + (LINE_SPACING + CHAR_HEIGHT) * i;

    if (i == choice) {
      arduboy.setTextColor(BLACK);
      arduboy.fillRect(0, y - LINE_SPACING / 2, SCREEN_W, CHAR_HEIGHT + LINE_SPACING);
    }

    arduboy.setCursor(x, y);
    arduboy.print((FlashString)pgm_read_word(text + i));
  }
};

void Menu::sceneInit() {
  choice = 0;
  prevChoice = -1;
};

void Menu::sceneUpdate() {
  checkEvents();

  if (prevChoice == choice) return;
  prevChoice = choice;

  arduboy.clear();

  drawTitle();
  drawOptions();

  arduboy.display();
};
