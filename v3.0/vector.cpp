#include <iostream>

class vector {
private:
    int size_; //kiek elementu vektoriuje
    double* element_; //patys tie elementai (tiksliau pointeris i array pradzia)
    int space_; //kiek atminties uzrezervuota

public:
    vector() :size_{0} , element_{nullptr}, space_{0} {} //default constructor

    vector(int s) //constructor
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

    ~vector() //destructor
        { delete[] element_; }

};

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

    for(int i = size_; i < newsize; i++)
        element_[i] = 0;
    
    size_ = newsize;
}


void vector::push_back(double d)
{
    if(space_==0)
        reserve(8);
    else if(size_ = space_)
        reserve(2*space_);
    element_[size_] = d;;
    ++size_;
}

int main()
{
    vector v(10);
    v.resize(-77);

    for(int i = 0; i < v.size(); i++)
    {
        v[i] = i;
        std::cout << v[i] << "\n";
    }

    std::cout << v.size();
    return 0;
}