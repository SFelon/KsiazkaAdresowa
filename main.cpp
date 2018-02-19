#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <fstream>
#include <vector>
#include <sstream>


using namespace std;

struct User
{
    int id;
    string login;
    string password;
};

int loadUserData(vector <User>& users) {
    users.clear();
    User userToLoad;
    int lastUserIdNumber = 0;
    string lineToLoad="";
    fstream plik;
    plik.open("Uzytkownicy.txt", ios::in);

    if(plik.good()==true) {
        while(getline(plik, lineToLoad)) {
            stringstream linestream(lineToLoad);
            string dataToLoad;
            cin.clear(); cin.sync();
                getline(linestream, dataToLoad, '|');
                userToLoad.id = atoi(dataToLoad.c_str());
                getline(linestream, dataToLoad, '|');
                userToLoad.login = dataToLoad;
                getline(linestream, dataToLoad, '|');
                userToLoad.password = dataToLoad;
                users.push_back( userToLoad );
                lastUserIdNumber = userToLoad.id;
                }
        plik.close();
        return lastUserIdNumber;
    } else
        return lastUserIdNumber;
}


void registerNewUser(vector <User>& users, int lastIdNumber) {
User newUser;
string login, password;
cout << "Podaj nowy login uzytkownika: ";
cin >> login;

vector <User> ::iterator it;
    for (it = users.begin(); it != users.end(); it++) {
        if (it->login == login) {
            cout << "Podany login jest juz wykorzystany. Wybierz inny: ";
            cin >> login;
        }
    }
    cout << "Podaj haslo: ";
    cin >> password;

    fstream plik;
    plik.open("Uzytkownicy.txt",ios::out | ios::app);

       if(plik.good()==true) {
       plik<<( newUser.id = lastIdNumber+1 ) << "|";
       plik<<( newUser.login = login ) << "|";
       plik<<( newUser.password = password ) << "|" << endl;
       plik.close();
       users.push_back(newUser);
       cout<<"Konto zalozone"<<endl;
       Sleep(1000);
       } else {
        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych.";
        system("pause");
       }
 }

int loginUser(vector <User>& users) {
    string login, password;
    cout << "Podaj login: ";
    cin >> login;
    vector <User> ::iterator it;
    for (it = users.begin(); it != users.end(); it++) {
        if (it->login == login) {
            for(int j=0; j<3; j++) {
                cout<<"Podaj haslo. Pozostalo prob: "<<3-j<<endl;
                cin >> password;
                if ( users[(it - users.begin())].password == password ) {
                    cout<<"Zalogowales sie."<<endl;
                    Sleep(1000);
                    return users[(it - users.begin())].id;
                }
            }
            cout<<"Podales 3 razy bledne haslo. Poczekaj";
            Sleep(3000);
            return 0;
        }
    }
    cout<<"Uzytkownik o podanym loginie nie istnieje"<<endl;
    Sleep(1500);
    return 0;
}

void changePassword(vector <User>& users, int idLoggedUser) {
    int id;
    string login, password;
    cout<<"Podaj nowe haslo: ";
    cin >> password;
    vector <User> ::iterator it;
    for (it = users.begin(); it != users.end(); it++) {
        if (it->id == idLoggedUser) {

            id = users[(it - users.begin())].id;
            login = users[(it - users.begin())].login;

            int idFromFile;
            string lineToLoad = "";

            ifstream plik;
            ofstream temporary;
            plik.open("Uzytkownicy.txt");
            temporary.open("temporary.txt");

            if(plik.good() == true) {
                while(getline(plik, lineToLoad)) {
                    stringstream linestream(lineToLoad);
                    string dataToLoad;
                    cin.clear();
                    cin.sync();
                    getline(linestream, dataToLoad, '|');
                    idFromFile = atoi(dataToLoad.c_str());
                    if (idLoggedUser != idFromFile)
                        temporary << lineToLoad << endl;
                    else if (idLoggedUser == idFromFile) {
                        temporary << (users[(it - users.begin())].id = id) << "|";
                        temporary << (users[(it - users.begin())].login = login) << "|";
                        temporary << (users[(it - users.begin())].password = password) << "|" << endl;
                    }
                }
                plik.close();
                temporary.close();
                remove("Uzytkownicy.txt");
                rename("temporary.txt", "Uzytkownicy.txt");
                cout<<"Haslo zostalo zmienione";
                Sleep(1000);
            } else {
                cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych.";
                system("pause");
            }
        }
    }
}

