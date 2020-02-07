#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <time.h>
using namespace std;

struct zwrot {
	string eng;
	string pl;
	int indeks = 0;
	int punkty = 0;
};
struct uzytkownik {
	string nick;
	string haslo;
	int punktacja;
};
zwrot slowko[20];
uzytkownik gracz[20];


int wczytajLiczbe() // funkcja sprawdzajaca poprawnosc wpisywanych danych do menu
{
	bool wczytywanieOK = true;
	int zwracana;
	do
	{
		cin >> zwracana;
		if (cin.fail() == 1)
		{
			wczytywanieOK = false;
			cout << "taka opcja nie istnieje w menu. Wprowadz liczbe od 1 do 6 i nacisnij enter" << endl;
			cin.clear();
			cin.ignore(1000, '\n');
		}
		else wczytywanieOK = true;
	} while (!wczytywanieOK);
	if (zwracana > 7 || zwracana < 1)
		cout << "taka opcja nie istnieje w menu. Wprowadz liczbe od 1 do 6 i nacisnij enter" << endl;
	else
		return zwracana;
}
void rozdzielanie(int i, string srednik) { // przetwarza plik ze slowkami wprowadzajac dane do programu
	size_t znalezionaPozycja = slowko[i].pl.rfind(srednik);
	slowko[i].eng = slowko[i].pl.substr(0, znalezionaPozycja);
	slowko[i].pl.erase(0, znalezionaPozycja+1);
}
void rozdzielanie2(int i, string srednik) {// przetwarza plik z rankingiem wprowadzajac dane do programu
	string str;
	size_t znalezionaPozycja = gracz[i].nick.rfind(srednik);
	str = gracz[i].nick.substr(0, znalezionaPozycja);
	gracz[i].punktacja = atoi(str.c_str());
	gracz[i].nick.erase(0, znalezionaPozycja + 1);
}
void odczytywaniePliku (string sNazwaPliku, int& i) // otwiera plik txt z slowkami
{
	ifstream plik;
	plik.open(sNazwaPliku.c_str());
	if (!plik.good())
		cout << "nazwa zle podana ";

	string wiersz;
	i = 1;
	while (getline(plik, wiersz)) {
		slowko[i].indeks = i;
		slowko[i].pl = wiersz;
		rozdzielanie(i, ";");
		i++;
	}
	plik.close();
	//system("cls");
}
int sprawdzenieIlosciGraczy() { 
	int licznik = 0;
	for (int i = 0; i < 20; i++) {
		if (gracz[i].nick != "")
			licznik += 1;
		else
		{
			continue;
		}
	}
	return licznik +1;
}
int zaloguj() {
	string tymcz;
	string pass;
	cout << "Wpisz nazwe uzytkownika " << endl;
	cin >> tymcz;
	cout << "Wpisz haslo " << endl;
	cin >> pass;
	for (int i = 0; i < 20; i++) {
		if ((gracz[i].nick == tymcz && gracz[i].haslo == pass) || (gracz[i].nick == tymcz && gracz[i].punktacja != 0)) {
			cout << " Logowanie powiodlo sie ..." << endl;
				return i;
		}
		else {
			continue;
		}
	}
	
}
void rejestruj() { // wprowadza nowego uzytkownika do bazy
	int iloscGraczy = sprawdzenieIlosciGraczy();
	for (int i = iloscGraczy; i < 20;) {
		string tymcz;
		string tymcz2;
		cout << "wpisz nazwe uzytkownika " << endl;
		cin >> tymcz;
		cout << "wpisz haslo uzytkownika " << endl;
		cin >> tymcz2;
		gracz[i].nick = tymcz;
		gracz[i].haslo = tymcz2;
		cout << " uzytkownik o nicku " << gracz[i].nick << " zostal wpisany do bazy " << endl;
		i++;
		break;
	}
	system("cls");
}
int sprawdzenieWilkosciIndeksu() { // sprawdza ilosc slowek w pliku txt
	int licznik = 0;
	for (int i = 0; i < 20; i++) {
		if (slowko[i].indeks != 0)
			licznik += 1;
		else
		{
			continue;
		}
	}
	return licznik;
}

