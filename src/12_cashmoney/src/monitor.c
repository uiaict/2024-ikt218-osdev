#include "monitor.h"

#define VIDEO_MEMORY_ADDRESS 0xB8000
#define VIDEO_SCREEN_WIDTH 80
#define VIDEO_SCREEN_ROW_END 25
#define VIDEO_SCREEN_BG 0
#define VIDEO_SCREEN_FG 15

// Globals
uint16_t *Video = (uint16_t*)(VIDEO_MEMORY_ADDRESS);
uint16_t Cursor_x = 0, Cursor_y = 0;

static void monitor_move_cursor()
{
   const uint16_t cursor = Cursor_y * VIDEO_SCREEN_WIDTH + Cursor_x;
   outbyte(0x3D4, 14);          // Tell the VGA board we are setting the high cursor byte.
   outbyte(0x3D5, cursor >> 8); // Send the high cursor byte.
   outbyte(0x3D4, 15);          // Tell the VGA board we are setting the low cursor byte.
   outbyte(0x3D5, cursor);      // Send the low cursor byte.
}

// Get attribute byte with background and foreground colour
static uint8_t get_attribute_byte(uint8_t bg, uint8_t fg)
{
    return (bg << 4) | (fg & 0x0F);
}

// Scrolls the text on the screen up by one line.
static void monitor_scroll_down()
{
   // Get a space character with the default colour attributes.
   const uint8_t attributeByte = get_attribute_byte(VIDEO_SCREEN_BG, VIDEO_SCREEN_FG);
   const uint16_t blank = 0x20 /* space */ | (attributeByte << 8);

   // Start scroll if we reach the end
   if(Cursor_y >= VIDEO_SCREEN_ROW_END)
   {
       // Move the current text chunk that makes up the screen
       // back in the buffer by a line
       int i;
       for (i = 0; i < (VIDEO_SCREEN_ROW_END - 1) * VIDEO_SCREEN_WIDTH; i++)
       {
           Video[i] = Video[i + VIDEO_SCREEN_WIDTH];
       }

       // The last line should now be blank. Do this by writing
       // 80 spaces to it.
       for (i = (VIDEO_SCREEN_ROW_END - 1) * VIDEO_SCREEN_WIDTH; i < VIDEO_SCREEN_ROW_END * VIDEO_SCREEN_WIDTH; i++)
       {
           Video[i] = blank;
       }
       // The cursor should now be on the last line.
       Cursor_y = VIDEO_SCREEN_ROW_END - 1;
   }
}

// Writes a single character out to the screen.
void monitor_put(char c)
{
   // The attribute byte is made up of two nibbles - the lower being the
   // foreground colour, and the upper the background colour.
   const uint8_t attributeByte = get_attribute_byte(VIDEO_SCREEN_BG, VIDEO_SCREEN_FG);
   // The attribute byte is the top 8 bits of the word we have to send to the
   // VGA board.
   const uint16_t attribute = attributeByte << 8;
   uint16_t *location;

   // Handle a backspace, by moving the cursor back one space
   if (c == 0x08 && Cursor_x)
   {
       Cursor_x--;
   }

   // Handle a tab by increasing the cursor's X, but only to a point
   // where it is divisible by 8.
   else if (c == 0x09)
   {
       Cursor_x = (Cursor_x + 8) & ~(8 - 1);
   }

   // Handle carriage return
   else if (c == '\r')
   {
       Cursor_x = 0;
   }

   // Handle newline by moving cursor back to left and increasing the row
   else if (c == '\n')
   {
       Cursor_x = 0;
       Cursor_y++;
   }
   // Handle any other printable character.
   else if(c >= ' ')
   {
       location = Video + (Cursor_y * VIDEO_SCREEN_WIDTH + Cursor_x);
       *location = c | attribute;
       Cursor_x++;
   }

   // Check if we need to insert a new line because we have reached the end
   // of the screen.
   if (Cursor_x >= 80)
   {
       Cursor_x = 0;
       Cursor_y ++;
   }

   monitor_scroll_down();
   monitor_move_cursor();
}