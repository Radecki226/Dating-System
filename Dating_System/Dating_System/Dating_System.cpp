#include<iostream>
#include<vector>
#include<map>
#include<fstream>
#include<string>
#include<cmath>
#include <algorithm>  
using namespace std;

void print_string_vector(vector<string> v) {
    /*Funkcja wyświetlająca wektor stringów*/
    std::cout << "[ ";
    for (size_t i = 0; i < v.size(); i++)
        if (i == v.size() - 1)
            std::cout << v[i];
        else
            std::cout << v[i] << " , ";
    std::cout << " ]" << endl;
}


struct search_settings {
    /*
    Struktura zawierająca ustawienia wyszukiwania.
    Pola:
    ->  preferences "age" lub "hobbies" sa uzywane w aplikacji
    ->  age_window to przedzial wieku w jakim chce sie otrzymywac matche
    ->  number_of matches to ilosc matchy
    */
    string preferences = "age";
    int number_of_matches = 5;
    int age_window = 20;

    search_settings& operator=(search_settings ss) {
        this->number_of_matches = ss.number_of_matches;
        this->age_window = ss.age_window;
        this->preferences = ss.preferences;
        return *this;
    }
};

float string_vector_distance(vector<string> const &v1, vector<string> const &v2) {
    /*
    Porownanie wektorow, jesli ktorys z wyrazow to none nie jest porownywany
    zwracane wartości:
    ->  float w przedziale [0,1] w zaleznosci od ilosci podobienstw
    */
    if (v1.size() != v2.size()) {
        return -1;
    }
    int counter = 0;
    int N = v1.size();
    for (size_t i = 0; i < v1.size(); i++) {
        for (size_t j = 0; j < v2.size(); j++) {
            if (v1[i] == v2[j] && v1[i] != "none" && v2[j] != "none") {
                counter++;
                break;
            }
        }
    }
    return 1-(float)(counter)/N;
}
//Klasa uzytkownika
class User {

    string m_login;
    string m_email;
    string m_password;
    string m_name;
    vector<string> m_hobbies;
    int m_age;
    string m_gender;
    vector<int> m_matches;
    struct search_settings m_settings;

public:
    
    //konstruktor
    User(string login, string email, string password, string name, vector<string> hobbies
        , int age, string gender, search_settings settings);


    //inne metody

    void print_data(); //wyświetla dane o użytkowniku
    void print_settings(); //wyświetla ustawienie wyszukiwania

    //settery
    void set_login(string login);
    void set_email(string email);
    void set_password(string password);
    void set_name(string name);
    void set_hobbies(vector<string> hobbies);
    void set_age(int age);
    void set_gender(string gender);
    void set_matches(vector<int> matches);
    void set_settings(struct search_settings settings);


    //gettery
    string get_login() const;
    string get_email() const;
    string get_password() const;
    string get_name() const;
    vector<string> get_hobbies() const;
    int get_age() const;
    string get_gender() const;
    vector<int> get_matches() const;
    struct search_settings get_settings() const;
    




};
//definicje
User::User(string login, string email, string password, string name, vector<string> hobbies
    , int age, string gender, search_settings settings) {

    m_login = login;
    m_email = email;
    m_password = password;
    m_name = name;
    m_hobbies = hobbies;
    m_age = age;
    m_gender = gender;
    m_settings = settings;

}

void User::print_data() {
    std::cout << "Name : " << m_name << endl;
    std::cout << "Email : " << m_email << endl;
    std::cout << "Login : " << m_login << endl;
    std::cout << "Hobbies : ";
    print_string_vector(m_hobbies);
    std::cout << "Age : " << m_age << endl;
    std::cout << "Gender : " << m_gender << endl;

}
void User::print_settings() {

    std::cout << "Preferences : " << m_settings.preferences << endl;
    std::cout << "Number of matches : " << m_settings.number_of_matches << endl;
    std::cout << "Age window : " << m_settings.age_window << endl;
}
void User::set_login(string login) { m_login = login; }
void User::set_email(string email) { m_email = email; }
void User::set_password(string password) { m_password = password; }
void User::set_name(string name) { m_name = name; }
void User::set_hobbies(vector<string> hobbies) { m_hobbies = hobbies; }
void User::set_age(int age) { m_age = age; }
void User::set_gender(string gender) { m_gender = gender; }
void User::set_settings(struct search_settings settings) { m_settings = settings; }
void User::set_matches(vector<int> matches) { m_matches = matches; }

