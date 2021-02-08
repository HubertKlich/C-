#include <iostream>
#include <string> 
#include <algorithm>   
#include <array>        
#include <random>      
#include <chrono>       
#include <stack> 
#include <functional>
using namespace std;
string PostawioneZetonyPom;
int Runda=1;
bool KolejnaRunda=false;
int sumaZetonow = 0;
class Poczatek {       
public:            
    int LiczbaGraczy=0;       
    int LiczbaKomputerow;
};
class Gracz {       
public:           
    string ImieGracza;
    int karty[2];
    int Zetony;
    int ZetonyPoczatek = 5000;
};
class Komputer {   
public:        
    string NazwaKomputera;
    int karty[2];
    int Zetony;
    int ZetonyPoczatek = 5000;
};
class Karty {       
public:            
    int KartyNaStole[5];
    stack<int> KartyWTaliiStos;
    int KartyWTaliiInt[52];
    int PostawioneZetony=100;
    char KartyWTalii[52][2];
    void ZapelnijTalie(char Karty[13],char Kolory[4]) {
        for (int i = 0; i < 52; i++) {
            KartyWTaliiInt[i] = i;
        }
        int p=0;
        for (int i = 0; i < 13; i++) {
            for (int j = 0; j < 4; j++) { 
                KartyWTalii[p][0] = Karty[i];
                p++;
            }
        }
        for (int i = 0; i < 52; i+=4) {
                KartyWTalii[i][1] = Kolory[0];
                KartyWTalii[i+1][1] = Kolory[1];
                KartyWTalii[i+2][1] = Kolory[2];
                KartyWTalii[i+3][1] = Kolory[3];
        }
            random_shuffle(&KartyWTaliiInt[0], &KartyWTaliiInt[52]);
        for (int i = 0; i < 52; i++) {
            KartyWTaliiStos.push(KartyWTaliiInt[i]);
        }
    }   
};
class Gra {      
public:           
    int PostawioneZetony=0;
    bool PASS = false;
    bool Podbicie = false;
     int nagroda = 0;
     bool wynik = false;
};
const int MaksymalnaLiczbaGraczy = 5;
Poczatek Wprowadzenie;
Gracz Indeks[MaksymalnaLiczbaGraczy];
Komputer IndeksKomp[MaksymalnaLiczbaGraczy];
Karty Ogolne;
Gra Kolejka[MaksymalnaLiczbaGraczy];
class Tury {      
public:             
    void WtasowanieKartGracza() {
        for (int i = 0; i < Wprowadzenie.LiczbaGraczy; i++)
        {
            Indeks[i].karty[0] = Ogolne.KartyWTaliiStos.top();
            Ogolne.KartyWTaliiStos.pop();
            Indeks[i].karty[1] = Ogolne.KartyWTaliiStos.top();
            Ogolne.KartyWTaliiStos.pop();
        }
    }
    void WtasowanieKartKomputera() {
        for (int i = 0; i < Wprowadzenie.LiczbaKomputerow; i++)
        {
            IndeksKomp[i].karty[0] = Ogolne.KartyWTaliiStos.top();
            Ogolne.KartyWTaliiStos.pop();
            IndeksKomp[i].karty[1] = Ogolne.KartyWTaliiStos.top();
            Ogolne.KartyWTaliiStos.pop();
        }
    }
    void WtasowanieKartNaStol() {
        for (int i = 0; i < 5; i++) {
            Ogolne.KartyNaStole[i] = Ogolne.KartyWTaliiStos.top();
            Ogolne.KartyWTaliiStos.pop();
        }
    }
    void Rozpoczecie() {

        for (int i = 0; i < Wprowadzenie.LiczbaGraczy; i++) {
            Indeks[i].Zetony = Indeks[i].ZetonyPoczatek;
        }
        for (int i = 0; i < Wprowadzenie.LiczbaKomputerow; i++) {
            IndeksKomp[i].Zetony = IndeksKomp[i].ZetonyPoczatek;
        }
    }
    void Kolejka1() {        
        for (int i = 0; i < Wprowadzenie.LiczbaGraczy; i++) {
            if (Kolejka[i].PASS == false) {
                if (Kolejka[i].Podbicie == true) {
                    KolejnaRunda = true;
                    break;
                }
                else {
                    KolejnaRunda = true;
                    for (int j = 0; j < Wprowadzenie.LiczbaGraczy; j++) {
                        if (Kolejka[j].Podbicie == true) {
                            KolejnaRunda = false;
                        }
                    }
                }               
                while (Kolejka[i].PostawioneZetony < Ogolne.PostawioneZetony) {
                cout << "Kolejka gracza:" << Indeks[i].ImieGracza << endl << "Twoje zetony:" << Indeks[i].Zetony << endl;
                cout << "Twoje karty:"; 
                int TablicaDoRysowania[2] = { Indeks[i].karty[0], Indeks[i].karty[1] };
                Rysowanie(2, TablicaDoRysowania);
                if (Runda == 1) {
                    int TablicaDoRysowania[5] = { -1,-1,-1,-1,-1 };
                    Rysowanie(5, TablicaDoRysowania);
                    cout << endl << "Ile postawisz zetonow?(min." << Ogolne.PostawioneZetony << ")" << endl;
                }
                else if (Runda == 2) {
                    int TablicaDoRysowania[5] = { Ogolne.KartyNaStole[0],Ogolne.KartyNaStole[1],Ogolne.KartyNaStole[2],-1,-1 };
                    Rysowanie(5, TablicaDoRysowania);
                    cout << endl << "Ile postawisz zetonow?(min." << Ogolne.PostawioneZetony << ")" << endl;
                }
                else if (Runda == 3) {
                    int TablicaDoRysowania[5] = { Ogolne.KartyNaStole[0],Ogolne.KartyNaStole[1],Ogolne.KartyNaStole[2],Ogolne.KartyNaStole[3],-1 };
                    Rysowanie(5, TablicaDoRysowania);
                    cout << endl << "Ile postawisz zetonow?(min." << Ogolne.PostawioneZetony << ")" << endl;
                }
                else if (Runda == 4) {
                    int TablicaDoRysowania[5] = { Ogolne.KartyNaStole[0],Ogolne.KartyNaStole[1],Ogolne.KartyNaStole[2],Ogolne.KartyNaStole[3],Ogolne.KartyNaStole[4] };
                    Rysowanie(5, TablicaDoRysowania);
                    cout << endl << "Ile postawisz zetonow?(min." << Ogolne.PostawioneZetony << ")" << endl;
                }                    
                    cin >> PostawioneZetonyPom;
                    if (PostawioneZetonyPom != "PASS" && stoi(PostawioneZetonyPom.c_str()) == Ogolne.PostawioneZetony && stoi(PostawioneZetonyPom.c_str()) <= Indeks[i].ZetonyPoczatek) {
                        Kolejka[i].PostawioneZetony = stoi(PostawioneZetonyPom.c_str());
                        Ogolne.PostawioneZetony = Kolejka[i].PostawioneZetony;
                    }
                    if (PostawioneZetonyPom != "PASS" && stoi(PostawioneZetonyPom.c_str()) > Ogolne.PostawioneZetony && stoi(PostawioneZetonyPom.c_str()) <=Indeks[i].ZetonyPoczatek) {
                        Kolejka[i].PostawioneZetony = stoi(PostawioneZetonyPom.c_str());
                        Ogolne.PostawioneZetony = Kolejka[i].PostawioneZetony;
                        for (int j = 0; j < Wprowadzenie.LiczbaGraczy; j++) {
                            Kolejka[j].Podbicie = false;
                        }
                        Kolejka[i].Podbicie = true;                       
                    }                    
                    if (PostawioneZetonyPom == "PASS") {
                        Kolejka[i].PASS = true;
                        break;
                    }                                      
                    system("cls");
                }
                Indeks[i].Zetony =Indeks[i].ZetonyPoczatek-Kolejka[i].PostawioneZetony;
                sumaZetonow += Kolejka[i].PostawioneZetony;
                system("cls");
            }
        }
        for (int i = 0; i < Wprowadzenie.LiczbaKomputerow; i++) {
            if (Kolejka[i+Wprowadzenie.LiczbaGraczy].PASS == false) {
                if (Kolejka[i + Wprowadzenie.LiczbaGraczy].Podbicie == true) {
                    KolejnaRunda = true;
                    break;
                }
                else {
                    KolejnaRunda = true;
                    for (int j = 0; j < Wprowadzenie.LiczbaKomputerow; j++) {
                        if (Kolejka[j + Wprowadzenie.LiczbaGraczy].Podbicie == true) {
                            KolejnaRunda = false;
                        }
                    }
                }             
                    PostawioneZetonyPom = to_string(rand() % IndeksKomp[i].Zetony);
                    if (PostawioneZetonyPom != "PASS" && stoi(PostawioneZetonyPom.c_str()) == Ogolne.PostawioneZetony && stoi(PostawioneZetonyPom.c_str()) <= IndeksKomp[i].ZetonyPoczatek) {
                        Kolejka[i + Wprowadzenie.LiczbaGraczy].PostawioneZetony = stoi(PostawioneZetonyPom.c_str());
                        Ogolne.PostawioneZetony = Kolejka[i + Wprowadzenie.LiczbaGraczy].PostawioneZetony;
                    }
                    if (PostawioneZetonyPom != "PASS" && stoi(PostawioneZetonyPom.c_str()) > Ogolne.PostawioneZetony && stoi(PostawioneZetonyPom.c_str()) <= IndeksKomp[i].ZetonyPoczatek) {
                        Kolejka[i + Wprowadzenie.LiczbaGraczy].PostawioneZetony = stoi(PostawioneZetonyPom.c_str());
                        Ogolne.PostawioneZetony = Kolejka[i + Wprowadzenie.LiczbaGraczy].PostawioneZetony;
                        for (int j = 0; j < Wprowadzenie.LiczbaKomputerow; j++) {
                            Kolejka[j + Wprowadzenie.LiczbaGraczy].Podbicie = false;
                        }
                        Kolejka[i + Wprowadzenie.LiczbaGraczy].Podbicie = true;
                    }
                        if (stoi(PostawioneZetonyPom.c_str()) < Ogolne.PostawioneZetony) {
                            Kolejka[i + Wprowadzenie.LiczbaGraczy].PASS = true;
                            break;
                        }                
                    system("cls");              
                IndeksKomp[i].Zetony = IndeksKomp[i].ZetonyPoczatek - Kolejka[i+Wprowadzenie.LiczbaGraczy].PostawioneZetony;
                sumaZetonow += Kolejka[i + Wprowadzenie.LiczbaGraczy].PostawioneZetony;
                system("cls");
            }
        }
        int SprawdzenieStanuGraczy = 0;
        for (int j = 0; j < Wprowadzenie.LiczbaGraczy+Wprowadzenie.LiczbaKomputerow; j++) {           
            if (Kolejka[j].PASS == false) {
                SprawdzenieStanuGraczy++;
            }           
        }
        if (SprawdzenieStanuGraczy <= 1) {
            Runda = 5;
        }
        if (KolejnaRunda) {
            Runda++;
            for (int j = 0; j < MaksymalnaLiczbaGraczy; j++) {                
                Kolejka[j].Podbicie = false;
                Kolejka[j].PostawioneZetony = 0;
            }
            KolejnaRunda = false;
        }              
    }
    void Rysowanie(int IleKartNarysowac,int Numery[5]) {
        cout << endl;
        for (int i = 0; i < IleKartNarysowac; i++) {
            cout << "--------------------- ";
        }
        cout << endl;
        for (int i = 0; i < IleKartNarysowac; i++) {
            if(Numery[i] != -1 && Ogolne.KartyWTalii[Numery[i]][0]!='1')
            cout << "|" << Ogolne.KartyWTalii[Numery[i]][0] << "                   |";
            else if(Numery[i] != -1 && Ogolne.KartyWTalii[Numery[i]][0] == '1')
                cout << "|" << Ogolne.KartyWTalii[Numery[i]][0] << "0                  |";
            else
                cout << "|                    |";
        }
        cout << endl;
        for (int k = 0; k < 12; k++) {
        for (int i = 0; i < IleKartNarysowac; i++) {           
                if (Numery[i] == -1) {
                    cout << "|                    |";
                }
                else if (Ogolne.KartyWTalii[Numery[i]][1] == 'S')
                {
                    if (k == 0)
                        cout << "|     __     __      |";
                    if (k == 1)
                        cout << "|    /  \\   /   \\    |";
                    if (k == 2)
                        cout << "|   /    \\ /     \\   |";
                    if (k == 3)
                        cout << "|  /      V       \\  |";
                    if (k == 4)
                        cout << "|  \\              /  |";
                    if (k == 5)
                        cout << "|   \\            /   |";
                    if (k == 6)
                        cout << "|    \\          /    |";
                    if (k == 7)
                        cout << "|     \\        /     |";
                    if (k == 8)
                        cout << "|      \\      /      |";
                    if (k == 9)
                        cout << "|       \\    /       |";
                    if (k == 10)
                        cout << "|        \\  /        |";
                    if (k == 11)
                        cout << "|         \\/         |";
                }
                else if (Ogolne.KartyWTalii[Numery[i]][1] == 'K')
                {
                    if (k == 0)
                        cout << "|         /\\         |";
                    if (k == 1)
                        cout << "|        /  \\        |";
                    if (k == 2)
                        cout << "|       /    \\       |";
                    if (k == 3)
                        cout << "|      /      \\      |";
                    if (k == 4)
                        cout << "|     /        \\     |";
                    if (k == 5)
                        cout << "|    /          \\    |";
                    if (k == 6)
                        cout << "|    \\          /    |";
                    if (k == 7)
                        cout << "|     \\        /     |";
                    if (k == 8)
                        cout << "|      \\      /      |";
                    if (k == 9)
                        cout << "|       \\    /       |";
                    if (k == 10)
                        cout << "|        \\  /        |";
                    if (k == 11)
                        cout << "|         \\/         |";
                }
                else if (Ogolne.KartyWTalii[Numery[i]][1] == 'T')
                {
                    if (k == 0)
                        cout << "|                    |";
                    if (k == 1)
                        cout << "|                    |";
                    if (k == 2)
                        cout << "|         /\\         |";
                    if (k == 3)
                        cout << "|        /  \\        |";
                    if (k == 4)
                        cout << "|       /    \\       |";
                    if (k == 5)
                        cout << "|  _____\\    /_____  |";
                    if (k == 6)
                        cout << "|  \\    \\\\  //    /  |";
                    if (k == 7)
                        cout << "|   \\____\\\\//____/   |";
                    if (k == 8)
                        cout << "|         /\\         |";
                    if (k == 9)
                        cout << "|        /__\\        |";
                    if (k == 10)
                        cout << "|                    |";
                    if (k == 11)
                        cout << "|                    |";
                }
                else if (Ogolne.KartyWTalii[Numery[i]][1] == 'P')
                {
                    if (k == 0)
                        cout << "|         /\\         |";
                    if (k == 1)
                        cout << "|        /  \\        |";
                    if (k == 2)
                        cout << "|       /    \\       |";
                    if (k == 3)
                        cout << "|      /      \\      |";
                    if (k == 4)
                        cout << "|     /        \\     |";
                    if (k == 5)
                        cout << "|    /          \\    |";
                    if (k == 6)
                        cout << "|   /            \\   |";
                    if (k == 7)
                        cout << "|  /              \\  |";
                    if (k == 8)
                        cout << "| |                | |";
                    if (k == 9)
                        cout << "|  \\    //  \\\\    /  |";
                    if (k == 10)
                        cout << "|   \\__//    \\\\__/   |";
                    if (k == 11)
                        cout << "|      /______\\      |";
                }
            }
            cout << endl;
        }
        for (int i = 0; i < IleKartNarysowac; i++) {
            if (Numery[i] != -1 && Ogolne.KartyWTalii[Numery[i]][0] != '1')
            cout << "|                   " << Ogolne.KartyWTalii[Numery[i]][0] << "|";
            else if (Numery[i] != -1 && Ogolne.KartyWTalii[Numery[i]][0] == '1')
                cout << "|                  " << Ogolne.KartyWTalii[Numery[i]][0] << "0|";
            else
                cout << "|                    |";
        }
        cout << endl;
        for (int i = 0; i < IleKartNarysowac; i++) {
            cout << "--------------------- ";          
        }
        cout << endl;
    }
};
Tury runda;
void Pokazanie() {
    cout <<endl<< "Zetony graczy:"<<endl;
    for (int i = 0; i < Wprowadzenie.LiczbaGraczy; i++) {
        cout << Indeks[i].ImieGracza << ":" << Indeks[i].Zetony << endl;
    }
    cout << "Zetony komputera:" << endl;
    for (int i = 0; i < Wprowadzenie.LiczbaKomputerow; i++) {
        cout << IndeksKomp[i].NazwaKomputera << ":" << IndeksKomp[i].Zetony << endl;
    }  
}
void Sprawdzenie() {
    string nagrody[10] = { "WYSOKA KARTA","PARA","DWIE PARY","TRÓJKA","STRIT","KOLOR","FULL","KARETA","POKER","POKER KRÓLEWSKI" };
    int wygrana[7];
    for (int p = 0; p < Wprowadzenie.LiczbaGraczy+Wprowadzenie.LiczbaKomputerow; p++) {
        if (Kolejka[p].PASS == false) {           
            if (p < Wprowadzenie.LiczbaGraczy) {
                wygrana[0] =  Ogolne.KartyNaStole[0];
                wygrana[1] = Ogolne.KartyNaStole[1];
                wygrana[2] = Ogolne.KartyNaStole[2];
                wygrana[3] = Ogolne.KartyNaStole[3];
                wygrana[4] = Ogolne.KartyNaStole[4];
                wygrana[5] = Indeks[p].karty[0];
                wygrana[6] =  Indeks[p].karty[1] ;
            }
            else {
                wygrana[0] = Ogolne.KartyNaStole[0];
                wygrana[1] = Ogolne.KartyNaStole[1];
                wygrana[2] = Ogolne.KartyNaStole[2];
                wygrana[3] = Ogolne.KartyNaStole[3];
                wygrana[4] = Ogolne.KartyNaStole[4];
                wygrana[5] = IndeksKomp[p].karty[0];
                wygrana[6] = IndeksKomp[p].karty[1];
            }
            sort(wygrana,wygrana+7);
            for (int i = 0; i < 7; i++) {
                for (int j = 0; j < 7; j++) {
                    for (int k = 0; k < 7; k++) {
                        for (int l = 0; l < 7; l++) {
                            for (int m = 0; m < 7; m++) {
                                if (j !=i && j!=k && j!=l && j!=m && i!=k && i!=l && i!=m && k!=l && k!=m && l!=m ) {
                                    //POKER KRÓLEWSKI
                                    if (Ogolne.KartyWTalii[wygrana[i]][0] == 'A' && Ogolne.KartyWTalii[wygrana[j]][0] == 'K' && Ogolne.KartyWTalii[wygrana[k]][0] == 'D' && Ogolne.KartyWTalii[wygrana[l]][0] == 'J' && Ogolne.KartyWTalii[wygrana[m]][0]=='1' && Kolejka[p].nagroda < 9) {
                                        if (Ogolne.KartyWTalii[wygrana[i]][1] == Ogolne.KartyWTalii[wygrana[j]][1] == Ogolne.KartyWTalii[wygrana[k]][1] == Ogolne.KartyWTalii[wygrana[l]][1] == Ogolne.KartyWTalii[wygrana[m]][1]) {
                                                Kolejka[p].nagroda = 9;                                        
                                        }
                                    }
                                    //POKER
                                    if (Ogolne.KartyWTalii[wygrana[i]][0] == Ogolne.KartyWTalii[wygrana[j] - 1][0] == Ogolne.KartyWTalii[wygrana[k] - 2][0] == Ogolne.KartyWTalii[wygrana[l] - 3][0] == Ogolne.KartyWTalii[wygrana[m] - 4][0] && Kolejka[p].nagroda <8) {
                                        if (Ogolne.KartyWTalii[wygrana[i]][1] == Ogolne.KartyWTalii[wygrana[j]][1] == Ogolne.KartyWTalii[wygrana[k]][1] == Ogolne.KartyWTalii[wygrana[l]][1] == Ogolne.KartyWTalii[wygrana[m]][1] ) {
                                            Kolejka[p].nagroda = 8;
                                        }
                                    }
                                    //KARETA
                                    else if (Ogolne.KartyWTalii[wygrana[m]][0] == Ogolne.KartyWTalii[wygrana[j]][0] == Ogolne.KartyWTalii[wygrana[k]][0] == Ogolne.KartyWTalii[wygrana[l]][0] && Kolejka[p].nagroda < 7) {
                                        Kolejka[p].nagroda = 7;

                                    }
                                    //FULL
                                    else if (Ogolne.KartyWTalii[wygrana[i]][0] == Ogolne.KartyWTalii[wygrana[j]][0] == Ogolne.KartyWTalii[wygrana[k]][0] && Ogolne.KartyWTalii[wygrana[l]][0] == Ogolne.KartyWTalii[wygrana[m]][0] && Kolejka[p].nagroda < 6) {
                                        Kolejka[p].nagroda = 6;
                                    }
                                    //KOLOR
                                    else if (Ogolne.KartyWTalii[wygrana[i]][1] == Ogolne.KartyWTalii[wygrana[j]][1] == Ogolne.KartyWTalii[wygrana[k]][1] == Ogolne.KartyWTalii[wygrana[l]][1] == Ogolne.KartyWTalii[wygrana[m]][1] && Kolejka[p].nagroda < 5) {
                                        Kolejka[p].nagroda = 5;
                                    }
                                    //STRIT
                                    else if (Ogolne.KartyWTalii[wygrana[i]][0] == Ogolne.KartyWTalii[wygrana[j] - 1][0] == Ogolne.KartyWTalii[wygrana[k] - 2][0] == Ogolne.KartyWTalii[wygrana[l] - 3][0] == Ogolne.KartyWTalii[wygrana[m] - 4][0] && Kolejka[p].nagroda < 4) {
                                        Kolejka[p].nagroda = 4;
                                    }
                                    //TRÓJKA
                                    else if (Ogolne.KartyWTalii[wygrana[i]][0] == Ogolne.KartyWTalii[wygrana[j]][0] == Ogolne.KartyWTalii[wygrana[k]][0] && Kolejka[p].nagroda < 3) {
                                        Kolejka[p].nagroda = 3;
                                    }
                                    //DWIE PARY
                                    else if (Ogolne.KartyWTalii[wygrana[i]][0] == Ogolne.KartyWTalii[wygrana[j]][0] && Ogolne.KartyWTalii[wygrana[k]][0] == Ogolne.KartyWTalii[wygrana[l]][0] && Kolejka[p].nagroda < 2) {
                                        Kolejka[p].nagroda = 2;
                                    }
                                    //PARA
                                    else if (Ogolne.KartyWTalii[wygrana[i]][0] == Ogolne.KartyWTalii[wygrana[j]][0] && Kolejka[p].nagroda < 1) {
                                        Kolejka[p].nagroda = 1;
                                    }
                                }
                            }
                        }
                    }
                }
            }                                
        }
    }
    int Podsumowanie = 0;
    int LiczbaWygranych = 0;   
    for (int i = 0; i < Wprowadzenie.LiczbaGraczy+Wprowadzenie.LiczbaKomputerow; i++) {       
        if (Kolejka[i].nagroda > Podsumowanie) {
            Podsumowanie = Kolejka[i].nagroda;
        }       
    }
    for (int i = 0; i < Wprowadzenie.LiczbaGraczy + Wprowadzenie.LiczbaKomputerow; i++) {
        if (Kolejka[i].nagroda == Podsumowanie) {
            LiczbaWygranych++;
        }
    }
    for (int i = 0; i < Wprowadzenie.LiczbaGraczy + Wprowadzenie.LiczbaKomputerow; i++) {
        if (Kolejka[i].nagroda == Podsumowanie && Kolejka[i].PASS==false) {
            if (i < Wprowadzenie.LiczbaGraczy) {
                Indeks[i].ZetonyPoczatek =Indeks[i].Zetony+sumaZetonow / LiczbaWygranych;
                cout << "Gracz " << Indeks[i].ImieGracza << " wygral " << (sumaZetonow / LiczbaWygranych) << " zetonow posiadajac " << nagrody[Kolejka[i].nagroda] << endl;
            }
            else if(Kolejka[i].PASS == false) {
                IndeksKomp[i-Wprowadzenie.LiczbaGraczy].ZetonyPoczatek = IndeksKomp[i].Zetony + sumaZetonow / LiczbaWygranych;
                cout << "Gracz " << IndeksKomp[i - Wprowadzenie.LiczbaGraczy].NazwaKomputera << " wygral " << (sumaZetonow / LiczbaWygranych) << " zetonow posiadajac " << nagrody[Kolejka[i].nagroda]<< endl;
            }
        }
    }   
}
int main() {
    srand((unsigned)time(0));
    char Karty[13] = {'2','3','4','5','6','7','8','9','1','J','D','K','A'};
    char Kolory[4] = { 'S','K','T','P' };//serce,karo,trefl,pik   
    while ((Wprowadzenie.LiczbaGraczy+Wprowadzenie.LiczbaKomputerow)<1 || (Wprowadzenie.LiczbaGraczy + Wprowadzenie.LiczbaKomputerow) >5) {
        system("cls");    
        cout << "\nIle graczy ma grac?(1-5)\n";
        cin >> Wprowadzenie.LiczbaGraczy;
        cout << "\nIle z nich ma byc komputerem?\n";
        cin >> Wprowadzenie.LiczbaKomputerow;
        Wprowadzenie.LiczbaGraczy -= Wprowadzenie.LiczbaKomputerow;
    }
    Ogolne.ZapelnijTalie(Karty, Kolory);        
    cout << "\nPodaj imiona graczy:\n";
    for (int i = 0; i < Wprowadzenie.LiczbaGraczy; i++)
    {       
        cin>>Indeks[i].ImieGracza;       
    }
    runda.WtasowanieKartGracza();
    for (int i = 0; i < Wprowadzenie.LiczbaKomputerow; i++)
    {
        IndeksKomp[i].NazwaKomputera = "Komputer" + to_string(i); 
    }
    runda.WtasowanieKartKomputera();
    runda.WtasowanieKartNaStol();
    system("cls");
    runda.Rozpoczecie();
    while(Runda<5){
        runda.Kolejka1();
    }
    Pokazanie();
    Sprawdzenie();
    char odpowiedz='T';
    while (odpowiedz == 'T') {
        cout << "Czy chcesz zagrac ponownie?[T/N]"<<endl;
        cin >> odpowiedz;
        if (odpowiedz == 'T') {
            Runda = 1;
            sumaZetonow = 0;
            Ogolne.PostawioneZetony = 100;
            KolejnaRunda = false;
            for (int i = 0; i < Wprowadzenie.LiczbaGraczy+Wprowadzenie.LiczbaKomputerow; i++)
            {
                Kolejka[i].PASS = false;
                Kolejka[i].wynik = false;
                Kolejka[i].Podbicie = false;
                Kolejka[i].PostawioneZetony = 0;
                Kolejka[i].nagroda = 0;
            }
            Ogolne.ZapelnijTalie(Karty, Kolory);
            runda.WtasowanieKartGracza();
            runda.WtasowanieKartKomputera();
            runda.WtasowanieKartNaStol();
            system("cls");
            runda.Rozpoczecie();
            while (Runda < 5) {
                runda.Kolejka1();
            }
            Pokazanie();
            Sprawdzenie();
        }
        else {
            system("cls");    
                cout << "KONIEC GRY" << endl;
        }
    }
    system("pause");
    system("cls");    
    return 0;
}
