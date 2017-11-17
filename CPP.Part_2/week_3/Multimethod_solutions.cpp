#include <typeinfo>
#include <typeindex>
#include <functional>
#include <map>

template<class Base, class Result, bool Commutative>
struct Multimethod2
{
	using F = std::function<Result (Base*, Base*)>;
	
    void addImpl(std::type_index t1, std::type_index t2, const F& f)
    {
		m.insert({ { t1, t2 }, f });	
    }

    bool hasImpl(Base * a, Base * b) const
    {
        return hasHidden(a, b) || (Commutative && hasHidden(b, a)); 
    }
    
    Result call(Base * a, Base * b) const
    {
    	return hasHidden(a, b) ? callHidden(a, b) : callHidden(b, a);
    }

private:
	mutable std::map<std::pair<std::type_index, std::type_index>, F> m; 
	
    bool hasHidden(Base * a, Base * b) const
    {
    	return m.count( { typeid(*a), typeid(*b) } );
	}
	
	Result callHidden(Base * a, Base * b) const
	{
		return m[{ typeid(*a), typeid(*b) }](a, b);
	}
};

//***************************************************************************

#include <functional>
#include <typeindex>
#include <iostream>
#include <typeinfo>
#include <cassert>
#include <map>

template<class Base, class Result, bool Commutative>
struct Multimethod2 {
    void addImpl(std::type_info const & t1, std::type_info const & t2, std::function<Result(Base *, Base *)> f) {
        auto p1 = std::make_pair(std::type_index(t1), std::type_index(t2));
        mp[p1] = f;
    }
    
    bool hasImpl(Base * a, Base * b) const {
        auto p1 = std::make_pair(std::type_index(typeid(*a)), std::type_index(typeid(*b)));
        if (Commutative) {
            auto p2 = std::make_pair(std::type_index(typeid(*b)), std::type_index(typeid(*a)));
            return mp.find(p1) != mp.end() || mp.find(p2) != mp.end();
        }
        return mp.find(p1) != mp.end();
    }
    
    Result call(Base * a, Base * b) const {
        auto p1 = std::make_pair(std::type_index(typeid(*a)), std::type_index(typeid(*b)));
        auto p2 = std::make_pair(std::type_index(typeid(*b)), std::type_index(typeid(*a)));
        if (mp.find(p1) != mp.end())
            return mp.at(p1)(a, b);
        assert(mp.find(p2) != mp.end());
        return mp.at(p2)(b, a);
    }
    
private:
    std::map<std::pair<std::type_index, std::type_index>, std::function<Result(Base *, Base*)>> mp;
};

//***************************************************************************
/*
Очень много повторяющегося кода: hasImpl и call отличаются только типом возвращаемого значения. Так же сомневаюсь, что в call применение мною нулевого указателя уместно. Но в данном тесте он неявно преобразуется в bool.
@Дмитрий_Тимофеев, > Так же сомневаюсь, что в call применение мною нулевого указателя уместно.
Правильно сомневаетесь. Добавил тест, чтобы такое решение не проходило.
В данном случае можете безопасно удалить эту строку, т.к. гарантируется, что call будет вызываться только для существующих методов.
*/
#include <typeinfo>
#include <typeindex>
#include <functional>
#include <map>
#include <utility>

// Base - базовый класс иерархии
// Result - тип возвращаемого значения мультиметода
// Commutative - флаг, который показывает, что
// мультиметод коммутативный (т.е. f(x,y) = f(y,x)).
template<class Base, class Result, bool Commutative>
struct Multimethod2
{
    using F = std::function<Result (Base*, Base*)>;
    using Key = std::pair<std::type_index, std::type_index>;
    // устанавливает реализацию мультиметода
    // для типов t1 и t2 заданных через typeid 
    // f - это функция или функциональный объект
    // принимающий два указателя на Base 
    // и возвращающий значение типа Result
    void addImpl(const std::type_info& t1, const std::type_info& t2, const F& f)
    {
        map.emplace(Key(std::type_index(t1), std::type_index(t2)), f);
    }

