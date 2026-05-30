/**
 * @brief It defines the libscreen interface
 *
 * @file libscreen.h
 * @author José Miguel Romero Oubiña
 * @version 1.2
 * @date 8-05-2026
 * @copyright GNU Public License
 */

#ifndef __LIBSCREEN_H
#define __LIBSCREEN_H

/**
 * @brief Color of the background frame
 */
typedef enum {
  BLACK = 0, /**< Black color */
  RED   = 1, /**< Red color */
  GREEN = 2, /**< Green color */
  YELLOW = 3, /**< Yellow color */
  BLUE = 4, /**< Blue color */
  PURPLE = 5, /**< Purple color */
  CYAN = 6, /**< Cyan color */
  WHITE = 7 /**< White color */
} Frame_color;

/**
 * @brief Color attribute constants for use with screen_area_puts_bold_color_at.
 */
typedef enum {
  COLOR_ATTR_NONE = 0, /**< No special color attribute (normal style) */
  COLOR_ATTR_BOLD = 1, /**< Bold style (bold black on white) */
  COLOR_ATTR_BOLD_BLUE = 2, /**< Bold blue style */
  COLOR_ATTR_BOLD_GREEN = 3, /**< Bold green style */
  COLOR_ATTR_BOLD_RED = 4, /**< Bold red style */
  COLOR_ATTR_BOLD_YELLOW = 5  /**< Bold yellow style */
} Color_attr;

/**
 * @brief Opaque type representing a screen area
 */
typedef struct _Area Area;

/**
 * @brief Initializes the screen with the given dimensions.
 * @param rows Number of rows
 * @param columns Number of columns
 */
void screen_init(int rows, int columns);

/**
 * @brief Frees all screen resources.
 */
void screen_destroy(void);

/**
 * @brief Renders the screen buffer to the terminal.
 * @param color Background frame color
 */
void screen_paint(Frame_color color);

/**
 * @brief Creates a new screen area.
 * @param x Column of the top-left corner
 * @param y Row of the top-left corner
 * @param width Width in columns
 * @param height Height in rows
 * @return Pointer to the new Area, or NULL on error
 */
Area *screen_area_init(int x, int y, int width, int height);

/**
 * @brief Frees an area created with screen_area_init.
 * @param area Target area
 */
void screen_area_destroy(Area *area);

/**
 * @brief Clears the content of an area (fills with spaces).
 * @param area Target area
 */
void screen_area_clear(Area *area);

/**
 * @brief Resets the write cursor to the top-left of the area.
 * @param area Target area
 */
void screen_area_reset_cursor(Area *area);

/**
 * @brief Writes a string in normal style (black on white).
 * @param area Target area
 * @param str  String to write
 */
void screen_area_puts(Area *area, char *str);

/**
 * @brief Writes a string in bold style (bold black on white).
 * @param area Target area
 * @param str  String to write
 */
void screen_area_puts_bold(Area *area, char *str);

/**
 * @brief Writes a string in bright red on white (entire line).
 * @param area Target area
 * @param str  String to write
 */
void screen_area_puts_red(Area *area, char *str);

/**
 * @brief Writes a string in bright yellow on white (entire line).
 * @param area Target area
 * @param str  String to write
 */
void screen_area_puts_yellow(Area *area, char *str);

/**
 * @brief Writes a string with a highlighted section in bright blue.
 * @param area Target area
 * @param str String to write
 * @param bold_start Start column of the highlighted section
 * @param bold_len Length of the highlighted section
 */
void screen_area_puts_bold_at(Area *area, char *str, int bold_start, int bold_len);

/**
 * @brief Writes a string with a highlighted section in a chosen color attribute.
 *
 * @param area Target area
 * @param str String to write
 * @param bold_start Start column of the highlighted section
 * @param bold_len Length of the highlighted section
 * @param color_attr Color attribute constant (see Color_attr)
 */
void screen_area_puts_bold_color_at(Area *area, char *str, int bold_start, int bold_len, int color_attr);

#endif /* __LIBSCREEN_H */