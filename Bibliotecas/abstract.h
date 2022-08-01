typedef void (*cut_callback)(Rectangle *);

/** *
click
lock_click
init_graphics_engine
selected_mini_circle
generate_board
generate_point
draw_rectangle
draw_mini_circle
generate_circle
generate_rectangle
selected_rectangle
draw_circle
draw_rectangle
draw_triangle
dibujar_lienzo
dibujar_lienzo
selected_rectangle
limits
copy_section
Mouse
Lienzo
* */

int mtest(void);

void mocultar(void);

void mver(void);

int mxpos(int);

int mypos(int);

void msituar(int, int, int);

int mclick(void);

void mlimit(int, int, int, int, int);

int minlimit(int, int, int, int, int);

/**
 * Engine
 * */
Point *init_graphics_engine(Point *);

void close_graphics_engine();

/**
 * Lienzo
 * */
Lienzo *generate_board(Lienzo *, Point *, int, int, int, int);

void dibujar_lienzo(Lienzo *, enum COLORS);

int is_in_board(Lienzo *, Point *);

/**
 * Ellipse
 * */
Ellipse *generate_ellipse(Ellipse *, Point *, int, int, int, int);

void draw_ellipse(Ellipse *, enum COLORS);

int is_in_ellipse(Ellipse *, Point *);

int selected_ellipse(Ellipse (*)[], int, Point *);

void draw_ellipse_border(Ellipse *, enum COLORS);

/*
 * Rectangle
 * */
Rectangle *generate_rectangle(Rectangle *, Point *, int, int, int);

void draw_rectangle(Rectangle *, enum COLORS);

int is_in_rectangle(Rectangle *, Point *);

int is_in_mini_circle(Rectangle *, Point *);

int selected_rectangle(Rectangle (*)[], int, Point *);

void draw_rectangle_border(Rectangle *, enum COLORS);
/*void rectangle_raw(Rectangle*, enum COLORS, enum COLORS);*/

/**
 * Circle
 * */
Circle *generate_circle(Circle *, Point *, int);

void draw_circle(Circle *, enum COLORS);

int is_in_circle(Circle *, Point *);

int selected_circle(Circle (*)[], int, Point *);

void draw_circle_border(Circle *, enum COLORS);
/*void circle_raw(Circle *, enum COLORS, enum COLORS);*/

/*
 * Triangle
 * */
Triangle *generate_triangle(Triangle *, Point *, int);

void draw_triangle(Triangle *, enum COLORS);

int is_in_triangle(Triangle *, Point *);

int selected_triangle(Triangle (*)[], int, Point *);
/*void draw_triangle_border(Triangle *, enum COLORS);
void triangle_raw(Triangle*, enum COLORS, enum COLORS);*/

/**
 * Cursor
 * */
Cursor *digest_click(Cursor *);

int lock_click(Lienzo *board, Cursor *click);

/**
 * Miscellaneous
 * */
int measure_center(double, int, double, double);

int is_in_area(Point *, Point *, Point *);

enum COLORS negate_colour(enum COLORS);

void text_center(int x, int y, const char *text, enum COLORS colour);

Point *generate_point(Point *, int, int);

int rng(int, int);
/*void line_raw(Point, Point, enum COLORS, enum COLORS);
void load_image(Rectangle *);
void save_image(Rectangle *);*/

/*
 * RasterOp
 * */
void copy_section(Point *, Point *, Point *, enum putimage_ops);

#pragma region TURBO_C
#ifndef __TURBOC__

const enum COLORS getcolor();

void setcolor(enum COLORS);

void rectangle(int, int, int, int);

void ellipse(int, int, int, int, int, int);

void getlinesettings(struct linesettingstype *);

void setlinestyle(enum line_styles, int, enum line_widths);

void circle(int, int, int);

void line(int, int, int, int);

void outtextxy(size_t, int, const char *);

size_t imagesize(int, int, int, int);

void getimage(int, int, int, int, void *);

void putimage(int, int, void *, enum putimage_ops);

void closegraph();

void initgraph(int *, int *, const char *);

int getmaxx();

int getmaxy();

void setfillstyle(enum fill_patterns patterns, enum COLORS colors);

