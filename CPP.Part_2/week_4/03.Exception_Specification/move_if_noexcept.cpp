struct Bad {
    Bad() {}
    Bad(Bad&&);             // mat_throw
    Bad(const Bad&);        // not matter
};

struct Good {
    Good() {}
    Good(Good&&) noexcept;  // no_throw
    Good(const Good&);      // not matter
};

Good g1;
Bad  b1;
Good g2 = std::move_if_noexcept(g1);    // move
Bad  b2 = std::move_if_noexcept(b1);    // copy

