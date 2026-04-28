#pragma once

#include <iomanip>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <random>
#include <ctime>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <chrono>
#include <stdexcept>
#include <filesystem>
#include <utility>


using std::vector;
using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::left;
using std::ifstream;
using std::ofstream;
using std::cerr;
using std::getline;
using std::stringstream;
using std::setw;
using std::fixed;
using std::setprecision;
using std::sort;
using std::move;
using std::ostringstream;
using std::milli;
using std::invalid_argument;
using std::to_string;
using std::runtime_error;
using std::istream;
using std::ostream;

/**
 * @brief Bazine klase zmogui (vardas ir pavarde).
 *
 * "Human" saugo asmens varda ir pavarde bei teikia paprastus prieigos metodus.
 * Tai abstrakti bazine klase: is jos paveldetos klases turi igyvendinti
 * virtualu metoda print(), kuris atvaizduoja objekta tekstiniu pavidalu.
 */
class Human
{
protected:
    string first_name_;
    string last_name_;
public:
    /**
     * @brief Numatytoji konstruktorius: sukuria Human su tusciomis reiksmemis.
     */
    Human() : first_name_(""), last_name_("") {}

    /// Grazina varda
    inline string first_name() const { return first_name_; }

    /// Grazina pavarde
    inline string last_name() const { return last_name_; }

    /// Nustato varda
    void set_first_name(const string& name) { first_name_ = name; }

    /// Nustato pavarde
    void set_last_name(const string& name) { last_name_ = name; }

    /**
     * @brief Kopijavimo konstruktorius
     * @param other Human objektas, is kurio kopijuojama
     */
    Human(const Human& other) : first_name_(other.first_name_),
                                last_name_(other.last_name_)
    { }

    /**
     * @brief Perkelimo (move) konstruktorius
     * @param other Human objektas, is kurio perkelia duomenis
     */
    Human(Human&& other) : first_name_(std::move(other.first_name_)),
                            last_name_(std::move(other.last_name_))
    { }

    /**
     * @brief Iveda zmogaus reprezentacija kaip tekstine eilute.
     *
     * Paveldetos klases turi igyvendinti sita metoda,
     * kad pateiktu skaitytojui tinkama teksto forma (naudojama testuose ir isvestyje).
     */
    virtual void print() const = 0;

    /**
     * @brief Virtualus destruktorius, uztikrinantis teisinga valyma paveldetose klasese.
     */
    virtual ~Human() {}
};