#pragma once
#include "human.hpp"
#include <vector>
#include <string>
#include <istream>
#include <ostream>
#include <iostream>

using std::vector;
using std::string;
using std::istream;
using std::ostream;

/**
 * @brief Studento modelis saugantis namu darbu pazymius, egzamina ir apskaiciuotus rezultatus.
 *
 * Paveldi is Human ir teikia pagalbines funkcijas svoriniam vidurkiui bei medianai
 * apskaiciuoti (itraukiant egzamina). Taip pat turi priemones atsitiktiniams duomenims
 * generuoti ir failu ivedimui/isvedimui.
 */
class Students : public Human
{
private:
    int exam_;             ///< exam grade
    vector<int> grade_;    ///< homework grades
    double result_, median_; ///< cached values (can be recalculated)

    // private helper functions
    /**
     * @brief Apskaiciuoja svorini vidurki (40% namu darbai, 60% egzaminas).
     * @return Svorinis vidurkis (double). Grazina 0, jei nera namu darbu pazymiu.
     */
    double calc_result() const;

    /**
     * @brief Apskaiciuoja mediana, itraukiant egzamino pazymi.
     * @return Mediana (double). Jei elementu skaicius lyginis, grazina dvieju viduriniu reiksmiu vidurki.
     */
    double calc_median() const;

    void random_grades_generator();
    vector <string> random_name_generator();
public:
    /**
     * @brief Numatytoji konstruktorius: tuscias studentas.
     */
    Students() : Human(),  exam_(0), result_(0), median_(0){ }

    /**
     * @brief Sukuria objekta nuskaitydamas viena studento irasa is srauto.
     * @param is Ivesties srautas, turintis viena studento irasa (eilute).
     */
    Students(istream& is) { read_students(is); }

    /* Getters */
    inline int exam() const { return exam_; }
    inline double result() const { return calc_result(); }
    inline double median() const { return calc_median(); }

    /**
     * @brief Parsina viena studento irasa is pateikto srauto.
     *
     * Tikimasi, kad eiluteje bus: vardas pavarde [namu darbu pazymiai...] egzaminas
     * @param is Ivesties srautas, is kurio skaitoma eilute.
     * @return Nuoroda i ta pati ivedimo srauta.
     */
    istream& read_students(istream&);

    /* Setters */
    void set_exam(int exam) { exam_ = exam; }
    void add_grade(int grade) { grade_.push_back(grade); }
    void set_result() { result_ = calc_result(); }
    void set_median() { median_ = calc_median(); }

    // Random helpers
    void set_random_grades();
    void set_random_name();

    /**
     * @brief Isspausdina formatuota vienos eilutes studento irasa.
     */
    void print() const override;

    // Rule of 5
    Students(const Students& other); // copy constructor
    Students(Students&& other); // move constructor
    Students& operator=(const Students& other); // copy assignment
    Students& operator=(Students&& other); // move assignment
    ~Students() { grade_.clear(); first_name_.clear(); last_name_.clear(); }
};

// I/O operators
/** Read a Students from a stream (delegates to Students::read_students). */
istream& operator>>(istream& is, Students& student);
/** Write a Students to a stream in aligned columns (first last avg median). */
ostream& operator<<(ostream& os, const Students& student);

// Comparison helpers used for sorting
bool compare_by_first_name(const Students& a, const Students& b);
bool compare_by_last_name(const Students& a, const Students& b);
bool compare_by_result(const Students& a, const Students& b);
bool compare_by_median(const Students& a, const Students& b);

