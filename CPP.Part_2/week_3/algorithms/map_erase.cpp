std::map<string, int> m;

// Wrong
for (auto it = m.begin(); it != m.end(); ++it)
    if (it->second == 0)
        m.erase(it); // invalidate iterator, can't increment after

// Correct
for (auto it = m.begin() ; it != m.end(); /* nothing */)
    if (it->second == 0)
        it = m.erase(it); // return ++it
    else
        ++it;

// C++03
for (map<string,int>::iterator it  = m.begin();
                               it != m.end()  ; )
    if (it->second == 0)
        m.erase(it++);
    else
        ++it;
