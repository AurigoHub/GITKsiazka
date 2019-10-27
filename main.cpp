#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

struct DaneUzytkownika
{
    int idUzytkownika;
    string nazwa, haslo;
};

struct DaneAdresata
{
    int idAdresata;
    string imie, nazwisko, adres, telefon, email;
};

void wczytajSegmentZLiniiTekstuSpisuUzytkownikow (vector <DaneUzytkownika> &uzytkownicy, int liczbaUzytkownikow, string segmentDanychUzytkownika, int numerSegmentuWLiniiTekstu)
{
    switch (numerSegmentuWLiniiTekstu)
    {
    case 1:
        uzytkownicy[liczbaUzytkownikow].idUzytkownika = atoi(segmentDanychUzytkownika.c_str());
        break;
    case 2:
        uzytkownicy[liczbaUzytkownikow].nazwa = segmentDanychUzytkownika;
        break;
    case 3:
        uzytkownicy[liczbaUzytkownikow].haslo = segmentDanychUzytkownika;
        break;
    }
}

int wczytajUzytkownikowZPliku (vector <DaneUzytkownika> &uzytkownicy, int liczbaUzytkownikow)
{
    fstream spisUzytkownikow;
    string liniaTekstuSpisuUzytkownikow;

    spisUzytkownikow.open ("Uzytkownicy.txt", ios::in);
    if (spisUzytkownikow.good() == true)
    {
        while (getline(spisUzytkownikow,liniaTekstuSpisuUzytkownikow))
        {
            uzytkownicy.push_back(DaneUzytkownika());
            stringstream ss (liniaTekstuSpisuUzytkownikow);
            string segmentDanychUzytkownika;
            int numerSegmentuWLiniiTekstu = 1;

            while (getline(ss, segmentDanychUzytkownika, '|'))
            {
                wczytajSegmentZLiniiTekstuSpisuUzytkownikow (uzytkownicy, liczbaUzytkownikow, segmentDanychUzytkownika, numerSegmentuWLiniiTekstu);
                numerSegmentuWLiniiTekstu ++;
            }
            liczbaUzytkownikow ++;
        }
    }
    spisUzytkownikow.close();

    return liczbaUzytkownikow;
}

void wczytajSegmentZLiniiTekstuSpisuAdresatow (vector <DaneAdresata> &adresaci, int liczbaAdresatow, string segmentDanychAdresata, int numerSegmentuWLiniiTekstu)
{
    switch (numerSegmentuWLiniiTekstu)
    {
    case 1:
        adresaci[liczbaAdresatow].idAdresata = atoi(segmentDanychAdresata.c_str());
        break;
    case 2:
        adresaci[liczbaAdresatow].imie = segmentDanychAdresata;
        break;
    case 3:
        adresaci[liczbaAdresatow].nazwisko = segmentDanychAdresata;
        break;
    case 4:
        adresaci[liczbaAdresatow].adres = segmentDanychAdresata;
        break;
    case 5:
        adresaci[liczbaAdresatow].telefon = segmentDanychAdresata;
        break;
    case 6:
        adresaci[liczbaAdresatow].email = segmentDanychAdresata;
        break;
    }
}

int wczytajAdresatowZPliku (vector <DaneAdresata> &adresaci, int liczbaAdresatow)
{
    fstream ksiazkaAdresowa;
    string liniaTekstuSpisuAdresatow;

    ksiazkaAdresowa.open ("Adresaci.txt", ios::in);
    if (ksiazkaAdresowa.good() == true)
    {
        while (getline(ksiazkaAdresowa,liniaTekstuSpisuAdresatow))
        {
            adresaci.push_back(DaneAdresata());
            stringstream ss (liniaTekstuSpisuAdresatow);
            string segmentDanychAdresata;
            int numerSegmentuWLiniiTekstu = 1;

            while (getline(ss, segmentDanychAdresata, '|'))
            {
                wczytajSegmentZLiniiTekstuSpisuAdresatow (adresaci, liczbaAdresatow, segmentDanychAdresata, numerSegmentuWLiniiTekstu);
                numerSegmentuWLiniiTekstu ++;
            }
            liczbaAdresatow ++;
        }
    }
    ksiazkaAdresowa.close();

    return liczbaAdresatow;
}

