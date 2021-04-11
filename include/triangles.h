//
// Created by kimigaev on 11.04.2021.
//

#ifndef THREEFORCE_TRIANGLES_H
#define THREEFORCE_TRIANGLES_H


#include <vector>
#include <iostream>
#include "geometry.h"

class triangles {
    std::vector<triangle> triangles_;
    GLuint program_, vao_, vbo_;
    int max_triangles_;

public:
    triangles(GLuint program, int max_triangles);

    size_t size() const;

    void draw() const;

    triangle get(int n) const {
        return triangles_[n];
    }

    void set(int n, const triangle & tr);

    void push_back(const triangle & tr);

    int get_triangle_index_by_point(const point & p) const;
};


#endif //THREEFORCE_TRIANGLES_H
