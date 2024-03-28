#include <iostream>
#include <cmath>

void iterateLine(int x1, int y1, int x2, int y2) {
    int dx = std::abs(x2 - x1);
    int dy = std::abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        std::cout << "(" << x1 << ", " << y1 << ")" << std::endl;

        if (x1 == x2 && y1 == y2) {
            break;
        }

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

int main() {
    int x1 = 1, y1 = 1;
    int x2 = 10, y2 = 4;

    std::cout << "Iterating points along the line between (" << x1 << ", " << y1 << ") and (" << x2 << ", " << y2 << "):" << std::endl;
    iterateLine(x1, y1, x2, y2);

    return 0;
}
