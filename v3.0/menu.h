#pragma once

#include "io.h"

/** @file menu.h
 *  @brief Meniu ir auksto lygio orkestravimo pagalbines funkcijos programai.
 */

/// Predefined student counts used by the generator
const vector<int> STUDENT_COUNTS = {1000, 10000, 100000, 1000000, 10000000};

/// Common file paths for test input files
const vector<string> FILE_PATHS = {
    "../studentInput/studentai_gen1000.txt",
    "../studentInput/studentai_gen10000.txt",
    "../studentInput/studentai_gen100000.txt",
    "../studentInput/studentai_gen1000000.txt",
    "../studentInput/studentai_gen10000000.txt",
};

/** @brief Atspausdina ivadinį tekstą ir parinktis. */
void intro_text();

/**
 * @brief Papraso vartotojo pasirinkti ivedimo budu ir uzpildo group vektoriu.
 * @param group Vektorius, kuris bus uzpildytas studentais.
 * @param menu_option I si reikse ivestas pasirinktas meniu punktas (1-6).
 */
void input_method(vector<Students>& group, int& menu_option);

/** @brief Pagalbine funkcija rusiuoto parinkciai pasirinkti ir pritaikyti. */
void sort_method(vector<Students>& group, int& sort_option);

/**
 * @brief Pasirinkti atskyrimo strategija ir ją atlikti.
 * @param group Pradinis vektorius su visais studentais.
 * @param above_five Vektorius studentams su result() >= 5.
 * @param below_five Vektorius studentams su result() < 5.
 * @param split_option I si reikse irasomas pasirinktas atskyrimo budas (1..3).
 * @param sort_option Esama rusiuotuvo parinktis (naudojama kai kuriose strategijose).
 */
void split_method(vector<Students>& group, vector<Students>& above_five, vector<Students>& below_five, int& split_option, int& sort_option);

/**
 * @brief Pasirinkti isvesties vieta ir formata bei isvesti studentus.
 * @param group Pagrindinis studentu vektorius, kuri isvesime.
 * @param above_five Vektorius studentu su result() >= 5 (gali buti tuscias).
 * @param below_five Vektorius studentu su result() < 5 (gali buti tuscias).
 * @param menu_option Anksciau pasirinktas ivedimo rezimas (itakoja formata).
 * @param output_option Vartotojo pasirinkta isvesties parinktis (1=terminalas,2=failas,3=du failai).
 * @param split_option Ankstesnis pasirinktas atskyrimo budas (naudojamas kuriant du failus).
 * @param sort_option Rusiavimo parinktis, pritaikoma isvedant.
 */
void output_method(vector<Students>& group, vector<Students>& above_five, vector<Students>& below_five, int& menu_option,int& output_option, int& split_option, int& sort_option);

/** @brief The top-level menu/driver for the program. */
void menu();