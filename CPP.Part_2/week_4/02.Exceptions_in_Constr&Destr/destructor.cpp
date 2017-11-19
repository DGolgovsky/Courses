// Doubled exception
void foo() {
    try {
        Bad b; // exception in destructor
        bar(); // exception
    } catch (std::exception & e) {
        // ...
    }
}

// UB
void bar() {
    Bad * bad = new Bad[100];
    // Exception in destructor num 20
    delete [] bad;
}

