#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <windows.h>

using namespace std;

const int MAX_PALABRAS = 10;

void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void highlightSpecificWords(const string& texto, const string palabrasResaltar[MAX_PALABRAS], int numPalabras){
    size_t pos=0;
    size_t found;

    while ((found = texto.find_first_of(" \n\t", pos)) != string::npos){
        string palabra = texto.substr(pos, found - pos);

        bool resaltar = false;
        
        for (int i=0; i < numPalabras; i++){
            if (palabra == palabrasResaltar[i]){
                resaltar = true;
                break;
            }
        }
        if (resaltar){
            setColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
            cout << palabra;
            setColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        }
        else{
            cout << palabra;
        }
        cout << texto[found];
        pos = found + 1;
    }
    cout << texto.substr(pos);
}

int main (){
    setColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);

    ifstream archivoTexto("texto.txt");
    if (!archivoTexto.is_open()){
        cerr << "No se pudo abrir el archivo" << endl;
        return 1;
    }

    stringstream buffer;
    buffer << archivoTexto.rdbuf();
    string texto = buffer.str();

    archivoTexto.close();

    cout << "Ingrese la palabra que quiera resaltar: ";
    string palabraResaltar;
    cin >> palabraResaltar;

    highlightSpecificWords(texto, &palabraResaltar, 1);

    setColor(FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);

    return 0;
}