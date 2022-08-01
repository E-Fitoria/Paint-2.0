enum CURSOR_TYPE {
	CURSOR_NONE,
	CURSOR_MOUSE,
	CURSOR_KEYS
};

enum CLICK_TYPES {
    CLICK_NONE,
    CLICK_LEFT,
    CLICK_RIGHT
};

enum KEYBOARD_KEYS {
    KEYBOARD_ENTER = 13,
    KEYBOARD_ESC = 27,
    KEYBOARD_UP = 72,
    KEYBOARD_RIGHT = 75,
    KEYBOARD_LEFT = 77,
    KEYBOARD_DOWN = 80
};

typedef struct PointStruct {
    int x;
    int y;
} Point;

typedef struct CursorStruct {
    Point start;
    Point end;
    int drag;
    int held;
    enum CLICK_TYPES button;
    enum CURSOR_TYPE type;
} Cursor;

typedef struct EllipseStruct {
    Point center;
    Point start;
    Point end;
    int radius_max;
    int radius_min;
} Ellipse;

typedef struct CircleStruct {
    Point center;
    int radius;
} Circle;

typedef struct TriangleStruct {
    Point center;
    Point a;
    Point b;
    Point c;
} Triangle;

typedef struct RectangleStruct {
    Point start;
    Point end;
    Point center;
} Rectangle;


typedef struct BoardStruct {
    Point limit;
    Point center;
    Rectangle area;
    int width;
    int height;
} Lienzo;
