//
// Created by kimigaev on 10.04.2021.
//

#include <geometry.h>

point point::operator+() const {
    return *this;
}

point point::operator-() const {
    return {-x, -y};
}

point point::operator+(const point &p) const {
    return {x + p.x, y + p.y};
}

point point::operator-(const point &p) const {
    return *this + (-p);
}

point &point::operator+=(const point &p) {
    return *this = *this + p;
}

point &point::operator-=(const point &p) {
    return *this = *this - p;
}

bool triangle::is_in_triangle(point p) const {
    GLfloat a = (p1.x - p.x) * (p2.y - p1.y) - (p2.x - p1.x) * (p1.y - p.y),
            b = (p2.x - p.x) * (p3.y - p2.y) - (p3.x - p2.x) * (p2.y - p.y),
            c = (p3.x - p.x) * (p1.y - p3.y) - (p1.x - p3.x) * (p3.y - p.y);
    return (a >= 0 && b >= 0 && c >= 0) || (a <= 0 && b <= 0 && c <= 0);
}

triangle triangle::move(point p) const {
    return {p1 + p, p2 + p, p3 + p,};
}

point get_normalized_point(int x, int y, int width, int height) {
    return {
            ((GLfloat) x * 2 / (GLfloat) width) - 1,
            -(((GLfloat) y * 2 / (GLfloat) height) - 1)
    };
}

color::color(std::uint32_t hex, GLfloat alpha) : a(alpha){
    b = (GLfloat) (hex & 0xff) / (GLfloat) 0xff;
    g = (GLfloat) ((hex >> 8)  & 0xff) / (GLfloat) 0xff;
    r = (GLfloat) ((hex >> 16)  & 0xff) / (GLfloat) 0xff;
}

color::color(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) : r(red), g(green), b(blue), a(alpha){}