void floodfill(int i, int i1, enum COLORS colors);

void fillellipse(int x, int y, int i, int i1);

void bar(int i, int i1, int i2, int i3);

#endif
#pragma endregion

/**
 * Lienzo
 * */
Lienzo *
generate_board(Lienzo *board, Point *limit, int margin_top, int margin_left, int margin_bottom, int margin_right) {
    Point start = *generate_point(&start, (margin_left * limit->x) / 100, (margin_top * limit->y) / 100);
    Point end = *generate_point(&end, limit->x - (margin_right * limit->x) / 100,
                                limit->y - (margin_bottom * limit->y) / 100);
    Point center = *generate_point(&center, (start.x + end.x) / 2, (start.y + end.y) / 2);
    Rectangle area = *generate_rectangle(&area, &center, board->width = end.x - start.x,
                                         board->height = end.y - start.y, 0);
    board->area = area;
    board->limit = *limit;
    board->center = center;
    return board;
}

void dibujar_lienzo(Lienzo *board, enum COLORS colour) {
    const enum COLORS old_color = getcolor();
    setcolor(colour);
    setfillstyle(SOLID_FILL, colour);
    bar(board->area.start.x, board->area.start.y, board->area.end.x, board->area.end.y);
    setcolor(old_color);
}

int is_in_board(Lienzo *board, Point *point) {
    return is_in_rectangle(&board->area, point);
}

/**
 * Ellipse
 * */
Ellipse *generate_ellipse(Ellipse *ellipse, Point *center, int width, int height, int radius_min, int radius_max) {
    ellipse->center = *center;
    ellipse->start.x = center->x - width / 2;
    ellipse->start.y = center->y - height / 2;
    ellipse->end.x = center->x + width / 2;
    ellipse->end.y = center->y + height / 2;
    ellipse->radius_min = radius_min;
    ellipse->radius_max = radius_max;
    return ellipse;
}

void draw_ellipse(Ellipse *_ellipse, enum COLORS colour) {
    const enum COLORS old_color = getcolor();
    setcolor(colour);
    ellipse(_ellipse->center.x, _ellipse->center.y, 0, 360, _ellipse->radius_max, _ellipse->radius_min);
    setcolor(old_color);
}

int is_in_ellipse(Ellipse *ellipse, Point *point) {
    return is_in_area(&ellipse->start, &ellipse->end, point) &&
           ((float) ((point->x - ellipse->center.x) * (point->x - ellipse->center.x)) /
            (float) (ellipse->radius_max * ellipse->radius_max))
           + ((float) ((point->y - ellipse->center.y) * (point->y - ellipse->center.y)) /
              (float) (ellipse->radius_min * ellipse->radius_min)) < 1.004;
}

int selected_ellipse(Ellipse (*ellipses)[], int size, Point *point) {
    int index = 0;
    for (; index < size; index++) if (is_in_ellipse(&(*ellipses)[index], point)) return index;
    return -1;
}

void draw_ellipse_border(Ellipse *ellipse, enum COLORS colour) {
    struct linesettingstype old_line;
    getlinesettings(&old_line);
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    draw_ellipse(ellipse, colour);
    setlinestyle(old_line.linestyle, old_line.thickness, old_line.upattern);
}

/*
 * Rectangle
 * */
Rectangle *generate_rectangle(Rectangle *rectangle, Point *center, int width, int height, int mhelp) {
    int sum = 0;

    if (mhelp) sum = 10;

    rectangle->center = *center;
    rectangle->start.x = center->x - width / 2;
    rectangle->start.y = (center->y - height / 2) - sum;
    rectangle->end.x = center->x + width / 2;
    rectangle->end.y = (center->y + height / 2) - sum;
    return rectangle;
}

void draw_rectangle(Rectangle *_rectangle, enum COLORS colour) {
    const enum COLORS old_color = getcolor();
    setcolor(colour);
    rectangle(_rectangle->start.x, _rectangle->start.y, _rectangle->end.x, _rectangle->end.y);
    setcolor(old_color);
}

int is_in_rectangle(Rectangle *rectangle, Point *point) {
    return is_in_area(&rectangle->start, &rectangle->end, point);
}

