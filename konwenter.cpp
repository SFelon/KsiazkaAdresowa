#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <fstream>
#include <sstream>

using namespace std;

int main() {
        cout<<"------------------"<<endl;
        cout<<" KONWENTER DANYCH:"<<endl;
        cout<<"------------------"<<endl;
        string fileName;
        string fileNametxt;
        string newFileName;
        string lineToLoad="";
        fstream plik;
        ofstream temp;
        bool done;

        do {
        cout << "Podaj nazwe pliku wejsciowego: ";
        getline( cin, fileName);
        fileNametxt = fileName + ".txt";

        plik.open(fileNametxt.c_str());

        if(plik.good()==true) {
            newFileName = fileName + "_nowy_format.txt";
            temp.open(newFileName.c_str());
            while(!plik.eof()) {
                getline(plik, lineToLoad);
                temp << (lineToLoad+="|");
                getline(plik, lineToLoad);
                temp << (lineToLoad+="|");
                getline(plik, lineToLoad);
                temp << (lineToLoad+="|");
                getline(plik, lineToLoad);
                temp << (lineToLoad+="|");
                getline(plik, lineToLoad);
                temp << (lineToLoad+="|");
                getline(plik, lineToLoad);
                temp << (lineToLoad+="|") <<endl;
                }
        plik.close();
        temp.close();
        cout<<"Przekonwertowano dane!"<<endl;
        cout<<"Nowe dane znajdziesz w pliku pod nazwa: " << newFileName << endl;
        Sleep(1000);
        done = true;
        } else {
        cout << "Nie mozna otworzyc pliku o podanej nazwie" <<endl;
        Sleep(1000);
        done = false;
        }
        }while(done == false);
    return 0;
}
