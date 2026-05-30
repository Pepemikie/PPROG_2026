/**
 * @brief It implements the screen module
 *
 * @file libscreen.c
 * @author José Miguel Romero Oubiña
 * @version 0
 * @date 07-05-2026
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libscreen.h"

#pragma GCC diagnostic ignored "-Wpedantic"

/* Global variables */
int ROWS = 23; /**< Number of rows in the screen */
int COLUMNS = 80; /**< Number of columns in the screen */

/** @brief Total data size for the screen buffer */
#define TOTAL_DATA ((ROWS * COLUMNS) + 1) 
/** @brief Background character */
#define BG_CHAR '~' 
/** @brief Foreground character */
#define FG_CHAR ' ' 
/** @brief Macro to access a specific position in the screen buffer */
#define ACCESS(d, x, y) ((d) + ((y) * COLUMNS) + (x)) 

/**
 * @brief Structure representing a screen area
 */
struct _Area {
  int x; /**< x coordinate of the area (column) */
  int y; /**< y coordinate of the area (row) */
  int width; /**< width of the area */
  int height; /**< height of the area */
  char *cursor; /**< pointer to the current write position */
};

static char *__data  = NULL;
static unsigned char *__attrs = NULL;

/* Attribute constants */
/** @brief No attribute */
#define ATTR_NONE 0 
/** @brief Bold attribute */
#define ATTR_BOLD 1 
/** @brief Bold blue attribute */
#define ATTR_BOLD_BLUE 2 
/** @brief Bold green attribute */
#define ATTR_BOLD_GREEN 3 
/** @brief Bold red attribute */
#define ATTR_BOLD_RED 4 
/** @brief Bold yellow attribute */
#define ATTR_BOLD_YELLOW 5 

/* Private function */
/**
 * @brief It checks if the cursor of the area is out of bounds
 * 
 * @param area a pointer to the Area struct
 * @return TRUE if the cursor is out of bounds, FALSE otherwise
 */
static int screen_area_cursor_is_out_of_bounds(Area *area);

/** 
 * @brief It scrolls the area up
 * 
 * @param area a pointer to the Area struct
 */
static void screen_area_scroll_up(Area *area);

/**
 * @brief It replaces special characters in a string with spaces
 * 
 * @param str a pointer to the string to be processed
 */
static void screen_utils_replaces_special_chars(char *str);

/**
 * @brief It puts a string into the area with the specified attributes
 * 
 * @param area a pointer to the Area struct
 * @param str a pointer to the string to be printed
 * @param attr the attribute for the string
 * @param bold_start the starting position of the bold text
 * @param bold_len the length of the bold text
 * @param bold_attr the attribute for the bold text
 */
static void screen_area_puts_internal(Area *area, char *str, unsigned char attr, int bold_start, int bold_len, unsigned char bold_attr);

/**
 * @brief It converts a frame color to a string with the corresponding ANSI escape code
 * 
 * @param color the Frame_color to be converted
 * @return a string with the ANSI escape code for the given color
 */
static char *frame_color_to_string(Frame_color color);

/* Initializes the screen with the given dimensions*/
void screen_init(int rows, int columns) {
  screen_destroy(); /* dispose if previously initialised */

  ROWS = rows;
  COLUMNS = columns;

  __data = (char *) malloc(sizeof(char) * (size_t) TOTAL_DATA);
  __attrs = (unsigned char *) malloc(sizeof(unsigned char) * (size_t) TOTAL_DATA);

  if (__data) {
    memset(__data, (int) BG_CHAR, (size_t) TOTAL_DATA);
    __data[TOTAL_DATA - 1] = '\0'; /* NULL-terminated string */
  }

  if (__attrs) {
    memset(__attrs, ATTR_NONE, (size_t) TOTAL_DATA);
  }
}

/* It destroys the screen, freeing the allocated memory */
void screen_destroy(void) {
  if (__data) {
    free(__data);
    __data = NULL;
  }
  if (__attrs) {
    free(__attrs);
    __attrs = NULL;
  }
}

