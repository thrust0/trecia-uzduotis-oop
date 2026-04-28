#include <iostream>
#include <stdexcept>
#include <algorithm>

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
class vector {
private:
    int size_; //kiek elementu vektoriuje
    double* element_; //patys tie elementai (tiksliau pointeris i array pradzia)
    int space_; //kiek atminties uzrezervuota

public:
    vector() :size_{0} , element_{nullptr},space_{0} {} //default constructor
    vector(const vector& v);                            //copy constructor
    vector& operator=(const vector& v);                 //copy assignment
    vector(vector&& v);                                 //move constructor
    vector& operator=(vector&& v);                      //move assignment
    ~vector() { delete[] element_; }                    //destructor
        
    explicit vector(int s) //constructor
        : size_{s}, element_{ new double[s] }
        { for(int i=0; i<s; ++i) element_[i] = 0; }

    int size() const { return size_; } //current size of vector

    double& operator[] (int n) { return element_[n]; } //operatorius []
    double operator[] (int n) const { return element_[n]; }; //const versija ant const vektoriu kad pasakytume kad nekeisime su [] operatorium
    
    double get(int n) const { return element_[n]; } //getteris
    void set(int n, double v) { element_[n] = v; } //setteris
    
    void reserve(int newalloc); //reservuoti naujos vietos
    int capacity() const { return space_; } //kiek vietos yra funk

    void push_back(double d);

    void resize(int newsize);

};
//copy constructor
vector::vector(const vector& v)
    :size_(v.size_), element_{new double[v.size_]} 
        //allocatint memory praeito vectoriaus dydzio ir initicializuoti kopijuojant
    {
        std::copy(v.element_, v.element_ + v.size_, element_); 
    }

//copy assignment
vector& vector::operator=(const vector& v)
{
    double* p = new double[v.size_]; //allocatinam naujos vietos
    std::copy(v.element_, v.element_ + v.size_, p);
    delete[] element_; //istrinam "v2" vectoriaus senus elementus
    element_ = p; //prisikiram jam p elementus
    size_ = v.size_;
    return *this;
}
//move constructor
vector::vector(vector&& v)
    :size_{v.size_}, element_{v.element_}
{
    v.size_ = 0;
    v.element_ = nullptr;
}
//move assignment
vector& vector::operator=(vector&& v)
{
    delete[] element_;
    element_ = v.element_;
    size_ = v.size_;
    v.element_ = nullptr;
    v.size_ = 0;
    return *this;
}
void vector::reserve(int newalloc)
{
    if(newalloc <= space_) return; //nesumazint vietos netycia

    double* p = new double[newalloc]; //allocatint naujos vietos

    for(int i = 0; i<size_; i++) //deep copy
        p[i] = element_[i];
    
    delete[] element_; //istrint sena vectoriu
    element_ = p; //reassigntint pointeri
    space_ = newalloc; //max vieta padidejo

}

void vector::resize(int newsize)
{
    reserve(newsize);

    if(newsize < 0)
        throw std::length_error("vector::resize");

    for(int i = size_; i < newsize; i++)
        element_[i] = 0;
    
    size_ = newsize;
}


void vector::push_back(double d)
{
    if(space_ == 0)
        reserve(8);
    else if(size_ == space_)
        reserve(2*space_);
    element_[size_] = d;
    ++size_;
}

int main()
try{
    vector v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    std::cout << "v.size(): " << v.size() << "\n";
    for(int i = 0; i < v.size(); i++)
        std::cout << "v: " <<  v[i] << "\n" ;
    vector v2;

    v2 = v;

    std::cout << "v2.size(): " << v2.size() << "\n";
    for(int i = 0; i < v2.size(); i++)
        std::cout << "v2: " << v2[i] << "\n" ;
    return 0;
}
catch(std::length_error& e)
{
    std::cerr << "error: " << e.what() << "\n";
}