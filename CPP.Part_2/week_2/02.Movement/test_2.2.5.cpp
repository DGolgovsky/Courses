/**
 * Дополните класс Array перемещающим конструктором и перемещающим оператором присваивания.
 * Замечание: все объявленные методы класса Array уже реализованы.
 */

template<class T>
struct Array
{
    // все объявленные ниже методы уже реализованы
    explicit Array(std::size_t size = 0);
    Array(Array const& a);
    Array & operator=(Array const& a);
    ~Array();

    size_t size() const;
    T &         operator[](std::size_t i);
    T const&    operator[](std::size_t i) const;

    // реализуйте перемещающий конструктор
    Array (Array && rhs)
        : data_{rhs.data_}
        , size_(rhs.size_)
    {
        rhs.data_ = nullptr;
        rhs.size_ = 0;
    }

    // реализуйте перемещающий оператор присваивания
    Array &operator=(Array &&rhs) {
        Array copy{std::move(rhs)};
        std::swap(data_, copy.data_);
        std::swap(size_, copy.size_);
        return *this;
    }

private:
    std::size_t  size_;
    T *     data_;
};
