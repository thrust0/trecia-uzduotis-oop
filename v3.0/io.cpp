#include "menu.h"
#include "student.hpp"


/**
 * @brief Interaktyvus rankinis ivedimas.
 *
 * Papraso vartotojo ivesti studento varda ir pavarde, namu darbu pazymius ir egzamino pazymi.
 * Sukurtas Students objektas pridedamas prie pateikto vektoriaus. Ivedus ';' vardui ar pavardei
 * baigiamas ivedimo rezimas.
 * @param group Vektorius, prie kurio pridedami Students objektai.
 */
void manual_input(vector<Students>& group)
{
    while(true)
    {
        Students student;
        string first, last;
        int grade_count = 0;

    cout << "Jei norite, kad rezultatai butu isspausdinami, iveskite ';'" << endl;
    cout << "Iveskite varda ir pavarde studento: ";

        cin >> first;
        if(first == ";") { cout << endl; return; }
        student.set_first_name(first);

        cin >> last;
        if(last == ";") { cout << endl; return; }
        student.set_last_name(last);

        print_line();

        while(true)
        {
            int temp;
            cout << "Jei norite pereit i kita studenta, iveskite ';'\n";
            cout << "Iveskite " << grade_count + 1 << " pazymi:  ";
            temp = get_int(0, 10);
            if(temp == -1) break; ///< ';' returns -1 to indicate end of grades
            student.add_grade(temp);
        }

        print_line();
        cout << "Iveskite egzamino pazymi: "; 
        int exam = get_int(0, 10);
        student.set_exam(exam);
        
        // ensure derived cached values are computed
        student.set_result();
        student.set_median();

        group.push_back(std::move(student));
        print_line();
    }
}

/**
 * @brief Atsitiktiniu pazymiu generatorius ivestam studento vardui.
 *
 * Vartotojas iveda varda; namu darbu pazymiai sukuriai atsitiktinai ir pridedami prie vektoriaus.
 */
void generate_grades_input(vector<Students>& group)
{
    while(true)
    {   
        Students student;
        string first, last;
    // name input as usual
        cout << "Jei norite, kad rezultatai butu isspausdinami, iveskite ';'" << endl;
        cout << "Iveskite varda ir pavarde studento: ";
        
        cin >> first;
        if(first == ";") return;
        student.set_first_name(first);


        cin >> last;
        if(last == ";") return;
        student.set_last_name(last);

        // random grade generation
        student.set_random_grades();
        // append the vector
        group.push_back(student);
    }
}
/**
 * @brief Sugeneruoja atsitiktinius studentu vardus (is failu) ir praso pazymiu/egzamino kaip interaktyviame rezime.
 */
void generate_names_input(vector<Students>& group)
{
    while(true)
    {
        Students student;
        student.set_random_name();
        group.push_back(student);

        print_line();
        cout << "Jei norite, kad butu, isvesti rezultatai, iveskite ';' " << endl;
        cout << "Jeigu norite pereiti prie kito studento, iveskite '1' ";
        int exit_option = get_int(1,1);
        if(exit_option == -1) return;
        print_line();
    }
}

/**
 * @brief Nuskaityti studentus is teksto failo ir prideti prie vektoriaus.
 *
 * Failas turetu tureti po viena studento irasa kiekvienoje eiluteje, suderinta
 * su Students::read_students(). Pirmoji eilute laikoma antraste ir praleidziama.
 * @param group Vektorius, prie kurio pridedami nuskaityti studentai.
 * @param filename Ivesties failo kelias.
 * @throws runtime_error jei nepavyksta atidaryti failo.
 */
void file_input(vector<Students>& group, const string& filename)
{
    ifstream file(filename); ///< open file
    if(!file) ///< check if file opened
    {
        throw runtime_error("Neisejo atidaryti failo ");
        return;
    }

    string line;
    getline(file, line); // skip header

    Students student;
    while(file >> student)
    {
        group.push_back(std::move(student));
    }
}

/**
 * @brief Atspausdina studentus terminale, leidziant vartotojui pasirinkti vidurki arba mediana.
 * @param group Studentai, kuriuos reikia parodyti.
 */