/* It paints the screen with the specified color */
void screen_paint(Frame_color color) {
  char *src = NULL;
  unsigned char *attr_ptr = NULL;
  char *dest = NULL;
  int i = 0;

  dest = malloc((size_t) COLUMNS + 1);
  if (!dest)
    return;

  memset(dest, 0, (size_t) COLUMNS + 1);

  if (__data) {
    puts("\033[2J"); /* clears the terminal */

    for (src = __data, attr_ptr = __attrs; src < (__data + TOTAL_DATA - 1); src += COLUMNS, attr_ptr += COLUMNS) {
      memcpy(dest, src, (size_t) COLUMNS);

      for (i = 0; i < COLUMNS; i++) {
        if (dest[i] == BG_CHAR) {
          /* background tile */
          printf("%s%c\033[0m", frame_color_to_string(color), dest[i]);

        } else if (attr_ptr[i] == ATTR_BOLD) {
          /* bold black on white */
          printf("\033[1;30;47m%c\033[0m", dest[i]);

        } else if (attr_ptr[i] == ATTR_BOLD_BLUE) {
          /* bright blue on white */
          printf("\033[1;94;47m%c\033[0m", dest[i]);

        } else if (attr_ptr[i] == ATTR_BOLD_GREEN) {
          /* bright green on white */
          printf("\033[1;32;47m%c\033[0m", dest[i]);
        } else if (attr_ptr[i] == ATTR_BOLD_RED) {
          /* bright red on white */
          printf("\033[1;91;47m%c\033[0m", dest[i]);

        } else if (attr_ptr[i] == ATTR_BOLD_YELLOW) {
          /* bright yellow on white */
          printf("\033[1;93;47m%c\033[0m", dest[i]);

        } else {
          /* normal: black on white */
          printf("\033[1;30;47m%c\033[0m", dest[i]);
        }
      }
      printf("\n");
    }
  }

  free(dest);
}

/* Area management */
/* Creates a new screen area*/
Area *screen_area_init(int x, int y, int width, int height) {
  int i = 0;
  Area *area = NULL;

  area = (Area *) malloc(sizeof(struct _Area));
  if (!area)
    return NULL;

  *area = (struct _Area) { x, y, width, height, ACCESS(__data, x, y) };

  for (i = 0; i < area->height; i++) {
    memset(ACCESS(area->cursor, 0, i), (int) FG_CHAR, (size_t) area->width);
    memset(ACCESS(__attrs, x, y + i),  ATTR_NONE, (size_t) area->width);
  }

  return area;
}

/* It destroys the screen area, freeing the allocated memory */
void screen_area_destroy(Area *area) {
  if (area)
    free(area);
}

/* It clears the screen area */
void screen_area_clear(Area *area) {
  int i = 0;

  if (!area)
    return;

  screen_area_reset_cursor(area);

  for (i = 0; i < area->height; i++) {
    memset(ACCESS(area->cursor, 0, i), (int) FG_CHAR, (size_t) area->width);
    memset(ACCESS(__attrs, area->x, area->y + i), ATTR_NONE, (size_t) area->width);
  }
}

/* It resets the cursor of the screen area */
void screen_area_reset_cursor(Area *area) {
  if (area)
    area->cursor = ACCESS(__data, area->x, area->y);
}

/* Text output */
/* It puts a string into the area with the specified attributes */
void screen_area_puts(Area *area, char *str) {
  screen_area_puts_internal(area, str, ATTR_NONE, 0, 0, ATTR_NONE);
}

/* It puts a string into the area with bold attributes */
void screen_area_puts_bold(Area *area, char *str) {
  screen_area_puts_internal(area, str, ATTR_BOLD, 0, 0, ATTR_NONE);
}

/* It puts a string into the area with red attributes */
void screen_area_puts_red(Area *area, char *str) {
  screen_area_puts_internal(area, str, ATTR_BOLD_RED, 0, 0, ATTR_NONE);
}

/* It puts a string into the area with yellow attributes */
void screen_area_puts_yellow(Area *area, char *str) {
  screen_area_puts_internal(area, str, ATTR_BOLD_YELLOW, 0, 0, ATTR_NONE);
}

