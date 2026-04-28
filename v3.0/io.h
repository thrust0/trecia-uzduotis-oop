#pragma once
#include "student.hpp"
#include <filesystem>

using namespace std::filesystem;

/** @file io.h
 *  @brief Ivesties, isvesties ir pagalbiniu funkciju deklaracijos programai.
 */

// Input functions
/**
 * @brief Interaktyviai papraso vartotojo studento vardo ir pazymiu.
 * @param group Vektorius, prie kurio pridedamas sukurtas Students objektas.
 */
void manual_input(vector<Students>& group);

/**
 * @brief Papraso studento vardo ir sugeneruoja atsitiktines pazymes.
 * @param group Vektorius, prie kurio pridedamas sukurtas Students objektas.
 */
void generate_grades_input(std::vector<Students>& group);

/**
 * @brief Sugeneruoja atsitiktinius studentu vardus ir papraso pazymiu/egzamino.
 * @param group Vektorius, prie kurio pridedamas sukurtas Students objektas.
 */
void generate_names_input(std::vector<Students>& group);

/**
 * @brief Nuskaityti studentus is teksto failo, naudojant Students operator>>.
 * @param group Vektorius, prie kurio pridedami nuskaityti Students objektai.
 * @param filename Ivesties failo kelias.
 * @throws runtime_error jei nepavyksta atidaryti failo.
 */
void file_input(std::vector<Students>& group, const std::string& filename);

// Output functions
/**
 * @brief Atspausdina studentus terminale (pagal vidurki arba mediana pagal pasirinkima).
 * @param group Vektorius studentu, kuriuos reikia atspausdinti.
 */
void terminal_output(std::vector<Students>& group);

/**
 * @brief Atspausdina pilna studentu lentele terminale (vidurkis ir mediana).
 * @param group Vektorius studentu, kuriuos reikia atspausdinti.
 */
void temp_output(std::vector<Students>& group);

/**
 * @brief Isveda formatuota studentu lentele i faila.
 * @param group Studentu vektorius, kuri rašysime.
 * @param filename Tikslinis failo kelias.
 */
void file_output(const vector<Students>& group, const string filename);

// Sorting / splitting helpers
/**
 * @brief Surikiuoja studentus pagal pasirinkta parinkti.
 * @param group Vektorius studentu, kuris rikiuojamas vietoje.
 * @param sort_option 1=vardas, 2=pavarde, 3=vidurkis, 4=mediana
 */
void sort_output(std::vector<Students>& group, int sort_option);

/**
 * @brief Atskirsto studentus i du vektorius (>=5 ir <5) perkeliamas elementus.
 */
void split_students_by_grades(vector<Students>& group,vector<Students>& above_five, vector<Students>& below_five);

/**
 * @brief Alternatyvi atskyrimo strategija (traukia elementus is galo tol, kol <5).
 */
void split_strategy_two(vector<Students>& group, vector<Students>& below_five);

/**
 * @brief Atskyrimas su partition: palieka >=5 pirmiau ir pasalina likusius.
 */
void split_strategy_three(vector<Students> & group, vector<Students>& below_five);

// Student data generating functions
/**
 * @brief Sugeneruoja zalia (raw) studentu ivedimo faila su atsitiktiniais duomenimis.
 * @param student_amount Kiek studentu sugeneruoti.
 * @param grade_amount Kiek namu darbu pazymiu sugeneruoti kiekvienam studentui.
 * @return Sugeneruoto failo kelias arba tuscias stringas klaidos atveju.
 */
string generate_raw_student_file(int student_amount, int grade_amount);

// Timing / test helpers
string test_generate_raw_student_file(int student_amount, int grade_amount); ///< helper for timing tests
void test_data_processing(const string& filename); ///< second timing test helper

// Helper functions
/** @brief Print a decorative separator line to the terminal. */
void print_line();

/**
 * @brief Read an integer in [start..end] from stdin. Returns -1 if user enters ';'.
 * @param start Minimum accepted value.
 * @param end Maximum accepted value.
 * @return The parsed integer or -1 if terminated by ';'.
 */
int get_int(int start, int end);