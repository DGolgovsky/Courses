vector<int> v = {2, 5, 1, 5, 8, 5, 2, 5, 8};
remove(v.begin(), v.end(), 5); // removes all 5?

v.size(); // not modified
v == {2, 1, 8, 2, 8, 5, 2, 5, 8}
//                  ^   std::remove return iterator after 8

vector<int> v = {2, 5, 1, 5, 8, 5, 2, 5, 8};
v.erase(remove(v.begin(), v.end(), 5), v.end()); // removes all 5
v == {2, 1, 8, 2, 8}

list<int> l = {2, 5, 1, 5, 8, 5, 2, 5, 8};
l.remove(5); // really removes all 5

vector<int> v = {1,2,2,2,3,4,5,5,5,6,7,8,9};
v.erase(unique(v.begin(), v.end()), v.end());

list<int> l = {1,2,2,2,3,4,5,5,5,6,7,8,9};
l.unique();

