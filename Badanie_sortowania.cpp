#include <iostream>
#include <cstdlib>
#include <chrono>
#include <fstream>

using namespace std;

const unsigned long long WielkoscTablicy = 20; // określanie rozmiaru tablicy
unsigned int zakres_losowania = 10000;     // zakres losowania
int Tablica_org[WielkoscTablicy];        // tworzenie tablicy o określonym rozmiarze
int Tablica[WielkoscTablicy];            // tworzenie tablicy o określonym rozmiarze
int temp_tab[WielkoscTablicy];

int LiczPor = 0, LiczSwap = 0;              //Licznik porównań oraz licznik zamian
unsigned short i = 0, n = 0;                // zmienne używane do iteracji
int ilerazy, theend = 1;
short memo;                             //zmienna zamiany miejsc
bool check;

void Losowanie_Tablicy()
{
    srand(time(0)); // seed dla funkcji rand()
    unsigned int random;
    for (i = 0; i < WielkoscTablicy; i++)
    {
        random = rand() % zakres_losowania; // losowanie liczby w zakresie modulo
        Tablica_org[i] = random;            // wpisywanie wylosowanych wartości do tablicy
        Tablica[i] = random;
    }
}

void Losowanie_Tablicy_Posortowanej()
{
    for (i = 0; i < WielkoscTablicy; i++)
    {
        Tablica_org[i] = i;
        Tablica[i] = i;
    }
}

void Losowanie_Tablicy_Odwrotnie_Posortowanej()
{
    for (i = 0; i < WielkoscTablicy; i++)
    {
        Tablica_org[i] = WielkoscTablicy-i;
        Tablica[i] = WielkoscTablicy-i;
    }
}
void Przywracanie_Tablicy()
{
    for (i = 0; i < WielkoscTablicy; i++)
    {
        Tablica[i] = Tablica_org[i];
    }
}

void Sortowanie_Przez_Wybor(int tab[]) // sortowanie przez wybór
{
    LiczPor = 0;
    LiczSwap = 0;
    short min, max, temp;
    for (i = 0; i < WielkoscTablicy - 1; i++)
    {
        min = i;
        for (n = i + 1; n < WielkoscTablicy; n++) // sortowanie po minimum
        {
            LiczPor++;
            if (tab[min] > tab[n])
            {
                min = n;
            }
        }
        LiczSwap++;
        temp = tab[i]; // zamiana miejsc min
        tab[i] = tab[min];
        tab[min] = temp;

        max = WielkoscTablicy - 1 - i;
        for (n = WielkoscTablicy - 1 - i; n > 0; n--) // sortowanie po maximum
        {
            LiczPor++;
            if (tab[max] < tab[n])
            {
                max = n;
            }
        }
        LiczSwap++;
        temp = tab[WielkoscTablicy - 1 - i]; // zamiana miejsc max
        tab[WielkoscTablicy - 1 - i] = tab[max];
        tab[max] = temp;
    }
}
void Sortowanie_Przez_Wstawianie(int tab[]) // sortowanie przez wstaiwanie
{
    LiczPor = 1;
    LiczSwap = 0;
    for (i = 1; i < WielkoscTablicy; i++)
    {
        while (i > 0 && tab[i - 1] > tab[i])
        {
            LiczPor++;
            LiczSwap++;
            memo = tab[i - 1];
            tab[i - 1] = tab[i];
            tab[i] = memo;
            i--;
        }
    }
}

void Sortowanie_Przez_Wstawianie_binsearch(int tab[]) // binary insertion sort
{
    LiczPor = 1;
    LiczSwap = 0;
    for(i = 1; i <= WielkoscTablicy; i++)
    {
        int left = 0;
        int right = i-1;
        
        int middle = (right+left)/2;
        while(left != middle || right!=middle)
        {
            LiczPor+=2;
            if(tab[i-1] <= tab[middle])
            {
                right = middle;
                middle = (right+left)/2;                
            }
            else
            {
                left = middle + 1;
                middle = (right + left) / 2;
            }

        }
        
        memo = tab[i-1];
        for(n = i-1; n > middle; n--)
        {
            LiczSwap++;
            tab[n]= tab[n-1];
        }
        tab[middle]=memo;
        LiczSwap+=2;

    }
}

