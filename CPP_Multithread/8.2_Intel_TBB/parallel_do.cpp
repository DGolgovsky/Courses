// Prototype
void SerialApplyFooToList(const std::list<Item> &list)
{
    for (std::list<Item>::const_iterator i = list.begin(); i!= list.end(); ++i) {
        Foo(*i);
    }
}

// Parallel
class ApplyFooToList
{
public:
    void operator()(Item &item) const {
        Foo(item);
    }
};

void ParallelApplyFooToList(const std::list<Item> &list)
{
    tbb::parallel_do(list.begin(), list.end(), ApplyFooToList());
}

