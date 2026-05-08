/**
 * @brief It implements the screen module
 *
 * @file libscreen.c
 * @author Profesores PPROG
 * @version 0
 * @date 24-01-2026
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libscreen.h"

#pragma GCC diagnostic ignored "-Wpedantic"

/* Global variables */
int ROWS    = 23;
int COLUMNS = 80;

#define TOTAL_DATA   ((ROWS * COLUMNS) + 1)
#define BG_CHAR      '~'
#define FG_CHAR      ' '
#define ACCESS(d, x, y) ((d) + ((y) * COLUMNS) + (x))

/**
 * @brief Structure representing a screen area
 */
struct _Area {
  int   x;       /**< x coordinate of the area (column) */
  int   y;       /**< y coordinate of the area (row)    */
  int   width;   /**< width of the area                 */
  int   height;  /**< height of the area                */
  char *cursor;  /**< pointer to the current write position */
};

static char          *__data  = NULL;
static unsigned char *__attrs = NULL;

/* ------------------------------------------------------------------ */
/*  Attribute constants (also exposed via Color_attr in the header)    */
/* ------------------------------------------------------------------ */
#define ATTR_NONE        0
#define ATTR_BOLD        1
#define ATTR_BOLD_BLUE   2
#define ATTR_BOLD_GREEN  3
#define ATTR_BOLD_RED    4
#define ATTR_BOLD_YELLOW 5

/* ------------------------------------------------------------------ */
/*  Private function declarations                                       */
/* ------------------------------------------------------------------ */
static int   screen_area_cursor_is_out_of_bounds(Area *area);
static void  screen_area_scroll_up(Area *area);
static void  screen_utils_replaces_special_chars(char *str);
static void  screen_area_puts_internal(Area *area, char *str,
                                        unsigned char attr,
                                        int bold_start, int bold_len,
                                        unsigned char bold_attr);
static char *frame_color_to_string(Frame_color color);

/* ================================================================== */
/*  Public API                                                          */
/* ================================================================== */

void screen_init(int rows, int columns)
{
  screen_destroy(); /* dispose if previously initialised */

  ROWS    = rows;
  COLUMNS = columns;

  __data  = (char *)         malloc(sizeof(char)          * (size_t) TOTAL_DATA);
  __attrs = (unsigned char *) malloc(sizeof(unsigned char) * (size_t) TOTAL_DATA);

  if (__data) {
    memset(__data, (int) BG_CHAR, (size_t) TOTAL_DATA);
    __data[TOTAL_DATA - 1] = '\0'; /* NULL-terminated string */
  }

  if (__attrs) {
    memset(__attrs, ATTR_NONE, (size_t) TOTAL_DATA);
  }
}

void screen_destroy(void)
{
  if (__data) {
    free(__data);
    __data = NULL;   /* FIX: avoid dangling pointer / double-free */
  }
  if (__attrs) {
    free(__attrs);
    __attrs = NULL;  /* FIX: avoid dangling pointer / double-free */
  }
}

