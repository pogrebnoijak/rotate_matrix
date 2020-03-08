#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

const int ZERO = 0;
const int ONE = 1;

class Matrix {
public:
    Matrix(const std::size_t s = 0);
    Matrix(const Matrix&) = delete;
    Matrix& operator=(const Matrix& m) = delete;
    ~Matrix();

    void set(const std::size_t i, const std::size_t j, const int val);
    friend std::ostream& operator<<(std::ostream& os, const Matrix&);
    void load(std::string fname);
    void unload(std::string fname) const;
    void rotate();
private:
    std::size_t _side;
    int **_data;

    void correct_file(std::ifstream& file) const;
    void swap(Matrix& that);
};

#endif