template<class T>
struct Array
{
    // все объявленные ниже методы уже реализованы
    explicit Array(size_t size = 0);
    Array(Array const& a);
   
    Array & operator=(Array const& a);
    
    ~Array();

    size_t size() const;
    T &         operator[](size_t i);
    T const&    operator[](size_t i) const;

    // реализуйте перемещающий конструктор
	Array(Array && a) {
		size_ = a.size_;
		a.size_ = 0;
		data_ = a.data_;
		a.data_ = nullptr;
	};
	// реализуйте перемещающий оператор присваивания
	Array & operator=(Array && a) {
		size_t t = a.size_;
		a.size_ = size_;
		size_ = t;

		T* tt = a.data_;
		a.data_ = data_;
		data_ = tt;
		return *this;
	};
private:    
    size_t  size_;
    T *     data_;    
};