string User::get_login() const { return m_login; }
string User::get_email() const { return m_email; }
string User::get_password() const { return m_password; }
string User::get_name() const { return m_name; }
vector<string> User::get_hobbies() const { return m_hobbies; }
int User::get_age() const { return m_age; }
string User::get_gender() const { return m_gender; }
struct search_settings User::get_settings() const { return m_settings; }
vector<int> User::get_matches() const { return m_matches; }


float u_distance(User const &u1, User const &u2) { //u1 jest użytkownikiem, dla którego szuka się pary
    /*
    Funkcja mierząca podobieństwo między uzytkownikami, mierzy srednia kwadratowa z roznicy pomiedzy cechami.
    W zależności od ustawień zmieniane są wagi.
    zwracane wartości:
    ->  float z przedzialu [0,1] oznaczajact podobienstwo pomiedzy uzytkownikami
    -> Jesli uzytkownicy sa tej samej plci zwraca -1
    */
    float dist = 0;
    if (u1.get_gender() == u2.get_gender())
        return -1;
    else {
        int age_window = u1.get_settings().age_window;
        double reference_age = max(u1.get_age(), u2.get_age());
        double age_diff = abs(u1.get_age() - u2.get_age());
        if (age_window < age_diff)
            return 0;
        if (u1.get_settings().preferences == "age") {

            dist += (float)(2 * pow(1 - age_diff/reference_age, 2));
            dist += (float)(pow(1 - string_vector_distance(u1.get_hobbies(), u2.get_hobbies()),2));
          
          
        }
        else {
            dist += (float)(pow(1 - age_diff / reference_age, 2));
           
            dist += (float)(2*pow(1 - string_vector_distance(u1.get_hobbies(), u2.get_hobbies()), 2));
        }
    }
    dist = sqrt(dist/3);
    return dist;

}

//Klasa zbioru użytkowników
//Przechowuje jako pola: zbiór użytkowników , scieżkę do pliku 
class Dataset {

    vector<User> m_users;
    string m_file;
    string m_admin_password;

public:

    //Konstruktor
    Dataset(string path); //ścieżka do pliku jako argument konstruktora

    //Destruktor 
    ~Dataset();

    //settery
    void set_login(int idx , string password);
    void set_email(int idx , string email);
    void set_password(int idx , string password);
    void set_name(int idx , string name);
    void set_hobbies(int idx , vector<string> hobbies);
    void set_age(int  idx, int age);
    void set_gender(int idx,string gender);
    void set_matches(int idx,vector<int> matches);
    void set_settings(int idx,struct search_settings settings);
    void set_admin_password(string admin_password);


    //gettery
    int get_user(string login); //zwraca index do użytkownika po loginie
    int get_user_by_email(string email);
    string get_login(int idx) const;
    string get_email(int idx) const;
    string get_password(int idx) const;
    string get_name(int idx) const;
    vector<string> get_hobbies(int idx) const;
    int get_age(int idx) const;
    string get_gender(int idx) const;
    vector<int> get_matches(int idx) const;
    struct search_settings get_settings(int idx) const;
    string get_admin_password() const;

    //inne metody
    
