#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <memory>

using std::cout;
/*
Atkuriamas STL std::vector tam kad ismokt kurt savo konteineri

TODO:
Constructors & Destructor

Fill constructor (n, val)
Range constructor (from iterators)
Initializer list constructor

Element Access

at() (with bounds checking)
front()
back()
data()

Iterators

begin() / end()
cbegin() / cend()
rbegin() / rend()
crbegin() / crend()

Capacity


max_size()
capacity()
empty()
resize()
shrink_to_fit()

Modifiers

pop_back()
insert()
erase()
clear()
assign()
emplace()
emplace_back()
swap()

Operators

operator== / operator!=
operator< / operator<= / operator> / operator>=
*/


template<typename T, typename A = std::allocator<T>>
class vector {
private:
    A alloc_;
    int size_; //kiek elementu vektoriuje
    T* element_; //patys tie elementai (tiksliau pointeris i array prazia)
    int space_; //kiek atminties uzrezervuota

public:
    vector() :size_{0} , element_{nullptr},space_{0} {}      //default constructor
    vector(const vector<T,A>& v);                            //copy constructor
    vector& operator=(const vector<T, A>&v);                 //copy assignment
    vector(vector<T, A>&& v);                                //move constructor
    vector& operator=(vector<T, A>&& v);                     //move assignment
    ~vector() { delete[] element_; }                         //destructor
        
    explicit vector(int s) //constructor
        : size_{s}, element_{ new T[s] }
        { for(int i=0; i<s; ++i) element_[i] = 0; }

    int size() const { return size_; } //current size of vector

    T& operator[] (int n) { return element_[n]; } //operatorius []
    T operator[] (int n) const { return element_[n]; }; //const versija ant const vektoriu kad pasakytume kad nekeisime su [] operatorium
    
    T get(int n) const { return element_[n]; } //getteris
    void set(int n, T v) { element_[n] = v; } //setteris
    
    void reserve(int newalloc); //reservuoti naujos vietos
    int capacity() const { return space_; } //kiek vietos yra funk
    void push_back(T d);
    void resize(int newsize, T val = T());

    T* begin() const { return element_; }
    T* end() const { return element_ + size_;}
};
template<typename T, typename A>
bool operator==(const vector<T, A>& v1, const vector<T, A>& v2)
{
    if(v1.size() != v2.size())
        return false;
    for(int i = 0; i < v1.size(); ++i)
        if(v1[i] != v2[i])
            return false;
    return true;    
}

template<typename T, typename A>
bool operator!=(const vector<T, A>& v1, const vector<T, A>& v2)
{ return !(v1 == v2); }

//copy constructor
template<typename T, typename A>
vector<T, A>::vector(const vector<T, A>& v)
    : alloc_(v.alloc_), size_(v.size_), element_{new T[v.size_]}, space_(v.space_) 
        //allocatint memory praeito vectoriaus dydzio ir initicializuoti kopijuojant
    {
            std::copy(v.element_, v.element_ + v.size_, element_); 
    }

//copy assignment
template<typename T, typename A>
vector<T, A>& vector<T, A>::operator=(const vector<T, A>& v)
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
template <typename T, typename A>
vector<T, A>::vector(vector<T, A>&& v)
    :size_{v.size_}, element_{v.element_}, alloc_
{
    v.size_ = 0;
    v.element_ = nullptr;
}
//move assignment
template <typename T, typename A>
vector<T, A>& vector<T, A>::operator=(vector<T, A>&& v)
{
    delete[] element_;
    element_ = v.element_;
    size_ = v.size_;
    v.element_ = nullptr;
    v.size_ = 0;
    return *this;
}

template <typename T, typename A>
void vector<T, A>::reserve(int newalloc)
{
    if(newalloc <= space_) return;                //nesumazint vietos netycia

    T* p = alloc_.allocate(newalloc)            //allocatint naujos vietos

    for(int i = 0; i<size_; i++)                
        alloc_.construct(&p[i], element_[i]);       //deep copy
    
    for(int i = 0; i < size_; i++)
        alloc_.destroy(&elem[i]);               //istrint sena
    alloc_.deallocate(element_, space_);
    element_ = p;                               //reassigntint pointeri
    space_ = newalloc;                          //max vieta padidejo
}

template<typename T, typename A>
void vector<T, A>::resize(int newsize, T val)
{
    reserve(newsize);

    if(newsize < 0)
        throw std::length_error("vector::resize");

    for(int i = size_; i < newsize; i++)
        alloc_.construct(&elem[i], val);

    for(int i = newsize, )
    
    size_ = newsize;
}

template<typename T, typename A>
void vector<T, A>::push_back(T d)
{
    if(space_ == 0)
        reserve(8);
    else if(size_ == space_)
        reserve(2*space_);
    alloc_.construct(&element_[size_], cal)
    ++size_;
}

int main()
try{
    vector<double> v;
    v.resize(5);
    cout << "v size: " << v.size() << "\n";

    v.resize(10, 5.0);

    cout << "v resize size:  " << v.size() << "\n";

    for(int i = 0; i < v.size(); i++)
        cout << v[i] << "\n";
    
    return 0;
}
catch(std::length_error& e)
{
    std::cerr << "error: " << e.what() << "\n";
}