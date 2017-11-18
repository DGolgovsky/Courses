size_t write(string file, string data) {
    if (!open(file)) throw FileOpenError(file);
    // ...
}

double safediv(int x, int y) {
    if (y == 0) throw MathError("Division by zero");
    return double(x) / y;
}

void write_x_dir_y(string file, int x, int y) {
    try {
        write(file, to_string(safediv(x, y)));
    } catch (MathError &s) {
        // Error handling in safediv
    } catch (FileError &e) {
        // Error handling in write
    } catch(...) {
        // Other errors
    }
}

