#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

struct AnalizaPlikuTekstowego
{
    int idOstatniegoAdresata, liczbaAdresatow;
};

struct DaneUzytkownika
{
    int idUzytkownika;
    string nazwa, haslo;
};

struct DaneAdresata
{
    int idAdresata, wlascicielWpisu;
    string imie, nazwisko, adres, telefon, email;
};

void wyswietlHeaderMenu ()
{
    system("cls");
    cout << "**********************************" << endl;
    cout << "*        KSI¤½KA ADRESOWA        *" << endl;
    cout << "**********************************" << endl << endl;
}

void wyswietlMenuStartowe ()
{
    wyswietlHeaderMenu ();
    cout << "1. Logowanie" << endl;
    cout << "2. Rejestracja" << endl;
    cout << "3. Zakoäcz program" << endl;
    cout << endl;
}

void wyswietlMenuZAdresatami ()
{
    cout << "1. Dodaj nowego adresata" << endl;
    cout << "2. Wyszukaj adresata po imieniu" << endl;
    cout << "3. Wyszukaj adresata po nazwisku" << endl;
    cout << "4. Lista zapisanych adresat¢w" << endl;
    cout << "5. Usuä adresata" << endl;
    cout << "6. Edytuj dane adresata" << endl;
    cout << "7. Zmieä hasˆo" << endl;
    cout << "8. Wyloguj" << endl;
    cout << endl;
}

void wyswietlDaneAdresata (vector <DaneAdresata> &adresaci, int i)
{
    cout << "NUMER ID WPISU: " << adresaci[i].idAdresata << endl;
    cout << "IMI¨: " << adresaci[i].imie << endl;
    cout << "NAZWISKO: " << adresaci[i].nazwisko << endl;
    cout << "ADRES: " << adresaci[i].adres << endl;
    cout << "TELEFON: " << adresaci[i].telefon << endl;
    cout << "E-MAIL: " << adresaci[i].email << endl << endl;
}