int selected_rectangle(Rectangle (*rectangles)[], int size, Point *point) {
    int index = 0;
    for (; index < size; index++) if (is_in_rectangle(&(*rectangles)[index], point)) return index;
    return -1;
}

void draw_rectangle_border(Rectangle *rectangle, enum COLORS colour) {
    struct linesettingstype old_line;
    getlinesettings(&old_line);
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    draw_rectangle(rectangle, colour);
    setlinestyle(old_line.linestyle, old_line.thickness, old_line.upattern);
}

/**
 * Circle
 * */
Circle *generate_circlpointe(Circle *circle, Point *center, int radius) {
    circle->center = *center;
    circle->radius = radius;
    return circle;
}

void draw_circle(Circle *_circle, enum COLORS colour) {
    const enum COLORS old_color = getcolor();
    setcolor(colour);
    circle(_circle->center.x, _circle->center.y, _circle->radius);
    floodfill(_circle->center.x, _circle->center.y, colour);
    setcolor(old_color);
}

Circle *generate_circle(Circle *circle, Point *center, int radius) {
    circle->center = *center;
    circle->radius = radius;
    return circle;
}

void draw_mini_circle(Rectangle *_rectangle, enum COLORS colour) {
    const enum COLORS old_color = getcolor();
    setcolor(colour);
    circle(_rectangle->start.x + 22, _rectangle->start.y, 10);
    floodfill(_rectangle->start.x + 22, _rectangle->start.y, colour);
    setcolor(old_color);
}

int is_in_mini_circle(Rectangle *rectangle, Point *point) {

  int ans = (((float)((point->x-(rectangle->start.x+22))*point->x-(rectangle->start.x+22))) + ((float)((point->y-(rectangle->start.y+10))*(point->y-(rectangle->start.y+10))))) < 100.00;

  return ans;
}

int is_in_circle(Circle *circle, Point *point) {
    Point start, end;
    start.x = circle->center.x - circle->radius;
    start.y = circle->center.y - circle->radius;
    end.x = circle->center.x + circle->radius;
    end.y = circle->center.y + circle->radius;
    return is_in_area(&start, &end, point) &&
           ((float) ((point->x - circle->center.x) * (point->x - circle->center.x)) /
            (float) (circle->radius * circle->radius)) < 1.004;
}


int selected_mini_circle(Rectangle (*rectangles)[], int size, Point *point) {

    int index = 0;
    for (; index < size; index++) {

      if (is_in_rectangle(&(*rectangles)[index], point)) {
        if (is_in_mini_circle(&(*rectangles)[index], point)) {
          return index;
        }
      }
    }

    return -1;
}

int selected_circle(Circle (*circles)[], int size, Point *point) {
    int index = 0;
    for (; index < size; index++)
        if (is_in_circle(&(*circles)[index], point)) return index;
    return -1;
}



void draw_circle_border(Circle *circle, enum COLORS colour) {
    struct linesettingstype old_line;
    getlinesettings(&old_line);
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    draw_circle(circle, colour);
    setlinestyle(old_line.linestyle, old_line.thickness, old_line.upattern);
}

/*
 * Triangle
 * */
Triangle *generate_triangle(Triangle *triangle, Point *center, int size) {
    triangle->center = *center;
    triangle->a.x = center->x - size / 2;
    triangle->a.y = triangle->c.y = center->y + size / 2;
    triangle->b.x = center->x;
    triangle->b.y = center->y - size / 2;
    triangle->c.x = center->x + size / 2;
    return triangle;
}

void draw_triangle(Triangle *triangle, enum COLORS colour) {
    int points[8];
    const enum COLORS old_color = getcolor();

    points[0] = triangle->a.x;
    points[1] = triangle->a.y;
    points[2] = triangle->b.x;
    points[3] = triangle->b.y;
    points[4] = triangle->c.x;
    points[5] = triangle->c.y;
    points[6] = triangle->a.x;
    points[7] = triangle->a.y;

    setcolor(colour);
    drawpoly(4, points);
    setfillstyle(SOLID_FILL, colour);
    fillpoly(4, points);

    setcolor(old_color);
}

