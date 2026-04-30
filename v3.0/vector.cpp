#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <initializer_list>
#include <iterator>
#include <utility>


using std::cout;
/*
Atkuriamas STL std::vector tam kad ismokt kurt savo konteineri

TODO:
Modifiers

emplace()
emplace_back()

Operators

operator< / operator<= / operator> / operator>=

TESTS for all functions
Documentation
*/

template<typename T>
class vector {
private:
    int size_;                              //kiek elementu vektoriuje
    T* element_;                            //patys tie elementai (tiksliau pointeris i array prazia)
    int space_;                             //kiek atminties uzrezervuota

public:
    using size_type = int;
    using value_type = T;
    using iterator = T*;
    using const_iterator = const T*;
    vector() :size_{0} , element_{nullptr},space_{0} {}      //default constructor

    explicit vector(int s)                                   //constructor
        : size_{s}, element_{ new T[s] }
        { 
            if(s < 0)
                throw std::length_error("size cannot be < 0 for a vector");
            for(int i=0; i<s; ++i) 
                element_[i] = T{}; 
        }

    vector(std::initializer_list<T> lst)                    // initilizer list {} constuctor
        :size_{static_cast<int>(lst.size())},
        element_{new T[size_]}
        { std::copy(lst.begin(), lst.end(), element_); }

    template<typename InputIt> vector(InputIt first, InputIt last);    //range constructor

    vector(const vector<T>& v);                              //copy constructor
    vector& operator=(const vector<T>&v);                    //copy assignment
    vector(vector<T>&& v);                                   //move constructor
    vector& operator=(vector<T>&& v);                        //move assignment
    ~vector() { delete[] element_; }                         //destructor

    size_type size() const { return size_; }                 //current size of vector
    int max_size() const { return INT_MAX / sizeof(T); }     //max size

    T& operator[] (int n) { return element_[n]; }                   //operatorius []
    const T& operator[] (int n) const { return element_[n]; };     //const versija ant const vektoriu kad pasakytume kad nekeisime su [] operatorium

    T& at(int n);                                           //checked access            
    const T& at(int n) const;                               //const checked access
    
    T& front() { return element_[0]; }                      //return first element reference
    const T& front() const { return element_[0]; }          //const version

    T& back() { return element_[size_ - 1]; }               //return last element reference
    const T& back() const { return element_[size_ - 1]; }   //const version

    bool empty() const { return begin() == end(); }         //check if container empty

    T get(int n) const { return element_[n]; }              //getteris
    void set(int n, T val) { element_[n] = val; }           //setteris
    
    void reserve(int newalloc);                             //reservuoti naujos vietos
    size_type capacity() const { return space_; }           //kiek vietos yra funk
    void push_back(const T& val);                           //idet elementa T i gala vektorius ir jei ka allocatint mem
    void push_back(T&& val);
    void resize(int newsize, T val = T());                  //pakeist didy vectoriaus, jei neduodamas value tai sukonstruos su default konstrukt.

    void pop_back();                                        //remove last element of container

    iterator begin() { return element_; }                   //pradzios iteratorius
    const_iterator cbegin() const { return element_; }      //const pradzios iteratorius

    iterator rbegin(){ return std::reverse_iterator<iterator>(begin()); }
    const_iterator crbegin() const { return std::reverse_iterator<const_iterator>(cbegin()); }
    
    iterator end() { return element_ + size_;}              //galo iteratorius
    const_iterator cend() const { return element_ + size_; }//const galo iteratorius
    
    iterator rend() { return std::reverse_iterator<iterator>(end()); } //reverse iterator
    const_iterator crend() const { return std::reverse_iterator<const_iterator>(cend()); }

    iterator insert(iterator p, const T& val);
    iterator erase(iterator p);

    void clear() { size_ = 0; }                             //allocated space still belongs to the container but cant access with at()

    void assign(size_type count, const T& val);

    T* data() { return element_; }                          //public access to element_
    const T* data() const { return element_; }              //const public access to element_

    void shrink_to_fit();                                   //sumazint space_ = size_
    
    void swap(vector& other) noexcept;
    
    template<typename... Args>
    void emplace_back(Args&&... Args);

    void assign(size_type n, const T& val);                 //fill assign
    template<typename InputIt>
    void assign(InputIt first, InputIt last);               //range assign
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

//copy constructor
template<typename T>
vector<T>::vector(const vector<T>& v)
    : size_(v.size_), element_{new T[v.size_]}, space_(v.space_) 
        //allocatint memory praeito vectoriaus dydzio ir initicializuoti kopijuojant
    {
            std::copy(v.element_, v.element_ + v.size_, element_); 
    }

//copy assignment
template<typename T>
vector<T>& vector<T>::operator=(const vector<T>& v)
{
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
    :size_{v.size_}, element_{v.element_}, space_{v.space_}
{
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
        v.element_ = nullptr;
        v.size_ = 0;
    }
    return *this;
}

template <typename T>
void vector<T>::reserve(int newalloc)
{
    if (newalloc<=space_)                // never decrease allocation
        return;
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
template<typename InputIt>
vector<T>::vector(InputIt first, InputIt last) 
    : size_{ static_cast<int>(std::distance(first, last)) },
    space_{size_},
    element_{ new T[size_] }
{ std::copy(first, last, element_); }

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
    size_ = static_cast<int>(std::distance(first, last));
    if(distance > space_)
        reserve(distance);
    std::copy(first, last, element_);
}

template<typename T>
void vector<T>::assign(std::initializer_list<T> ilist)
{
    size_ = ilist.size();
    if(size_ > space_)
        reserve(size_);
    std::copy(ilist.begin(), ilist.end(), element_);
}

int main()
try{
    vector<double> v = { 1, 2, 3 ,4 ,5};
    cout << "v size: " << v.size() << "\n";

    v.push_back(6);
    cout << "v size: " << v.size() << "\n";
    for(int i = 0; i < v.size(); i++)
        cout << v.at(i) << "\n";

    cout << v.front() << " " << v.back() << std::endl;
    
    return 0;
}
catch(std::length_error& e)
{
    std::cerr << "error: " << e.what() << "\n";
}
catch(std::out_of_range& e)
{
    std::cerr << "error: " << e.what() << "\n";
}