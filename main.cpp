#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

struct DaneAdresata
{
    int id;
    string imie, nazwisko, adres, telefon, email;
};

void wczytajSegmentZLiniiTekstu (vector <DaneAdresata> &adresaci, int liczbaAdresatow, string segmentDanychAdresata, int numerSegmentuWLiniiTekstu)
{
    switch (numerSegmentuWLiniiTekstu)
    {
    case 1:
        adresaci[liczbaAdresatow].id = atoi(segmentDanychAdresata.c_str());
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
    string liniaTekstu;

    ksiazkaAdresowa.open ("ksiazkaAdresowa_nowy_format.txt", ios::in);
    if (ksiazkaAdresowa.good() == true)
    {
        while (getline(ksiazkaAdresowa,liniaTekstu))
        {
            adresaci.push_back(DaneAdresata());
            stringstream ss (liniaTekstu);
            string segmentDanychAdresata;
            int numerSegmentuWLiniiTekstu = 1;

            while (getline(ss, segmentDanychAdresata, '|'))
            {
                wczytajSegmentZLiniiTekstu (adresaci, liczbaAdresatow, segmentDanychAdresata, numerSegmentuWLiniiTekstu);
                numerSegmentuWLiniiTekstu ++;
            }
            liczbaAdresatow ++;
        }
    }
    ksiazkaAdresowa.close();

    return liczbaAdresatow;
}

void wyczyscPlikTekstowy ()
{
    fstream ksiazkaAdresowa;
    ksiazkaAdresowa.open("ksiazkaAdresowa_nowy_format.txt", ios::out|ios::trunc);
    ksiazkaAdresowa.close();
}

void zapiszAdresatowWPliku (vector <DaneAdresata> &adresaci, int liczbaAdresatow)
{
    fstream ksiazkaAdresowa;

    ksiazkaAdresowa.open("ksiazkaAdresowa_nowy_format.txt", ios::out|ios::app);
    if (ksiazkaAdresowa.good() == true)
    {
        for (int i=0; i<liczbaAdresatow; i++)
        {
            ksiazkaAdresowa << adresaci[i].id << '|';
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
        cout << "Nie udaˆo si© otworzy† pliku i zapisa† danych!" << endl;
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
        return (adresaci[liczbaAdresatow-1].id + inkrementacjaID);
}

int dodajAdresataDoKsiazki (vector <DaneAdresata> &adresaci, int liczbaAdresatow)
{
    string imie, nazwisko, adres, telefon, email;
    int indeksNowegoAdresata = 0;
    int IDNowegoAdresata;

    cout << "Wpisz imi© adresata: ";
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
    adresaci[indeksNowegoAdresata].id = IDNowegoAdresata;
    liczbaAdresatow++;

    wyczyscPlikTekstowy ();
    zapiszAdresatowWPliku (adresaci, liczbaAdresatow);
    cout << endl << "Zapisano" << endl;
    Sleep(1000);

    return liczbaAdresatow;
}

void wyswietlDaneAdresata (vector <DaneAdresata> &adresaci, int i)
{
    cout << "NUMER ID WPISU: " << adresaci[i].id << endl;
    cout << "IMI¨: " << adresaci[i].imie << endl;
    cout << "NAZWISKO: " << adresaci[i].nazwisko << endl;
    cout << "ADRES: " << adresaci[i].adres << endl;
    cout << "TELEFON: " << adresaci[i].telefon << endl;
    cout << "E-MAIL: " << adresaci[i].email << endl << endl;
}

void wyswietlWszystkichAdresatow (vector <DaneAdresata> &adresaci, int liczbaAdresatow)
{
    if (liczbaAdresatow == 0)
    {
        cout << "Ksi¥¾ka adresowa jest pusta." << endl << endl;
        system("pause");
    }
    else
    {
        cout << "Liczba adresat¢w zapisanych w ksi¥¾ce adresowej: " << liczbaAdresatow << endl << endl;

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
        if (IDAdresata == adresaci[i].id)
        {
            indeksWyszukanegoAdresata = i;
            liczbaWynikow ++;
        }
    }

    if (liczbaWynikow == 0)
    {
        cout << endl << "Nie znaleziono ¾adnych adresat¢w." << endl << endl;
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

    cout << "Wpisz imi© do wyszukania: ";
    cin.sync();
    getline(cin,szukaneImie);

    for (int i=0; i<liczbaAdresatow; i++)
    {
        if (szukaneImie == adresaci[i].imie)
            liczbaWynikow ++;
    }

    if (liczbaWynikow == 0)
        cout << endl << "Nie znaleziono ¾adnych adresat¢w." << endl << endl;

    else
    {
        cout << endl << "Znaleziono " << liczbaWynikow << " adresat¢w w ksi¥¾ce:" << endl << endl;
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
        cout << endl << "Nie znaleziono ¾adnych adresat¢w." << endl << endl;

    else
    {
        cout << endl << "Znaleziono " << liczbaWynikow << " adresat¢w w ksi¥¾ce:" << endl << endl;
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
    cout << "1. IMI¨" << endl;
    cout << "2. NAZWISKO" << endl;
    cout << "3. ADRES" << endl;
    cout << "4. TELEFON" << endl;
    cout << "5. E-MAIL" << endl;
    cout << "6. Cofnij do menu gˆ¢wnego" << endl << endl;
}

void edytujWybranePole (vector <DaneAdresata> &adresaci, int indeksWyszukanegoAdresata, char wybranyZnakWMenuEdycji, int liczbaAdresatow)
{
    string nowaWartoscPola;

    cin.clear();
    cin.sync();

    if (wybranyZnakWMenuEdycji == '1')
    {
        cout << "Wpisz nowe imi© adresata: ";
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
    wyczyscPlikTekstowy ();
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
    int IDAdresataDoUsuniecia = adresaci[indeksWyszukanegoAdresata].id;

    for (vector <DaneAdresata>::iterator it = adresaci.begin(); it != adresaci.end(); it++)
    {
        if (it->id == IDAdresataDoUsuniecia)
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
        cout << "Usun¥† wybranego adresata z ksi¥¾ki?" << endl << endl;
        cout << "Wybierz TAK (t) lub NIE (n): ";

        cin.clear();
        cin.sync();
        wybranyZnakWMenuUsuwania = getch();

        switch (wybranyZnakWMenuUsuwania)
        {
        case 't':
        case 'T':
            liczbaAdresatow = usunWybranegoAdresata (adresaci, liczbaAdresatow, indeksWyszukanegoAdresata);
            wyczyscPlikTekstowy ();
            zapiszAdresatowWPliku (adresaci, liczbaAdresatow);
            cout << endl << endl << "Adresat usuni©ty!" << endl;
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
        cout << "Wpisz ID adresata do usuni©cia: ";
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

void wyswietlMenuProgramu ()
{
    system("cls");
    cout << "**********************************" << endl;
    cout << "*        KSI¤KA ADRESOWA        *" << endl;
    cout << "**********************************" << endl << endl;
    cout << "1. Dodaj nowego adresata" << endl;
    cout << "2. Wyszukaj adresata po imieniu" << endl;
    cout << "3. Wyszukaj adresata po nazwisku" << endl;
    cout << "4. Lista zapisanych adresat¢w" << endl;
    cout << "5. Usuä adresata" << endl;
    cout << "6. Edytuj dane adresata" << endl;
    cout << "9. Zakoäcz program" << endl;
    cout << endl;
}

int main()
{
    vector <DaneAdresata> adresaci;
    int liczbaAdresatow = 0;
    char wybranyZnak;

    liczbaAdresatow = wczytajAdresatowZPliku (adresaci, liczbaAdresatow);

    do
    {
        wyswietlMenuProgramu ();

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
        case '9':
            wyczyscPlikTekstowy ();
            zapiszAdresatowWPliku (adresaci, liczbaAdresatow);
            cout << " * Zapisano w pliku tekstowym! *" << endl;
            Sleep(1500);
            exit (0);
        default:
            cout << "Nie ma takiej opcji w menu!";
            Sleep(1500);
        }
    }
    while (wybranyZnak != 9);

    return 0;
}