int is_in_triangle(Triangle *triangle, Point *point) {
    const double
            a1 = sqrt(((triangle->b.x - triangle->a.x) * (triangle->b.x - triangle->a.x)) +
                      ((triangle->b.y - triangle->a.y) - (triangle->b.y - triangle->a.y))),
            b1 = sqrt(((triangle->c.x - triangle->b.x) * (triangle->c.x - triangle->b.x)) +
                      ((triangle->c.y - triangle->b.y) - (triangle->c.y - triangle->b.y))),
            a2 = sqrt((point->x - triangle->b.x) * (point->x - triangle->b.x) +
                      (point->y - triangle->b.y) * (point->y - triangle->b.y)),
            b2 = sqrt((point->x - triangle->c.x) * (point->x - triangle->c.x) +
                      (point->y - triangle->c.y) * (point->y - triangle->c.y));
    Rectangle area = *generate_rectangle(&area, &triangle->center, triangle->b.x - triangle->a.x,
                                         triangle->c.x - triangle->c.x, 0);
    if (!is_in_rectangle(&area, point)) return 0;
    return a1 >= a2 && b1 >= b2;
}

int selected_triangle(Triangle (*triangles)[], int size, Point *point) {
    int index = 0;
    for (; index < size; index++)
        if (is_in_triangle(&(*triangles)[index], point)) return index;
    return -1;
}

void draw_triangle_border(Triangle *triangle, enum COLORS colour) {
    struct linesettingstype old_line;
    getlinesettings(&old_line);
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    draw_triangle(triangle, colour);
    setlinestyle(old_line.linestyle, old_line.thickness, old_line.upattern);
}

/**
 * Cursor
 * */
Cursor *digest_click(Cursor *click) {
    Cursor _click;
    _click.start = *generate_point(&_click.start, click->type == CURSOR_MOUSE ? mxpos(1) : click->end.x, click->type == CURSOR_MOUSE ?mypos(1) : click->end.y);
    _click.button = mclick();
    click->end = _click.start;
    /* Old and new click is none */
    if (click->button == _click.button && _click.button == CLICK_NONE) return click;
        /* Starts a new click event */
    else if (click->button == CLICK_NONE && _click.button != CLICK_NONE) {
        click->button = _click.button;
        click->start = _click.start;
    }
        /* Continued left click event */
    else if (click->button == _click.button && _click.button == CLICK_LEFT
             && click->start.x != _click.start.x && click->start.y != _click.start.y) {
        /* If previously held, check if it has been dragged */
        if (click->held) { /* Maybe needs check */
            click->drag = click->start.x == click->end.x && click->start.y == click->end.y;
        }
        click->held = 1;
    }
        /* Cancels left click held event */
    else if (click->held && click->button == CLICK_LEFT && _click.button != CLICK_LEFT) {
        click->held = 0;
        /* Check is it has been dragged */
        click->drag =
                _click.button != CLICK_LEFT ? 0 : click->start.x == click->end.x && click->start.y == click->end.y;
        click->button = _click.button;
    }
        /* Cancels every other click event */
    else if (click->button != CLICK_NONE && _click.button == CLICK_NONE) {
        /* Check is it has been dragged */
        click->drag =
                _click.button != CLICK_LEFT ? 0 : click->start.x == click->end.x && click->start.y == click->end.y;
        click->button = _click.button;
    }
    return click;
}

int lock_click(Lienzo *board, Cursor *click) {
    int inside = is_in_board(board, &click->end);
    if (click->button == CLICK_RIGHT && inside) {
        mlimit(1, 0, 0, board->limit.x, board->limit.y);
        msituar(1, board->area.end.x, board->area.end.y + 10);
        return 0;
    } else if (inside) {
        mlimit(1, board->area.start.x, board->area.start.y, board->area.end.x, board->area.end.y);
    }
    return inside;
}

/**
 * Miscellaneous
 * */
int measure_center(double width /* 100 */, int position /* 2 */, double count /* 4 */, double padding /* .20 */) {
    int size = (int) (width / count); /* 25 */
    int jump = size * position; /* 50 */
    int center = ((int) count % 2 == 1 && position == (count / 2 + 1)) ? jump : jump - size / 2;
    return center + (int) (size * padding);
}