void wyczyscPlikTekstowyZUzytkownikami ()
{
    fstream spisUzytkownikow;
    spisUzytkownikow.open("Uzytkownicy.txt", ios::out|ios::trunc);
    spisUzytkownikow.close();
}

void wyczyscPlikTekstowyZAdresatami ()
{
    fstream ksiazkaAdresowa;
    ksiazkaAdresowa.open("Adresaci.txt", ios::out|ios::trunc);
    ksiazkaAdresowa.close();
}

void zapiszUzytkownikowWPliku (vector <DaneUzytkownika> &uzytkownicy, int liczbaUzytkownikow)
{
    fstream spisUzytkownikow;

    spisUzytkownikow.open("Uzytkownicy.txt", ios::out|ios::app);
    if (spisUzytkownikow.good() == true)
    {
        for (int i=0; i<liczbaUzytkownikow; i++)
        {
            spisUzytkownikow << uzytkownicy[i].idUzytkownika << '|';
            spisUzytkownikow << uzytkownicy[i].nazwa << '|';
            spisUzytkownikow << uzytkownicy[i].haslo << endl;
        }
        spisUzytkownikow.close();
    }
    else
    {
        cout << "Nie udało się otworzyć pliku i zapisać danych!" << endl;
        system("pause");
    }
}

void zapiszAdresatowWPliku (vector <DaneAdresata> &adresaci, int liczbaAdresatow)
{
    fstream ksiazkaAdresowa;

    ksiazkaAdresowa.open("Adresaci.txt", ios::out|ios::app);
    if (ksiazkaAdresowa.good() == true)
    {
        for (int i=0; i<liczbaAdresatow; i++)
        {
            ksiazkaAdresowa << adresaci[i].idAdresata << '|';
            ksiazkaAdresowa << adresaci[i].imie << '|';
            ksiazkaAdresowa << adresaci[i].nazwisko << '|';
            ksiazkaAdresowa << adresaci[i].adres << '|';
            ksiazkaAdresowa << adresaci[i].telefon << '|';
            ksiazkaAdresowa << adresaci[i].email << endl;
        }
        ksiazkaAdresowa.close();
    }
    else
    {
        cout << "Nie udało się otworzyć pliku i zapisać danych!" << endl;
        system("pause");
    }
}

int wyznaczIndeksNowegoAdresata (vector <DaneAdresata> &adresaci)
{
    int dlugoscWektoraWpisow = adresaci.size();
    adresaci.push_back(DaneAdresata());
    return dlugoscWektoraWpisow;
}

int wyznaczIDNowegoAdresata (vector <DaneAdresata> &adresaci, int liczbaAdresatow)
{
    const int IDPierwszegoWpisu = 1;
    const int inkrementacjaID = 1;

    if (liczbaAdresatow == 0)
        return IDPierwszegoWpisu;
    else
        return (adresaci[liczbaAdresatow-1].idAdresata + inkrementacjaID);
}

int dodajAdresataDoKsiazki (vector <DaneAdresata> &adresaci, int liczbaAdresatow)
{
    string imie, nazwisko, adres, telefon, email;
    int indeksNowegoAdresata = 0;
    int IDNowegoAdresata;

    cout << "Wpisz imię adresata: ";
    cin.sync();
    getline(cin,imie);
    cout << "Wpisz nazwisko adresata: ";
    cin.sync();
    getline (cin,nazwisko);
    cout << "Wpisz adres adresata (w jednej linii tekstu): ";
    cin.sync();
    getline(cin,adres);
    cout << "Wpisz numer telefonu adresata: ";
    cin.sync();
    getline(cin,telefon);
    cout << "Wpisz adres e-mail adresata: ";
    cin >> email;

    indeksNowegoAdresata = wyznaczIndeksNowegoAdresata(adresaci);
    IDNowegoAdresata = wyznaczIDNowegoAdresata (adresaci, liczbaAdresatow);

    adresaci[indeksNowegoAdresata].imie = imie;
    adresaci[indeksNowegoAdresata].nazwisko = nazwisko;
    adresaci[indeksNowegoAdresata].adres = adres;
    adresaci[indeksNowegoAdresata].telefon = telefon;
    adresaci[indeksNowegoAdresata].email = email;
    adresaci[indeksNowegoAdresata].idAdresata = IDNowegoAdresata;
    liczbaAdresatow++;

    wyczyscPlikTekstowyZAdresatami ();
    zapiszAdresatowWPliku (adresaci, liczbaAdresatow);
    cout << endl << "Zapisano" << endl;
    Sleep(1000);

    return liczbaAdresatow;
}