struct PersonData {
    int idNumber;
    string name;
    string surname;
    string telephoneNumber;
    string email;
    string address;
};

int loadAddressBook(vector <PersonData>& addressBook, int idLoggedUser) {
    addressBook.clear();
    PersonData personToLoad;
    int lastIdNumber = 0;
    int userIdFromFile;
    string lineToLoad="";
    fstream plik;
    plik.open("Adresaci.txt", ios::in);

    if(plik.good()==true) {
        while(getline(plik, lineToLoad)) {
            stringstream linestream(lineToLoad);
            string dataToLoad;
            cin.clear(); cin.sync();
                getline(linestream, dataToLoad, '|');
                    personToLoad.idNumber = atoi(dataToLoad.c_str());
                    lastIdNumber = personToLoad.idNumber;
                getline(linestream, dataToLoad, '|');
                    userIdFromFile = atoi(dataToLoad.c_str());
                if (userIdFromFile == idLoggedUser) {
                    getline(linestream, dataToLoad, '|');
                        personToLoad.name = dataToLoad;
                    getline(linestream, dataToLoad, '|');
                        personToLoad.surname = dataToLoad;
                    getline(linestream, dataToLoad, '|');
                        personToLoad.telephoneNumber = dataToLoad;
                    getline(linestream, dataToLoad, '|');
                        personToLoad.email = dataToLoad;
                    getline(linestream, dataToLoad, '|');
                        personToLoad.address = dataToLoad;
                    addressBook.push_back( personToLoad );
                }
                }
        plik.close();
        return lastIdNumber;
    } else
        return lastIdNumber;
}

void addNewContact(vector <PersonData>& addressBook, int lastIdNumber, int idLoggedUser) {

    PersonData newPerson;
    string name, surname, email, telephoneNumber, address;
    cout<<"Podaj imie: "; cin>>name; cin.clear(); cin.sync();
    cout<<"Podaj nazwisko: "; cin>>surname; cin.clear(); cin.sync();
    addressBook.push_back(PersonData());
    int i=0;
    while(i < addressBook.size()) {
        if(addressBook[i].name == name && addressBook[i].surname == surname) {
            cout<<"Kontakt o imieniu "<<name<<" i nazwisku "<<surname<<" juz istnieje."<<endl;
            cout<<"Podaj nowe dane"<<endl;
            cout<<"Podaj imie: "; cin>>name; cin.clear();  cin.sync();
            cout<<"Podaj nazwisko: "; cin>>surname; cin.clear(); cin.sync();
            i=0;
        } else
            i++;
    }
    cout<<"Podaj nr telefonu: "; cin>>telephoneNumber; cin.clear(); cin.sync();
    cout<<"Podaj email: "; cin>>email; cin.clear(); cin.sync();
    cout<<"Podaj adres: "; getline(cin,address); cin.clear(); cin.sync();

    fstream plik;
    plik.open("Adresaci.txt",ios::out | ios::app);

    if(plik.good()==true) {
    plik<<(newPerson.idNumber = lastIdNumber+1)<<"|";
    plik<< idLoggedUser <<"|";
    plik<<(newPerson.name = name)<<"|";
    plik<<(newPerson.surname = surname)<<"|";
    plik<<(newPerson.telephoneNumber = telephoneNumber)<<"|";
    plik<<(newPerson.email = email)<<"|";
    plik<<(newPerson.address = address)<<"|"<<endl;
    plik.close();
    addressBook.push_back(newPerson);
    } else {
        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych.";
        system("pause");
    }

    cout<<"Dodano nowy kontakt"<<endl;
    Sleep(1000);
}