void wyswietlMenuEdycji (vector <DaneAdresata> &adresaci, int indeksWyszukanegoAdresata)
{
    wyswietlHeaderMenu();
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

void wczytajUzytkownikowZPliku (vector <DaneUzytkownika> &uzytkownicy)
{
    fstream spisUzytkownikow;
    string liniaTekstuSpisuUzytkownikow;
    int liczbaUzytkownikow = 0;

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
}

void wczytajPierwszeDwaSegmentyLinii (DaneAdresata &buforAdresatow, string segmentDanychAdresata, int numerSegmentuWLiniiTekstu)
{
    switch (numerSegmentuWLiniiTekstu)
    {
    case 1:
        buforAdresatow.idAdresata = atoi(segmentDanychAdresata.c_str());
        break;
    case 2:
        buforAdresatow.wlascicielWpisu = atoi(segmentDanychAdresata.c_str());
        break;
    }
}

void  wczytajPozostaleSegmentyLinii (DaneAdresata &buforAdresatow, string segmentDanychAdresata, int numerSegmentuWLiniiTekstu)
{
    switch (numerSegmentuWLiniiTekstu)
    {
    case 3:
        buforAdresatow.imie = segmentDanychAdresata;
        break;
    case 4:
        buforAdresatow.nazwisko = segmentDanychAdresata;
        break;
    case 5:
        buforAdresatow.adres = segmentDanychAdresata;
        break;
    case 6:
        buforAdresatow.telefon = segmentDanychAdresata;
        break;
    case 7:
        buforAdresatow.email = segmentDanychAdresata;
        break;
    }
}

void skopiujBuforDoWektoraAdresatow (DaneAdresata &buforAdresatow, vector <DaneAdresata> &adresaci, int liczbaAdresatow)
{
    adresaci.push_back(DaneAdresata());
    adresaci[liczbaAdresatow].idAdresata = buforAdresatow.idAdresata;
    adresaci[liczbaAdresatow].wlascicielWpisu = buforAdresatow.wlascicielWpisu;
    adresaci[liczbaAdresatow].imie = buforAdresatow.imie;
    adresaci[liczbaAdresatow].nazwisko = buforAdresatow.nazwisko;
    adresaci[liczbaAdresatow].adres = buforAdresatow.adres;
    adresaci[liczbaAdresatow].telefon = buforAdresatow.telefon;
    adresaci[liczbaAdresatow].email = buforAdresatow.email;
}

AnalizaPlikuTekstowego wczytajAdresatowZPliku (vector <DaneAdresata> &adresaci, int liczbaAdresatow, int idZalogowanegoUzytkownika)
{
    fstream ksiazkaAdresowa;
    string liniaTekstuSpisuAdresatow;
    DaneAdresata buforAdresatow;
    buforAdresatow.wlascicielWpisu = 0;
    AnalizaPlikuTekstowego wynikAnalizyPlikuTekstowego;

    ksiazkaAdresowa.open ("Adresaci.txt", ios::in);
    if (ksiazkaAdresowa.good() == true)
    {
        while (getline(ksiazkaAdresowa,liniaTekstuSpisuAdresatow))
        {
            stringstream ss (liniaTekstuSpisuAdresatow);
            string segmentDanychAdresata;
            int numerSegmentuWLiniiTekstu = 1;

            while (getline(ss, segmentDanychAdresata, '|'))
            {
                if (numerSegmentuWLiniiTekstu <= 2)
                {
                    wczytajPierwszeDwaSegmentyLinii (buforAdresatow, segmentDanychAdresata, numerSegmentuWLiniiTekstu);
                    if ((numerSegmentuWLiniiTekstu == 2) && (buforAdresatow.wlascicielWpisu != idZalogowanegoUzytkownika))
                        break;
                }
                if ((numerSegmentuWLiniiTekstu > 2) || (buforAdresatow.wlascicielWpisu == idZalogowanegoUzytkownika))
                {
                    wczytajPozostaleSegmentyLinii (buforAdresatow, segmentDanychAdresata, numerSegmentuWLiniiTekstu);
                }
                numerSegmentuWLiniiTekstu ++;
            }

            wynikAnalizyPlikuTekstowego.idOstatniegoAdresata = buforAdresatow.idAdresata;
            if (buforAdresatow.wlascicielWpisu == idZalogowanegoUzytkownika)
            {
                skopiujBuforDoWektoraAdresatow (buforAdresatow, adresaci, liczbaAdresatow);
                liczbaAdresatow ++;
            }
        }
        wynikAnalizyPlikuTekstowego.liczbaAdresatow = liczbaAdresatow;
    }
    ksiazkaAdresowa.close();

    return wynikAnalizyPlikuTekstowego;
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

void zapiszUzytkownikowWPliku (vector <DaneUzytkownika> &uzytkownicy)
{
    fstream spisUzytkownikow;
    int liczbaUzytkownikow = uzytkownicy.size();

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
        cout << "Nie udaˆo si© otworzy† pliku i zapisa† danych!" << endl;
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
            ksiazkaAdresowa << adresaci[i].wlascicielWpisu << '|';
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
        return (adresaci[liczbaAdresatow-1].idAdresata + inkrementacjaID);
}

int dodajAdresataDoKsiazki (vector <DaneAdresata> &adresaci, int liczbaAdresatow, int idZalogowanegoUzytkownika, int idOstatniegoAdresataWKsiazce) // WIP -------------
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
    adresaci[indeksNowegoAdresata].idAdresata = IDNowegoAdresata;
    adresaci[indeksNowegoAdresata].wlascicielWpisu = idZalogowanegoUzytkownika;
    liczbaAdresatow++;

    wyczyscPlikTekstowyZAdresatami ();
    zapiszAdresatowWPliku (adresaci, liczbaAdresatow);
    cout << endl << "Zapisano." << endl;
    Sleep(1000);

    return liczbaAdresatow;
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

int wyszukajID (vector <DaneAdresata> &adresaci, int liczbaAdresatow, int IDAdresata, int idZalogowanegoUzytkownika)
{
    const int NIE_ZNALEZIONO_WYNIKOW = -1;
    int indeksWyszukanegoAdresata;
    int liczbaWynikow = 0;

    for (int i=0; i<liczbaAdresatow; i++)
    {
        if ((adresaci[i].idAdresata == IDAdresata) && (adresaci[i].wlascicielWpisu == idZalogowanegoUzytkownika))
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
        if (adresaci[i].imie == szukaneImie)
            liczbaWynikow ++;
    }

    if (liczbaWynikow == 0)
        cout << endl << "Nie znaleziono ¾adnych adresat¢w." << endl << endl;
    else
    {
        cout << endl << "Znaleziono " << liczbaWynikow << " adresat¢w w ksi¥¾ce:" << endl << endl;
        for (int i=0; i<liczbaAdresatow; i++)
        {
            if (adresaci[i].imie == szukaneImie)
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
        if (adresaci[i].nazwisko == szukaneNazwisko)
            liczbaWynikow ++;
    }

    if (liczbaWynikow == 0)
        cout << endl << "Nie znaleziono ¾adnych adresat¢w." << endl << endl;
    else
    {
        cout << endl << "Znaleziono " << liczbaWynikow << " adresat¢w w ksi¥¾ce:" << endl << endl;
        for (int i=0; i<liczbaAdresatow; i++)
        {
            if (adresaci[i].nazwisko == szukaneNazwisko)
                wyswietlDaneAdresata (adresaci, i);
        }
    }
    system("pause");
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
    wyczyscPlikTekstowyZAdresatami ();
    zapiszAdresatowWPliku (adresaci, liczbaAdresatow);
    cout << endl << "Zapisano." << endl;
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
            Sleep(1000);
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
        wyswietlHeaderMenu();
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
            wyczyscPlikTekstowyZAdresatami ();
            zapiszAdresatowWPliku (adresaci, liczbaAdresatow);
            cout << endl << endl << "Adresat usuni©ty." << endl;
            Sleep(1000);
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

int modyfikujDaneAdresata (vector <DaneAdresata> &adresaci, int liczbaAdresatow, char wybranyZnak, int idZalogowanegoUzytkownika)
{
    int IDAdresata, indeksWyszukanegoAdresata;

    if (wybranyZnak == '5')
        cout << "Wpisz ID adresata do usuni©cia: ";
    else if (wybranyZnak == '6')
        cout << "Wpisz ID adresata do edycji: ";

    cin >> IDAdresata;

    indeksWyszukanegoAdresata = wyszukajID (adresaci, liczbaAdresatow, IDAdresata, idZalogowanegoUzytkownika);

    if (indeksWyszukanegoAdresata >= 0)
    {
        if (wybranyZnak == '5')
            liczbaAdresatow = potwierdzUsuniecieAdresata (adresaci, liczbaAdresatow, indeksWyszukanegoAdresata);
        else if (wybranyZnak == '6')
            liczbaAdresatow = edytujWybranegoAdresata (adresaci, liczbaAdresatow, indeksWyszukanegoAdresata);
    }
    return liczbaAdresatow;
}

int zalogujUzytkownika (vector <DaneUzytkownika> &uzytkownicy)
{
    string wpisanaNazwa, wpisaneHaslo;
    int liczbaUzytkownikow = uzytkownicy.size();

    wyswietlHeaderMenu ();
    cout << "Wpisz nazw© u¾ytkownika: ";
    cin.sync();
    getline(cin,wpisanaNazwa);

    for (int i=0; i<liczbaUzytkownikow; i++)
    {
        if (uzytkownicy[i].nazwa == wpisanaNazwa)
        {
            for (int j=0; j<3; j++)
            {
                cout << "Podaj hasˆo (pozostaˆo " << 3-j << " pr¢b): ";
                cin.sync();
                getline(cin,wpisaneHaslo);

                if (uzytkownicy[i].haslo == wpisaneHaslo)
                {
                    cout << endl << "Zalogowano." << endl;
                    Sleep (1000);
                    return uzytkownicy[i].idUzytkownika;
                }
            }
            cout << endl << "Trzykrotnie wpisano bˆ©dne hasˆo. Poczekaj 3 sekundy przed kolejn¥ pr¢b¥." << endl;
            Sleep (3000);
            return 0;
        }
    }

    cout << endl << "Nie ma takiego u¾ytkownika." << endl;
    Sleep(1500);
    return 0;
}

void zarejestrujUzytkownika (vector <DaneUzytkownika> &uzytkownicy)
{
    string nazwa, haslo;
    int liczbaUzytkownikow = uzytkownicy.size();

    wyswietlHeaderMenu ();
    cout << "Wpisz nazw© u¾ytkownika: ";
    cin.sync();
    getline(cin,nazwa);

    int i = 0;
    while (i<liczbaUzytkownikow)
    {
        if (uzytkownicy[i].nazwa == nazwa)
        {
            cout << "Taki u¾ytkownik ju¾ istnieje. Wpisz inn¥ nazw© u¾ytkownika: ";
            cin.sync();
            getline(cin,nazwa);
            i = 0;
        }
        else
            i++;
    }

    cout << "Wpisz hasˆo: ";
    cin.sync();
    getline (cin,haslo);

    uzytkownicy.push_back(DaneUzytkownika());
    uzytkownicy[liczbaUzytkownikow].nazwa = nazwa;
    uzytkownicy[liczbaUzytkownikow].haslo = haslo;
    uzytkownicy[liczbaUzytkownikow].idUzytkownika = liczbaUzytkownikow + 1;

    wyczyscPlikTekstowyZUzytkownikami ();
    zapiszUzytkownikowWPliku (uzytkownicy);
    cout << endl << "Konto utworzone." << endl;
    Sleep(1000);
}

void zmienHasloZalogowanegoUzytkownika (vector <DaneUzytkownika> &uzytkownicy, int idZalogowanegoUzytkownika)
{
    string noweHaslo;
    int liczbaUzytkownikow = uzytkownicy.size();

    wyswietlHeaderMenu ();
    cout << "Podaj nowe hasˆo: ";
    cin.sync();
    getline (cin,noweHaslo);

    for (int i=0; i<liczbaUzytkownikow; i++)
    {
        if (uzytkownicy[i].idUzytkownika == idZalogowanegoUzytkownika)
            uzytkownicy[i].haslo = noweHaslo;
    }

    wyczyscPlikTekstowyZUzytkownikami ();
    zapiszUzytkownikowWPliku (uzytkownicy);
    cout << endl << "Hasˆo zmienione." << endl;
    Sleep(1000);
}

int uruchomObslugeUzytkownikow (vector <DaneUzytkownika> &uzytkownicy)
{
    char wybranyZnak;

    do
    {
        wyswietlMenuStartowe ();
        cin.clear();
        cin.sync();
        wybranyZnak = getch();

        switch (wybranyZnak)
        {
        case '1':
            return zalogujUzytkownika (uzytkownicy);
            break;
        case '2':
            zarejestrujUzytkownika (uzytkownicy);
            break;
        case '3':
            cout << "Do nast©pnego razu!" << endl;
            Sleep(1000);
            exit (0);
        default:
            cout << "Nie ma takiej opcji w menu!";
            Sleep(1000);
        }
    }
    while (wybranyZnak !=3);
}

int uruchomKsiazkeAdresowa (vector <DaneUzytkownika> &uzytkownicy, int idZalogowanegoUzytkownika)
{
    vector <DaneAdresata> adresaci;
    int liczbaAdresatow = 0, idOstatniegoAdresataWKsiazce = 0;
    char wybranyZnak;
    AnalizaPlikuTekstowego wynikAnalizyPlikuTekstowego;

    wynikAnalizyPlikuTekstowego = wczytajAdresatowZPliku (adresaci, liczbaAdresatow, idZalogowanegoUzytkownika); // done!
    liczbaAdresatow = wynikAnalizyPlikuTekstowego.liczbaAdresatow; // done!
    idOstatniegoAdresataWKsiazce = wynikAnalizyPlikuTekstowego.idOstatniegoAdresata; // done!

    do
    {
        wyswietlHeaderMenu();
        cout << "Witaj, " << uzytkownicy[idZalogowanegoUzytkownika-1].nazwa << ". Wybierz opcj©:" << endl << endl;
        wyswietlMenuZAdresatami ();
        cout << endl << "liczba wczytanych adresatow: " << liczbaAdresatow << endl; ///////////////////////////////////////////
        cout << "id ostatniego adresata: " << idOstatniegoAdresataWKsiazce << endl; /////////////////////////////////////////

        cin.clear();
        cin.sync();
        wybranyZnak = getch();

        switch (wybranyZnak)
        {
        case '1':
            liczbaAdresatow = dodajAdresataDoKsiazki (adresaci, liczbaAdresatow, idZalogowanegoUzytkownika, idOstatniegoAdresataWKsiazce);  // WIP  ---------------------
            // dodac funkcje analizujaca idOstatniego wpisu (ale nie z pliku)
            break;
        case '2':
            wyszukajImie (adresaci, liczbaAdresatow); // done!
            break;
        case '3':
            wyszukajNazwisko (adresaci, liczbaAdresatow); // done!
            break;
        case '4':
            wyswietlWszystkichAdresatow (adresaci, liczbaAdresatow); // done!
            break;
        case '5':
        case '6':
            liczbaAdresatow = modyfikujDaneAdresata (adresaci, liczbaAdresatow, wybranyZnak, idZalogowanegoUzytkownika);
            // dodac funkcje analizujaca idOstatniego wpisu (ale nie z pliku)
            break;
        case '7':
            zmienHasloZalogowanegoUzytkownika (uzytkownicy, idZalogowanegoUzytkownika); // done!
            break;
        case '8':
            adresaci.clear();
            cout << " * Wylogowano! *" << endl;
            Sleep(1000);
            return 0;
        default:
            cout << "Nie ma takiej opcji w menu!";
            Sleep(1000);
        }
    }
    while (wybranyZnak != 8);
}

int main ()
{
    vector <DaneUzytkownika> uzytkownicy;
    int idZalogowanegoUzytkownika = 0;
    wczytajUzytkownikowZPliku (uzytkownicy);

    while(1)
    {
        if (idZalogowanegoUzytkownika == 0)
            idZalogowanegoUzytkownika = uruchomObslugeUzytkownikow (uzytkownicy);
        else
            idZalogowanegoUzytkownika = uruchomKsiazkeAdresowa (uzytkownicy, idZalogowanegoUzytkownika);
    }

    return 0;
}

