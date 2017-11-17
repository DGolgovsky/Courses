// Random
vector<int> a(100);
generate(a.begin(), a.end(), [](){return rand() % 100;});

// 0, 1, 2, 3, ...
vector<int> b(a.size());
iota(b.begin(), b.end(), 0);

// c[i] = a[i] * b[i]
vector<int> c(b.size());
transform(a.begin(), a.end(), b.begin(),
          c.begin(), multiplies<int>());

// c[i] *= 2
transform(c.begin(), c.end(), c.begin(),
          [](int x){return x * 2;});

// sum c[i]
int init = 0; // base
int sum = accumulate(c.begin(), c.end(), init); // init += c::iterator
