#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
//all done

using namespace std;

int kierunkiX[] = { -1, 1, 0, 0 }; // tablice do zmiany kierunku wyboru pola
int kierunkiY[] = { 0, 0, -1, 1 };
int gridtab[22][22]; // 0 pola, 5 sciany tab[i][0,22] i tab[0,22][j] to sciany z 5, 8 to droga
int closedtab[22][22] = {}; // 1 - jest na liscie 0 to nic
int opentab[22][22] = {};// 1 - jest na liscie 5 to sciana 0 to nic
int parenttab[22][22]; // 0 nie ma 1 parent na dole, 2 na gorze , 3 po prawej, 4 po lewej, 9 to START, 7 TO KONIEC
double ftab[22][22] = {}; //tablica jest zapelniana zerami
int g;
double h;
int a, b;
int i = 20;
int j = 1;
int poziomo = 0;
int pionowo = 0;
int n = 20;
int m = 1;


void dodajiodejmij()
{
	closedtab[n][m] = 1; //wpisuje pole z najmniejszym f do closed tab
	opentab[n][m] = 0; //usuwa te pole z open tab
	i = n;
	j = m;
}

int potega(int liczba) // sprawdzone, dzia³a
{
	return liczba*liczba;
}

int obliczanieG(int wartosci, int wartoscj) // zwraca koszt g | sprawdzone, powinno dzia³aæ
{
	int koszt = 0;
	while (parenttab[wartosci][wartoscj] != 9) // petla sie konczy po dojsciu do pola START oznaczonego 4
	{
		if (parenttab[wartosci][wartoscj] == 1) // sprawdza gdy jest parent obecnego w petli pola i ustawia na niego namiar
		{
			koszt = koszt + 1; // przy kazdym odpaleniu petli zwieksza koszt o 1
			wartosci = wartosci + 1;
		}
		if (parenttab[wartosci][wartoscj] == 2)
		{
			koszt = koszt + 1; // przy kazdym odpaleniu petli zwieksza koszt o 1
			wartosci = wartosci - 1;
		}
		if (parenttab[wartosci][wartoscj] == 3)
		{
			koszt = koszt + 1; // przy kazdym odpaleniu petli zwieksza koszt o 1
			wartoscj = wartoscj + 1;
		}
		if (parenttab[wartosci][wartoscj] == 4)
		{
			koszt = koszt + 1; // przy kazdym odpaleniu petli zwieksza koszt o 1
			wartoscj = wartoscj - 1;
		}
	}
	return koszt;
}

void liczenieFOtaczajacychKratek(int i, int j) //  sprawdzone, powinno dzia³aæ
{
	for (int d = 0; d < 4; d++)
	{
		pionowo = kierunkiX[d]; // { -1, 1, 0, 0 };
		poziomo = kierunkiY[d]; // { 0, 0, -1, 1 };
		if (closedtab[i + pionowo][j + poziomo] != 1)
		{
			if (gridtab[i + pionowo][j + poziomo] != 5) // sprawdza czy pole jest scian¹
			{
				opentab[i + pionowo][j + poziomo] = 1; // zaznacza w tab otwartej ze jest przeszukiwana
				if (ftab[i + pionowo][j + poziomo] == 0) // sprawdza czy f juz bylo liczone dla danego pola, jak przejdzie to nie bylo
				{
					parenttab[i + pionowo][j + poziomo] = d + 1; // parent
					g = obliczanieG(i + pionowo, j + poziomo);
					h = sqrt(potega((i + pionowo) - 1) + potega((j + poziomo) - 20));
					double f = g + h; // obliczanie f
					ftab[i + pionowo][j + poziomo] = f; //przypisuje f do pola
				}
				else
				{
					g = obliczanieG(i + pionowo, j + poziomo);
					h = sqrt(potega((i + pionowo) - 1) + potega((j + poziomo) - 20));
					double f = g + h; // obliczanie f
					if (ftab[i + pionowo][j + poziomo] > f) // sprawdza czy stare f jest gorsze od nowego
					{
						parenttab[i + pionowo][j + poziomo] = d + 1; // parent
						ftab[i + pionowo][j + poziomo] = f; //jak nowe f jest krotsze to przypisuje f, a jak nie to nie ruszaj, 
					}
				}// jak ify nie ³api¹ przypadku to znaczy ze zachowuje starego parenta i stary f
			}
			else
			{
				opentab[i + pionowo][j + poziomo] = 5; // zaznacza ze to pole jest scian¹ 
			}
		}
	}
}