void wyswietlDaneAdresata (vector <DaneAdresata> &adresaci, int i)
{
    cout << "NUMER ID WPISU: " << adresaci[i].idAdresata << endl;
    cout << "IMIĘ: " << adresaci[i].imie << endl;
    cout << "NAZWISKO: " << adresaci[i].nazwisko << endl;
    cout << "ADRES: " << adresaci[i].adres << endl;
    cout << "TELEFON: " << adresaci[i].telefon << endl;
    cout << "E-MAIL: " << adresaci[i].email << endl << endl;
}

void wyswietlWszystkichAdresatow (vector <DaneAdresata> &adresaci, int liczbaAdresatow)
{
    if (liczbaAdresatow == 0)
    {
        cout << "Książka adresowa jest pusta." << endl << endl;
        system("pause");
    }
    else
    {
        cout << "Liczba adresatów zapisanych w książce adresowej: " << liczbaAdresatow << endl << endl;

        for (int i=0; i<liczbaAdresatow; i++)
        {
            wyswietlDaneAdresata (adresaci, i);
        }
        system("pause");
    }
}

int wyszukajID (vector <DaneAdresata> &adresaci, int liczbaAdresatow, int IDAdresata)
{
    const int NIE_ZNALEZIONO_WYNIKOW = -1;
    int indeksWyszukanegoAdresata;
    int liczbaWynikow = 0;

    for (int i=0; i<liczbaAdresatow; i++)
    {
        if (IDAdresata == adresaci[i].idAdresata)
        {
            indeksWyszukanegoAdresata = i;
            liczbaWynikow ++;
        }
    }

    if (liczbaWynikow == 0)
    {
        cout << endl << "Nie znaleziono żadnych adresatów." << endl << endl;
        system("pause");
        return NIE_ZNALEZIONO_WYNIKOW;
    }
    else
        return indeksWyszukanegoAdresata;
}

void wyszukajImie (vector <DaneAdresata> &adresaci, int liczbaAdresatow)
{
    string szukaneImie;
    int liczbaWynikow = 0;

    cout << "Wpisz imię do wyszukania: ";
    cin.sync();
    getline(cin,szukaneImie);

    for (int i=0; i<liczbaAdresatow; i++)
    {
        if (szukaneImie == adresaci[i].imie)
            liczbaWynikow ++;
    }

    if (liczbaWynikow == 0)
        cout << endl << "Nie znaleziono żadnych adresatów." << endl << endl;

    else
    {
        cout << endl << "Znaleziono " << liczbaWynikow << " adresatów w książce:" << endl << endl;
        for (int i=0; i<liczbaAdresatow; i++)
        {
            if (szukaneImie == adresaci[i].imie)
                wyswietlDaneAdresata (adresaci, i);
        }
    }
    system("pause");
}

void wyszukajNazwisko (vector <DaneAdresata> &adresaci, int liczbaAdresatow)
{
    string szukaneNazwisko;
    int liczbaWynikow = 0;

    cout << "Wpisz nazwisko do wyszukania: ";
    cin.sync();
    getline(cin,szukaneNazwisko);

    for (int i=0; i<liczbaAdresatow; i++)
    {
        if (szukaneNazwisko == adresaci[i].nazwisko)
            liczbaWynikow ++;
    }

    if (liczbaWynikow == 0)
        cout << endl << "Nie znaleziono żadnych adresatów." << endl << endl;

    else
    {
        cout << endl << "Znaleziono " << liczbaWynikow << " adresatów w książce:" << endl << endl;
        for (int i=0; i<liczbaAdresatow; i++)
        {
            if (szukaneNazwisko == adresaci[i].nazwisko)
                wyswietlDaneAdresata (adresaci, i);
        }
    }
    system("pause");
}

