#include "my_matrix.h"

Matrix::Matrix(const std::size_t s) : _side(s) {
    if (_side > 0) {
        _data = new int*[_side];
        if (_data != nullptr) {
            _data[0] = new int[_side*_side];
            if (_data[0] == nullptr) {
                delete[] _data;
                _data = nullptr;
            }
            else {
                for (std::size_t i = 1; i < _side; i++) {
                    _data[i] = _data[i-1] + _side;
                }
            }
        }
    }
    else 
        _data = nullptr;
}

void Matrix::swap(Matrix& that) {
    std::swap(_side, that._side);
    std::swap(_data, that._data);
}

Matrix::~Matrix() {
    if (_data) {
        delete[] _data[0];
        delete[] _data;
    }
}

std::ostream& operator<<(std::ostream& os, const Matrix& mat) {
    std::stringstream line;
    for (std::size_t i = 0; i < mat._side; i++) {
        for (std::size_t j = 0; j < mat._side; j++) { 
            line << mat._data[i][j] << " ";
        }
        os << line.str() << std::endl;
        line.str("");
    }   
    return os;
}

void Matrix::set(const std::size_t i, const std::size_t j, const int val) {
    _data[i][j] = val;
}

void Matrix::correct_file(std::ifstream& file) const {
    if (file.eof()){
        file.close();
        throw "Error: invalid file format.\n";
    }
}

void Matrix::rotate() {
    Matrix buf(_side);
    for (std::size_t i = 0; i < _side; i++) {
        for (std::size_t j = 0; j < _side; j++) {
            buf.set(i,j,_data[_side - j - ONE][i]);
        }
    }
    buf.swap(*this);
}

void Matrix::load(std::string fname) {
    std::ifstream file(fname);
    if (file.is_open()) {
        std::size_t side;
        int val;
        file >> side;
        correct_file(file);
        Matrix buf(side);
        for (std::size_t i = 0; i < side; i++) {
            for (std::size_t j = 0; j < side; j++) {
                file >> val;
                buf.set(i,j,val);
                correct_file(file);
            }
        }
        file.close();
        buf.swap(*this);
    }
    else {
        throw "LOAD: unable to open file.\n"; 
    }
}

void Matrix::unload(std::string fname) const {
    std::ofstream file(fname);
    if (file.is_open()) {
        file << _side << "\n" << *this;
        file.close();
    }
}