void findContact(vector <PersonData>& addressBook) {
    char menuOperation=0;
    do {
        int numberOfPersonFound=0;
        string personToFind;
        cout<<"Podaj imie lub nazwisko szukanej osoby: ";
        cin>>personToFind; cin.clear(); cin.sync(); cout<<endl;

        vector <PersonData> ::iterator it;
        for (it = addressBook.begin(); it != addressBook.end(); it++) {
        if (it->name == personToFind || it->surname == personToFind) {
                cout << "ID: "<< it->idNumber<<endl;
                cout << "Imie: "<< it->name<<endl;
                cout << "Nazwisko: "<< it->surname<<endl;
                cout << "Nr tel: "<< it->telephoneNumber<<endl;
                cout << "Email: "<< it->email<<endl;
                cout << "Adres: "<< it->address<<endl<<endl;
                numberOfPersonFound++;
            }
        } if(numberOfPersonFound==0) {
            cout<<"Nie odnaleziono zadnych kontaktow!"<<endl<<endl;
        }
        cout<<"1. Ponow wyszukiwanie"<<endl;
        cout<<"2. Powrot do menu glownego"<<endl;
        cout<<"3. Zakoncz program"<<endl;
        cin>>menuOperation; cin.clear(); cin.sync();
        if (menuOperation == '3')
            exit(0);
    } while(menuOperation == '1');
}

void showContacts(vector <PersonData>& addressBook, int lastIdNumber) {
    if(lastIdNumber==0)
        cout<<"Ksiazka adresowa jest pusta!"<<endl;
    for(int i = 0; i < addressBook.size(); i++) {
        cout<<"ID: " << addressBook[i].idNumber<<endl;
        cout<<"Imie: " << addressBook[i].name<<endl;
        cout<<"Nazwisko: " << addressBook[i].surname<<endl;
        cout<<"Nr tel: " << addressBook[i].telephoneNumber<<endl;
        cout<<"Email: " << addressBook[i].email<<endl;
        cout<<"Adres: " << addressBook[i].address<<endl<<endl;
    }
    char menuOperation;
    cout << "1. Powrot do menu glownego" << endl;
    cout << "2. Zakoncz program" << endl;
    cin >> menuOperation; cin.clear(); cin.sync();
    if (menuOperation == '2')
        exit(0);
}