void wyswietlMenuEdycji (vector <DaneAdresata> &adresaci, int indeksWyszukanegoAdresata)
{
    system("cls");

    cout << "Aktualne dane wybranego adresata: " << endl << endl;
    wyswietlDaneAdresata (adresaci, indeksWyszukanegoAdresata);

    cout << "Wybierz pole do edycji: " << endl;
    cout << "1. IMIĘ" << endl;
    cout << "2. NAZWISKO" << endl;
    cout << "3. ADRES" << endl;
    cout << "4. TELEFON" << endl;
    cout << "5. E-MAIL" << endl;
    cout << "6. Cofnij do menu głównego" << endl << endl;
}

void edytujWybranePole (vector <DaneAdresata> &adresaci, int indeksWyszukanegoAdresata, char wybranyZnakWMenuEdycji, int liczbaAdresatow)
{
    string nowaWartoscPola;

    cin.clear();
    cin.sync();

    if (wybranyZnakWMenuEdycji == '1')
    {
        cout << "Wpisz nowe imię adresata: ";
        getline(cin,nowaWartoscPola);
        adresaci[indeksWyszukanegoAdresata].imie = nowaWartoscPola;
    }
    else if (wybranyZnakWMenuEdycji == '2')
    {
        cout << "Wpisz nowe nazwisko adresata: ";
        getline(cin,nowaWartoscPola);
        adresaci[indeksWyszukanegoAdresata].nazwisko = nowaWartoscPola;
    }
    else if (wybranyZnakWMenuEdycji == '3')
    {
        cout << "Wpisz nowy adres adresata: ";
        getline(cin,nowaWartoscPola);
        adresaci[indeksWyszukanegoAdresata].adres = nowaWartoscPola;
    }
    else if (wybranyZnakWMenuEdycji == '4')
    {
        cout << "Wpisz nowy telefon adresata: ";
        getline(cin,nowaWartoscPola);
        adresaci[indeksWyszukanegoAdresata].telefon = nowaWartoscPola;
    }
    else if (wybranyZnakWMenuEdycji == '5')
    {
        cout << "Wpisz nowy e-mail adresata: ";
        getline(cin,nowaWartoscPola);
        adresaci[indeksWyszukanegoAdresata].email = nowaWartoscPola;
    }
    wyczyscPlikTekstowyZAdresatami ();
    zapiszAdresatowWPliku (adresaci, liczbaAdresatow);
    cout << endl << "Zapisano" << endl;
    Sleep(1000);
}

int edytujWybranegoAdresata (vector <DaneAdresata> &adresaci, int liczbaAdresatow, int indeksWyszukanegoAdresata)
{
    char wybranyZnakWMenuEdycji;

    do
    {
        wyswietlMenuEdycji (adresaci, indeksWyszukanegoAdresata);
        cin.clear();
        cin.sync();
        wybranyZnakWMenuEdycji = getch();

        switch (wybranyZnakWMenuEdycji)
        {
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
            edytujWybranePole (adresaci, indeksWyszukanegoAdresata, wybranyZnakWMenuEdycji, liczbaAdresatow);
            break;
        case '6':
            return liczbaAdresatow;
        default:
            cout << "Nie ma takiej opcji w menu!";
            Sleep(1500);
        }
    }
    while (wybranyZnakWMenuEdycji != '6');
}

int usunWybranegoAdresata (vector <DaneAdresata> &adresaci, int liczbaAdresatow, int indeksWyszukanegoAdresata)
{
    int IDAdresataDoUsuniecia = adresaci[indeksWyszukanegoAdresata].idAdresata;

    for (vector <DaneAdresata>::iterator it = adresaci.begin(); it != adresaci.end(); it++)
    {
        if (it->idAdresata == IDAdresataDoUsuniecia)
        {
            it = adresaci.erase(it);
            liczbaAdresatow--;
            break;
        }
    }
    return liczbaAdresatow;
}

