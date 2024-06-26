#include "menu.h"

#include <Arduboy2.h>

#include "../constants.h"
#include "../scenes.h"

extern Arduboy2 arduboy;

/* ====== MenuBase ====== */
bool MenuBase::justPressedOnce(uint8_t button) {
  bool pressed = arduboy.justPressed(button);
  if (pressed) arduboy.previousButtonState |= button;
  return pressed;
};

int8_t MenuBase::centerFString(char *str) {
  uint8_t length = strlen_P(str), width = CHAR_WIDTH * length + CHAR_SPACING * (length - 1);

  return (SCREEN_W - width) / 2;
};

void MenuBase::checkEvents() {
  arduboy.pollButtons();

  if (justPressedOnce(B_BUTTON)) scene = (Scene)pgm_read_byte(scenes);
};

void MenuBase::drawTitle(char *title) {
  arduboy.setTextColor(BLACK);

  arduboy.fillRect(0, 0, SCREEN_W, CHAR_HEIGHT + LINE_SPACING * 3);

  int8_t x = centerFString(title);
  arduboy.setCursor(x, 2);

  arduboy.print((FlashString)title);
  arduboy.drawFastHLine(0, CHAR_HEIGHT + LINE_SPACING * 2, SCREEN_W, BLACK);
};

void MenuBase::sceneInit() {
  drawTitle(pgm_read_word(text));
};
void MenuBase::sceneUpdate() {
  checkEvents();
};

/* ====== MenuOptions ====== */
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
  uint8_t page = (choice - 1) / 5;

  for (uint8_t i = page * 5 + 1; i < min(n, (page + 1) * 5 + 1); ++i) {
    arduboy.setTextColor(BLACK);

    int8_t x = centerFString(pgm_read_word(text + i)),
           y = TITLE_OFFSET_Y + (LINE_SPACING + CHAR_HEIGHT) * ((i - 1) % 5);

    if (i == choice) {
      arduboy.setTextColor(WHITE);
      arduboy.fillRect(0, y - LINE_SPACING / 2, SCREEN_W, CHAR_HEIGHT + LINE_SPACING, BLACK);
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

  arduboy.fillScreen();

  drawTitle(pgm_read_word(text));
  drawOptions();

  arduboy.display();
};

/* ====== MenuScore ====== */
void MenuScore::checkEvents() {
  MenuBase::checkEvents();
  if (justPressedOnce(A_BUTTON)) scene = (Scene)pgm_read_byte(scenes);
};

void MenuScore::drawScore() {
  char scoreString[9];

  ultoa(*score, scoreString, 10);
  uint8_t length = strlen(scoreString), width = CHAR_WIDTH * length + CHAR_SPACING * (length - 1);

  uint8_t x = (SCREEN_W - width) / 2,
          y = (SCREEN_H - TITLE_OFFSET_Y - CHAR_HEIGHT) / 2 + TITLE_OFFSET_Y;

  arduboy.setCursor(x, y);
  arduboy.setTextColor(BLACK);
  arduboy.print(scoreString);
};

void MenuScore::sceneInit() {
  arduboy.fillScreen();

  drawTitle(pgm_read_word(text));
  drawScore();

  arduboy.display();
};

void MenuScore::sceneUpdate() {
  checkEvents();
};