void changeData(vector <PersonData>& addressBook, int lastIdNumber, int idLoggedUser) {
char menuOperation = 0;
int idToChange;
int numberOfPersonFound = 0;
string name, surname, email, telephoneNumber, address;

    if(lastIdNumber==0) {
        cout<<"Ksiazka adresowa jest pusta!"<<endl;
        Sleep(1500);
    } else {
    do {
        cout << "Podaj nr ID osoby, ktorej dane chcesz zmienic: ";
        cin >> idToChange;
        cout << endl;
        vector <PersonData> ::iterator it;
        for (it = addressBook.begin(); it != addressBook.end(); ++it) {
            if (it->idNumber == idToChange) {
                numberOfPersonFound++;
                cout << "ID: " << it->idNumber << endl;
                cout << "Imie: " << it->name << endl;
                cout << "Nazwisko: " << it->surname << endl;
                cout << "Nr tel: " << it->telephoneNumber << endl;
                cout << "Email: " << it->email << endl;
                cout << "Adres: " << it->address << endl << endl;

                name = addressBook[(it - addressBook.begin())].name;
                surname = addressBook[(it - addressBook.begin())].surname;
                telephoneNumber = addressBook[(it - addressBook.begin())].telephoneNumber;
                email = addressBook[(it - addressBook.begin())].email;
                address = addressBook[(it - addressBook.begin())].address;

                cout << "Wybierz dane do edycji: " << endl;
                cout<<"1. Imie"<<endl;
                cout<<"2. Nazwisko"<<endl;
                cout<<"3. Numer telefonu"<<endl;
                cout<<"4. Email"<<endl;
                cout<<"5. Adres"<<endl;
                cout<<"6. Powrot do menu"<<endl;

                char innerMenuOperation = 0;
                cin >> innerMenuOperation; cin.clear(); cin.sync();

                switch (innerMenuOperation) {
                case '1':
                    cout << "Podaj imie: "; cin>>name; cin.clear();  cin.sync(); cout<<endl;
                    break;
                case '2':
                    cout << "Podaj nazwisko: "; cin>>surname; cin.clear(); cin.sync(); cout<<endl;
                    break;
                case '3':
                    cout << "Podaj nr telefonu: "; cin>>telephoneNumber; cin.clear(); cin.sync(); cout<<endl;
                    break;
                case '4':
                    cout << "Podaj email: "; cin>>email; cin.clear(); cin.sync(); cout<<endl;
                    break;
                case '5':
                    cout << "Podaj adres: "; getline(cin,address); cin.clear(); cin.sync(); cout<<endl;
                    break;
                case '6':
                    return;
                    break;
                }

                int idFromFile;
                string lineToLoad = "";

                ifstream plik;
                ofstream temp;
                plik.open("Adresaci.txt");
                temp.open("temp.txt");

                if(plik.good() == true) {
                    while(getline(plik, lineToLoad)) {
                        stringstream linestream(lineToLoad);
                        string dataToLoad;
                        cin.clear();
                        cin.sync();
                        getline(linestream, dataToLoad, '|');
                        idFromFile = atoi(dataToLoad.c_str());
                        if (idToChange != idFromFile)
                            temp << lineToLoad << endl;
                        else if (idToChange == idFromFile) {
                            temp << (addressBook[(it - addressBook.begin())].idNumber = idToChange) << "|";
                            temp <<  idLoggedUser << "|";
                            temp << (addressBook[(it - addressBook.begin())].name = name) << "|";
                            temp << (addressBook[(it - addressBook.begin())].surname = surname) << "|";
                            temp << (addressBook[(it - addressBook.begin())].telephoneNumber = telephoneNumber) << "|";
                            temp << (addressBook[(it - addressBook.begin())].email = email) << "|";
                            temp << (addressBook[(it - addressBook.begin())].address = address) << "|" << endl;
                        }
                    }
                    plik.close();
                    temp.close();
                    remove("Adresaci.txt");
                    rename("temp.txt", "Adresaci.txt");
                }
               cout<<"Dane zostaly zmienione!" << endl;
               Sleep(1000);
               return;
            }
        } if(numberOfPersonFound == 0) {
            cout<<"Nie odnaleziono kontaktu o wskazanym ID!"<<endl<<endl;
            cout<<"1. Ponow polecenie" << endl;
            cout<<"2. Powrot do menu glownego" << endl;
            cout<<"3. Zakoncz program" << endl;
        }
        cin>>menuOperation; cin.clear(); cin.sync();
        if (menuOperation == '3')
            exit(0);
    }while(menuOperation == '1');
}
}