int potwierdzUsuniecieAdresata (vector <DaneAdresata> &adresaci, int liczbaAdresatow, int indeksWyszukanegoAdresata)
{
    char wybranyZnakWMenuUsuwania;

    do
    {
        system("cls");
        cout << "Aktualne dane wybranego adresata: " << endl << endl;
        wyswietlDaneAdresata (adresaci, indeksWyszukanegoAdresata);
        cout << "Usunąć wybranego adresata z książki?" << endl << endl;
        cout << "Wybierz TAK (t) lub NIE (n): ";

        cin.clear();
        cin.sync();
        wybranyZnakWMenuUsuwania = getch();

        switch (wybranyZnakWMenuUsuwania)
        {
        case 't':
        case 'T':
            liczbaAdresatow = usunWybranegoAdresata (adresaci, liczbaAdresatow, indeksWyszukanegoAdresata);
            wyczyscPlikTekstowyZAdresatami ();
            zapiszAdresatowWPliku (adresaci, liczbaAdresatow);
            cout << endl << endl << "Adresat usunięty!" << endl;
            Sleep(1500);
            return liczbaAdresatow;
        case 'n':
        case 'N':
            return liczbaAdresatow;
        default:
            cout << endl << endl << "Nie ma takiej opcji!" << endl;
            cout << "Wybierz TAK (t) lub NIE (n)." << endl;
            Sleep(2000);
        }
    }
    while (wybranyZnakWMenuUsuwania != ('n' | 'N'));
}

int modyfikujDaneAdresata (vector <DaneAdresata> &adresaci, int liczbaAdresatow, char wybranyZnak)
{
    int IDAdresata, indeksWyszukanegoAdresata;

    if (wybranyZnak == '5')
        cout << "Wpisz ID adresata do usunięcia: ";
    else if (wybranyZnak == '6')
        cout << "Wpisz ID adresata do edycji: ";

    cin >> IDAdresata;

    indeksWyszukanegoAdresata = wyszukajID (adresaci, liczbaAdresatow, IDAdresata);

    if (indeksWyszukanegoAdresata >= 0)
    {
        if (wybranyZnak == '5')
            liczbaAdresatow = potwierdzUsuniecieAdresata (adresaci, liczbaAdresatow, indeksWyszukanegoAdresata);
        else if (wybranyZnak == '6')
            liczbaAdresatow = edytujWybranegoAdresata (adresaci, liczbaAdresatow, indeksWyszukanegoAdresata);
    }
    return liczbaAdresatow;
}

void wyswietlMenuStartowe ()
{
    system("cls");
    cout << "**********************************" << endl;
    cout << "*        KSIĄŻKA ADRESOWA        *" << endl;
    cout << "**********************************" << endl << endl;
    cout << "1. Logowanie" << endl;
    cout << "2. Rejestracja" << endl;
    cout << "3. Zakończ program" << endl;
    cout << endl;
}

void wyswietlMenuZAdresatami ()
{
    system("cls");
    cout << "**********************************" << endl;
    cout << "*        KSIĄŻKA ADRESOWA        *" << endl;
    cout << "**********************************" << endl << endl;
    cout << "1. Dodaj nowego adresata" << endl;
    cout << "2. Wyszukaj adresata po imieniu" << endl;
    cout << "3. Wyszukaj adresata po nazwisku" << endl;
    cout << "4. Lista zapisanych adresatów" << endl;
    cout << "5. Usuń adresata" << endl;
    cout << "6. Edytuj dane adresata" << endl;
    cout << "7. Zmień hasło" << endl;
    cout << "8. Zakończ program" << endl;
    cout << endl;
}

int zalogujUzytkownika (vector <DaneUzytkownika> &uzytkownicy, int liczbaUzytkownikow)
{
    string wpisanaNazwa, wpisaneHaslo;
    int idUzytkownika;









    return idUzytkownika;
}