void terminal_output(vector<Students>& group)
{
    print_line();
    // this func is for printing all names and result average OR median
    char print_option;
    while(true) // reprompt user for wrong input
    {
        cout << endl;
        cout << "Iveskite 'v', jei norite vidurkio rezultatus pamatyti." << endl << "Iveskite 'm', jei norite medianos rezultatus pamatyti." << endl;
        cin >> print_option;
        tolower(print_option);

        if(print_option == 'v' || print_option == 'm') break;
        cout << "Tokio isvesties pasirinkimo nera!" << endl;
    }
    
    switch (print_option)
    {
    case 'v':
        cout << endl;
        cout << left << setw(20) << "Vardas" << left << setw(20) << "Pavarde";
        cout << setw(20) << " Galutinis (Vid.)" << endl;
        print_line();
        for (auto student : group)
        {
            cout << left << setw(20) << student.first_name() << left << setw(20) << student.last_name();

            cout << setw(20) << fixed << setprecision(2) << student.result() << endl;
        }
        break;
    
    case 'm':
        cout << endl;
        cout << left << setw(20) << "Vardas" << left << setw(20) << "Pavarde";
        cout << setw(20) << " Galutinis (Med.)" << endl;
        print_line();
        for (auto student : group)
        {
            cout << left << setw(20) << student.first_name() << left << setw(20) << student.last_name();

            cout << setw(20) << fixed << setprecision(2) << student.median() << endl;
        }
        break;
    }
}

/**
 * @brief Isveda studentus i formatuota faila, naudojant Students::operator<<.
 * @param group Studentai, kuriuos rasysime.
 * @param filename Tikslinis failo kelias.
 */
void file_output(const vector<Students>& group, const string filename)
{
       // create directory if it doesn't exist
    std::filesystem::path filepath(filename);
    if(filepath.has_parent_path())
        std::filesystem::create_directories(filepath.parent_path());

    ofstream outFile(filename);

    if(!outFile) { cerr << "Klaida irasyme..." << endl; return;}

    // header
    outFile << left << setw(20) << "Vardas" << left << setw(20) << "Pavarde";
    outFile << setw(20) << " Galutinis (Vid.)";
    outFile << setw(20) << " Galutinis (Med.)" << endl;
    for(int i = 0; i<76; i++)
        outFile << "-";
    outFile << endl;

    for (const auto& student : group)
        outFile << student;
}

/**
 * @brief Atspausdina terminale lentele su vidurkiu ir mediana.
 */
void temp_output(vector<Students>& group)
{
    print_line();
    cout << endl;
    cout << left << setw(20) << "Vardas" << left << setw(20) << "Pavarde";
    cout << setw(20) << " Galutinis (Vid.)";
    cout << setw(20) << " Galutinis (Med.)";
    print_line();
    for (auto student : group)
        student.print();
}

/**
 * @brief Surikiuoja grupe pagal sort_option.
 * @param group Vektorius, kuris rikiuojamas vietoje.
 * @param sort_option 1=vardas, 2=pavarde, 3=vidurkis, kitu atveju mediana
 */
void sort_output(vector<Students>& group, int sort_option)
{ 
    if(sort_option == 1)
    {
        // sort by first names
        sort(group.begin(), group.end(), compare_by_first_name);
    }
    else if(sort_option == 2)
    {
        // sort by last names
        sort(group.begin(), group.end(), compare_by_last_name);
    }
    else if(sort_option == 3)
    {
        // sort by grade avg
        sort(group.begin(), group.end(), compare_by_result);

    }
    else
    {
        // sort by median
        sort(group.begin(), group.end(), compare_by_median);
    }
}

/**
 * @brief Perkelia studentus i above_five arba below_five pagal result().
 */
void split_students_by_grades(vector<Students>& group,vector<Students>& above_five, vector<Students>& below_five)
{
    for(auto& student : group) // avoid copying with reference
    {
        if(student.result() < 5)
            below_five.push_back(std::move(student)); // move to avoid copy
        else
            above_five.push_back(std::move(student));
    }
    group.clear(); // source container is emptied but retains capacity
}