void screen_paint(Frame_color color)
{
  char          *src      = NULL;
  unsigned char *attr_ptr = NULL;
  char          *dest     = NULL;
  int            i        = 0;

  dest = malloc((size_t) COLUMNS + 1);
  if (!dest)
    return;

  memset(dest, 0, (size_t) COLUMNS + 1);

  if (__data) {
    puts("\033[2J"); /* clear the terminal */

    for (src = __data, attr_ptr = __attrs;
         src < (__data + TOTAL_DATA - 1);
         src += COLUMNS, attr_ptr += COLUMNS)
    {
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

/* ================================================================== */
/*  Area management                                                     */
/* ================================================================== */

Area *screen_area_init(int x, int y, int width, int height)
{
  int   i    = 0;
  Area *area = NULL;

  area = (Area *) malloc(sizeof(struct _Area));
  if (!area)
    return NULL;

  *area = (struct _Area) { x, y, width, height, ACCESS(__data, x, y) };

  for (i = 0; i < area->height; i++) {
    memset(ACCESS(area->cursor, 0, i), (int) FG_CHAR, (size_t) area->width);
    memset(ACCESS(__attrs, x, y + i),  ATTR_NONE,     (size_t) area->width);
  }

  return area;
}

void screen_area_destroy(Area *area)
{
  if (area)
    free(area);
}

void screen_area_clear(Area *area)
{
  int i = 0;

  if (!area)
    return;

  screen_area_reset_cursor(area);

  for (i = 0; i < area->height; i++) {
    memset(ACCESS(area->cursor, 0, i),          (int) FG_CHAR, (size_t) area->width);
    memset(ACCESS(__attrs, area->x, area->y + i), ATTR_NONE,   (size_t) area->width);
  }
}

void screen_area_reset_cursor(Area *area)
{
  if (area)
    area->cursor = ACCESS(__data, area->x, area->y);
}

/* ================================================================== */
/*  Text output (public)                                                */
/* ================================================================== */

void screen_area_puts(Area *area, char *str)
{
  screen_area_puts_internal(area, str, ATTR_NONE, 0, 0, ATTR_NONE);
}

void screen_area_puts_bold(Area *area, char *str)
{
  screen_area_puts_internal(area, str, ATTR_BOLD, 0, 0, ATTR_NONE);
}

void screen_area_puts_red(Area *area, char *str)
{
  screen_area_puts_internal(area, str, ATTR_BOLD_RED, 0, 0, ATTR_NONE);
}

void screen_area_puts_yellow(Area *area, char *str)
{
  screen_area_puts_internal(area, str, ATTR_BOLD_YELLOW, 0, 0, ATTR_NONE);
}

void screen_area_puts_bold_at(Area *area, char *str, int bold_start, int bold_len)
{
  screen_area_puts_internal(area, str, ATTR_NONE, bold_start, bold_len, ATTR_BOLD_BLUE);
}

void screen_area_puts_bold_color_at(Area *area, char *str,
                                    int bold_start, int bold_len,
                                    int color_attr)
{
  screen_area_puts_internal(area, str, ATTR_NONE,
                            bold_start, bold_len,
                            (unsigned char) color_attr);
}

/* ================================================================== */
/*  Private helpers                                                     */
/* ================================================================== */

static void screen_area_puts_internal(Area *area, char *str,
                                       unsigned char attr,
                                       int bold_start, int bold_len,
                                       unsigned char bold_attr)
{
  int            len      = 0;
  char          *ptr      = NULL;
  unsigned char *attr_line = NULL;

  if (!area || !str)
    return;

  /* FIX: sanitise special chars BEFORE the loop so strlen() is stable */
  screen_utils_replaces_special_chars(str);

  if (screen_area_cursor_is_out_of_bounds(area))
    screen_area_scroll_up(area);

  for (ptr = str; ptr < (str + strlen(str)); ptr += area->width) {

    if (screen_area_cursor_is_out_of_bounds(area))
      screen_area_scroll_up(area);

    memset(area->cursor, FG_CHAR, (size_t) area->width);

    attr_line = ACCESS(__attrs, area->x,
                       (int)((area->cursor - __data) / COLUMNS));
    memset(attr_line, ATTR_NONE, (size_t) area->width);

    len = ((int) strlen(ptr) < area->width) ? (int) strlen(ptr) : area->width;
    memcpy(area->cursor, ptr, (size_t) len);

    /* apply whole-line attribute */
    if (attr != ATTR_NONE && len > 0)
      memset(attr_line, attr, (size_t) len);

    /* apply partial bold/color range */
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

/* FIX: corrected upper bound — was ACCESS(__data, x+width, y+height-2)
   which could step outside the buffer when the area reaches the right edge */
static void screen_area_scroll_up(Area *area)
{
  for (area->cursor = ACCESS(__data, area->x, area->y);
       area->cursor < ACCESS(__data, area->x, area->y + area->height - 1);
       area->cursor += COLUMNS)
  {
    unsigned char *dest_attr = ACCESS(__attrs, area->x,
                                      (int)((area->cursor - __data) / COLUMNS));
    unsigned char *src_attr  = ACCESS(__attrs, area->x,
                                      (int)((area->cursor - __data) / COLUMNS) + 1);
    memcpy(area->cursor,  area->cursor + COLUMNS, (size_t) area->width);
    memcpy(dest_attr,     src_attr,                (size_t) area->width);
  }
}

static int screen_area_cursor_is_out_of_bounds(Area *area)
{
  return area->cursor > ACCESS(__data,
                               area->x + area->width,
                               area->y + area->height - 1);
}

static void screen_utils_replaces_special_chars(char *str)
{
  char *pch = NULL;

  /* Replace accented/special Spanish chars with '??' */
  while ((pch = strpbrk(str, "ÁÉÍÓÚÑáéíóúñ")))
    memcpy(pch, "??", 2);
}

static char *frame_color_to_string(Frame_color color)
{
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