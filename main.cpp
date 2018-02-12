#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <fstream>

using namespace std;

struct PersonData {
    int idNumber;
    string name;
    string surname;
    string telephoneNumber;
    string email;
    string address;
};

int addNewContact(PersonData addressBook[], int numberOfContacts) {
    string name, surname, email, telephoneNumber, address;
    cout<<"Podaj imie: "; cin>>name; cin.clear(); cin.sync();
    cout<<"Podaj nazwisko: "; cin>>surname; cin.clear(); cin.sync();

    int i=0;
    while(i<numberOfContacts) {
        if(addressBook[i].name==name && addressBook[i].surname==surname) {
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

    addressBook[numberOfContacts].name=name;
    addressBook[numberOfContacts].surname=surname;
    addressBook[numberOfContacts].telephoneNumber=telephoneNumber;
    addressBook[numberOfContacts].email=email;
    addressBook[numberOfContacts].address=address;
    addressBook[numberOfContacts].idNumber=numberOfContacts+1;

    fstream plik;
    plik.open("KsiazkaAdresowa.txt",ios::out | ios::app);

    if(plik.good()==true) {
        plik<<addressBook[numberOfContacts].idNumber<<endl;
        plik<<addressBook[numberOfContacts].name<<endl;
        plik<<addressBook[numberOfContacts].surname<<endl;
        plik<<addressBook[numberOfContacts].telephoneNumber<<endl;
        plik<<addressBook[numberOfContacts].email<<endl;
        plik<<addressBook[numberOfContacts].address<<endl;
        plik.close();
    } else {
        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych.";
        system("pause");
    }

    cout<<"Dodano nowy kontakt"<<endl;
    Sleep(1000);
    return numberOfContacts+1;
}

void findContact(PersonData addressBook[],int numberOfContacts) {
    char menuOperation=0;
    do {
        int numberOfPersonFound=0;
        string personToFind="";
        cout<<"Podaj imie lub nazwisko szukanej osoby: ";
        cin>>personToFind; cin.clear(); cin.sync(); cout<<endl;

        for(int i=0; i<numberOfContacts; i++) {
            if(addressBook[i].name==personToFind || addressBook[i].surname==personToFind) {
                cout<<addressBook[i].name<<endl;
                cout<<addressBook[i].surname<<endl;
                cout<<addressBook[i].telephoneNumber<<endl;
                cout<<addressBook[i].email<<endl;
                cout<<addressBook[i].address<<endl<<endl;
                numberOfPersonFound++;
            }
        }
        if(numberOfPersonFound==0) {
            cout<<"Nie odnaleziono zadnych kontaktow!"<<endl<<endl;
        }
        cout<<"1. Ponow wyszukiwanie"<<endl;
        cout<<"2. Powrot do menu glownego"<<endl;
        cout<<"3. Zakoncz program"<<endl;
        cin>>menuOperation; cin.clear(); cin.sync();
        if (menuOperation=='3')
            exit(0);
    } while(menuOperation=='1');
}

void showContacts(PersonData addressBook[], int numberOfContacts) {
    if(numberOfContacts==0)
        cout<<"Ksiazka adresowa jest pusta!"<<endl;
    for(int i=0; i<numberOfContacts; i++) {
        cout<<addressBook[i].name<<endl;
        cout<<addressBook[i].surname<<endl;
        cout<<addressBook[i].telephoneNumber<<endl;
        cout<<addressBook[i].email<<endl;
        cout<<addressBook[i].address<<endl<<endl;

    }
    char menuOperation;
    cout<<"1. Powrot do menu glownego"<<endl;
    cout<<"2. Zakoncz program"<<endl;
    cin>>menuOperation; cin.clear(); cin.sync();
    if (menuOperation=='2')
        exit(0);
}

int loadAddressBook(PersonData addressBook[]) {
    int contactNumber=0;
    string lineToLoad="";
    cin.clear(); cin.sync();

    fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::in);

    if(plik.good()==true) {
        while(!plik.eof()) {
            getline(plik, lineToLoad);
            addressBook[contactNumber].idNumber=atoi(lineToLoad.c_str()); cin.clear(); cin.sync();
            getline(plik, lineToLoad);
            addressBook[contactNumber].name=lineToLoad; cin.clear(); cin.sync();
            getline(plik, lineToLoad);
            addressBook[contactNumber].surname=lineToLoad; cin.clear();  cin.sync();
            getline(plik, lineToLoad);
            addressBook[contactNumber].telephoneNumber=lineToLoad; cin.clear(); cin.sync();
            getline(plik, lineToLoad);
            addressBook[contactNumber].email=lineToLoad; cin.clear(); cin.sync();
            getline(plik, lineToLoad);
            addressBook[contactNumber].address=lineToLoad; cin.clear(); cin.sync();
            contactNumber++;
        }
        plik.close();
        return contactNumber-1;
    } else
        return contactNumber;
}

int main() {
    PersonData addressBook[1000];
    int contactID=0;
    int numberOfContacts=loadAddressBook(addressBook);
    char menuOperation;

    while(1) {
        system("cls");
        cout<<"------------------"<<endl;
        cout<<" KSIAZKA ADRESOWA:"<<endl;
        cout<<"------------------"<<endl;
        cout<<"1. Dodaj nowy kontakt"<<endl;
        cout<<"2. Znajdz kontakt"<<endl;
        cout<<"3. Wyswietl kontakty"<<endl;
        cout<<"4. Zakoncz program"<<endl;
        cin>>menuOperation;
        switch (menuOperation) {
        case '1':
            numberOfContacts = addNewContact(addressBook,numberOfContacts);
            break;
        case '2':
            findContact(addressBook,numberOfContacts);
            system("cls");
            break;
        case '3':
            showContacts(addressBook,numberOfContacts);
            system("cls");
            break;
        case '4':
            exit(0);
            break;
        }
    }
    return 0;
}
