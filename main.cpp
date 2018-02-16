#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

struct PersonData {
    int idNumber;
    string name;
    string surname;
    string telephoneNumber;
    string email;
    string address;
};

int loadAddressBook(vector <PersonData>& addressBook) {
    addressBook.clear();
    PersonData personToLoad;
    int lastIdNumber = 0;
    string lineToLoad="";
    fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::in);

    if(plik.good()==true) {
        while(getline(plik, lineToLoad)) {
            stringstream linestream(lineToLoad);
            string dataToLoad;
            cin.clear(); cin.sync();
                getline(linestream, dataToLoad, '|');
                personToLoad.idNumber = atoi(dataToLoad.c_str());
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
                lastIdNumber = personToLoad.idNumber;
                }
        plik.close();
        return lastIdNumber;
    } else
        return lastIdNumber;
}

void addNewContact(vector <PersonData>& addressBook, int lastIdNumber) {

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
    plik.open("KsiazkaAdresowa.txt",ios::out | ios::app);

    if(plik.good()==true) {
    plik<<(newPerson.idNumber = lastIdNumber+1)<<"|";
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

void changeData(vector <PersonData>& addressBook, int numberOfContacts) {
char menuOperation = 0;
    do {
        string name, surname, email, telephoneNumber, address;
        int idToChange;
        int numberOfPersonFound = 0;
        cout<<"Podaj nr ID osoby, ktorej dane chcesz zmienic: ";
        cin>>idToChange; cin.clear(); cin.sync(); cout<<endl;

        int idFromFile;
        string lineToLoad = "";

        ifstream plik;
        ofstream temp;
        plik.open("KsiazkaAdresowa.txt");
        temp.open("temp.txt");

        if(plik.good() == true) {
        while(getline(plik, lineToLoad)) {
            stringstream linestream(lineToLoad);
            string dataToLoad;
            cin.clear(); cin.sync();
                getline(linestream, dataToLoad, '|');
                idFromFile = atoi(dataToLoad.c_str());
                if (idToChange != idFromFile)
                temp << lineToLoad << endl;
                else if (idToChange == idFromFile){
                cout << "Podaj nowe dane: " << endl;
                cout << "Podaj imie: "; cin>>name; cin.clear();  cin.sync();
                cout << "Podaj nazwisko: "; cin>>surname; cin.clear(); cin.sync();
                cout << "Podaj nr telefonu: "; cin>>telephoneNumber; cin.clear(); cin.sync();
                cout << "Podaj email: "; cin>>email; cin.clear(); cin.sync();
                cout << "Podaj adres: "; getline(cin,address); cin.clear(); cin.sync();
                cout << endl;
                temp << (addressBook[idToChange-1].idNumber = idToChange) << "|";
                temp << (addressBook[idToChange-1].name = name) << "|";
                temp << (addressBook[idToChange-1].surname = surname) << "|";
                temp << (addressBook[idToChange-1].telephoneNumber = telephoneNumber) << "|";
                temp << (addressBook[idToChange-1].email = email) << "|";
                temp << (addressBook[idToChange-1].address = address) << "|" << endl;
                numberOfPersonFound++;
                }
        }
        plik.close();
        temp.close();
        remove("KsiazkaAdresowa.txt");
        rename("temp.txt", "KsiazkaAdresowa.txt");
        } if(numberOfPersonFound == 0) {
            cout<<"Nie odnaleziono kontaktu o wskazanym ID!"<<endl<<endl;
        }
        cout<<"1. Ponow polecenie" << endl;
        cout<<"2. Powrot do menu glownego" << endl;
        cout<<"3. Zakoncz program" << endl;
        cin>>menuOperation; cin.clear(); cin.sync();
        if (menuOperation == '3')
            exit(0);
    }while(menuOperation == '1');
}


void eraseContact(vector <PersonData>& addressBook, int lastIdNumber) {
    int idToErase;
    do {
        cout << "Podaj nr ID osoby, ktorej dane chcesz wykasowac: ";
        cin >> idToErase; cin.clear(); cin.sync(); cout << endl;
        if (idToErase > lastIdNumber)
        cout << "Nie odnaleziono kontaktu o wskazanym ID!" << endl;
    }while (idToErase >  lastIdNumber);

        int idFromFile;
        string lineToLoad = "";

        ifstream plik;
        ofstream temp;
        plik.open("KsiazkaAdresowa.txt");
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
                addressBook.erase(addressBook.begin()+(idToErase-1));
            }
        plik.close();
        temp.close();
        remove("KsiazkaAdresowa.txt");
        rename("temp.txt", "KsiazkaAdresowa.txt");
        cout<<"Usunieto kontakt"<<endl;
        Sleep(1000);
        }
}


int main() {
    vector <PersonData> addressBook;
    loadAddressBook(addressBook);
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
        cout<<"6. Zakoncz program"<<endl;
        cin >> menuOperation;
        switch (menuOperation) {
        case '1':
            addNewContact(addressBook,loadAddressBook(addressBook));
            break;
        case '2':
            findContact(addressBook);
            system("cls");
            break;
        case '3':
            showContacts(addressBook,loadAddressBook(addressBook));
            system("cls");
            break;
        case '4':
            changeData(addressBook,loadAddressBook(addressBook));
            break;
        case '5':
            eraseContact(addressBook,loadAddressBook(addressBook));
            break;
        case '6':
            exit(0);
            break;
        }
    }
    return 0;
}
