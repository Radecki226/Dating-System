#include<iostream>
#include<vector>
#include<map>
#include<fstream>
#include<string>
#include<cmath>
#include <algorithm>  
#define USER_MODE 1
#define ADMIN_MODE 2
using namespace std;

void print_string_vector(vector<string> v) {
    cout << "[ ";
    for (size_t i = 0; i < v.size(); i++)
        if (i == v.size() - 1)
            cout << v[i];
        else
            cout << v[i] << " , ";
    cout << " ]" << endl;
}


//Mozliwe będzie wybranie przez uzytkownika preferencji w algorytmie szukania
//Algorytm będzie mógl być oparty bardziej na wieku lub bardziej na zainteresowaniach

//Struktura zawierająca ustawienia wyszkukiwania u¿ytkownika z operatorem porownania
struct search_settings {
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
//Funkcja mierząca podobieństwo dwóch wektorów stringów
//Wejscie: dwa wektory, Wyjście: miara podobienstwa z przedziału <0,1>
float string_vector_distance(vector<string> const &v1, vector<string> const &v2) {
    if (v1.size() != v2.size()) {
        return -1;
    }
    int counter = 0;
    int N = v1.size();
    for (size_t i = 0; i < v1.size(); i++) {
        for (size_t j = 0; j < v2.size(); j++) {
            if (v1[i] == v2[j]) {
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
    cout << "Name : " << m_name << endl;
    cout << "Email : " << m_email << endl;
    cout << "Login : " << m_login << endl;
    cout << "Hobbies : ";
    print_string_vector(m_hobbies);
    cout << "Age : " << m_age << endl;
    cout << "Gender : " << m_gender << endl;

}
void User::print_settings() {

    cout << "Preferences : " << m_settings.preferences << endl;
    cout << "Number of matches : " << m_settings.number_of_matches << endl;
    cout << "Age window : " << m_settings.age_window << endl;
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

//Funkcja mierząca podobieństwo pomiędzy użytkownikami
//Mierzy pierwiastek z róznicy kwadratów pomiędzy cechami 
//W zależności od ustawień parametry brane są z różną wagą
float u_distance(User const &u1, User const &u2) { //u1 jest użytkownikiem, dla którego szuka się pary
    float dist = 0;
    if (u1.get_gender() == u2.get_gender())
        return 0;
    else {
        int age_window = u1.get_settings().age_window;
        double reference_age = max(u1.get_age(), u2.get_age());
        double age_diff = abs(u1.get_age() - u2.get_age());
        if (age_window < age_diff)
            return 0;
        cout << age_diff / reference_age << endl;
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

    //inne metody
    
    void find_matches(string login);
    void add_user(User user);
    void remove_user(User user) {};
    void print_users();
    void print_matches(string login);



};
//definicje
Dataset::Dataset(string path) {

    m_file = path;
    fstream file(path); //open file
    string temp; //temporary string
    if (file.is_open()) {
        //Petla wpisujaca do pliku chodzi dopoki nie wykryje słowa end lub braku slowa next w odpowiednim miejscu
        while (1) {
            
            string login;
            string email;
            string password;
            string name;
            vector<string> hobbies;;
            int age;
            string gender;
            struct search_settings settings;

            getline(file, temp);
            string next_string = "next";
            if (temp != next_string) {
                cout << "Wrong Format" << endl;
                break;
            }
            //Wpisz informacje z pliku do klasy

            getline(file, temp);
            login = temp;
            
            getline(file, temp);
            email = temp;
            
            getline(file, temp);
            password = temp;
            
            getline(file, temp);
            name = temp;

            int i = 0;

            while (i < 3) { //add 3 elements to hobbies vector
                getline(file, temp);
                hobbies.push_back(temp);
                i++;

            }

            getline(file, temp);
            age = stoi(temp);

            getline(file, temp);
            gender = temp;

            getline(file, temp);
            settings.preferences = temp;

            getline(file, temp);
            settings.age_window = stoi(temp);
            
            getline(file, temp);
            settings.number_of_matches = stoi(temp);

            //next user
            User user(login, email, password, name, hobbies, age, gender, settings);




            m_users.push_back(user);
          

  
            getline(file, temp);

            string end_string = "end";
            if (temp == end_string) {
                file.close();
                break;
            }

        }

    }
    else
        cout << "Error while loading file" << endl;

}
Dataset::~Dataset() {
    fstream file(m_file);
    if (file.is_open()) {
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
        cout << "Error while loading file" << endl;
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

string Dataset::get_login(int idx) const { return m_users[idx].get_login(); }
string Dataset::get_email(int idx) const { return m_users[idx].get_email(); }
string Dataset::get_password(int idx) const { return m_users[idx].get_password(); }
string Dataset::get_name(int idx) const { return m_users[idx].get_name(); }
vector<string> Dataset::get_hobbies(int idx) const { return m_users[idx].get_hobbies(); }
int Dataset::get_age(int idx) const { return m_users[idx].get_age(); }
string Dataset::get_gender(int idx) const { return m_users[idx].get_gender(); }
struct search_settings Dataset::get_settings(int idx) const { return m_users[idx].get_settings(); }
vector<int> Dataset::get_matches(int idx) const { return m_users[idx].get_matches(); }





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
//Algorytm znajdujący dopasowania
void Dataset::find_matches(string login) {
    int idx = get_user(login); //idx bedzie indeksem uzytkownika
    //matches- tymczasowy wektor przechowujacy indeksy uzytkownikow, ktorzy beda matchami
    //n_matches - pozyskana ze struktury settings liczba dopasowan dla danego uzytkownika
    vector<int> matches;
    int n_matches = m_users[idx].get_settings().number_of_matches;

    for (size_t i = 0; i < m_users.size(); i++) { //i iteruje po uzytkownikach
        if (i != idx) {
            if (matches.size() < (size_t)(n_matches))
                matches.push_back(i);
            else {
                float local_distance = u_distance(m_users[idx] , m_users[i]);
                for (int j = 0; j < n_matches; j++) { //j iteruje po wektorze matches
                    if (local_distance > u_distance(m_users[idx], m_users[matches[j]])) {
                        matches[j] = i;
                        break;
                    }
                }
                
            }
        }
        
    }
    m_users[idx].set_matches(matches); //ustawia wypelniony wektor jako matche uzytkownika idx

}

void Dataset::add_user(User user) {
    m_users.push_back(user);
}

void Dataset::print_users() {
    for (size_t i = 0; i < m_users.size(); i++) {
        cout << "----------------" << endl;
        m_users[i].print_data();
        cout << "----------------" << endl;
   }
}

void Dataset::print_matches(string login) {
    int idx = get_user(login); //idx to indeks uzytkownika z loginem login
    int n_matches = m_users[idx].get_settings().number_of_matches;
    cout << "Matches for user: " << m_users[idx].get_login() << endl;
    
    for (int i = 0; i < n_matches; i++) { //i iteruje po indeksach matchy danego uzytkownika
        cout << "----------------" << endl;
        m_users[m_users[idx].get_matches()[i]].print_data(); //wyswietla i-ty match uzytkownika idx
        cout << "----------------" << endl;
    }
 
}


//Aplikacja


int login_procedure(Dataset &dataset) {
    //Procedura logowania
    //Zwracana wartość- index do uzytkownika, w przypadku błędu : -1
    int ok = 0; //flaga wskazująca czy logowanie przebiegło prawidłowo
    int n = -1;
    while (!ok) {
        int counter = 0; //liczby do 3, jesli trzy logowania beda niepoprawne, wychodzi z aplikacji
        string exit_string; //jesli zostanie wywolana wychodzi z programu
        string password, login;
        cout << "Login: "; getline(cin, login, '\n');
        cout << "Password: "; cin >> password;
        cin.clear();
        cin.ignore(1000, '\n');
        n = dataset.get_user(login);
        if (n  == -1) {//n to numer uzytkownika
            cout << "Wrong ->username or password, try again." << endl;
            cout << "Do you want to exit? If so type exit"; cin >> exit_string;

            cin.clear();
            cin.ignore(1000, '\n');
            cout << endl;
        }
        else {
            string actual_password = dataset.get_password(n);
            if (actual_password == password) {
                cout << "Hello " << login << endl;
                ok = 1;
            }
            else {
                cout << "Wrong username or ->password, try again" << endl;
                cout << "Do you want to exit? If so, type exit: ";cin >> exit_string;

                cin.clear();
                cin.ignore(1000, '\n');
                cout << endl;
            }
        }
        counter++;
        if (exit_string == "exit" || counter == 3 || ok == 1)
            break;
    }
    if (ok == 1)
        return -1; //w przypadku błędu zwraca flagę -1
    else
        return n; //w przypadku powodzenia zwracany jest uzytkownik
    
}
void create_account(Dataset &dataset) {
    string login, email, password, name, gender;
    vector<string> hobbies;
    int age;
    search_settings settings;
    int ok = 0;
    string exit_string;
    int temp;

    while (!ok) {
        cout << "Login: "; getline(cin , login , '\n');
        int n = dataset.get_user(login);
        if (n == -1) {
            ok = 1;
        }
        else {
            cout << "This username aldready exist!" << endl;
            cout << "Do you want to exit? If so, type exit "; cin >> exit_string;
            cin.clear();
            cin.ignore(1000, '\n');
            cout << endl;
            if (exit_string == "exit")
                return;

        }
    }
    ok = 0;

    cout << "Password: "; cin >> password;
    cin.clear();
    cin.ignore(1000, '\n');
  
    while (!ok) {
        cout << "Email: "; cin >> email;
        cin.clear();
        cin.ignore(1000, '\n');
        int n = dataset.get_user_by_email(email);
        if (n == -1) {
            ok = 1;
        }
        else {
            cout << "This email aldready exist!" << endl;
            cout << "Do you want to exit? If so, type exit "; cin >> exit_string;
            cin.clear();
            cin.ignore(1000, '\n');
            cout << endl;
            if (exit_string == "exit")
                return;

        }
    }
    ok = 0;

    cout << "Name: "; getline(cin , name , '\n');
    ok = 0;

    while (!ok) {
        cout << "Gender: "; cin >> gender;
        cin.clear();
        cin.ignore(1000, '\n');

        if (gender == "man" || gender == "woman")
            ok = 1;
        else {
            cout << "Type correct gender!" << endl;
            cout << "Do you want to exit? If so, type exit"; cin >> exit_string;
            cin.clear();
            cin.ignore(1000, '\n');
            cout << endl;
            if (exit_string == "exit")
                return;
        }
    }
    ok = 0;

    while (!ok) {
        cout << "Age: "; cin >> age;
        if (cin.fail()) {
            cout << "Wrong character" << endl;
            cin.clear();
            cin.ignore(1000 , '\n');
            cout << "Do you want to exit? If so, type exit "; cin >> exit_string;
            cin.clear();
            cin.ignore(1000, '\n');
            cout << endl;
            if (exit_string == "exit")
                return;
        }
        else {
            cin.clear();
            cin.ignore(1000, '\n');
            ok = 1;
        }
    }
    ok = 0;
 
    cout << "Choose three hobbies from below list: " << endl;
    cout << "[0] skiing" << endl;
    cout << "[1] bowling" << endl;
    cout << "[2] basketball" << endl;
    cout << "[3] soccer" << endl;
    cout << "[4] climbing " << endl;
    cout << "[5] fashion" << endl;
    cout << "[6] instagram" << endl;
    cout << "[7] netflix" << endl;
    cout << "[8] travelling" << endl;
    cout << "[9] cats" << endl;
    cout << "[10] dogs" << endl;
    cout << "[11] none" << endl;
    for (int i = 0; i < 3; i++) {
        string temp_string;
        while (!ok) {
            cout << "index: "; cin >> temp;
            if (cin.fail() || temp < 0 || temp>11) {
                cout << "Wrong character" << endl;
                cin.clear();
                cin.ignore();
                cout << "Do you want to exit? If so, type exit "; cin >> exit_string;
                cout << endl;
                if (exit_string == "exit")
                    return;
            }
            else {
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
                cin.clear();
                cin.ignore(1000, '\n');
            }
        }
        ok = 0;
        hobbies.push_back(to_string(temp));
    }
    

   

    User user(login, email, password, name, hobbies, age, gender, settings);
    dataset.add_user(user);
    cout << "Account Created" << endl;
}
int main() {
    
    Dataset my_dataset("klasa.txt"); //zmienna globalna- klasa mojej aplikacji
    int control = 0;
    int current_user = -1; //indeks zalogowanego uzytkownika
    int exit_flag = 0;


    while (!exit_flag) {
        cout << "Hello! It's your favourite dating app again!!!!" << endl;
        cout << "[1] Log in" << endl;
        cout << "[2] Create Account" << endl;
        cout << "[Anything else] Exit" << endl;
        cout << "Type the digit:";
        cin >> control;
        cin.clear();
        cin.ignore(1000, '\n');
        string login, password;
        switch (control) {
        case 1: {
            //Procedura logowania
            current_user = login_procedure(my_dataset);
            break;
        }
        case 2: {
            create_account(my_dataset);
            break;
        }

        default:
            exit_flag = 1;
            break;
           
        }

    }

   
   

}
