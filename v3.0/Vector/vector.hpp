#pragma once

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <initializer_list>
#include <iterator>
#include <utility>

/*
Atkuriamas STL std::vector tam kad ismokt kurt savo konteineri

TODO:


Documentation
*/
namespace my{
template<typename T>
/// Paprastas vektoriaus konteineris, imituoja std::vector
/// @tparam T elementu tipas
class vector {
private:
    int size_;                              //kiek elementu vektoriuje
    int space_;                             //kiek atminties uzrezervuota
    T* element_;                            //patys tie elementai (tiksliau pointeris i array prazia)

public:
    using size_type = int;
    using value_type = T;
    using iterator = T*;
    using const_iterator = const T*;
    /// default konstruktorius
    vector() :size_{0} ,space_{0}, element_{nullptr} {}

    /// Konstruktuoja vektoriu su pradiniu dydziu
    /// @param s pradinis elementu skaicius
    /// @throws std::length_error jei s < 0
    explicit vector(int s)                                   //constructor
        : size_{s}, space_{s}, element_{ new T[s] }
        { 
            if(s < 0)
                throw std::length_error("size cannot be < 0 for a vector");
            for(int i=0; i<s; ++i) 
                element_[i] = T{}; 
        }

    /// Konstrukcija is initializer_list
    /// @param lst sarasas elementu
    vector(std::initializer_list<T> lst)                    // initilizer list {} constuctor
        :size_{static_cast<int>(lst.size())},
        space_{static_cast<int>(lst.size())},
        element_{new T[size_]}
        { std::copy(lst.begin(), lst.end(), element_); }

    /// Range constructor: sukuria vektoriu kopijuojant intervala [first, last)
    template<typename InputIt> vector(InputIt first, InputIt last)
        : size_{ static_cast<int>(std::distance(first, last)) },
        space_{ static_cast<int>(std::distance(first, last)) }, 
        element_{ new T[size_] }
        { std::copy(first, last, element_); }    //range constructor

    /// Copy constructor
    /// @param v kitas vector
    vector(const vector<T>& v);                              //copy constructor

    /// Copy assignment operator
    /// @param v kitas vector
    /// @return reference i this
    vector& operator=(const vector<T>&v);                    //copy assignment

    /// Move constructor
    /// @param v movable vector
    vector(vector<T>&& v);                                   //move constructor

    /// Move assignment
    /// @param v movable vector
    /// @return reference i this
    vector& operator=(vector<T>&& v);                        //move assignment

    /// Destruktorius, atlaisvina dinamine atmintyje saugoma masyva
    ~vector() { delete[] element_; }                         //destructor

    /// Grazina vektoriaus dydzi (kiek elementu yra)
    /// @return elementu skaicius
    size_type size() const { return size_; }                 //current size of vector

    /// Griztina maksimalu galima dydzio skaiciu (apytiksliai)
    int max_size() const { return INT_MAX / sizeof(T); }     //max size

    /// Nepatikrintas indekso operatorius
    /// @param n indekso pozicija
    /// @return reference i elementa
    T& operator[] (int n) { return element_[n]; }                   //operatorius []
    /// Nepatikrintas indekso operatorius (const versija)
    const T& operator[] (int n) const { return element_[n]; };     //const versija ant const vektoriu

    /// Tikrintas prieigos metodas, metamas out_of_range jei uz ribu
    /// @param n indeksas
    /// @return reference i elementa
    T& at(int n);                                           //checked access            
    const T& at(int n) const;                               //const checked access
    
    /// Grazina pirma elemento reference
    T& front() { return element_[0]; }                      //return first element reference
    const T& front() const { return element_[0]; }          //const version

    /// Grazina paskutinio elemento reference
    T& back() { return element_[size_ - 1]; }               //return last element reference
    const T& back() const { return element_[size_ - 1]; }   //const version

    /// Patikrina ar vektorius tuscias
    /// @return true jei tuscias
    bool empty() const { return begin() == end(); }         //check if container empty

    /// Getteris (kopija) elemento
    T get(int n) const { return element_[n]; }              //getteris
    /// Setteris elemento
    void set(int n, T val) { element_[n] = val; }           //setteris
    
    /// Rezervuoja atminties vieta be elemento inicializacijos
    /// @param newalloc naujas rezervuotas elementu kiekis
    void reserve(int newalloc);                             //reservuoti naujos vietos

    /// Grazina kapaciteta (kiek vietos uzrezervuota)
    size_type capacity() const { return space_; }           //kiek vietos yra funk

    /// Prideda elementa i pabaiga (lvalue)
    /// @param val elementas
    void push_back(const T& val);                           //idet elementa T i gala vektorius
    /// Prideda elementa i pabaiga (rvalue)
    void push_back(T&& val);

