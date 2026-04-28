#include "menu.h"

/**
 * @brief Pagrindinis interaktyvus meniu, valdantis ivedima, rikiavima ir isveda.
 *
 * Inicializuoja RNG, surenka studentu duomenis ir deleguoja rikiavima/isvedima
 * pagal vartotojo pasirinkimus.
 */
void menu(){
    srand(time(0));
    vector<Students>group;
    vector<Students> above_five;
    vector<Students> below_five;

    int menu_option = 0;
    int sort_option = 0;
    int output_option = 0;
    int split_option = 0;

    // empty lines to create some vertical spacing in the terminal
    for(int i = 0; i<6; i++) cout << endl;

    intro_text();
    input_method(group, menu_option);
    if(menu_option == 6) return; // exit program

    print_line();

    // choose how to sort the students
    sort_method(group, sort_option);
    print_line();

    // choose where to output: 1 terminal, 2 txt file, 3 two txt files
    output_method(group,above_five, below_five, menu_option, output_option, split_option, sort_option);
}

/** @brief Atspausdina sveikinimo teksta ir meniu parinktis. */
void intro_text()
{
    cout << "\tSveiki, cia yra vidurkio ir medianos is pazymiu skaiciuokle" <<
    endl << endl;
    cout << "Iveskite:\n\t'1' jei norite ranka suvesti pazymius\n\t'2' jei norite, kad pazymiai butu sugeneruoti\n\t'3' jei norite, kad butu sugeneruoti studentu vardai ir pazymiai\n\t" 
            <<"'4' jei norite nuskaityti duomenis is failo\n\t'5' jei norite sugeneruoti faile duomenis \n\t'6' jei norite iseiti is programos\nIveskite pasirinkima:";
}


/**
 * @brief Papraso vartotojo pasirinkti ivedimo budu ir surenka duomenis.
 * @param group Vektorius, kuris bus uzpildytas studentais.
 * @param menu_option Nuoroda i kintamaji, kuriame bus saugomas pasirinktas meniu punktas.
 */
void input_method(vector<Students>& group, int& menu_option)
{
    while(true)
    {
        menu_option = get_int(1, 6);

        if(menu_option == 1)
        {
            manual_input(group);
            break;
        }
        else if(menu_option == 2)
        {
            generate_grades_input(group);
            break;
        }
        else if(menu_option == 3)
        {
            generate_names_input(group);
            break;
        }
        else if(menu_option == 4)
        {
            print_line();

            cout << "Pasirinkite is kurio failo nuskaityti:\n"
            << "\t'1' is studentai_gen1000.txt\n"
            << "\t'2' is studentai_gen10000.txt\n"
            << "\t'3' is studentai_gen100000.txt\n"
            << "\t'4' is studentai_gen1000000.txt\n"
            << "\t'5' is studentai_gen10000000.txt\n"
            << "Iveskite pasirinkima: ";            
            int file_option = get_int(1,5);
            file_input(group, FILE_PATHS[file_option - 1]);
            break;
        }
        else if(menu_option == 5) // generavimas studentu faile
        {
            cout << "Pasirinkite kiek norite studentu sugeneruoti: \n"
            << "\t'1' 1 000\n"
            << "\t'2' 10 000\n"
            << "\t'3' 100 000\n"
            << "\t'4' 1 000 000\n"
            << "\t'5' 10 000 000\n"
            << "Iveskite pasirinkima: ";
            
            int amount_option = get_int(1, 5);
            int student_amount = STUDENT_COUNTS[amount_option - 1];
            
            // creating the file
            string filename = generate_raw_student_file(student_amount, 7);
            // string filename = test_generate_raw_student_file(student_amount, 7);
            file_input(group, filename);
            break;
        } // exit program option 
        else if(menu_option == 6)
        {
            cout << "Iseinama is programos...\n";
            return;
        }
        else
        {
            cout << "Nera tokio pasirinkimo!\n";
            intro_text();
        }
    }
}