int is_in_area(Point *start, Point *end, Point *point) {
    return point->x >= start->x && point->x <= end->x && point->y >= start->y && point->y <= end->y;
}

enum COLORS negate_colour(enum COLORS colour) {
    return (enum COLORS) ((colour + 8) % 16);
}

void text_center(int x, int y, const char *text, enum COLORS colour) {
    const enum COLORS old_colour = getcolor();
    const enum COLORS using_colour = colour ^ old_colour;
    setcolor(colour);
	outtextxy(x - (strlen(text) / 2) * 8, y - 4, text);
    setcolor(old_colour);
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-msc50-cpp"

int rng(int min, int max) {
    return rand() % (max + 1 - min) + min;
}

#pragma clang diagnostic pop

Point *generate_point(Point *point, int x, int y) {
    point->x = x;
    point->y = y;
    return point;
}

/*
 * RasterOp
 * */
void copy_section(Point *start, Point *end, Point *destination, enum putimage_ops op) {

    void *buffer = malloc(imagesize(start->x, start->y, end->x, end->y));
    if (buffer == NULL) return;
    getimage(start->x, start->y, end->x, end->y, buffer);
    putimage(destination->x - (end->x - start->x) / 2, destination->y - (end->y - start->y) / 2, buffer, op);
    free(buffer);

}

void cut_section(Rectangle* area, Point *destination, cut_callback callback) {
    void *buffer = malloc(imagesize(area->start.x, area->start.y, area->end.x, area->end.y));
    if (buffer == NULL) return;
    getimage(area->start.x, area->start.y, area->end.x, area->end.y, buffer);
    /* Callback function to DELETE the content onscreen */
    callback(area);
    putimage(destination->x - (area->end.x - area->start.x) / 2, destination->y - (area->end.y - area->start.y) / 2, buffer, COPY_PUT);
    free(buffer);
}

/**
 * Mouse
 * */
union REGS reg;

int mtest(void) {
    reg.x.ax = 0x0;
    int86(0x33, &reg, &reg);
    if (reg.x.ax > 0) return reg.x.bx; /* n�mero de botones */
    else return 0;
}

void mocultar(void) {
    reg.x.ax = 0x2;
    int86(0x33, &reg, &reg);
}

void mver(void) {
    reg.x.ax = 0x1;
    int86(0x33, &reg, &reg);
}

int mxpos(int modo) {
    reg.x.ax = 0x3;
    int86(0x33, &reg, &reg);
    return reg.x.cx / modo;
}

int mypos(int modo) {
    reg.x.ax = 0x3;
    int86(0x33, &reg, &reg);
    return reg.x.dx / modo;
}

void msituar(int modo, int x, int y) {
    reg.x.ax = 0x4;
    reg.x.cx = x * modo;
    reg.x.dx = y * modo;
    int86(0x33, &reg, &reg);
}

int mclick(void) {
    int r = 0;
    reg.x.ax = 0x5;
    reg.x.bx = 0;
    int86(0x33, &reg, &reg);
    if ((reg.x.ax) & 1) r = 1;
    else if ((reg.x.ax >> 1) & 1) r = 2;
    return r;
}

void mlimit(int modo, int x1, int y1, int x2, int y2) {
    reg.x.ax = 0x7;
    reg.x.cx = x1 * modo;
    reg.x.dx = x2 * modo;
    int86(0x33, &reg, &reg);
    reg.x.ax = 0x8;
    reg.x.cx = y1 * modo;
    reg.x.dx = y2 * modo;
    int86(0x33, &reg, &reg);
}

int minlimit(int modo, int x1, int y1, int x2, int y2) {
    if ((mxpos(modo) >= x1) &&
        (mxpos(modo) <= x2) &&
        (mypos(modo) >= y1) &&
        (mypos(modo) <= y2))
        return 1;
    return 0;
}

void close_graphics_engine() {
    closegraph();
}

Point *init_graphics_engine(Point *limits) {
    int driver = DETECT, mode;
    initgraph(&driver, &mode, "C:\\TC20\\BIN");
    return (limits = generate_point(limits, getmaxx(), getmaxy()));
}