    /// Pakeicia vektoriaus dydzio reiksme, jei reikia inicializuoja naujus elementus
    /// @param newsize naujas dydis
    /// @param val reiksme naujiems elementams
    void resize(int newsize, T val = T());                  //pakeist didy vectoriaus

    /// Pasalina paskutini elementa
    void pop_back();                                        //remove last element of container

    /// Grazina iteratoriu i pradzia
    iterator begin() { return element_; }                   //pradzios iteratorius
    const_iterator begin() const { return element_; }
    const_iterator cbegin() const noexcept { return element_; }      //const pradzios iteratorius

    std::reverse_iterator<iterator> rbegin(){ return std::reverse_iterator<iterator>(end()); }
    std::reverse_iterator<const_iterator> crbegin() const { return std::reverse_iterator<const_iterator>(cend()); }
    
    /// Grazina iteratoriu i pabaiga
    iterator end() { return element_ + size_;}              //galo iteratorius
    const_iterator end() const { return element_ + size_; }
    const_iterator cend() const noexcept { return element_ + size_; }//const galo iteratorius
    
    std::reverse_iterator<iterator> rend() { return std::reverse_iterator<iterator>(begin()); } //reverse iterator
    std::reverse_iterator<const_iterator> crend() const { return std::reverse_iterator<const_iterator>(cbegin()); }

    /// Iteratoriaus i pozicija p istrynimas
    /// @param p iteratorius i istrinama elementa
    /// @return iteratorius i elementa po istrynimo
    iterator insert(iterator p, const T& val);
    iterator erase(iterator p);
    iterator erase( iterator first, iterator last);

    /// Istrina visus elementus (neatlaisvina atminties)
    void clear() { size_ = 0; }                             //allocated space still belongs to the container

    /// Uzpildo vektoriaus pirma n elementu reiksme
    

    /// Grazina rodykle i vidini duomenu masyva
    T* data() { return element_; }                          //public access to element_
    const T* data() const { return element_; }              //const public access to element_

    /// Sumazina rezervuota vieta iki dydzio
    void shrink_to_fit();                                   //sumazint space_ = size_
    
    /// Apkeicia su kitu vector'iumi
    void swap(vector& other) noexcept;
    
    /// In-place konstravimas paskutinio elemento
    template<typename... Args>
    void emplace_back(Args&&... args);

    template<typename... Args>
    iterator emplace(iterator pos, Args&&... args); 

    /// Uzpildo vektoriu n elementu su val
    void assign(size_type n, const T& val);                 //fill assign
    /// Uzpildo vektoriu intervale [first,last)
    template<typename InputIt>
    void assign(InputIt first, InputIt last);               //range assign
    /// Uzpildo vektoriu is initializer list
    void assign(std::initializer_list<T> ilist);            //initializer list assign
};

template<typename T>
bool operator==(const vector<T>& v1, const vector<T>& v2)
{
    if(v1.size() != v2.size())
        return false;
    for(int i = 0; i < v1.size(); ++i)
        if(v1[i] != v2[i])
            return false;
    return true;    
}



template<typename T>
bool operator!=(const vector<T>& v1, const vector<T>& v2)
{ return !(v1 == v2); }

template<typename T>
bool operator<(const vector<T>& v1, const vector<T>& v2)
{
    return std::lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end());
}

template<typename T>
bool operator<=(const vector<T>& v1, const vector<T>& v2)
{ return !(v2 < v1); }

template<typename T>
bool operator>(const vector<T>& v1, const vector<T>& v2)
{ return v2 < v1; }

template<typename T>
bool operator>=(const vector<T>& v1, const vector<T>& v2)
{ return !(v1 < v2); }

//copy constructor
template<typename T>
vector<T>::vector(const vector<T>& v)
    : size_(v.size_), space_(v.space_), element_{new T[v.size_]}
        //allocatint memory praeito vectoriaus dydzio ir initicializuoti kopijuojant
    {
            std::copy(v.element_, v.element_ + v.size_, element_); 
    }

//copy assignment
template<typename T>
vector<T>& vector<T>::operator=(const vector<T>& v)
{
    //std::cerr << "copy assignment called\n";
    if (this==&v) return *this; //self assignment

    if(v.size_<= space_) //jei nereik allocatint
    {
        for(int i = 0; i < v.size_; i++)
            element_[i] = v.element_[i];
        size_ = v.size_;
        return *this;
    }

    T* p = new T[v.size_];
    for(int i = 0; i<v.size_; i++)
        p[i] = v.element_[i];
    
    delete[] element_;
    space_ = size_ = v.size_;
    element_ = p;
    return *this;
}
//move constructor
template <typename T>
vector<T>::vector(vector<T>&& v)
    :size_{v.size_}, space_{v.space_}, element_{v.element_}
{
    v.space_ = 0;
    v.size_ = 0;
    v.element_ = nullptr;
}
//move assignment
template <typename T>
vector<T>& vector<T>::operator=(vector<T>&& v)
{
    if(this != &v){                 //protection against self assignment
        delete[] element_;
        element_ = v.element_;
        size_ = v.size_;
        space_ = v.space_;
        v.element_ = nullptr;
        v.space_ = 0;
        v.size_ = 0;
    }
    return *this;
}

