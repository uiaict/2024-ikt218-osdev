#include <libc/stdbool.h>
#include <libc/stdio.h>
#include "common.h"

#define VIDEO_MEMORY_ADDRESS 0xB8000
#define VIDEO_SCREEN_WIDTH 80
#define VIDEO_SCREEN_ROW_END 25
#define VIDEO_SCREEN_BG 0
#define VIDEO_SCREEN_FG 15

// Globals
uint16_t *Video = (uint16_t*)(VIDEO_MEMORY_ADDRESS);
uint16_t Cursor_x = 0, Cursor_y = 0;

// Moves screen cursor ahead
static void monitor_move_cursor()
{
    const uint16_t cursor = Cursor_y * VIDEO_SCREEN_WIDTH + Cursor_x;
    outbyte(0x3D4, 14);          // Tell the VGA board we are setting the high cursor byte.
    outbyte(0x3D5, cursor >> 8); // Send the high cursor byte.
    outbyte(0x3D4, 15);          // Tell the VGA board we are setting the low cursor byte.
    outbyte(0x3D5, cursor);      // Send the low cursor byte.
}

// Get attribute byte with background and foreground colour
static inline uint8_t get_attribute_byte(uint8_t bg, uint8_t fg)
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

void monitor_put(char c)
{
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
        Cursor_x = (Cursor_x + 8) & ~(7);
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
    if (Cursor_x >= VIDEO_SCREEN_WIDTH)
    {
        Cursor_x = 0;
        Cursor_y++;
    }

    monitor_scroll_down();
    monitor_move_cursor();
}

// Clears the screen, by copying lots of spaces to the framebuffer.
void monitor_clear()
{
    const uint8_t attributeByte = get_attribute_byte(VIDEO_SCREEN_BG, VIDEO_SCREEN_FG);
    const uint16_t blank = 0x20 /* space */ | (attributeByte << 8);

    for (int32_t i = 0; i < VIDEO_SCREEN_WIDTH * VIDEO_SCREEN_ROW_END; i++)
    {
        Video[i] = blank;
    }

    // Move the hardware cursor back to the start.
    Cursor_x = 0;
    Cursor_y = 0;
    monitor_move_cursor();
}

void monitor_write(const char *c_str)
{
    while(*c_str != '\0')
    {
        monitor_put(*(c_str++));
    }
}

void monitor_write_hex(uint32_t number)
{
    // uint32 max is 0xFFFFFFFF
    char temp[10] = {};
    int32_t i = 1;

    // Get digits and put them in temp
    while(number != 0)
    {
        const uint8_t digit = number % 16;
        // Add 0 to get ascii number
        temp[i++] = digit < 10 ? digit + '0' : 'A' + (digit - 10);
        number /= 16;
    }

    monitor_put('0');
    monitor_put('x');

    for (size_t j = i; j > 0; j--)
    {
        monitor_put(temp[j]);
    }
}

void monitor_write_udec(uint32_t number)
{
    // uint32 max has at most 10 digits
    char temp[10] = {};
    int32_t i = 1;

    // Get digits and put them in temp
    while(number != 0)
    {
        const uint8_t digit = number % 10;
        // Add 0 to get ascii number
        temp[i++] = digit + '0';
        number /= 10;
    }

    for (size_t j = i; j > 0; j--)
    {
        monitor_put(temp[j]);
    }
}

void monitor_write_sdec(int32_t number)
{
    // int32 max has at most 10 digits + minus sign
    char temp[11] = {};
    int32_t i = 1;

    // Handle negative numbers
    bool isNegative = (number < 0);
    number = abs32(number);

    // Get digits and put them in temp
    while(number != 0)
    {
        const uint8_t digit = number % 10;
        // Add 0 to get ascii number
        temp[i++] = digit + '0';
        number /= 10;
    }

    if(isNegative)
    {
        monitor_put('-');
    }

    for (size_t j = i; j > 0; j--)
    {
        monitor_put(temp[j]);
    }
}

void monitor_write_bool(bool b)
{
    if(b == true)
        monitor_write("true");
    else
        monitor_write("false");
}