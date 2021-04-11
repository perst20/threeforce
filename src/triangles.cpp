//
// Created by kimigaev on 11.04.2021.
//

#include <triangles.h>

triangles::triangles(GLuint program, int max_triangles) : program_(program), max_triangles_(max_triangles) {
    glGenVertexArrays(1, &vao_);
    glGenBuffers(1, &vbo_);
    glBindVertexArray(vao_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle) * 1024, NULL, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid *) 0);
    glEnableVertexAttribArray(0);
    triangles_.reserve(max_triangles);
}

size_t triangles::size() const {
    return triangles_.size();
}

void triangles::draw() const {
    glUseProgram(program_);
    glBindVertexArray(vao_);
    glDrawArrays(GL_TRIANGLES, 0, (int) size() * 3);
    glBindVertexArray(0);
}

void triangles::set(int n, const triangle &tr) {
    triangles_[n] = tr;
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferSubData(GL_ARRAY_BUFFER, n * sizeof(triangle), sizeof(triangle), &tr);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void triangles::push_back(const triangle &tr) {
    if (size() >= max_triangles_) {
        std::cout << "too much triangles" << std::endl;
        return;
    }
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferSubData(GL_ARRAY_BUFFER, (GLintptr) size() * sizeof(triangle), sizeof(triangle), &tr);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    triangles_.push_back(tr);
}

int triangles::get_triangle_index_by_point(const point &p) const {
    int tr = (int) size() - 1;
    for (; tr >= 0; --tr) {
        if (get(tr).is_in_triangle(p))
            break;
    }
    return tr;
}

triangles::~triangles() {
    glDeleteBuffers(1, &vbo_);
    glDeleteVertexArrays(1, &vao_);
}
