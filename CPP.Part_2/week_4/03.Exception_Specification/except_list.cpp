// Old standard
vodi foo() throw (std::logic_error) {
    if (...) throw std::logic_error();
    if (...) throw std::runtime_error(); // process terminated
}

// Second 'if' is true -> process abandoned
void foo() {
    try {
        if (...) throw std::logic_error();
        if (...) throw std::runtime_error();
    } catch (std::logic_error &e) {
        throw e;
    } catch (...) {
        terminate(); // set_unexpected
    }
}