void graj(int id_gracza) { 
	int wylosowaneSlowko = 0;
	int i = id_gracza;
	string wpisywane;
	cout << " ----- GRA ----- " << endl;
	wylosowaneSlowko = rand() % sprawdzenieWilkosciIndeksu() + 1;
	cout << slowko[wylosowaneSlowko].pl << " -> wpisz tlumaczenie: ";
	cin >> wpisywane;
	if (slowko[wylosowaneSlowko].eng == wpisywane) {
		cout << endl << " Poprawna odpowiedz! Zysujesz punkt " << endl;
		gracz[i].punktacja += 1;
	}
	else {
		cout << " Zle! Poprawna odpowiedz to: " << slowko[wylosowaneSlowko].eng << endl;
		cout << " Brak punktow dla uzytkownika " << gracz[i].nick << endl;
	}

}
void ranking() {
	cout << " ----- Ranking ------ " << endl;
	cout << "Gracz    |   Punktacja" << endl;
	for (int i = 0; i < 10; i++)
	{
		if (gracz[i].nick == "")
			continue;
		cout << gracz[i].nick << "                    " << gracz[i].punktacja << endl;

	}
}
void odczytRankingu(string nazwaPliku) { // Pobieranie rankingu z pliku txt
	ifstream plik;
	plik.open(nazwaPliku.c_str());
	if (!plik.good())
		cout << "nazwa zle podana ";

	string wiersz;
	int i = 1;
	while (getline(plik, wiersz)) {
		gracz[i].nick = wiersz;
		rozdzielanie2(i, ";");
		cout << gracz[i].nick << "     punkty      " << gracz[i].punktacja << endl;
		i++;
	}
	plik.close();
	
}
void zapisRankingu() { // wysylanie rankingu do pliku txt
	fstream plik;
	int iloscGraczy = sprawdzenieIlosciGraczy();
	plik.open("ranking.txt", ios::out);
	for (int i = 1; i < iloscGraczy; i++)
	{
		plik << gracz[i].punktacja << ";" << gracz[i].nick << endl;
	}
	plik.close();
}
void reset() { // resetowanie rankingu
	int ii = sprawdzenieIlosciGraczy();
	for (int i = 0; i <= ii; i++)
	{
		gracz[i].nick = "";
		gracz[i].haslo = "";
		gracz[i].punktacja = 0;
	}
}

void menu() {
	int wybor;
	int nr_gracza = -1;
	string nazwa_rankingu;
	for (;;)
	{
		cout << "1 - zaloguj" << endl;
		cout << "2 - rejestruj" << endl;
		cout << "3 - reset rankingu" << endl;
		cout << "4 - graj" << endl;
		cout << "5 - ranking " << endl;
		cout << "6 - odczyt rankingu pliku" << endl;
		cout << "7 - zapis do bazy i wyjscie " << endl;

			wybor = wczytajLiczbe();
		switch (wybor){
		case 1:
			system("cls");
			nr_gracza = zaloguj();
			if (nr_gracza <= 20 && nr_gracza >= 0)
				continue;
			else cout << "Ponady uzytkownik nie istnieje lub zle wpisane haslo " << endl;
			break;
		case 3:
			system("cls");
			reset();
			break;
		case 2:
			system("cls");
			rejestruj();
			break;
		case 4:
			system("cls");
			if (sprawdzenieIlosciGraczy != 0) {
				if(nr_gracza != -1)
					graj(nr_gracza);
				else cout << " Zaloguj sie najpierw " << endl;
			}
			else cout << " Musisz dodac i wybrac uzytkownika aby grac " << endl;
			break;
		case 5:
			system("cls");
			ranking();
			break;
		case 6:
			system("cls");
			cout << " Aby wczytac ranking, wpisz ranking.txt i Enter " << endl;
			cin >> nazwa_rankingu;
			odczytRankingu(nazwa_rankingu);
			break;
		case 7:
			zapisRankingu();
			exit(0);
			break;
		};
	}
}

int main()
{
	srand(time(NULL));
	int i;
	int id_gracza;
	cout << " program wspomagajicy nauke slowek " << endl;
	cout << " Wpisz nazwe lekcji z dopiskiem .txt " << endl;

	string nazwa_lekcji;
	cin >> nazwa_lekcji;
	odczytywaniePliku(nazwa_lekcji,i);
	menu();
	



	return 0;
}