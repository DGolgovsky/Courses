vector<int> v = randomVector<int>();

auto med = v.begin() + v.size() / 2;
nth_element(v.begin(), med, v.end());
cout << "Median: " << *med;

auto m = partition(v.begin(), v.end(),
                  [](int x){return x % 2 == 0;});
sort(v.begin(), m);
v.erase(m, v.end());

