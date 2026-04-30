#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <memory>
#include <initializer_list>

using std::cout;
/*
Atkuriamas STL std::vector tam kad ismokt kurt savo konteineri

TODO:
Constructors & Destructor

Fill constructor (n, val)
Range constructor (from iterators)
Initializer list constructor

Element Access

front()
back()
data()

Iterators

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


operator< / operator<= / operator> / operator>=
*/

template<typename T>
class vector {
private:
    int size_; //kiek elementu vektoriuje
    T* element_; //patys tie elementai (tiksliau pointeris i array prazia)
    int space_; //kiek atminties uzrezervuota

public:
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

    vector(const vector<T>& v);                              //copy constructor
    vector& operator=(const vector<T>&v);                    //copy assignment
    vector(vector<T>&& v);                                   //move constructor
    vector& operator=(vector<T>&& v);                        //move assignment
    ~vector() { delete[] element_; }                         //destructor

    int size() const { return size_; }                       //current size of vector

    T& operator[] (int n) { return element_[n]; }                   //operatorius []
    const T& operator[] (int n) const { return element_[n]; };     //const versija ant const vektoriu kad pasakytume kad nekeisime su [] operatorium

    T& at(int n);                                           //checked access            
    const T& at(int n) const;                               //const checked access
    
    T& front() { return element_[0]; }                      //return first element reference
    const T& front() const { return element_[0]; }           //const version

    T& back() { return element_[size_ - 1]; }                   //return last element reference
    const T& back() const { return element_[size_ - 1]; }       //const version

    T get(int n) const { return element_[n]; }              //getteris
    void set(int n, T val) { element_[n] = val; }           //setteris
    
    void reserve(int newalloc);                             //reservuoti naujos vietos
    int capacity() const { return space_; }                 //kiek vietos yra funk
    void push_back(T d);
    void resize(int newsize, T val = T());

    T* begin() const { return element_; }                   //pradzios iteratorius
    const T* cbegin() const { return element_; }            //const pradzios iteratorius

    
    T* end() const { return element_ + size_;}              //galo iteratorius
    const T* cend() const { return element_ + size_; }      //const galo iteratorius
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
    T* p = new double[newalloc];        // allocate new space
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
void vector<T>::push_back(T d)
{
    if(space_ == 0)
        reserve(8);
    else if(size_ ==space_)
        reserve(2*space_);
    element_[size_] = d;
    size_++;
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