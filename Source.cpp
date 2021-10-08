#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;
const int sirinaMape = 15;
const int duzinaMape = 15;
class PACMAN
{
	char character, neprijatelj;
	char Mapa[duzinaMape][sirinaMape]{ ' ' };
	int r, k,PozNr,PozNk;
	bool KrajIgre;
	void KontorleIgraca(char unos, int& r, int& k)
	{
		do
		{
			if (unos == 'a')
			{
				if (k==1)
					return;
				else
				{
					k -= 1;
					Mapa[r][k] = character;
					Mapa[r][k+1] = ' ';
				}
				return;

			}
			else if (unos == 'w')
			{
				if (r==1)
					return;
				else
				{
					r -= 1;
					Mapa[r][k] = character;
					Mapa[r+1][k] = ' ';
				}
				return;
			}
			else if (unos == 's')
			{
				if (r==13)
					return;
				else
				{
					r += 1;
					Mapa[r][k] = character;
					Mapa[r-1][k] = ' ';
				}
				return;
			}
			else if (unos == 'd')
			{
				if (k==13)
					return;
				else
				{
					k += 1;
					Mapa[r][k] = character;
					Mapa[r][k-1] = ' ';
				}
				return;
			}
		} while (unos=='a'|| unos == 'w' || unos == 's' || unos == 'd' );
		
	}
	void AINeprijatelj()
	{
		int pozicijaI, pozicijaJ;
		for (size_t i = 0; i < duzinaMape; i++)
		{
			for (size_t j = 0; j < sirinaMape; j++)
			{
				if (Mapa[i][j] == 'P')
				{
					pozicijaI = i;
					pozicijaJ = j;
				}
			}
		}
		if (PozNk < pozicijaJ)
		{
			PozNk++;
			Mapa[PozNr][PozNk] = neprijatelj;
			Mapa[PozNr][PozNk - 1] = ' ';
		}
		if (PozNk > pozicijaJ)
		{
			PozNk--;
			Mapa[PozNr][PozNk] = neprijatelj;
			Mapa[PozNr][PozNk + 1] = ' ';
		}
		if (PozNr < pozicijaI)
		{
			PozNr++;
			Mapa[PozNr][PozNk] = neprijatelj;
			Mapa[PozNr - 1][PozNk] = ' ';
		}
		if (PozNr > pozicijaI)
		{
			PozNr--;
			Mapa[PozNr][PozNk] = neprijatelj;
			Mapa[PozNr + 1][PozNk] = ' ';
		}
	}
public:
	PACMAN()
	{
		character = 'P';
		neprijatelj = 'N';
		Mapa[7][7] = neprijatelj;
		Mapa[1][1] = character;
		r = 1;
		k = 1;
		PozNr = 7;
		PozNk = 7;
	}

	void Igraj(char unos)
	{
		KontorleIgraca(unos,r,k);
		AINeprijatelj();
	}

	void PrikaziMapu()
	{
		for (size_t i = 0; i < duzinaMape; i++)
		{
			for (size_t j = 0; j < sirinaMape; j++)
			{
				if (i == 0 || j == 0 || j == sirinaMape - 1 || i == duzinaMape - 1)
					cout << '#';
				else
					cout << Mapa[i][j];
			}
			cout << endl;
		}
	}
	
};





int main()
{
	srand(time(0));
	PACMAN p1;
	char unos;
	do
	{
		p1.PrikaziMapu();
		cout << "Unesite kontorlu-> ";
		cin >> unos;
		system("cls");
		p1.Igraj(unos);
	} while (1);
}