template <typename T>
void vector<T>::reserve(int newalloc)
{
    
    if (newalloc<=space_)                // never decrease allocation
        return;
    //std::cerr << "reserve called, newalloc=" << newalloc << " size_=" << size_ << "\n";
    T* p = new T[newalloc];        // allocate new space
    for (int i=0; i<size_; ++i)            // copy old elements
        p[i] = element_[i];
    delete[] element_;                      // deallocate old space
    element_ = p;
    space_ = newalloc;
}

template<typename T>
void vector<T>::resize(int newsize, T val)
{
    reserve(newsize);

    for(int i = size_; i < newsize; i++)
        element_[i] = val;
    size_ = newsize;
}

template<typename T>
void vector<T>::push_back(const T& val)
{
    if(space_ == 0)
        reserve(8);
    else if(size_ == space_)
        reserve(2*space_);
    element_[size_] = val;
    size_++;
}

template<typename T>
void vector<T>::push_back(T&& val)
{
    if(space_ == 0)
        reserve(8);
    else if(size_ == space_)
        reserve(2*space_);
    element_[size_] = std::move(val);
    size_++;
}

template<typename T>
void vector<T>::pop_back()
{
    if(size_ == 0)
        throw std::out_of_range("used pop_back() on empty vector!");
    size_--;
}

template<typename T>
T& vector<T>::at(int n)
{
    if (n<0 || size_<= n)
        throw std::out_of_range("vector::at accessed element out of range");
    return element_[n];
}

template<typename T>
const T& vector<T>::at(int n) const
{
    if (n<0 || size_<= n)
        throw std::out_of_range("vector::at accessed element out of range");
    return element_[n];
}

template<typename T>
typename vector<T>::iterator vector<T>::erase(iterator p)
{
    if(p == end())
        return p;
    std::move(p+1, end(), p); //move elements from p+1, until end() to p
    --size_;
    return p;
}

template<typename T>
typename vector<T>::iterator vector<T>::erase(iterator first, iterator last)
{
    if(first == last) 
        return first;
    auto n = last - first;
    std::move(last, end(), first);
    size_ -= n;
    return first;
}

template<typename T>
typename vector<T>::iterator vector<T>::insert(iterator p, const T& val)
{
    int index = p-begin();         //jeigu reserve pakeistu vektoriaus vieta atmintyje
    if(size() == capacity())
        reserve(size() == 0?8:2*size());  
    p = begin() + index;          //uzdet p kur pries tai buvo relative to vector index
    std::move_backward(p, end(), end() + 1);
    *(begin() + index) = val;
    size_++;
    return p;
}

template<typename T>
void vector<T>::shrink_to_fit()
{
    if(size_ == space_)
        return;
    T* p = new T[size_];
    std::move(begin(), end(), p);
    delete[] element_;
    element_ = p;
    space_ = size_;
}

template<typename T>
void vector<T>::swap(vector& other) noexcept
{
    std::swap(element_, other.element_);
    std::swap(space_, other.space_);
    std::swap(size_, other.size_);
}

template<typename T>
void vector<T>::assign(size_type n, const T& val)
{
    if(n > space_)
        reserve(n);
    for(int i = 0; i < n; i++)
        element_[i] = val;
    size_ = n;
}

template<typename T>
template<typename InputIt>
void vector<T>::assign(InputIt first, InputIt last)
{
    int n = static_cast<int>(std::distance(first, last));
    if(n > space_)
        reserve(n);
    std::copy(first, last, element_);
    size_ = n;
}

template<typename T>
void vector<T>::assign(std::initializer_list<T> ilist)
{

    int n = ilist.size();
    if(n > space_)
        reserve(n);
    std::copy(ilist.begin(), ilist.end(), element_);
    size_ = n;
}

template<typename T>
template<typename... Args>
void vector<T>::emplace_back(Args&&... args)
{
    if(space_ == 0)
        reserve(8);
    else if(size_ == space_)
        reserve(2*space_);

    new(&element_[size_]) T(std::forward<Args>(args)... );
    ++size_;
}

template<typename T>
template<typename... Args>
typename vector<T>::iterator vector<T>::emplace(iterator pos, Args&&... args)
{
    int index = pos - begin();
    if(size() == capacity())
        reserve(size() == 0?8:2*size());  
    pos = begin() + index;          //uzdet p kur pries tai buvo relative to vector index
    std::move_backward(pos, end(), end() + 1);
    new(&*pos) T(std::forward<Args>(args)... );
    size_++;
    return pos;
}
}