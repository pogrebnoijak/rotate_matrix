#include "my_matrix.h"

int main() {
    std::string fname = "matrix.txt";
    std::string out_fname = "rotate_matrix.txt";
    Matrix matrix;
    try {
        matrix.load(fname);
    }
    catch (const char* s) {
        std::cout << s;
    }
    std::cout << matrix << "\n";
    matrix.rotate();

    std::cout << matrix << "\n";
    matrix.unload(out_fname);

    return 0;
}