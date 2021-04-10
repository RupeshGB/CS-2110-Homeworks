#include "main.h"

#include <stdio.h>
#include <stdlib.h>

#include "gba.h"
#include "images/End.h"
#include "images/Start.h"
#include "images/RAM.h"
#include "images/PC.h"

/* TODO: */
// Add any additional states you need for your app. You are not requried to use
// these specific provided states.
enum gba_state {
  START,
  PLAY,
  WIN,
};

int main(void) {
  /* TODO: */
  // Manipulate REG_DISPCNT here to set Mode 3. //

  REG_DISPCNT = MODE3 | BG2_ENABLE;

  // Save current and previous state of button input.
  u32 previousButtons = BUTTONS;
  u32 currentButtons = BUTTONS;

  // Load initial application state
  enum gba_state state = START;

  struct position pcObj = {160 - PC_HEIGHT, 0};
  const struct position ramObj = {(160 - RAM_HEIGHT) / 2, 240 - RAM_WIDTH};

  int time = 0;

  char arr[20];

  // char *s = "Score: ";
  // char *num = time;


  while (1) {
    currentButtons = BUTTONS; // Load the current state of the buttons

    /* TODO: */
    // Manipulate the state machine below as needed //
    // NOTE: Call waitFoVBlank() before you draw

    waitForVBlank();

    
    

    switch (state) {
      case START:
        drawImageDMA(0, 0, 240, 160, Start);
        //drawFullScreenImageDMA(Start);
        if (KEY_JUST_PRESSED(BUTTON_START, currentButtons, previousButtons)) {
          fillScreenDMA(BLACK);
          vBlankCounter = 0;
          state = PLAY;
        }
        // state = ?
        break;
      case PLAY:

        snprintf(arr, 20, "Score: %d", time);

        drawString(0, 0, arr, BLACK);

        time = vBlankCounter / 60;

        snprintf(arr, 20, "Score: %d", time);

        drawString(0, 0, arr, WHITE);

        drawRectDMA(pcObj.col, pcObj.row, PC_WIDTH, PC_HEIGHT, BLACK);

        if (KEY_DOWN(BUTTON_RIGHT, currentButtons)) {

          pcObj.row++;
        }
        if (KEY_DOWN(BUTTON_LEFT, currentButtons)) {
          if (pcObj.row > 0) {
            pcObj.row--;
          }
        }
        if (KEY_DOWN(BUTTON_UP, currentButtons)) {
          if (pcObj.col > 0) {
            pcObj.col--;
          }
        }
        if (KEY_DOWN(BUTTON_DOWN, currentButtons)) {
          if (pcObj.col < 160 - PC_HEIGHT) {
            pcObj.col++;
          }
        }

        if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)) {
          state = START;
          pcObj.col = 160 - PC_HEIGHT;
          pcObj.row = 0;
          vBlankCounter = 0;
        }
        if (pcObj.row + PC_WIDTH == ramObj.row) {
          state = WIN;
        }

        drawImageDMA(pcObj.col, pcObj.row, PC_WIDTH, PC_HEIGHT, PC);
        drawRectDMA(0, 240 - RAM_WIDTH, RAM_WIDTH, 160, RED);
        drawImageDMA(ramObj.col, ramObj.row, RAM_WIDTH, RAM_HEIGHT, RAM);
        

        // state = ?
        if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)) {
          state = START;
          pcObj.col = 160 - PC_HEIGHT;
          pcObj.row = 0;
          vBlankCounter = 0;
        }
        break;
      case WIN:
        drawFullScreenImageDMA(End);

        //char arr[20];

        snprintf(arr, 20, "Score: %d", time);

        drawString(100, 0, arr, BLACK);

        // *num = time;
        // drawString(0, 0, s, BLACK);
        // drawString(0, 50, num, BLACK);

        // state = ?
        if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)) {
          state = START;
          pcObj.col = 160 - PC_HEIGHT;
          pcObj.row = 0;
          vBlankCounter = 0;
        }
        break;
    }

    previousButtons = currentButtons; // Store the current state of the buttons
  }

  return 0;
}