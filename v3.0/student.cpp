#include "student.hpp"
#include <cassert>
#include <sstream>

/** @brief Sugeneruoja trumpa atsitiktiniu namu darbu pazymiu sarasa ir egzamino pazymi. */
void Students::random_grades_generator()
{
    int grade_count = rand() % 10 + 1;

    for(int i = 0; i<grade_count; i++)
        grade_.push_back(rand() % 10);

    exam_ = rand() % 10;
}

/**
 * @brief Sugeneruoja atsitiktines pazymes ir atspausdina jas i stdout (naudojama interaktyviame rezime).
 */
void Students::set_random_grades()
{
    random_grades_generator();
    
    for(size_t i = 0; i<grade_.size(); i++)
    {
        cout << "\t" << i+1 << " pazymys is " << grade_.size() << ": " << grade_[i] << "\n"; 
    }
    cout << "\tEgzamino pazymys: " << exam_ << "\n";
}

/**
 * @brief Nuskaito failus su vardais ir pavardemis ir grazina atsitiktini pilna varda (vardas, pavarde).
 *
 * Funkcija skaito failus is ../vardai/ ir grazina tuscia vektoriu, jei failu atidaryti nepavyko.
 */
vector<string> Students::random_name_generator()
{
    vector<string> v_first_names;
    vector<string> v_last_names;
    vector<string> full_name;

    string first_name_file;
    string last_name_file;
    string line;
    int gender = rand() % 2;

    if(gender == 0)
    {
        first_name_file = "../vardai/vyriski-vardai.txt";
        last_name_file = "../vardai/vyriskos-pavardes.txt";
    }
    else
    {
        first_name_file = "../vardai/moteriski-vardai.txt";
        last_name_file = "../vardai/moteriskos-pavardes.txt";
    }
    
    ifstream file_first_names(first_name_file);
    ifstream file_last_names(last_name_file);

    if(!file_first_names)
    {
        cerr << "Klaida atidarant faila su vardais" << endl;
        return {};
    }
    if(!file_last_names)
    {
        cerr << "Klaida atidarant faila su pavardemis" << endl;
        return {};
    }

    while(getline(file_first_names, line))
    {
        v_first_names.push_back(line);
    }

    while(getline(file_last_names, line))
    {
        v_last_names.push_back(line);
    }

    int rand_index = rand() % v_first_names.size();
    full_name.push_back(v_first_names[rand_index]);

    rand_index = rand() % v_last_names.size();
    full_name.push_back(v_last_names[rand_index]);

    return full_name;       
}

/**
 * @brief Nustato atsitiktini varda (vardas + pavarde), isveda ji ir sugeneruoja pazymes.
 */
void Students::set_random_name()
{
    vector<string> full_name = random_name_generator();
    if(full_name.size() >= 2)
    {
        first_name_ = full_name[0];
        last_name_ = full_name[1];
    }

    cout << "Studento vardas ir pavarde: " << first_name_ << " " << last_name_ << "\n";
    set_random_grades();
}

/**
 * @brief Apskaiciuoja svorini vidurki: 40% namu darbai + 60% egzaminas.
 * @return Svorinis vidurkis kaip double. Grazina 0, jei nera pazymiu.
 */
double Students::calc_result() const
{
    if(grade_.empty()) return 0; // handle empty case
    int sum = 0;
    for(size_t i = 0; i < grade_.size(); i++)
        sum += grade_[i];
    
    return sum * 1.0 / (grade_.size() * 1.0) * 0.4 + exam_ * 0.6;
}

/**
 * @brief Apskaiciuoja mediana, itraukiant egzamina (grazina double).
 * @return Namu darbu ir egzamino mediana kaip double. Jei elementu skaicius lyginis,
 * grazinamas dvieju viduriniu reiksmiu vidurkis.
 */
