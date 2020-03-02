namespace XML {
    struct Parser {};
    int GetCurrentLineNumber(Parser *parser);
}

void foo()
{
    XML::Parser *prsr;
    XML::GetCurrentLineNumber(prsr);
}

/**************************/

/* With C++17
 * namespace items::food {
 *     struct Fruct { ... };
 * }
 */
namespace items { namespace food {
    struct Fruit {
        Fruit(char const * name)
            :name_(name) {}
        char const * name_;
    };
}}

void bar()
{
    items::food::Fruit apple("Apple");
}

/**************************/

namespace weapons { struct Bow {}; }
namespace items {
    struct Scroll {};
    struct Artefact {};
}
namespace weapons { struct Sword {}; }

/**************************/

struct Dictionary {};

namespace items {
    struct Dictionary {};
    ::Dictionary globalDictionary;
}