    void find_matches(int idx);
    void find_user(int age_min, int age_max , string hobby);
    void add_user(User user);
    void remove_user(int idx);
    void print_user(int idx);
    void print_users();
    void print_matches(int idx);



};
//definicje
Dataset::Dataset(string path) {

    m_file = path;
    fstream file(path); //open file
    string temp; //temporary string
    if (file.is_open()) {
        //Petla wpisujaca do pliku chodzi dopoki nie wykryje słowa end lub braku slowa next w odpowiednim miejscu

        //Hasło do administratora
        string admin_password;
        std::getline(file, temp);
        admin_password = temp;
        while (1) {
            
            string login;
            string email;
            string password;
            string name;
            vector<string> hobbies;;
            int age;
            string gender;
            struct search_settings settings;



            std::getline(file, temp);
            string next_string = "next";
            if (temp != next_string) {
                std::cout << "Wrong Format" << endl;
                break;
            }
            //Wpisz informacje z pliku do klasy

            std::getline(file, temp);
            login = temp;
            
            std::getline(file, temp);
            email = temp;
            
            std::getline(file, temp);
            password = temp;
            
            std::getline(file, temp);
            name = temp;

            int i = 0;

            while (i < 3) { //add 3 elements to hobbies vector
                std::getline(file, temp);
                hobbies.push_back(temp);
                i++;

            }

            std::getline(file, temp);
            age = stoi(temp);

            std::getline(file, temp);
            gender = temp;

            std::getline(file, temp);
            settings.preferences = temp;

            std::getline(file, temp);
            settings.age_window = stoi(temp);
            
            std::getline(file, temp);
            settings.number_of_matches = stoi(temp);

            //next user
            User user(login, email, password, name, hobbies, age, gender, settings);




            m_users.push_back(user);

            //ustawienie hasla do admina

            m_admin_password = admin_password;
          

  
            std::getline(file, temp);

            string end_string = "end";
            if (temp == end_string) {
                file.close();
                break;
            }

        }

    }
    else
        std::cout << "Error while loading file" << endl;

}
Dataset::~Dataset() {
    fstream file(m_file);
    if (file.is_open()) {
        file << m_admin_password << endl;
        for (size_t i = 0; i < m_users.size(); i++) {
            file << "next" << endl;
            file << m_users[i].get_login() << endl;
            file << m_users[i].get_email() << endl;
            file << m_users[i].get_password() << endl;
            file << m_users[i].get_name() << endl;
            vector<string> hobbies = m_users[i].get_hobbies();
            file << hobbies[0] << endl;
            file << hobbies[1] << endl;
            file << hobbies[2] << endl;
            file << m_users[i].get_age() << endl;
            file << m_users[i].get_gender() << endl;
            struct search_settings settings = m_users[i].get_settings();
            file << settings.preferences << endl;
            file << settings.age_window << endl;
            file << settings.number_of_matches << endl;
            if (i == m_users.size() - 1)
                file << "end" << endl;
            else
                file << "----------------" << endl;

        }
        file.close();
    }
    else
        std::cout << "Error while loading file" << endl;
}

void Dataset::set_login(int idx , string login) { m_users[idx].set_login(login); }
void Dataset::set_email(int idx , string email) { m_users[idx].set_email(email); }
void Dataset::set_password(int idx , string password) { m_users[idx].set_password(password); }
void Dataset::set_name(int idx , string name) { m_users[idx].set_name(name); }
void Dataset::set_hobbies(int idx , vector<string> hobbies) { m_users[idx].set_hobbies(hobbies); }
void Dataset::set_age(int idx , int age) { m_users[idx].set_age(age); }
void Dataset::set_gender(int idx , string gender) { m_users[idx].set_gender(gender); }
void Dataset::set_settings(int idx, struct search_settings settings) { m_users[idx].set_settings(settings); }
void Dataset::set_matches(int idx , vector<int> matches) { m_users[idx].set_matches(matches); }
void Dataset::set_admin_password(string admin_password) { m_admin_password = admin_password; }

string Dataset::get_login(int idx) const { return m_users[idx].get_login(); }
string Dataset::get_email(int idx) const { return m_users[idx].get_email(); }
string Dataset::get_password(int idx) const { return m_users[idx].get_password(); }
string Dataset::get_name(int idx) const { return m_users[idx].get_name(); }
vector<string> Dataset::get_hobbies(int idx) const { return m_users[idx].get_hobbies(); }
int Dataset::get_age(int idx) const { return m_users[idx].get_age(); }
string Dataset::get_gender(int idx) const { return m_users[idx].get_gender(); }
struct search_settings Dataset::get_settings(int idx) const { return m_users[idx].get_settings(); }
vector<int> Dataset::get_matches(int idx) const { return m_users[idx].get_matches(); }
string Dataset::get_admin_password() const {return m_admin_password;}