    // проверяет, есть ли реализация мультиметода
    // для типов объектов a и b
    bool hasImpl(Base * a, Base * b) const
    {
        // возвращает true, если реализация есть
        // если операция коммутативная, то нужно 
        // проверить есть ли реализация для b и а
        const std::type_index tiA(typeid(*a));
        const std::type_index tiB(typeid(*b));
        Key key = std::make_pair(tiA, tiB);
        if (map.find(key) != map.end())
            return true;
        if (Commutative) {
            std::swap(key.first, key.second);
            if (map.find(key) != map.end())
                return true;
        }
        return false; 
    }

    // Применяет мультиметод к объектам
    // по указателям a и b
    Result call(Base * a, Base * b) const
    {
        // возвращает результат применения реализации
        // мультиметода к a и b
        const std::type_index tiA(typeid(*a));
        const std::type_index tiB(typeid(*b));
        Key key = std::make_pair(tiA, tiB);
        auto it = map.find(key);
        if (it != map.end())
            return it->second(a, b);
        if (Commutative) {
            std::swap(key.first, key.second);
            it = map.find(key);
            if (it != map.end())
                return it->second(b, a);
        }
        return nullptr;
    }
    
    std::map<Key, F> map;
};

//***************************************************************************

#include <typeinfo>
#include <typeindex>
#include <functional>
#include <map>

// Base - базовый класс иерархии
// Result - тип возвращаемого значения мультиметода
// Commutative - флаг, который показывает, что
// мультиметод коммутативный (т.е. f(x,y) = f(y,x)).
template<class Base, class Result, bool Commutative>
struct Multimethod2
{
    // устанавливает реализацию мультиметода
	// для типов t1 и t2 заданных через typeid 
	// f - это функция или функциональный объект
	// принимающий два указателя на Base 
	// и возвращающий значение типа Result
    using Foo = std::function<Result(Base*, Base*)>;
	using Key = std::pair<std::type_index, std::type_index>;
	using Map = std::map<Key, Foo>;

	Map m_;
    
	void addImpl(const std::type_info& t1, const std::type_info& t2, Foo f)
	{
		Key k(t1, t2);
		m_.insert(std::make_pair(k, f));
	}

	// проверяет, есть ли реализация мультиметода
	// для типов объектов a и b
	bool hasImpl(Base* a, Base* b) const
	{
		// возвращает true, если реализация есть
		// если операция коммутативная, то нужно 
		// проверить есть ли реализация для b и а 
		Key k(std::type_index(typeid(*a)), std::type_index(typeid(*b)));
		bool bRet = (m_.find(k) != m_.end()) ? true : false;

		if (!bRet && Commutative)
		{
			k = std::make_pair(std::type_index(typeid(*b)), std::type_index(typeid(*a)));
			bRet = (m_.find(k) != m_.end()) ? true : false;
		}

		return bRet;
	}

	// Применяет мультиметод к объектам
	// по указателям a и b
	Result call(Base* a, Base* b) const
	{
		// возвращает результат применения реализации
		// мультиметода к a и b
		Result res;

		Key k(std::type_index(typeid(*a)), std::type_index(typeid(*b)));
		if (m_.find(k) != m_.end())
			res = m_.at(k)(a, b);
		else if (Commutative)
		{
			k = std::make_pair(std::type_index(typeid(*b)), std::type_index(typeid(*a)));
			if (m_.find(k) != m_.end())
				res = m_.at(k)(b, a);
		}

		return res;
	}
};

//***************************************************************************

#include <typeinfo>
#include <typeindex>
#include <functional>
#include <unordered_map>
// Base - базовый класс иерархии
// Result - тип возвращаемого значения мультиметода
// Commutative - флаг, который показывает, что
// мультиметод коммутативный (т.е. f(x,y) = f(y,x)).

using Key = std::pair<std::type_index, std::type_index>;

