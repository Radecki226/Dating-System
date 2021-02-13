| ![](RackMultipart20210213-4-fhdr0p_html_56196db211ff095c.jpg)



# Dating System



# Opis projektu

Niniejszy projekt jest implementacją aplikacji randkowej w języku c++. Aplikacja umożliwia użytkownikom zakładanie kont i wyszukiwanie użytkowników, których system uzna za potencjalnie interesujących dla danej osoby.Jeśli dana osoba zostanie dopasowana do użytkownika, wyświetlone zostaną jej dane osobowe i dane kontaktowe. Aplikacja umożliwia także edycję danych osobowych i ustawień. Każdy użytkownik może usunąć konto w dowolnym momencie. Program ma także funkcjonalność pracy w trybie administratora. Administrator może wyświetlać dane użytkowników i ich usuwać. Aplikacja działa w terminalu Windows/Linux.

1.
# Project description

This project is an implementation of dating system in c++ programming language. Users can register and search for people considered by the system as interesing for them. If a particular person is matched to the user, they can see personal information of this person and contact details. User is allowed to edit their personal information and settings. Every account can be deleted by an user in any time. The program can be run in admin mode. Admin is permitted to see personal data of users and delete users. The application is running in Windows/Linux terminal.

1.
# Instrukcja użytkownika

1. Interfejs użytkownika:

W każdym menu użytkownikom wyświetlane są znaki w kwadratowych nawiasach i działania ułożone w listę. Aby wybrać dane działanie należy wpisać do terminala znak umieszczony w ramce obok tekstu wyrażającego działanie. Na przykład na fig. 1 użytkownik może zalogować się naciskając przycisk „1&quot;, założyć konto naciskając przycisk „2&quot; lub opuścic program wpisując dowolny inny znak lub sekwencję znaków.

![](RackMultipart20210213-4-fhdr0p_html_d7ff4d8072dcf0a4.png) fig. 1

Jeśli użytkownik poda w jakimś menu dialogowym niepoprawne dane wejściowe, program może zapytać czy wyjśc do menu głównego informując o komendzie koniecznej do tego aby powrócić(fig. 2). Jeśli użytkownik poda tę komendę powróci do menu, każdy inny znak lub ciąg znaków zostanie potraktowany jako chęć pozostania w obecnym submenu.

![](RackMultipart20210213-4-fhdr0p_html_979a64ed954b2ec6.png) fig. 2

Wszystkie ekrany opisane poźniej korzystają z tego formatu interfejsu.

2. Menu w programie

2.1 Menu początkowe

Użytkownik może założyć konto lub zalogować się do już istniejącego.

2.2 Procedura logowania

Użytkownik powinien wpisać swój login i hasło aby zalogować się do aplikacji. W przypadku podania błędnych danych jest możliwe powtórzenie logowania lub powrót do menu początkowego. Jeśli poprawne dane są poprawne następuje przeniesienie do panelu użytkownika.

2.3 Procedura zakładania konta

Użytkownik proszony jest o podanie swoich danych. W przypadku użycia występującego już loginu lub emaila zostanie o tym poinformowany. W przypadku pola „gender&quot; konieczne jest użycie słow man lub woman. W przypadku wieku konieczne jest podanie liczb z zakresu 18-120. Użytkownik może wybrać do 3 hobby jednak żadne nie może się powtarzać(z wyjątkiem braku hobby).

2.4 Panel użytkownika

W panelu użytkownika wyświetlone są dane i ustawienia konta. Użytkownik może przejść do edycji konta, wyszukwać innego użytkownika lub wyświetlić dopasowane dla niego osoby.

2.5 Edycja konta

Użytkonik może zmienić email, hasło, hobby, a także edytować ustawienia.

2.6 Wyszukiwanie użytkowników

Aplikacja prosi o wprowadzenie minimalnego i maksymalnego wieku, a także o podanie jednego hobby stanowiącego kryterium wyszkukiwania. Po wprowadzeniu tych wielkości pojawia się lista użytkowników spełniających kryteria

2.7 Panel administratora

Administrator ma możliwość zmiany hasła, wyświetlenia pełnej listy użytkowników i usunięcia użytkownika po loginie.

3. Kompilacja

Wystarczająca jest standardowa kompilacja zgodna z c++11.

4. Dodatkowe informacje

Aby dane z bieżącej sesji zostały zapisane konieczne jest poprawne zamknięcie aplikacji. Jako poprawne rozumie się naciśnięcie przycisku różnego od „1&quot; i „2&quot; w menu początkowym.

# 3. Pliki źródłowe

Projekt składa się z następujących plików źródłowych:

- _Dating\_System.cpp- zawiera definicje oraz deklaracje klas, definicje i deklaracje funkcji, a także funkcję main() z pętlą główną programu._

#


#


#


# 4. Opis klas

