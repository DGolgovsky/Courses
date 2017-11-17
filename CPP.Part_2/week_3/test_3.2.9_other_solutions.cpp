template<class It>
size_t max_increasing_len(It p, It q)
{
    size_t size = 1;
    size_t size_cur = 1;
    It prev = p;    
        
    while(p!=q) {
        if (*prev<*p) {
        	++size_cur;
        }
        else {
            if (size_cur>size) size = size_cur;
            size_cur = 1;             
        }
        prev = p;
        p++;
    }
    
    return (size>size_cur)? size:size_cur;
}
// -----------------------------
#include <iterator>

template<class It>
size_t max_increasing_len(It p, It q)
{
  int max = 1;
  int temp = 1;
  for(;p != std::prev(q); p++) {
    (*p < *(std::next(p))) ? temp++ : temp = 1;
    if (temp > max) {
      max = temp;
    }
  }
  return max;
}
// -----------------------------
#include <algorithm>
template<class It>
size_t max_increasing_len(It p, It q)
{
	if (p == q) return 0;	
	size_t m = 1;
	size_t t = 1;
	for (++p; p != q; ++p) {
		if (*p <= *std::prev(p)) t = 0;
		m = std::max(m, ++t);
	}
	return std::max(m, t);
}
// -----------------------------
#include <algorithm>
template<class It>
size_t max_increasing_len(It p, It q)
{
    if (p == q)
        return 0;

    size_t max_len{0}, curr_len {0};
    for (auto el = p; el != q; el++)
    {
        curr_len = (*el > *std::prev(el)) ? curr_len + 1 : 0;
        max_len = std::max(max_len, curr_len);
    }

    return std::max(max_len, curr_len) + 1;
}
// -----------------------------
template<class T>
std::size_t max_increasing_len(T &&b, T &&e){
	std::size_t maxLen = 0;
	if(b != e){
		T pc = b, c = ++b;
		std::size_t len = 1;		
		
		while (c != e) {
			if (*pc < *c)
				len += 1;
			else {
				maxLen = maxLen < len ? len : maxLen;
				len = 1;
			}
			pc = c++;
		}

		maxLen = maxLen < len ? len : maxLen;
	}	

	return maxLen;
}
// -----------------------------