//metody
int Dataset::get_user(string login) {
    for (size_t i = 0; i < m_users.size(); i++) {
        if (m_users[i].get_login() == login) {
            return i;
        }
    }
    return -1; //w przypadku braku uzytkownika zwroc -1
}
int Dataset::get_user_by_email(string email) {
    for (size_t i = 0; i < m_users.size(); i++) {
        if (m_users[i].get_email() == email) {
            return i;
        }
    }
    return -1; //w przypadku braku uzytkownika zwroc -1
}

void Dataset::find_matches(int idx) { //idx bedzie indeksem uzytkownika
    //matches- tymczasowy wektor przechowujacy indeksy uzytkownikow, ktorzy beda matchami
    //n_matches - pozyskana ze struktury settings liczba dopasowan dla danego uzytkownika
    /*Algorytm znajdujący dopasowania*/
    vector<int> matches;
    int n_matches = m_users[idx].get_settings().number_of_matches;
    //Ustawianie odpowiedniej długości wektora

    for (size_t i = 0; i < m_users.size(); i++) { //i iteruje po uzytkownikach
        if (i != idx) {
            
            float local_distance = u_distance(m_users[idx], m_users[i]);

            if (matches.size() == 0)
                matches.push_back(i);

            else if (matches.size() < (size_t)(n_matches)) {
                for (size_t j = 0; j < matches.size(); j++) {
                    //Jesli dopasowanie lepsze niz kolejny najlepiej dopasowany to doloz na to miejsce
                    if (local_distance > u_distance(m_users[idx], m_users[matches[j]])) {
                        matches.insert(matches.begin() + j, i);
                        break;
                    }
                    //W innym przypadku na koniec
                    if (j == matches.size() - 1) {
                        matches.push_back(i);
                        break;
                    }
                }
               
            }
            else {
                for (int j = 0; j < n_matches; j++) { //j iteruje po wektorze matches
                    if (local_distance > u_distance(m_users[idx], m_users[matches[j]])) {
                        //Jesli match jest wiekszy niz j-ty najwiekszy element zostaje wrzucony w jego miejsce
                        matches.insert(matches.begin() + j, i);
                        matches.erase(matches.begin()+n_matches);
                        break;
                    }
                }
            }
        }
        
    }
    m_users[idx].set_matches(matches); //ustawia wypelniony wektor jako matche uzytkownika idx

}
void Dataset::find_user(int age_min, int age_max, string hobby) {
    for (size_t i = 0; i < m_users.size(); i++) {
        if (m_users[i].get_age() > age_min && m_users[i].get_age() < age_max && (m_users[i].get_hobbies()[0] == hobby ||
            m_users[i].get_hobbies()[1] == hobby || m_users[i].get_hobbies()[1] == hobby)) {

            std::cout << "----------------" << endl;
            m_users[i].print_data();
            std::cout << "----------------" << endl;

        }
    }
}

void Dataset::add_user(User user) {
    m_users.push_back(user);
}
void Dataset::remove_user(int idx) {
    m_users.erase(m_users.begin() + idx);
}
void Dataset::print_user(int idx) {
    std::cout << "----------------" << endl;
    m_users[idx].print_data();
    m_users[idx].print_settings();
    std::cout << "----------------" << endl;
}
void Dataset::print_users() {
    for (size_t i = 0; i < m_users.size(); i++) {
        std::cout << "----------------" << endl;
        m_users[i].print_data();
        std::cout << "----------------" << endl;
   }
}

void Dataset::print_matches(int idx) {
    int n_matches = m_users[idx].get_settings().number_of_matches;
    std::cout << "Your matches: "<< endl;
    
    for (int i = 0; i < n_matches; i++) { //i iteruje po indeksach matchy danego uzytkownika
        std::cout << "----------------" << endl;
        m_users[m_users[idx].get_matches()[i]].print_data(); //wyswietla i-ty match uzytkownika idx
        std::cout << "----------------" << endl;
    }
 
}


//Aplikacja