double Students::calc_median() const
{
    // create a copy that we can sort without modifying the caller's data
    vector <int> v;
    double median;

    for(int x : grade_)
        v.push_back(x);
    
    v.push_back(exam_);
    sort(v.begin(), v.end());
    // median calculation depending on odd/even size
    if(v.size() % 2 == 1) // odd
    {
        median = v[v.size()/2]; 
        return median;
    }
    else // even
    {
        median = (v[(v.size()-1)/2] + v[(v.size()/2)]);
        return median/2;
    }
}

/**
 * @brief Nuskaito viena studento irasa is srauto. Tikimasi vieno studento per eilute.
 *
 * Formata sudaro: vardas pavarde [namu darbu pazymiai...] egzaminas
 * @param is Ivesties srautas, is kurio skaitoma eilute.
 * @return Nuoroda i ta pati ivesties srauta.
 */
istream& Students::read_students(istream& is)
{
    string line;
    if(!getline(is, line))
        return is;
    
    if(line.empty())
        return is;
    
    stringstream ss(line);
    ss >> first_name_ >> last_name_;

    grade_.clear();
    int g;
    while (ss >> g)
        grade_.push_back(g);

    if(!grade_.empty())
    {
        exam_ = grade_.back();
        grade_.pop_back();
    }
    else{
        exam_ = 0;
    }


    result_ = calc_result();
    median_ = calc_median();

    return is;
}

// rule of 5
Students::Students(const Students& other)
    : Human(other),
    exam_(other.exam_),
    grade_(other.grade_),
    result_(other.result_),
    median_(other.median_)
{ }

Students::Students(Students&& other)
    : Human(std::move(other)),
    exam_(other.exam_),
    grade_(std::move(other.grade_)),
    result_(other.result_),
    median_(other.median_)
{ }

Students& Students::operator=(const Students& other)
{
    if (this == &other) return *this;

    first_name_ = other.first_name_;
    last_name_ = other.last_name_;
    grade_ = other.grade_;
    exam_ = other.exam_;
    result_ = other.result_;
    median_ = other.median_;
    
    return *this;
}

Students& Students::operator=(Students&& other)
{
    if(this != &other)
    {
        first_name_ = std::move(other.first_name_);
        last_name_ = std::move(other.last_name_);
        exam_ = other.exam_;
        grade_ = std::move(other.grade_);
        result_ = other.result_;
        median_ = other.median_;

        // clear other
        other.first_name_ = "";
        other.last_name_ = "";
        other.exam_ = 0;
        other.result_ = 0;
        other.median_ = 0;
    }
    return *this;
}

// I/O operators
/**
 * @brief Extract a Students from a stream.
 * @param is Input stream to read from.
 * @param student Students instance to populate.
 * @return Reference to the input stream (is).
 */
istream& operator>>(istream& is, Students& student)
{
    student.read_students(is);
    return is;
}

/**
 * @brief Insert a Students into an output stream in aligned columns.
 * @param os Output stream to write to.
 * @param student Student to format and write.
 * @return Reference to the output stream (os).
 */
ostream& operator<<(ostream& os, const Students& student)
{

    os << left << setw(20) << student.first_name() << left << setw(20) << student.last_name();
            os << left << setw(20) << fixed << setprecision(2) << student.result();
            os << left << setw(20) << fixed << setprecision(2) << student.median() << endl;
    return os;
}

// Comparison functions
bool compare_by_first_name(const Students& a, const Students& b) {
    return a.first_name() < b.first_name();
}
bool compare_by_last_name(const Students& a, const Students& b) {
    return a.last_name() < b.last_name();
}
bool compare_by_result(const Students& a, const Students& b) {
    return a.result() > b.result();
}
bool compare_by_median(const Students& a, const Students& b) {
    return a.median() > b.median();
}

/**
 * @brief Print a single-line formatted student entry to stdout.
 */
void Students::print() const
{
    cout << left << setw(20) << first_name() << left << setw(20) << last_name();
    cout << left << setw(20) << fixed << setprecision(2) << result();
    cout << left << setw(20) << fixed << setprecision(2) << median() << endl;
}