void Sortowanie_Babelkowe(int tab[]) // sortowanie bąbelkowe
{
    LiczPor = 0;
    LiczSwap = 0;
    int min = 0;
    int max = WielkoscTablicy - 1;
    int zmiana;
    do
    {
        zmiana = -1;
        for (i = min; i < max; i++)
        {
            LiczPor++;
            if (tab[i] > tab[i + 1])
            {   
                LiczSwap++;
                memo = tab[i];
                tab[i] = tab[i + 1];
                tab[i + 1] = memo;
                if (zmiana < 0)
                {
                    min = i; // indeks pierwszej zmiany jako nowy początek pętli
                }
                zmiana = i; // indeks zmiany jako wartość logiczna
            }
        }

        if (min)
            min--;
        max = zmiana;
    } while (zmiana >= 0);
}

void merge(int tab[], int poczatek, int srodek, int koniec)
{
    for (i = poczatek; i <= koniec; i++)
    {
        temp_tab[i] = tab[i];
    }
    int k = poczatek;
    i = poczatek;
    n = srodek + 1;
    while (i <= srodek && n <= koniec)
    {
        LiczPor+=2;
        if (temp_tab[i] <= temp_tab[n])
        {
            tab[k] = temp_tab[i++];
            k++;
        }
        else
        {
            tab[k] = temp_tab[n++];
            k++;
        }
        LiczSwap++;
    }

    while (i <= srodek)
    {
        tab[k] = temp_tab[i++];
        k++;
        LiczSwap++;
    }

    while (n <= koniec)
    {
        tab[k] = temp_tab[n++];
        k++;
        LiczSwap++;
    }
}

void Sortowanie_Przez_Scalanie(int tab[], int poczatek, int koniec) //sortowanie przez scalanie
{

    if (poczatek >= koniec)
        return;

    int srodek = (poczatek + koniec) / 2;

    Sortowanie_Przez_Scalanie(tab, poczatek, srodek);
    Sortowanie_Przez_Scalanie(tab, srodek + 1, koniec);

    merge(tab, poczatek, srodek, koniec);
}

int Split(int tab[], int poczatek, int koniec)
{
    int splitpoint = (poczatek+koniec)/2;
    int n = tab[splitpoint];
    int memo = 0;
    int i = 0;
    LiczPor++;
    if (splitpoint != koniec)
    {
        LiczSwap++;
        memo = tab[splitpoint];
        tab[splitpoint] = tab[koniec];
        tab[koniec] = memo;
    }

    int k = poczatek;

    for(i = k; i <= koniec; i++)
    {
        LiczPor++;
        if(tab[i] < n)
        {
            LiczSwap++;
            memo = tab[i];
            tab[i] = tab[k];
            tab[k] = memo;
            k++;
        }
    }
    memo = tab[k];
    tab[k] = tab[koniec];
    tab[koniec] = memo;
    LiczSwap++;

    return k;

}

void Sortowanie_Szybkie(int tab[], int poczatek, int koniec)    //QuickSort
{
    if(poczatek >= koniec)
    {
        return;
    }

    int srodek = Split(tab, poczatek, koniec);
    Sortowanie_Szybkie(tab, poczatek, srodek);
    Sortowanie_Szybkie(tab, srodek + 1, koniec);
}


bool Sprawdz_Sortowanie(int tab[]) // sprawdzanie sortowania
{
    check = true;

    for (i = 0; i < WielkoscTablicy - 1; i++)
    {
        if (tab[i] > tab[i + 1])
        {
            check = false;
        }
    }

    return check;
}

void Wypisz_Tablice(int tab[]) // wypisywanie całej tablicy
{
    for (i = 0; i < WielkoscTablicy; i++)

    {
        cout << tab[i] << " ";
    }

    cout << endl;
}

