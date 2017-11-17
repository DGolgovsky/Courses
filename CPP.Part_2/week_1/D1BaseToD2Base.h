struct Base {}; 

struct D1 : Base {};

struct D2 : Base {}; 

struct D3 : D1, D2 {};