/* It puts a string into the area with bold attributes at a specific position */
void screen_area_puts_bold_at(Area *area, char *str, int bold_start, int bold_len) {
  screen_area_puts_internal(area, str, ATTR_NONE, bold_start, bold_len, ATTR_BOLD_BLUE);
}

/* It puts a string into the area with bold attributes and a specific color */
void screen_area_puts_bold_color_at(Area *area, char *str, int bold_start, int bold_len, int color_attr) {
  screen_area_puts_internal(area, str, ATTR_NONE, bold_start, bold_len, (unsigned char) color_attr);
}

/* It puts a string into the area with the specified attributes */
static void screen_area_puts_internal(Area *area, char *str, unsigned char attr, int bold_start, int bold_len, unsigned char bold_attr) {
  int len = 0;
  char *ptr = NULL;
  unsigned char *attr_line = NULL;

  if (!area || !str)
    return;

  screen_utils_replaces_special_chars(str);

  if (screen_area_cursor_is_out_of_bounds(area))
    screen_area_scroll_up(area);

  for (ptr = str; ptr < (str + strlen(str)); ptr += area->width) {

    if (screen_area_cursor_is_out_of_bounds(area))
      screen_area_scroll_up(area);

    memset(area->cursor, FG_CHAR, (size_t) area->width);

    attr_line = ACCESS(__attrs, area->x, (int)((area->cursor - __data) / COLUMNS));
    memset(attr_line, ATTR_NONE, (size_t) area->width);

    len = ((int) strlen(ptr) < area->width) ? (int) strlen(ptr) : area->width;
    memcpy(area->cursor, ptr, (size_t) len);

    /* apply to the whole line the attribute */
    if (attr != ATTR_NONE && len > 0)
      memset(attr_line, attr, (size_t) len);

    /* apply bold/color to a partial range */
    if (bold_start < 0)
      bold_start = 0;

    if (bold_start < len && bold_len > 0) {
      if (bold_start + bold_len > len)
        bold_len = len - bold_start;
      if (bold_len > 0)
        memset(attr_line + bold_start, bold_attr, (size_t) bold_len);
    }

    area->cursor += COLUMNS;
  }
}

/* It scrolls the screen area up */
static void screen_area_scroll_up(Area *area) {
  for (area->cursor = ACCESS(__data, area->x, area->y);
       area->cursor < ACCESS(__data, area->x, area->y + area->height - 1);
       area->cursor += COLUMNS)
  {
    unsigned char *dest_attr = ACCESS(__attrs, area->x, (int)((area->cursor - __data) / COLUMNS));
    unsigned char *src_attr  = ACCESS(__attrs, area->x, (int)((area->cursor - __data) / COLUMNS) + 1);
    memcpy(area->cursor,  area->cursor + COLUMNS, (size_t) area->width);
    memcpy(dest_attr, src_attr, (size_t) area->width);
  }
}

/* It checks if the cursor is out of bounds */
static int screen_area_cursor_is_out_of_bounds(Area *area) {
  return area->cursor > ACCESS(__data, area->x + area->width, area->y + area->height - 1);
}

/* It replaces special characters with their ASCII equivalents */
static void screen_utils_replaces_special_chars(char *str) {
  char *pch = NULL;

  /* Replace strange characters with '??' */
  while ((pch = strpbrk(str, "ÁÉÍÓÚÑáéíóúñ")))
    memcpy(pch, "??", 2);
}

static char *frame_color_to_string(Frame_color color) {
  switch (color) {
    case BLACK:  return "\033[0;30;40m";
    case RED:    return "\033[0;34;41m";
    case GREEN:  return "\033[0;34;42m";
    case YELLOW: return "\033[0;34;43m";
    case BLUE:   return "\033[0;34;44m";
    case PURPLE: return "\033[0;34;45m";
    case CYAN:   return "\033[0;34;46m";
    case WHITE:  return "\033[0;34;47m";
    default:     return "\033[0m";
  }
}