struct hash_name {
	size_t operator()(const Key &name) const
	{
		return name.first.hash_code() ^ name.second.hash_code();
	}
};
template<class Base, class Result, bool Commutative>
struct Multimethod2
{
	using Fun = std::function<Result(Base*, Base*)>;
	std::unordered_map<Key, Fun, hash_name> func;
	
	void addImpl(const std::type_info& t1, const std::type_info& t2, Fun f)
	{
		std::type_index t11 = std::type_index(t1);
		std::type_index t12 = std::type_index(t2);
		Key key(t11, t12);
		func.insert(std::make_pair(key, f));		
	}

	// проверяет, есть ли реализация мультиметода
	// для типов объектов a и b
	bool hasImpl(Base * a, Base * b) const
	{
		// возвращает true, если реализация есть
		// если операция коммутативная, то нужно 
		// проверить есть ли реализация для b и а
		bool find = false;
		auto it = func.find(Key(typeid(*a), typeid(*b)));
		if (it != func.end()) find = true;
		if (find) return find;
		if (Commutative)
		{
			it = func.find(Key(typeid(*b), typeid(*a)));
			if (it != func.end()) find = true;
		}
		return find;
	}

	// Применяет мультиметод к объектам
	// по указателям a и b
	Result call(Base * a, Base * b) const
	{
		// возвращает результат применения реализации
		// мультиметода к a и b
		Key key(typeid(*a), typeid(*b));
		if (!Commutative)
		{		
			return func.at(key)(a, b);
		}
		else
		{
			auto it = func.find(key);
			if(it != func.end()) return func.at(key)(a, b);
			Key key2(typeid(*b), typeid(*a));
			return func.at(key2)(b, a);
			
		}

	}
};
/*
@Anonymous_34815541, значительно лучше.
Однако
return name.first.hash_code() ^ name.second.hash_code();
лучше заменить на что-то вроде
return name.first.hash_code() ^ (name.second.hash_code() >> 1);
иначе все записи для пар одинаковых типов будут лежать в одной ячейке.

Ещё заметил вот это:
    std::type_index t11 = std::type_index(t1);
    std::type_index t12 = std::type_index(t2);
Это можно переписать так:
    std::type_index t11(t1);
    std::type_index t12(t2);
а можно и просто
    Key key(t1, t2);

@Anonymous_34815541, странно, взял Ваше решение, заменил на
  void addImpl(const std::type_info& t1, const std::type_info& t2, Fun f)
  {
    Key key(t1, t2);
    func.insert(std::make_pair(key, f));   
  }
и всё работает =)
*/

//***************************************************************************

#include <typeinfo>
#include <typeindex>

#include <map>
#include <functional>

template<class Base, class Result, bool Commutative>
struct Multimethod2
{
    using Func = std::function<Result(Base*, Base*)>;

    size_t key(std::type_index t1, std::type_index t2) const
    {
        return t1.hash_code() + 2 * t2.hash_code();
    }

    size_t key(Base* a, Base* b) const
    {
        return key(typeid(*a), typeid(*b));
    }

    bool testKey(Base* a, Base* b) const
    {
        return fMap.find(key(a, b)) != fMap.cend();
    }

    void addImpl(std::type_index t1, std::type_index t2, Func f)
    {
        fMap[key(t1, t2)] = f;
    }

    // проверяет, есть ли реализация мультиметода
    // для типов объектов a и b
    bool hasImpl(Base * a, Base * b) const
    {
        // возвращает true, если реализация есть
        // если операция коммутативная, то нужно
        // проверить есть ли реализация для b и а
        
        return testKey(a, b) || (Commutative && testKey(b, a));
    }

    // Применяет мультиметод к объектам
    // по указателям a и b
    Result call(Base * a, Base * b) const
    {
        return testKey(a, b) ? fMap.at(key(a, b))(a, b)
                             : Commutative ? fMap.at(key(b, a))(b, a)
                                           : Result();
    }

    std::map<size_t, Func> fMap;
};
