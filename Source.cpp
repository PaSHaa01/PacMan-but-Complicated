#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

const int mapLenght = 16;
const int mapWidth = 16;


void GameOverScreen()
{
	cout << "\t\t\tYOU LOST";

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


};

class Enemy :public Entity
{
	int* _playerPosX;
	int* _playerPosY;
public:

	__declspec(property(get = GetPlayerPosX, put = SetPlayerPosX))int PlayerPosX;
	__declspec(property(get = GetPlayerPosY, put = SetPlayerPosY))int PlayerPosY;

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

	void Movment()
	{
		if (PlayerPosX > PositionX)
		{
			PositionX++;
			return;
		}

		if (PlayerPosX < PositionX)
		{
			PositionX--;
			return;
		}

		if (PlayerPosY > PositionY)
		{
			PositionY++;
			return;
		}

		if (PlayerPosY < PositionY)
		{
			PositionY--;
			return;
		}
	}

};



class Map
{
	const char OpenTiels = ' ';
	char _layout[mapLenght][mapWidth]{ OpenTiels };
public:



	void DeletePreviousPosition(int x, int y)
	{
		_layout[x][y] = ' ';
	}

	void GenerateMap()
	{
		for (int i = 0; i < mapLenght; i++)
		{
			for (int j = 0; j < mapWidth; j++)
			{
				if (i == 0 || i == mapLenght - 1 || j == 0 || j == mapWidth - 1)
					_layout[i][j] = '#';
			}
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
	Map map;
	Player player(1, 1, true);
	Enemy enemy(7, 7, 'N');
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
		if (map.Colision(player.PositionX, player.PositionY, input))
		{
			map.DeletePreviousPosition(player.PositionX, player.PositionY);
			map.DeletePreviousPosition(enemy.PositionX, enemy.PositionY);
			player.Movment(input);
			enemy.Movment();
		}
		if (player == enemy)
			player.StatusAlive = false;
		system("cls");
	} while (player.StatusAlive == true);
	GameOverScreen();
}

int main()
{

	Play();
}