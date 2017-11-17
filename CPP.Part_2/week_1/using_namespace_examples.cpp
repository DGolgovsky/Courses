namespace ru
{
    namespace msk {
        int foo(int i) { return 1; }
        int bar(int i) { return -1; }
    }

    using namespace msk; // All names from msk
    using msk::foo;      // msk::foo only

    int foo(float f) { return 2; }
    int foo(double a, double b) { return 3; }

    namespace spb {
        int global = foo(5);
    }
}

// Alias
namespace csccpp17 = ru::spb::csc::cpp17;