int zarejestrujUzytkownika (vector <DaneUzytkownika> &uzytkownicy, int liczbaUzytkownikow)
{
    string nazwa, haslo;

    system("cls");
    cout << "**********************************" << endl;
    cout << "*        KSIĄŻKA ADRESOWA        *" << endl;
    cout << "**********************************" << endl << endl;
    cout << "Wpisz nazwę użytkownika: ";
    cin.sync();
    getline(cin,nazwa);

    int i = 0;
    while (i<liczbaUzytkownikow)
    {
        if (uzytkownicy[i].nazwa == nazwa)
        {
            cout << "Taki użytkownik już istnieje. Wpisz inną nazwę użytkownika: ";
            cin.sync();
            getline(cin,nazwa);
            i = 0;
        }
        else
            i++;
    }

    cout << "Wpisz hasło: ";
    cin.sync();
    getline (cin,haslo);

    uzytkownicy.push_back(DaneUzytkownika());
    uzytkownicy[liczbaUzytkownikow].nazwa = nazwa;
    uzytkownicy[liczbaUzytkownikow].haslo = haslo;
    uzytkownicy[liczbaUzytkownikow].idUzytkownika = liczbaUzytkownikow + 1;
    liczbaUzytkownikow++;

    wyczyscPlikTekstowyZUzytkownikami ();
    zapiszUzytkownikowWPliku (uzytkownicy, liczbaUzytkownikow);
    cout << endl << "Konto utworzone" << endl;
    Sleep(1000);

    return liczbaUzytkownikow;
}

int uruchomObslugeUzytkownikow ()
{
    vector <DaneUzytkownika> uzytkownicy;
    int liczbaUzytkownikow = 0;
    char wybranyZnak;

    liczbaUzytkownikow = wczytajUzytkownikowZPliku (uzytkownicy, liczbaUzytkownikow);

    do
    {
        wyswietlMenuStartowe ();

        cin.clear();
        cin.sync();
        wybranyZnak = getch();

        switch (wybranyZnak)
        {
        case '1':
            return zalogujUzytkownika (uzytkownicy, liczbaUzytkownikow);
            break;
        case '2':
            liczbaUzytkownikow = zarejestrujUzytkownika (uzytkownicy, liczbaUzytkownikow);
            break;
        case '3':
            exit (0);
        default:
            cout << "Nie ma takiej opcji w menu!";
            Sleep(1500);
        }
    }
    while (wybranyZnak !=3);
}

void uruchomKsiazkeAdresowa (int idZalogowanegoUzytkownika)
{
    vector <DaneAdresata> adresaci;
    int liczbaAdresatow = 0;
    char wybranyZnak;

    liczbaAdresatow = wczytajAdresatowZPliku (adresaci, liczbaAdresatow);

    do
    {
        wyswietlMenuZAdresatami ();

        cin.clear();
        cin.sync();
        wybranyZnak = getch();
        switch (wybranyZnak)
        {
        case '1':
            liczbaAdresatow = dodajAdresataDoKsiazki (adresaci, liczbaAdresatow);
            break;
        case '2':
            wyszukajImie (adresaci, liczbaAdresatow);
            break;
        case '3':
            wyszukajNazwisko (adresaci, liczbaAdresatow);
            break;
        case '4':
            wyswietlWszystkichAdresatow (adresaci, liczbaAdresatow);
            break;
        case '5':
        case '6':
            liczbaAdresatow = modyfikujDaneAdresata (adresaci, liczbaAdresatow, wybranyZnak);
            break;
        case '7':
            // zmien haslo
            break;
        case '8':
            wyczyscPlikTekstowyZAdresatami ();
            zapiszAdresatowWPliku (adresaci, liczbaAdresatow);
            cout << " * Zapisano w pliku tekstowym! *" << endl;
            Sleep(1500);
            idZalogowanegoUzytkownika = 0;
        default:
            cout << "Nie ma takiej opcji w menu!";
            Sleep(1500);
        }
    }
    while (wybranyZnak != 8);
}

int main ()
{
    int idZalogowanegoUzytkownika = 0;

    while(1)
    {
        if (idZalogowanegoUzytkownika == 0)
            idZalogowanegoUzytkownika = uruchomObslugeUzytkownikow ();
        else
            uruchomKsiazkeAdresowa (idZalogowanegoUzytkownika);
    }

    return 0;
}

