#include "storage.h"

#include <Arduboy2Ex.h>
#include <EEPROM.h>

#include "constants.h"

uint32_t storage_highScore;

void storageInit() {
  EEPROM.get(EEPROM_HIGH_SCORE, storage_highScore);
  if (storage_highScore == (uint32_t)-1) {
    storage_highScore = 0;
    EEPROM.put(EEPROM_HIGH_SCORE, storage_highScore);
  }
};

void storageUpdateHighScore(uint32_t highScore) {
  if (highScore > storage_highScore) {
    storage_highScore = highScore;
    EEPROM.write(EEPROM_HIGH_SCORE, storage_highScore);
  }
};

#if 0
uint32_t storage_HighScore = 0;

const uint8_t STORAGE_LAYOUT[] PROGMEM = {4};
const uint8_t STORAGE_DEFAULT[] PROGMEM = {  //
  0x00, 0x00, 0x00, 0x00  /* high score */
};
const uint8_t STORAGE_LENGTH PROGMEM = sizeof(STORAGE_LAYOUT) / sizeof(STORAGE_LAYOUT[0]);


void storageInit() {
  uint16_t baseInc = 0;
  for (uint8_t i = 0; i < STORAGE_LENGTH; ++i) {
    uint8_t data = 0xff;

    for (uint8_t j = 0; j < pgm_read_byte(&STORAGE_LAYOUT[i]); ++j) {
      ++baseInc;
      data &= EEPROM.read(EEPROM_BASE + baseInc);
    }

    if (data == 0xff) {
      baseInc -= pgm_read_byte(&STORAGE_LAYOUT[i]);

      for (uint8_t j = 0; j < pgm_read_byte(&STORAGE_LAYOUT[i]); ++j) {
        ++baseInc;
        EEPROM.write(EEPROM_BASE + baseInc, pgm_read_byte(&STORAGE_DEFAULT[baseInc]));
      }
    }
  }
};
#endif
