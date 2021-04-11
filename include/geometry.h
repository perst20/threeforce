#ifndef THREEFORCE_GEOMETRY_H
#define THREEFORCE_GEOMETRY_H

#include <GL/glew.h>

struct point {
    GLfloat x;
    GLfloat y;

    point operator+() const;

    point operator-() const;

    point operator+(const point &p) const;

    point operator-(const point &p) const;

    point &operator+=(const point &p);

    point &operator-=(const point &p);

};


struct triangle {
    point p1;
    point p2;
    point p3;

    bool is_in_triangle(point p) const;

    triangle move(point p) const;
};

struct color {
    GLfloat r;
    GLfloat g;
    GLfloat b;
    GLfloat a;
    color(std::uint32_t hex, GLfloat alpha);
    color(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
};

point get_normalized_point(int x, int y, int width, int height);


#endif //THREEFORCE_GEOMETRY_H