void szukanieNajmniejszegoF() // sprawdzone, powinno dzia³aæ
{
	double przechowalnik = 1000;
	for (int a = 0; a < 22; a++)
	{
		for (int b = 0; b < 22; b++)
		{
			if (closedtab[a][b] != 1 && ftab[a][b] != 0 && ftab[a][b] < przechowalnik)
			{
				przechowalnik = ftab[a][b];
				n = a;
				m = b;
			}
		}
	}
}

void wyznaczanieDrogi()
{
	i = 1;
	j = 20;
	while (parenttab[i][j] != 9) // petla sie konczy po dojsciu do pola START oznaczonego 9
	{
		if (parenttab[i][j] == 1) // sprawdza gdzie jest parent obecnego w petli pola i ustawia na niego namiar
		{
			gridtab[i][j] = 8; //zaznacza droge na tablicy
			i = i + 1;
		}
		if (parenttab[i][j] == 2)
		{
			gridtab[i][j] = 8; //zaznacza droge na tablicy
			i = i - 1;
		}
		if (parenttab[i][j] == 3)
		{
			gridtab[i][j] = 8; //zaznacza droge na tablicy
			j = j + 1;
		}
		if (parenttab[i][j] == 4)
		{
			gridtab[i][j] = 8; //zaznacza droge na tablicy
			j = j - 1;
		}
	}
}

void budowanieScian() // przetestowana, dzia³a
{
	for (int j = 0; j < 22; j++) // blokowanie bocznych scian
	{
		gridtab[0][j] = 5;
		gridtab[21][j] = 5;
	}
	for (int i = 0; i < 22; i++) //blokowanie poziomych œcian
	{
		gridtab[i][0] = 5;
		gridtab[i][21] = 5;
	}
}

bool sprawdzOtwarta() // przetestowana, dzia³a
{
	int temp = 0;
	for (int a = 1; a < 21; a++)
	{
		for (int b = 1; b < 21; b++)
		{
			if (opentab[a][b] == 1) //sprawdzamy czy chociaz 1 pole jest na liscie by móc dalej wykonac algorytm
			{
				temp = 1;
			}
		}
	}
	if (temp == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int main()
{
	ifstream siatka; // v ³adowienie z notatnika
	siatka.open("D:\\RobertProtasiuk\\grid.txt");

	if (siatka.good()) //test na poprawne za³adowanie
	{
		cout << "Plik udalo sie otworzyc" << endl;
	}
	else
	{
		cout << "Pliku NIE udalo sie otworzyc" << endl;
	}

	budowanieScian(); // otacza gridtab scianami

	for (int a = 1; a < 21; a++) //wype³nianie ograniczonego taba wartosciami z notatnika
	{
		for (int b = 1; b < 21; b++)
		{
			if (b != 22)
			{
				siatka >> gridtab[a][b];
			}
		}
	}

	budowanieScian();

	gridtab[1][20] = 9; // cel
	gridtab[20][1] = 7; // start
	parenttab[20][1] = 9; // oznaczanie parenttab jako start specialne pole
	closedtab[20][1] = 1; // inicjalizacja tab zamknietej polem start zapamietac

	cout << endl;
	siatka.close();

	//poczatek 
	if (gridtab[19][1] != 5) { opentab[19][1] = 1, parenttab[19][1] = 1; } //dodawanie pola z gory do open tab
	else { opentab[19][1] = 5; }

	if (gridtab[20][2] != 5) { opentab[20][2] = 1, parenttab[20][2] = 4; } //dodawanie pola z prawej do open tab
	else { opentab[20][2] = 5; }

	opentab[21][1] = 5;
	opentab[20][0] = 5;

	while (closedtab[1][20] != 1 && sprawdzOtwarta())
	{
		dodajiodejmij();
		liczenieFOtaczajacychKratek(i, j);
		szukanieNajmniejszegoF();
	}

	if (closedtab[1][20] == 1)
	{
		wyznaczanieDrogi();

		// sprawdzenie w konsoli
		for (int a = 0; a < 22; a++)
		{
			for (int b = 0; b < 22; b++)
			{
				cout << gridtab[a][b] << ' ';
			}
			cout << endl;
		}
	}
	else
	{
		// sprawdzenie w konsoli
		for (int a = 0; a < 22; a++)
		{
			for (int b = 0; b < 22; b++)
			{
				cout << gridtab[a][b] << ' ';
			}
			cout << endl;
		}
		cout << "Przejscie do celu nie jest mozliwe " << endl;
		cout << endl;
	}


	system("pause");
	return 0;
}