int main()
{
    ofstream wyniki, liczniki;
    string Nazwy_wynikow[6] = {"Przez_Wybor", "Przez_Wstawianie", "Przez_Wstawianie_Binarne", "Babelkowe", "Przez_Scalanie", "QuickSort"};

    //cout << "Wpisz zakres losowania %";
    // cin>>zakres_losowania;
    wyniki.open("AiZO.txt", ios::app);
    liczniki.open("AiZO-liczniki.txt", ios::app);

    while (theend != 0)
    {
        cout<<"Algorytmy sortujące"<<endl;
        cout<<"Wykorzystane algorytmy:"<<endl;
        cout<<"1.Przez wybór"<<endl;
        cout<<"2.Przez wstawianie"<<endl;
        cout<<"3.Przez wstawianie (binarnie)"<<endl;
        cout<<"4.Sortowanie Bąbelkowe"<<endl;
        cout<<"5.Sortownaie przez Scalanie"<<endl;
        cout<<"6.QuickSort"<<endl;

        cout << "Ile razy? \n"; // *Pętla ile razy*
        cin >> ilerazy;
        cout << endl;

        cout << "Sortowanie: \n";
        
        if (wyniki.is_open() && liczniki.is_open())
        {
            wyniki << "Przez wybór;Przez Wstawianie;Przez Wstawianie Binarne;Bąbelkowe;PrzezScalanie;QuickSort" << endl;
            liczniki << "Wybór;;Wstawianie;;WstawianieBinarne;;Bąbelkowe;;Merge;;QuickSort"<<endl;
            liczniki << "LiczPor;LiczSwap;LiczPor;LiczSwap;LiczPor;LiczSwap;LiczPor;LiczSwap;LiczPor;LiczSwap;LiczPor;LiczSwap;"<<endl;
        }
        for (ilerazy; ilerazy > 0; ilerazy--)
        {
            //Losowanie_Tablicy();                                //random
            //Losowanie_Tablicy_Posortowanej();                   //posortowana
            Losowanie_Tablicy_Odwrotnie_Posortowanej();         //odwrotnie posortowana


            cout<< "Wykonanie "<<endl;

                // cout<<"Przed sort "<<endl;
                // Wypisz_Tablice(Tablica);
                //cout<<endl<<Nazwy_wynikow[0]<<endl;

                chrono::time_point<std::chrono::high_resolution_clock> start, end;              //zmienne mierzonego czasu
                start = chrono::high_resolution_clock::now();
                    Sortowanie_Przez_Wybor(Tablica);
                end = chrono::high_resolution_clock::now();
                chrono::duration<long double> t0{end - start};                                  //t0, t1,..t6 - zmienne przechowujące czas wykonywania sortowania
                cout << "Wynik sprawdzania (1 - poprawne; 0 - niepoprawne) == " << Sprawdz_Sortowanie(Tablica) << endl;
                //cout << t0.count() << "s\n";
                if (wyniki.is_open() && liczniki.is_open())   
                {
                    //cout << "Udało się otworzyć plik" << endl;
                    wyniki << t0.count() << ";";
                    liczniki << LiczPor << ";" << LiczSwap << ";";

                }
                else
                {
                    cout << "Nie udało się otworzyć pliku" << endl;
                }
                Przywracanie_Tablicy();

                //cout<<endl<<Nazwy_wynikow[1]<<endl;
                start = chrono::high_resolution_clock::now();
                    Sortowanie_Przez_Wstawianie(Tablica);
                end = chrono::high_resolution_clock::now();
                chrono::duration<long double> t1{end - start};
                cout << "Wynik sprawdzania (1 - poprawne; 0 - niepoprawne) == " << Sprawdz_Sortowanie(Tablica) << endl;
                //cout << t1.count() << "s\n";
                if (wyniki.is_open() && liczniki.is_open())   
                {
                    //cout << "Udało się otworzyć plik" << endl;
                    wyniki << t1.count() << ";";
                    liczniki << LiczPor << ";" << LiczSwap << ";";
                }
                else
                {
                    cout << "Nie udało się otworzyć pliku" << endl;
                }
                Przywracanie_Tablicy();

                //cout<<endl<<Nazwy_wynikow[2]<<endl;
                start = chrono::high_resolution_clock::now();
                    Sortowanie_Przez_Wstawianie_binsearch(Tablica);
                end = chrono::high_resolution_clock::now();
                chrono::duration<long double> t2{end - start};
                cout << "Wynik sprawdzania (1 - poprawne; 0 - niepoprawne) == " << Sprawdz_Sortowanie(Tablica) << endl;
                //cout << t2.count() << "s\n";
                if (wyniki.is_open() && liczniki.is_open())   
                {
                    //cout << "Udało się otworzyć plik" << endl;
                    wyniki << t2.count() << ";";
                    liczniki << LiczPor << ";" << LiczSwap << ";";
                }
                else
                {
                    cout << "Nie udało się otworzyć pliku" << endl;
                }
                Przywracanie_Tablicy();

                //cout<<endl<<Nazwy_wynikow[3]<<endl;
                start = chrono::high_resolution_clock::now();
                    Sortowanie_Babelkowe(Tablica);
                end = chrono::high_resolution_clock::now();
                chrono::duration<long double> t3{end - start};
                cout << "Wynik sprawdzania (1 - poprawne; 0 - niepoprawne) == " << Sprawdz_Sortowanie(Tablica) << endl;
                //cout << t3.count() << "s\n";
                if (wyniki.is_open() && liczniki.is_open())   
                {
                    //cout << "Udało się otworzyć plik" << endl;
                    wyniki << t3.count() << ";";
                    liczniki << LiczPor << ";" << LiczSwap << ";";
                }
                else
                {
                    cout << "Nie udało się otworzyć pliku" << endl;
                }
                Przywracanie_Tablicy();

                //cout<<endl<<Nazwy_wynikow[4]<<endl;
                LiczPor = 0;
                LiczSwap = 0;
                start = chrono::high_resolution_clock::now();
                    Sortowanie_Przez_Scalanie(Tablica, 0, WielkoscTablicy - 1);
                end = chrono::high_resolution_clock::now();
                chrono::duration<long double> t4{end - start};
                cout << "Wynik sprawdzania (1 - poprawne; 0 - niepoprawne) == " << Sprawdz_Sortowanie(Tablica) << endl;
                //cout << t4.count() << "s\n";
                if (wyniki.is_open() && liczniki.is_open())   
                {
                    //cout << "Udało się otworzyć plik" << endl;
                    wyniki << t4.count() << ";";
                    liczniki << LiczPor << ";" << LiczSwap << ";";
                }
                else
                {
                    cout << "Nie udało się otworzyć pliku" << endl;
                }
                Przywracanie_Tablicy();

                //cout<<endl<<Nazwy_wynikow[5]<<endl;
                LiczPor = 0;
                LiczSwap = 0;
                start = chrono::high_resolution_clock::now();
                    Sortowanie_Szybkie(Tablica, 0, WielkoscTablicy - 1);
                end = chrono::high_resolution_clock::now();
                chrono::duration<long double> t5{end - start};
                cout << "Wynik sprawdzania (1 - poprawne; 0 - niepoprawne) == " << Sprawdz_Sortowanie(Tablica) << endl;
                //cout << t5.count() << "s\n";
                if (wyniki.is_open() && liczniki.is_open())   
                {
                    //cout << "Udało się otworzyć plik" << endl;
                    wyniki << t5.count() << ";";
                    liczniki << LiczPor << ";" << LiczSwap << ";";
                }
                else
                {
                    cout << "Nie udało się otworzyć pliku" << endl;
                }
                Przywracanie_Tablicy();

                //  cout<<"Po sort "<<endl;
                //  Wypisz_Tablice(Tablica);

                wyniki<<endl;
                liczniki<<endl;
        }

        cout << "Czy zakończyć?\n";
        cout << "0 - aby zakończyć | 1 - aby kontynuwać\n";
        cin >> theend;
        cout << "No to jeszcze raz"<<endl;
    }

    wyniki << WielkoscTablicy <<" elementów tablicy"<< endl;
    liczniki << WielkoscTablicy <<" elementów tablicy"<<endl;
    wyniki.close();
    liczniki.close();

    
    return 0;
}