void fill_hobbies(Dataset& dataset, int user_idx) {
    /*
    Procedura edycji hobby
    modyfikuje pole hobbies w klasie
    */
    int ok = 0;
    vector<string> hobbies;
    int temp;
    string exit_string;
    std::cout << "Choose three hobbies from below list: " << endl;
    std::cout << "[0] skiing" << endl;
    std::cout << "[1] bowling" << endl;
    std::cout << "[2] basketball" << endl;
    std::cout << "[3] soccer" << endl;
    std::cout << "[4] climbing " << endl;
    std::cout << "[5] fashion" << endl;
    std::cout << "[6] instagram" << endl;
    std::cout << "[7] netflix" << endl;
    std::cout << "[8] travelling" << endl;
    std::cout << "[9] cats" << endl;
    std::cout << "[10] dogs" << endl;
    std::cout << "[11] none" << endl;
    vector<int> temp_arr; //wektora przechowujacy juz wpisane wartosci
    for (int i = 0; i < 3; i++) {
        string temp_string;

        while (!ok) {
            int err_flag = 0; //jesli juz ustawiono jakies hobby wyrzuca blad
            std::cout << "index: "; std::cin >> temp;
            for (size_t j = 0; j < temp_arr.size(); j++) {
                if ((temp == temp_arr[j]) && (temp != 11)) {
                    err_flag = 1;
                    break;
                }
            }

            if (std::cin.fail() || temp < 0 || temp>11 || err_flag) {
                std::cout << "Wrong character" << endl;
                std::cin.clear();
                std::cin.ignore(1000 , '\n');
                std::cout << "Do you want to exit? If so, type exit "; std::cin >> exit_string;
                std::cout << endl;
                if (exit_string == "exit")
                    return;
            }
            else {
                temp_arr.push_back(temp);
                ok = 1;
                switch (temp) {
                case 0:
                    temp_string = "skiing";
                    break;
                case 1:
                    temp_string = "bowling";
                    break;
                case 2:
                    temp_string = "basketball";
                    break;
                case 3:
                    temp_string = "soccer";
                    break;
                case 4:
                    temp_string = "climbing";
                    break;
                case 5:
                    temp_string = "fashion";
                    break;
                case 6:
                    temp_string = "instagram";
                    break;
                case 7:
                    temp_string = "netflix";
                    break;
                case 8:
                    temp_string = "travelling";
                    break;
                case 9:
                    temp_string = "cats";
                    break;
                case 10:
                    temp_string = "dogs";
                    break;
                case 11:
                    temp_string = "none";
                    break;
                default:
                    break;


                }
                std::cin.clear();
                std::cin.ignore(1000, '\n');
            }
        }
        ok = 0;
        hobbies.push_back(temp_string);
    }
    dataset.set_hobbies(user_idx, hobbies);
}