W projekcie utworzono następujące klasy:

1. User //klasa reprezentująca użytkownika, przechowuje dane użytkownika

//konstruktor klasy przyjmujący dane użytkownika jako parametry

User(stringlogin, stringemail, stringpassword, stringname, vector\&lt;string\&gt; hobbies

, intage, stringgender, search\_settingssettings);

//inne metody

void print\_data(); //wyświetla dane o użytkowniku

void print\_settings(); //wyświetla ustawienie wyszukiwania użytkownika

2. Dataset //Baza danych użytkowników, przechowuje wektor użytkowników i scieżkę do pliku, do którego nastąpi zapis a także hasło administratora

//Konstruktor

Dataset(stringpath); //ścieżka do pliku jako argument konstruktora

//Destruktor- zapiusuje bazę do pliku tekstowego

~Dataset();

//inne metody

intDataset::get\_user(stringlogin) //Zwraca indeks do użytkownika na bazie podanego loginu, jeśli login nieprawidłowy, zwraca -1

intDataset::get\_user\_by\_email(stringemail) //Podobnie jak wyżej, ale na podstawie adresu email

void find\_matches(intidx); //Przeszukuje klasę w celu dopasowania odpowienich osób, przyjmuje indeks użytkownika jako argument

void add\_user(Useruser); //Dodaje użytkownika do klasy

void remove\_user(intidx); //Usuwa użytkownika z bazy, przyjmuje indeks jako argument

void print\_user(intidx); //Wyświetla użytkownika o zadanym indeksie

void print\_users();//Wyświetla wszystkich użytkowników

void print\_matches(intidx); //Wyświetla dopasowania dla użytkownika o indeksie idx

# 5. Inne funkcje i struktury danych

structsearch\_settings//struktura zawierająca ustawienia wyszkiwania

void print\_string\_vector(vector\&lt;string\&gt; v) //funkcja wyświetlająca wektor stringów

float string\_vector\_distance(vector\&lt;string\&gt; const &amp;v1, vector\&lt;string\&gt; const &amp;v2) //funkcja porównująca dwa wektory stringi zwraca liczbę z przedziału[0,1] w zależności od ilości wspólnych wyrazów

float u\_distance(Userconst &amp;u1, Userconst &amp;u2) //funkcja mierzaca podobienstwo pomiedzy uzytkownikami, zwraca liczbę z przedziału [0,1]

void fill\_hobbies(Dataset&amp; dataset, intuser\_idx) a//Funkcja przyjmuje jako argumenty bazę danych i indeks użytkownika, prowadzi interakcję z użytkownikiem i wypełnia jego wektor hobby podanymi wartościami

int edit\_menu(Dataset&amp; dataset, intuser\_idx) //Funkcja przyjmuje jako argumenty bazę danych i indeks użytkownika, zapewnia interfejs do edycji danych

int search(Dataset&amp; dataset) //Funkcja przyjmuje jako argument bazę danych. Zapewnia interfejs do komunikacji z użytkownikiem i przeszkuje bazę zgodnie z podanymi wartościami

int login\_procedure(Dataset &amp;dataset) //Funkcja przyjmuje jako argument bazę danych, zapewnia interfejs logowania

void create\_account(Dataset &amp;dataset) //Funkcja przyjmuje jako argument bazę danych. Prowadzi dialog z użytkownikiem zakładającym nowe konto.

void user\_panel(Dataset &amp;dataset , intuser\_idx) //Funkcja przyjmuje jako argumenty bazę danych i indeks użytkownika, zapewnia interfejs panelu użytkownika

void admin\_panel(Dataset&amp; dataset) //Funkcja przyjmuje jako argumenty bazę danych. Zapewnia interfejs dla administratora.

# 6. Zasoby

W projekcie wykorzystywane są następujące pliki zasobów:

- klasa.txt – plik zawierający dane użytkowników aplikacji. W przypadku braku pliku zostaje on utworzony. Plik w kolejnych liniach zawiera:
  - hasło administratora
  - użytkownik1, czyli:
    - słowo kontrolne „next&quot;
    - login
    - email
    - hasło
    - Imię/Imię Nazwisko
    - hobby1
    - hobby2
    - hobby3
    - wiek
    - płeć
    - kryterium porównywania(hobby/wiek)
    - przedział wieku z którego mają być dobierani użytkownicy
    - słowo kontrolne &#39;----------------&#39;
  - kolejni użytkownicy
  - Dla ostatniego użytkownia &#39;end&#39; zamiast &#39;----------------&#39;

# 7. Dalszy rozwój i ulepszenia

W dalszym rozwoju aplikacji zasadne wydaje się dodania funkcji sieciowych aplikacji i umożliwienie użytkowniom logowania się za pomocą internetu do serwera, na którym pracuje aplikacja.

# 8.Inne

Brak
