#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cassert>
using namespace std;

const int mapLenght = 17;
const int mapWidth = 17;

int Min(int obj1, int obj2)
{
	if (obj1 < obj2)
		return obj1;
	return obj2;
}

void GameOverScreen()
{
	cout << "\t\t\tYOU LOST";
	cin.get();
}

class Entity
{
	int _positionX;
	int _positionY;
	char _id;
public:

	__declspec(property(get = GetPositionX, put = SetPositionX))int PositionX;
	__declspec(property(get = GetPositionY, put = SetPositionY))int PositionY;
	__declspec(property(get = GetId, put = SetId))char Id;

	Entity(int PosX, int PosY, const char id)
	{
		_positionX = PosX;
		_positionY = PosY;
		_id = id;
	}

	Entity(const Entity& obj)
	{
		_positionX = obj._positionX;
		_positionY = obj._positionY;
		_id = obj._id;
	}

	void Movment(char input)
	{
		if (input == 'w')
			PositionX -= 1;

		if (input == 's')
			PositionX += 1;

		if (input == 'a')
			PositionY -= 1;

		if (input == 'd')
			PositionY += 1;
	}

	int GetPositionX()const { return _positionX; }
	int GetPositionY()const { return _positionY; }
	char GetId()const { return _id; }

	void SetPositionX(int PosX) { _positionX = PosX; }
	void SetPositionY(int PosY) { _positionY = PosY; }
	void SetId(char id) { _id = id; }

};



class Player :public Entity
{
	bool _statusAlive;
public:

	_declspec(property(get = GetStatusAlive, put = SetStatusAlive))bool StatusAlive;

	Player(int PosX, int PosY, bool statusAlive, char id = 'P') :
		Entity(PosX, PosY, id)
	{
		_statusAlive = statusAlive;
	}

	Player(const Player& obj) :
		Entity(obj)
	{
		_statusAlive = obj._statusAlive;
	}

	bool GetStatusAlive()const { return _statusAlive; }
	void SetStatusAlive(bool statusAlive) { _statusAlive = statusAlive; }

};

class Enemy :public Entity
{
	int* _playerPosX;
	int* _playerPosY;
public:

	__declspec(property(get = GetPlayerPosX, put = SetPlayerPosX))int PlayerPosX;
	__declspec(property(get = GetPlayerPosY, put = SetPlayerPosY))int PlayerPosY;
	__declspec(property(get = EnemyInput))char Input;

	Enemy(int PosX, int PosY, char id = 'N') :
		Entity(PosX, PosY, id)
	{
		_playerPosX = new int(1);
		_playerPosY = new int(1);
	}

	int& GetPlayerPosX()const { return *_playerPosX; }
	int& GetPlayerPosY()const { return *_playerPosY; }

	void SetPlayerPosX(int posX) { *_playerPosX = posX; }
	void SetPlayerPosY(int posY) { *_playerPosY = posY; }

	char& EnemyInputUpDown()
	{
		char* w = new char('w');
		char* s = new char('s');
		char* temp = new char('t');
		if (PlayerPosX < PositionX)
		{
			return *w;
		}
		
		if (PlayerPosX > PositionX)
		{
			return *s;
		}
		
		return *temp;

		delete w;
		delete s;
		
		w = s = nullptr;
	}

	char& EnemyInputSideToSide()
	{
		char* a = new char('a');
		char* d = new char('d');
		if (PlayerPosY > PositionY)
		{
			return *d;
		}

		if (PlayerPosY < PositionY)
		{
			return *a;
		}
		delete d;
		delete a;
		a = d = nullptr;
	}

	~Enemy()
	{
		delete _playerPosX;
		delete _playerPosY;
		_playerPosX = _playerPosY = nullptr;
	}

};

enum class  WallTipe { HORIZONTAL, VERTICAL, TOPRIGHTCORNER, TOPLEFTCORNER, BOTTOMLEFTCORNER, BOTTOMRIGHTCORNER };

const int _spawnRoomLenghtAndHeight = 5;
class Map
{
	char _openTilesSimbol = ' ';
	char _layout[mapLenght][mapWidth]{ _openTilesSimbol };
	char _spawnRoom[_spawnRoomLenghtAndHeight][_spawnRoomLenghtAndHeight]{ _openTilesSimbol };

public:

	void GenerateTwoHorizontal(int x, int y)
	{
		for (int i = 0; i < 2; i++)
		{
			_layout[x][y + i] = '#';
		}
	}

	void GenareteTwoVertical(int x, int y)
	{
		for (int i = 0; i < 2; i++)
		{
			_layout[x + i][y] = '#';
		}
	}

	void GenerateBottomLeft(int x, int y)
	{
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				if (i == 0 && j == 1)
					_layout[x + i][y + j] = _layout[x + i][y + j];
				else
					_layout[x + i][y + j] = '#';
			}
		}
	}

	void GenerateBottomRight(int x, int y)
	{
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				if (i == 0 && j == 0)
					_layout[x + i][y + j] = _layout[x + i][y + j];
				else
					_layout[x + i][y + j] = '#';
			}
		}
	}

	void GenerateTopLeft(int x, int y)
	{
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				if (i == 1 && j == 1)
					_layout[x + i][y + j] = _layout[x + i][y + j];
				else
					_layout[x + i][y + j] = '#';
			}
		}
	}

	void GenerateTopRight(int x, int y)
	{
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				if (i == 1 && j == 0)
					_layout[x + i][y + j] = _layout[x + i][y + j];
				else
					_layout[x + i][y + j] = '#';
			}
		}
	}

	bool CheckIfTilesFree(int x, int y, WallTipe walltipe)
	{		
		if (walltipe == WallTipe::HORIZONTAL)
		{
			for (int i = 0; i < 2; i++)
			{
				if(_layout[x][y+1] == '#' || _layout[x + i][y] == 'P' || _layout[x + i][y] == 'N')
					return false;
			}
		}

		if (walltipe == WallTipe::VERTICAL)
		{
			for (int i = 0; i < 2; i++)
			{
				if (_layout[x + i][y] == '#' || _layout[x + i][y] == 'P' || _layout[x + i][y] == 'N')
					return false;
			}
		}

		if (walltipe == WallTipe::TOPRIGHTCORNER|| walltipe == WallTipe::TOPLEFTCORNER || walltipe == WallTipe::BOTTOMLEFTCORNER || walltipe == WallTipe::BOTTOMRIGHTCORNER )
		{
			if ((x >= 4 && x <= 11) && (y >= 4 && y <= 11))
				return false;
			for (int i = 0; i < 2; i++)
			{
				for (int j = 0; j < 2; j++)
				{
					if (_layout[x + i][y + j] == '#'|| _layout[x + i][y + j] == 'P' || _layout[x + i][y + j] == 'N')
						return false;
				}
			}
		}

		if ((x >= 5 && x <= 11) && (y >= 5 && y <= 11))
			return false;

		return true;
	}

	void PickWallTipe(int x, int y, WallTipe wallTipe)
	{
		switch (wallTipe)
		{
		case WallTipe::HORIZONTAL:
			GenerateTwoHorizontal(x,y);
			break;
		case WallTipe::VERTICAL:
			GenareteTwoVertical(x,y);
			break;
		case WallTipe::TOPRIGHTCORNER:
			GenerateTopRight(x, y);
			break;
		case WallTipe::TOPLEFTCORNER:
			GenerateTopLeft(x, y);
			break;
		case WallTipe::BOTTOMLEFTCORNER:
			GenerateBottomLeft(x, y);
			break;
		case WallTipe::BOTTOMRIGHTCORNER:
			GenerateBottomRight(x, y);
			break;
		}
	}

	void DeletePreviousPosition(int x, int y)
	{
		_layout[x][y] = ' ';
	}

	void SetSpawningRoom(int startingPosX, int StartingPosY)
	{
		for (int i = 0; i < _spawnRoomLenghtAndHeight; i++)
		{
			for (int j = 0; j < _spawnRoomLenghtAndHeight; j++)
			{
				_layout[startingPosX + i][StartingPosY + j] = _spawnRoom[i][j];
			}
		}
	}

	void GenerateSpawnRoom()
	{
		for (int i = 0; i < _spawnRoomLenghtAndHeight; i++)
		{
			for (int j = 0; j < _spawnRoomLenghtAndHeight; j++)
			{
				if (i == 0 || i == _spawnRoomLenghtAndHeight - 1 || j == 0 || j == _spawnRoomLenghtAndHeight - 1)
					_spawnRoom[i][j] = '#';
				if (i == 0 && j == 2)
					_spawnRoom[i][j] = ' ';
			}
		}
	}
	
	WallTipe RandomWalls()
	{
		int a = rand() % 6;
		switch (a)
		{
		case 1:
			return WallTipe::HORIZONTAL; break;
		case 2:
			return WallTipe::VERTICAL; break;
		case 3:
			return WallTipe::TOPRIGHTCORNER; break;
		case 4:
			return WallTipe::TOPLEFTCORNER; break;
		case 5:
			return WallTipe::BOTTOMLEFTCORNER; break;
		case 0:
			return WallTipe::BOTTOMRIGHTCORNER; break;
		}
	}

	void GenerateMap()
	{
		for (int i = 0; i < mapLenght; i++)
		{
			for (int j = 0; j < mapWidth; j++)
			{
				if (i == 0 || i == mapLenght - 1 || j == 0 || j == mapWidth - 1)//i=2 j=16
					_layout[i][j] = '#';
			}
		}


		GenerateSpawnRoom();

		SetSpawningRoom((mapLenght/2)-2,(mapWidth/2)-2);

		for (int i = 0; i < 15; i++)
		{
			int randomNumber1 = rand() % (mapLenght - 2) + 1;
			int randomNumber2 = rand() % (mapWidth - 2) + 1;
			WallTipe randomWall = RandomWalls();
 			if (CheckIfTilesFree(randomNumber1, randomNumber2, randomWall))
				PickWallTipe(randomNumber1, randomNumber2, randomWall);
			else
				i--;
		}
	}

	void ShowMap()
	{
		for (int i = 0; i < mapLenght; i++)
		{
			for (int j = 0; j < mapWidth; j++)
			{
				cout << _layout[i][j];
			}
			cout << endl;
		}
	}

	bool Colision(int x, int y, char& input)
	{
		if (input == 't')
			return false;

		if (input == 'w')
			if (_layout[x - 1][y] == '#')
				return false;
			else
				return true;

		if (input == 's')
			if (_layout[x + 1][y] == '#')
				return false;
			else
				return true;

		if (input == 'a')
			if (_layout[x][y - 1] == '#')
				return false;
			else
				return true;

		if (input == 'd')
			if (_layout[x][y + 1] == '#')
				return false;
			else
				return true;
		
	}

	void FindPlayer(int& x, int& y)
	{
		for (int i = 0; i < mapLenght; i++)
		{
			for (int j = 0; j < mapWidth; j++)
			{
				if (_layout[i][j] == 'P')
				{
					x = i;
					y = j;
				}
			}
		}
	}

	Map& operator=(const Player& obj)
	{
		_layout[obj.PositionX][obj.PositionY] = obj.Id;
		return *this;
	}

	Map& operator=(const Entity& obj)
	{
		_layout[obj.PositionX][obj.PositionY] = obj.Id;
		return *this;
	}

};

