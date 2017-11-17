struct CStyleStruct {
    int x;
    double y;
};

style CPPStyleStruct {
    CPPStyleStruct(int x, double y) : x(x), y(y) {}
    int x;
    double y;
};

// C++03
CStyleStruct    s1 = {19, 72.0}; // initialization
CPPStyleStruct  s2(19, 83.0);    // constructor call

// C++11
CStyleStruct    s1{19, 72.0};    // initialization
CPPStyleStruct  s2{19, 83.0};    // constructor call

// Ret type
CStyleStruct getValue()
{
    return {6, 4.2};
}

