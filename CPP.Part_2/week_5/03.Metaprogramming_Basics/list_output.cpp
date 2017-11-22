// Output into ostream
template<typename TL>
void printTypeList(std::ostream &os)
{
    os << typeid(typename TL::Head).name() << '\n';
    printTypeList<typename TL::Tail>(os);
};

// Output empty list
template<>
void printTypeList<TypeList<>>(std::ostream &os) {}

int main()
{
    using TL = TypeList<double, float, int, char>;
    printTypeList<TL>(std::cout);

    return 0;
}

