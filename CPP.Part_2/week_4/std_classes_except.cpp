// Base class for all exceptions (in <exception>):
class exception {
    virtual ~exception();
    virtual const char* what() const;
};

// Standard classes ofexceptioms (in <stdexcept>):
logic_error: domain_error, invalid_argument,
             length_error, out_of_range
runtime_error: range_error, overflow_error,
               underflow_error
int main() {
    try { ... }
    catch (std::exception const &e) {
        std::cerr << e.what() << '\n';
    }
}