/**
 * @brief Papraso vartotojo pasirinkti rikiavimo budu ir taiko ji.
 * @param group Studentu vektorius, kuris rikiuojamas vietoje.
 * @param sort_option Nuoroda, kurioje bus saugoma pasirinkta rikiavimo parinktis.
 */
void sort_method(vector<Students>& group, int& sort_option)
{
    cout << "Pasirinkite kaip norite, kad studentai butu isrusiuoti:\n\t'1'Pagal varda\n\t'2'Pagal pavarde\n\t'3'Pagal vidurki\n\t'4'Pagal mediana\n";
    cout << "Iveskite pasirinkima: ";

    sort_option = get_int(1,4);
    sort_output(group, sort_option);
}

/**
 * @brief Tvarko vartotojo pasirinkima del isvesties vietos ir atlieka isvedima.
 * @param group Pagrindinis vektorius, kuri isvesime.
 * @param above_five Vektorius studentams su result() >= 5 (naudojamas atskyrimui).
 * @param below_five Vektorius studentams su result() < 5 (naudojamas atskyrimui).
 * @param menu_option Anksciau pasirinktas ivedimo rezimas.
 * @param output_option Nuoroda, kurioje saugomas pasirinktas isvesties variantas.
 * @param split_option Nuoroda, kurioje saugomas pasirinktas atskyrimo budas.
 * @param sort_option Rusiavimo parinktis, pritaikoma isvesties metu.
 */
void output_method(vector<Students>& group, vector<Students>& above_five, vector<Students>& below_five, int& menu_option,int& output_option, int& split_option, int& sort_option)
{
    cout << "Pasirinkite kur norite, kad duomenys butu isvesti:\n\t'1'Terminale\n\t'2'Teksto faile\n\t'3' I du atskirus failus\nIveskite pasirinkima: ";
    output_option = get_int(1,3);
    
    if(output_option == 1 && menu_option == 4)
    {
        temp_output(group); // temp output displays median and result avg
        return;
    }
    else if(output_option == 1)
    {
        terminal_output(group);
        return;
    }
    else if(output_option == 2) // simple single-file output
    {
        file_output(group, "../studentOutput/StudentOutput.txt");
        return;
    }
    else // output to two separate files
    {
        split_method(group, above_five, below_five, split_option, sort_option);
        if(split_option == 1)
        {
            file_output(above_five, "../studentOutput/kietiakai.txt");
            file_output(below_five, "../studentOutput/vargsiukai.txt");
        }
        else
        {
            file_output(group, "../studentOutput/kietiakai.txt");
            file_output(below_five, "../studentOutput/vargsiukai.txt");
        }

        return;
    }
}

/**
 * @brief Papraso vartotojo pasirinkti atskyrimo strategija ir ji atlieka.
 * @param group Pradinis vektorius su visais studentais.
 * @param above_five Vektorius studentams su result() >= 5.
 * @param below_five Vektorius studentams su result() < 5.
 * @param split_option Nuoroda, kurioje bus irasyta pasirinkta strategija.
 * @param sort_option Rusiavimo parinktis, naudojama kai kuriose strategijose.
 */
void split_method(vector<Students>& group, vector<Students>& above_five, vector<Students>& below_five, int& split_option, int& sort_option)
{
    cout << "Pasirinkite, su kokia strategija norite atskirti studentus: "
    << "\n\t1. Pirma strategija"
    << "\n\t2. Antra strategija"
    << "\n\t3. Trecia strategija\n"
    << "Iveskite pasirinkima: ";
    split_option = get_int(1, 3);

    if(split_option == 1)
        split_students_by_grades(group, above_five, below_five);
    else if (split_option == 2)
    {
        sort_output(group, 3);
        split_strategy_two(group, below_five);
        sort_output(group, sort_option);
        sort_output(below_five, sort_option);
    }
    else
    {
        split_strategy_three(group, below_five);
        sort_output(group, sort_option);
        sort_output(below_five, sort_option);
    }
}