int edit_menu(Dataset& dataset, int user_idx) { 
    /*
    Menu edycji uzytkownika 
    przekazywany jest edytowany dataset i indeks do użytkownika
    mozliwosc edycji konta 
    */
    int exit_flag = 0;
    int control = 0;
    string temp_string;
    int temp;
    while (!exit_flag) {
        cout << "[1] Set New Email" << endl;
        cout << "[2] Set New Password" << endl;
        cout << "[3] Set New Hobbies" << endl;
        cout << "[4] Edit settings" << endl;
        cout << "[5] Delete Account" << endl;
        cout << "[Anything Else] Exit" << endl;
        cout << "Type Digit: "; std::cin >> control;
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        switch (control) {
        case 1: {
            cout << "New Email: "; std::cin >> temp_string;
            std::cin.clear();
            std::cin.ignore(1000, '\n');

            int n = dataset.get_user_by_email(temp_string);
            if (n == -1) {
                dataset.set_email(user_idx, temp_string);
                std::cout << "Success" << endl;
            }
            else
                std::cout << "This email aldready exist!" << endl;
            break;

        }

        case 2:
            cout << "New Password: "; std::cin >> temp_string;
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            dataset.set_password(user_idx, temp_string);
            cout << "Success" << endl;
            break;
        case 3:
            fill_hobbies(dataset, user_idx);
            break;
        case 4: {
            search_settings settings;
            cout << "New Preferences: "; std::cin >> temp_string;
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            if (temp_string != "age" && temp_string != "hobbies") {
                cout << "Wrong expression" << endl;
                break;
            }
            else
                settings.preferences = temp_string;
            cout << "New Age Window(must be more than 3): "; std::cin >> temp;
            if (std::cin.fail() || temp < 3) {
                cout << "Wrong expression" << endl;
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                break;
            }
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            settings.age_window = temp;

            cout << "New Number of Matches(from 1 to 6): "; std::cin >> temp;
            if (std::cin.fail() || temp < 1 || temp > 6) {
                cout << "Wrong expression" << endl;
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                break;
            }
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            settings.number_of_matches = temp;
            dataset.set_settings(user_idx, settings);
            break;

        }
        case 5:
            dataset.remove_user(user_idx);
            return -1; //jesli usuniecie zwroc -1
            break;
        default:
            exit_flag = 1;
            break;

        }

    }
    return 0;
}
int search(Dataset& dataset) {
    /*
    Procedura wyszukiwania użytkowników
    Pyta użytkownika o kryteria wyszukiwania i wyświetla listę użytkowników spełniających te kryteria
    */
    int age_min;
    int age_max;
    string hobby;
    int error_flag = 0;


    std::cout << "Type minimum age: "; std::cin >> age_min;

    if (cin.fail())
        error_flag = 1;
    std::cin.clear();
    std::cin.ignore(1000, '\n');
    if (error_flag)
        return -1;

    
    std::cout << "Type maximum age: "; std::cin >> age_max;

    if (cin.fail())
        error_flag = 1;
    std::cin.clear();
    std::cin.ignore(1000, '\n');
    if (error_flag)
        return -1;



    std::cout << "Type hobby: "; std::cin >> hobby;
    std::cin.clear();
    std::cin.ignore(1000, '\n');
    std::cout << "Found users: " << endl;
    dataset.find_user(age_min, age_max, hobby);
    return 0;


  
}