void eraseContact(vector <PersonData>& addressBook, int lastIdNumber) {
    int idToErase;
    char menuOperation = 0;
    int numberOfPersonFound = 0;
    vector <PersonData> ::iterator it;

    if(lastIdNumber == 0) {
        cout<<"Ksiazka adresowa jest pusta!"<<endl;
        Sleep(1500);
    } else {
    do {
        cout << "Podaj nr ID osoby, ktorej dane chcesz wykasowac: ";
        cin >> idToErase;
        cout << endl;
        for (it = addressBook.begin(); it != addressBook.end(); ++it) {
        if (it->idNumber == idToErase) {
                cout << "ID: " << it->idNumber << endl;
                cout << "Imie: " << it->name << endl;
                cout << "Nazwisko: " << it->surname << endl;
                cout << "Nr tel: " << it->telephoneNumber << endl;
                cout << "Email: " << it->email << endl;
                cout << "Adres: " << it->address << endl << endl;
                numberOfPersonFound++;
                break;
        }
        } if (numberOfPersonFound == 0) {
        cout << "Nie odnaleziono kontaktu o wskazanym ID!" << endl << endl;
        Sleep(1000);
        return;
        }
    }while (numberOfPersonFound == 0);

    cout << "Czy na pewno chcesz wykasowac kontakt (t/n): ";
    cin >> menuOperation; cin.clear(); cin.sync();

    if (menuOperation == 't' || menuOperation == 'T') {
        int idFromFile = 0;
        string lineToLoad = "";

        ifstream plik;
        ofstream temp;
        plik.open("Adresaci.txt");
        temp.open("temp.txt");

        if(plik.good() == true) {
        while(getline(plik, lineToLoad)) {
            stringstream linestream(lineToLoad);
            string dataToLoad;
            cin.clear(); cin.sync();
                getline(linestream, dataToLoad, '|');
                idFromFile = atoi(dataToLoad.c_str());
                if (idToErase != idFromFile)
                temp << lineToLoad << endl;
            }
        plik.close();
        temp.close();
        remove("Adresaci.txt");
        rename("temp.txt", "Adresaci.txt");

        addressBook.erase(addressBook.begin()+(it - addressBook.begin()));
        cout<<"Usunieto kontakt!"<<endl;
        Sleep(1000);
        }
    }
}
}


int subMenu(vector <User>& users, int idLoggedUser) {
vector <PersonData> addressBook;
loadAddressBook(addressBook,idLoggedUser);
char menuOperation;

    while(1) {
        system("cls");
        cout<<"------------------"<<endl;
        cout<<" KSIAZKA ADRESOWA:"<<endl;
        cout<<"------------------"<<endl;
        cout<<"1. Dodaj nowy kontakt"<<endl;
        cout<<"2. Znajdz kontakt"<<endl;
        cout<<"3. Wyswietl kontakty"<<endl;
        cout<<"4. Zmien dane kontaktu"<<endl;
        cout<<"5. Usun kontakt"<<endl;
        cout<<"6. Zmien haslo"<<endl;
        cout<<"7. Wyloguj"<<endl;
        cout<<"8. Zakoncz program"<<endl;
        cin >> menuOperation;
        switch (menuOperation) {
        case '1':
            addNewContact(addressBook,loadAddressBook(addressBook, idLoggedUser), idLoggedUser);
            system("cls");
            break;
        case '2':
            findContact(addressBook);
            system("cls");
            break;
        case '3':
            showContacts(addressBook,loadAddressBook(addressBook, idLoggedUser));
            system("cls");
            break;
        case '4':
            changeData(addressBook,loadAddressBook(addressBook, idLoggedUser), idLoggedUser);
            system("cls");
            break;
        case '5':
            eraseContact(addressBook,loadAddressBook(addressBook, idLoggedUser));
            system("cls");
            break;
        case '6':
            changePassword(users, idLoggedUser);
            system("cls");
            break;
        case '7':
            return 0;
            break;
        case '8':
            exit(0);
        }
    }
}

int main() {
    vector <User> users;
    loadUserData(users);
    int idLoggedUser = 0;
    int numberOfUsers = 0;
    char mainMenuOperation;

    while(1) {
        system("cls");
        cout<<"------------------"<<endl;
        cout<<" KSIAZKA ADRESOWA:"<<endl;
        cout<<"------------------"<<endl;
        cout<<"1. Rejestracja"<<endl;
        cout<<"2. Logowanie"<<endl;
        cout<<"9. Zakoncz Program"<<endl;
        cin >> mainMenuOperation;
        switch(mainMenuOperation) {
        case '1':
            registerNewUser(users, loadUserData(users));
            system("cls");
            break;
        case '2': {
            do {
                idLoggedUser = subMenu(users, loginUser(users));
            } while (idLoggedUser != 0);
            system("cls");
            break;
        } case '9':
            exit(0);
            break;
        }
    }
    return 0;
}
