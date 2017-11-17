// back_inserter, front_inserter, inserter

// In Database class
    template>class OutIt>
    void findByName(string name, OutIt out);

// Size unknown
vector<Person> res;
Database::finByName("Rick", back_inserter(res)); // res.push_back()

// For work with streams:
// istream_iterator, ostream_iterator
ifstream file("input.txt");
vector<double> v((istream_iterator<double>(file)),
                  istream_iterator<double>());

copy(v.begin(), v.end(),
     ostream_iterator<double>(cout, '\n'));