int login_procedure(Dataset &dataset) {
    /*
    Procedura logowania
    zwracane wartości:
    ->  numer uzytkownika w przypadku normanlnego logowania
    ->  -1 w przypadku błędu
    ->  -2 w przypadku logowania jako admin
    */
    int ok = 0; //flaga wskazująca czy logowanie przebiegło prawidłowo
    int n = -1;
    while (!ok) {
        int counter = 0; //liczby do 3, jesli trzy logowania beda niepoprawne, wychodzi z aplikacji
        string exit_string; //jesli zostanie wywolana wychodzi z programu
        string password, login;
        std::cout << "Login: "; std::getline(std::cin, login, '\n');
        std::cout << "Password: "; std::cin >> password;
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        n = dataset.get_user(login);
        //Zaloguj jako administrator
        if (login == "admin") {
            //Procedura sprawdzenia hasła
            string actual_password = dataset.get_admin_password();
            if (actual_password == password) {
                std::cout << "Admin Mode" << endl;
                return -2;
                ok = 1;
            }
            else {
                std::cout << "Wrong username or password, try again" << endl;
                std::cout << "Do you want to exit? If so, type exit: "; std::cin >> exit_string;

                std::cin.clear();
                std::cin.ignore(1000, '\n');
                std::cout << endl;
            }
        }
        //Zla nazwa uzytkownika
        else if (n  == -1) {//n to numer uzytkownika
            std::cout << "Wrong username or password, try again." << endl;
            std::cout << "Do you want to exit? If so type exit "; std::cin >> exit_string;

            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << endl;
        }
        //Poprawny login
        else {
            //Procedura sprawdzenia hasła
            string actual_password = dataset.get_password(n);
            if (actual_password == password) {
                std::cout << "Hello " << login << endl;
                ok = 1;
            }
            else {
                std::cout << "Wrong username or password, try again" << endl;
                std::cout << "Do you want to exit? If so, type exit: ";std::cin >> exit_string;

                std::cin.clear();
                std::cin.ignore(1000, '\n');
                std::cout << endl;
            }
        }
        counter++;
        if (exit_string == "exit" || counter == 3 || ok == 1)
            break;
    }
    if (ok == 1)
        return n;//w przypadku powodzenia zwracany jest uzytkownik 
    else
        return -1; //w przypadku błędu zwraca flagę -1
    
}
void create_account(Dataset &dataset) {
    /*Procedura tworzenia konta*/
    string login, email, password, name, gender;
    vector<string> hobbies;
    int age;
    search_settings settings;
    int ok = 0;
    string exit_string;
    int temp;

    while (!ok) {
        std::cout << "Login: "; std::getline(std::cin , login , '\n');
        int n = dataset.get_user(login);
        if (n == -1 && login != "admin") {
            ok = 1;
        }
        else {
            std::cout << "This username aldready exist!" << endl;
            std::cout << "Do you want to exit? If so, type exit "; std::cin >> exit_string;
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << endl;
            if (exit_string == "exit")
                return;

        }
    }
    ok = 0;

    std::cout << "Password: "; std::cin >> password;
    std::cin.clear();
    std::cin.ignore(1000, '\n');
  
    while (!ok) {
        std::cout << "Email: "; std::cin >> email;
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        int n = dataset.get_user_by_email(email);
        if (n == -1) {
            ok = 1;
        }
        else {
            std::cout << "This email aldready exist!" << endl;
            std::cout << "Do you want to exit? If so, type exit "; std::cin >> exit_string;
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << endl;
            if (exit_string == "exit")
                return;

        }
    }
    ok = 0;

    std::cout << "Name: "; std::getline(std::cin , name , '\n');
    ok = 0;

    while (!ok) {
        std::cout << "Gender: "; std::cin >> gender;
        std::cin.clear();
        std::cin.ignore(1000, '\n');

        if (gender == "man" || gender == "woman")
            ok = 1;
        else {
            std::cout << "Type correct gender!" << endl;
            std::cout << "Do you want to exit? If so, type exit"; std::cin >> exit_string;
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << endl;
            if (exit_string == "exit")
                return;
        }
    }
    ok = 0;

    while (!ok) {
        std::cout << "Age: "; std::cin >> age;
        if (std::cin.fail() || age < 18 || age > 120) {
            std::cout << "Wrong character" << endl;
            std::cin.clear();
            std::cin.ignore(1000 , '\n');
            std::cout << "Do you want to exit? If so, type exit "; std::cin >> exit_string;
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << endl;
            if (exit_string == "exit")
                return;
        }
        else {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            ok = 1;
        }
    }
    ok = 0;
 
    std::cout << "Choose three hobbies from below list: " << endl;
    std::cout << "[0] skiing" << endl;
    std::cout << "[1] bowling" << endl;
    std::cout << "[2] basketball" << endl;
    std::cout << "[3] soccer" << endl;
    std::cout << "[4] climbing " << endl;
    std::cout << "[5] fashion" << endl;
    std::cout << "[6] instagram" << endl;
    std::cout << "[7] netflix" << endl;
    std::cout << "[8] travelling" << endl;
    std::cout << "[9] cats" << endl;
    std::cout << "[10] dogs" << endl;
    std::cout << "[11] none" << endl;
    vector<int> temp_arr; //wektora przechowujacy juz wpisane wartosci
    for (int i = 0; i < 3; i++) {
        string temp_string;
        
        while (!ok) {
            int err_flag = 0; //jesli juz ustawiono jakies hobby wyrzuca blad
            std::cout << "index: "; std::cin >> temp;
            for (size_t j = 0; j < temp_arr.size(); j++) {
                if ((temp == temp_arr[j]) && (temp != 11)) {
                    err_flag = 1;
                    break;
                }
            }
            
            if (std::cin.fail() || temp < 0 || temp>11 || err_flag) {
                std::cout << "Wrong character" << endl;
                std::cin.clear();
                std::cin.ignore();
                std::cout << "Do you want to exit? If so, type exit "; std::cin >> exit_string;
                std::cout << endl;
                if (exit_string == "exit")
                    return;
            }
            else {
                temp_arr.push_back(temp);
                ok = 1;
                switch (temp) {
                case 0:
                    temp_string = "skiing";
                    break;
                case 1:
                    temp_string = "bowling";
                    break;
                case 2:
                    temp_string = "basketball";
                    break;
                case 3:
                    temp_string = "soccer";
                    break;
                case 4:
                    temp_string = "climbing";
                    break;
                case 5:
                    temp_string = "fashion";
                    break;
                case 6:
                    temp_string = "instagram";
                    break;
                case 7:
                    temp_string = "netflix";
                    break;
                case 8:
                    temp_string = "travelling";
                    break;
                case 9:
                    temp_string = "cats";
                    break;
                case 10:
                    temp_string = "dogs";
                    break;
                case 11:
                    temp_string = "none";
                    break;
                default:
                    break;


                }
                std::cin.clear();
                std::cin.ignore(1000, '\n');
            }
        }
        ok = 0;
        hobbies.push_back(temp_string);
    }
    

   

    User user(login, email, password, name, hobbies, age, gender, settings);
    dataset.add_user(user);
    std::cout << "Account Created" << endl;
}
void user_panel(Dataset &dataset , int user_idx) {
    /*Głowny panel uzytkownika*/
    int ok=0;
    while (!ok) {
        int control = 0;
        dataset.print_user(user_idx);
        int remove_flag = 0;

        std::cout << "[1] Edit Account" << endl;
        std::cout << "[2] Show matches" << endl;
        std::cout << "[3] Search for users" << endl;
        std::cout << "[Anything else] Exit" << endl;
        std::cout << "Type the digit:"; std::cin >> control;
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        switch (control) {
        case 1:
            remove_flag = edit_menu(dataset , user_idx);
            if (remove_flag == -1)
                return;
            break;
        case 2:
            dataset.find_matches(user_idx);
            dataset.print_matches(user_idx);
            break;
        case 3: {
            int n = search(dataset);
            if (n == -1)
                std::cout << "Wrong character" << endl;
            break;
        }
        default:
            ok = 1;
            return;
        }

    }
}
void admin_panel(Dataset& dataset) {
    /*Panel administraktora, umozliwa wyswietlenie pelnej listy uzytkownikow i usuniecie pojedynczych uzytkownikow*/
    while (1) {
        int control=0;
        string temp_string;
        int n;
        std::cout << "[1] Print Users" << endl;
        std::cout << "[2] Delete user" << endl;
        std::cout << "[3] Change password" << endl;
        std::cout << "[Anything Else] exit" << endl;
        std::cout << "Type the digit:";
        std::cin >> control;
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        switch (control) {
        case 1:
            /*Wyswietlanie uzytkownikow*/
            dataset.print_users();
            break;
        case 2:
            /*Usuwanie uzytkownika*/
            cout << "User's login: "; cin >> temp_string;
            n = dataset.get_user(temp_string);
            if (n == -1) {
                std::cout << "Wrong login" << endl;
            }
            else
                dataset.remove_user(n);
            break;

        case 3:
            cout << "New password: "; cin >> temp_string;
            dataset.set_admin_password(temp_string);
            break;
        default:
            return;
        }
        


    }

}
int main() {
    Dataset my_dataset("klasa.txt"); //zmienna globalna- klasa głowna aplikacji
    int control = 0;
    int current_user = -1; //indeks zalogowanego uzytkownika
    int exit_flag = 0;


    while (!exit_flag) {
        std::cout << "Hello! It's your favourite dating app again!!!!" << endl;
        std::cout << "[1] Log in" << endl;
        std::cout << "[2] Create Account" << endl;
        std::cout << "[Anything else] Exit" << endl;
        std::cout << "Type the digit:";
        std::cin >> control;
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        string login, password;
        switch (control) {
        case 1: {
            //Procedura logowania
            current_user = login_procedure(my_dataset);
            if (current_user >= 0)
                user_panel(my_dataset, current_user);
            else if (current_user == -2)
                admin_panel(my_dataset);
            break;
        }
        case 2: {
            //Procedura tworzenia konta
            create_account(my_dataset);
            break;
        }

        default:
            exit_flag = 1;
            break;
           
        }

    }

   
   

}