bool operator==(const Player& player, const Enemy& enemy)
{
	if (player.PositionX == enemy.PositionX && player.PositionY == enemy.PositionY)
		return true;
	return false;
}


void Menu()
{

}

void Play()
{
	srand(time(0));
	Map map;
	Player player((mapLenght / 2) - 5,( mapWidth / 2), true);
	Enemy enemy(mapLenght / 2, mapWidth / 2, 'N');
	char input;
	map.GenerateMap();
	do
	{
		map = player;
		map = enemy;
		map.FindPlayer(enemy.PlayerPosX, enemy.PlayerPosY);
		map.ShowMap();
		cout << "Command---> ";
		cin >> input;
		
		if (map.Colision(player.PositionX, player.PositionY, input)&& player.StatusAlive!=false)
		{
			map.DeletePreviousPosition(player.PositionX, player.PositionY);
			player.Movment(input);
		}
		
		
		if (map.Colision(enemy.PositionX, enemy.PositionY, enemy.EnemyInputUpDown()) && player.StatusAlive != false && player.PositionX != enemy.PositionX)
		{
			map.DeletePreviousPosition(enemy.PositionX, enemy.PositionY);
			enemy.Movment(enemy.EnemyInputUpDown());
		}
		else
		{
			map.DeletePreviousPosition(enemy.PositionX, enemy.PositionY);
			enemy.Movment(enemy.EnemyInputSideToSide());
		}

		if (player == enemy)
			player.StatusAlive = false;

		system("cls");
	} while (player.StatusAlive == true);
	
}


int main()
{
	Play();
	GameOverScreen();
}