/**
 * @brief Antroji atskyrimo strategija: laikoma, kad grupe surikiuota pagal result() ir
 * traukiama is galo tol, kol likes elementas turi result() >= 5.
 */
void split_strategy_two(vector<Students>& group, vector<Students>& below_five)
{
    while(group.back().result() < 5)
    {
        below_five.push_back(group.back());
        group.pop_back();
    }
}

/**
 * @brief Atskyrimas naudojant partition: perkelia studentus su result()<5 i below_five.
 */
void split_strategy_three(vector<Students> & group, vector<Students>& below_five)
{
    // std::partition groups elements with predicate true first
    auto it = std::partition(group.begin(), group.end(),
        [](const Students& s) {return s.result() >= 5; });

    // copy poor-performing students to below_five and erase them from group
    below_five.assign(it, group.end());

    group.erase(it, group.end());
}



/**
 * @brief Sugeneruoja sintetinio studentu ivedimo faila su atsitiktinemis pazymemis.
 * @param student_amount Kiek studentu eilučių sugeneruoti.
 * @param grade_amount Kiek namu darbu pazymiu sukurti kiekvienam studentui (egzaminas pridedamas automatiškai).
 * @return Sugeneruoto failo kelias arba tuscias stringas klaidos atveju.
 */
string generate_raw_student_file(int student_amount, int grade_amount)
{
    ostringstream filename;
    filename << "../studentInput/studentai_gen" << student_amount << ".txt";
    
    std::filesystem::create_directories("../studentInput");

    ofstream outFile(filename.str());
    
    if(!outFile)
    {
        cerr << "Klaida atidarinėjant faila irasymui..." << endl;
        return ""; // return empty string for failure
    }
    outFile << left << setw(20) << "Vardas" << left << setw(20) << "Pavarde";

    for(int j = 0; j < grade_amount; j++)
    {
        outFile << left << setw(7) << ("ND" + to_string(j+1));
    }
    outFile << left << setw(7) << "Egz" << endl;

    for(int i = 0; i<student_amount; i++)
    {
        outFile << left << setw(20) 
        << ("Vardas" + to_string(i+1)) 
        << left 
        << setw(20) << ("Pavarde" + to_string(i+1));

        for(int i = 0; i<grade_amount+1; i++)
        {
            int grade = rand() % 10 + 1;
            outFile << left << setw(7) << grade;
        }
        outFile << endl;
    }
    // no explicit close required — destructor will flush the file
    return filename.str(); // usable with file_input(filename)
}



/**
 * @brief Nuskaito sveika skaiciu intervale [start..end] is stdin; grazina -1 jei ivestas ';'.
 *
 * Pagalbine funkcija tikrina vartotojo ivedi ir pateikia draugiskas klaidu zinutes.
 */
int get_int(int start, int end)
{
    while(true) // check if input is for grade count is int
        try // check if input is for grade count is int
        {
            string input;
            int temp = 0;
            bool is_number = true;
            cin >> input;
            if(input == ";") return -1;
            for(auto i : input)
            {
                if(!isdigit(static_cast<unsigned char>(i)))
                {
                    if(end==INT_MAX) throw invalid_argument("Iveskite naturalu skaiciu nuo");
                    else
                    {
                        throw invalid_argument("Iveskite naturalu skaiciu nuo " +
                        to_string(start) + " iki " + to_string(end) + "!");
                    }
                    is_number = false;
                    break;
                }
            }
            
            if(is_number)
                temp = stoi(input);
            if(temp < start  && is_number)
            {
                throw invalid_argument("Iveskite naturalu skaiciu daugiau uz " + to_string(start-1) + "!");
            }
            else if(temp > end && is_number) 
            {
                throw invalid_argument("Iveskite naturalu skaiciu mazesni uz " + to_string(end+1) + "!");
            }
            else if(temp <= end && temp >= start && is_number) return temp; // if conditions correct
        }
    
        catch(const invalid_argument& e)
        {
            cerr << "Ivedimo klaida: " << e.what() << endl;
            cout << "Bandykite dar karta: ";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
}


/** @brief Print a decorative separator line. */
void print_line()
{
    cout << endl << "----------------------------------------------------------------------------" << endl;
}


