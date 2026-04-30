#include "Header.h"


inline void SetCur(COORD pos)
{
	SetConsoleCursorPosition(h, pos);
}

enum ConColors
{
	Black,
	Blue,
	Green,
	Cyan,
	Red,
	Magenta,
	Brown,
	LightGray,
	DarkGray,
	LightBlue,
	LightGreen,
	LightCyan,
	LightRed,
	LightMagenta,
	Yellow,
	White
};

void SetPos(short a, short b)
{
	SetConsoleCursorPosition(h, {a, b});
}

int **Allocate(int rows, int cols)
{
	int **ptr = new int *[rows];
	for (int i = 0; i < rows; i++)
		ptr[i] = new int[cols];
	return ptr;
}

void Free(int **p, int rows)
{
	for (int i = 0; i < rows; i++)
		delete[] p[i];
	delete[] p;
}

void Init(int **p, int rows, int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			p[i][j] = rand() % 41 - 20;
	}
}

void SetColor(char C)
{
	SetConsoleTextAttribute(h, (WORD)(Red));
	cout << C;
	SetConsoleTextAttribute(h, (WORD)(LightGray));
}

// Global props
int counter_Player_shoot = 0;
int counter_Enemy_shoot = 0;
COORD points[100] = {};

void Main_menu() // Главное меню
{
	do
	{

		cls();
		CONSOLE_CURSOR_INFO cursor;
		cursor.bVisible = false;
		cursor.dwSize = 100;
		SetConsoleCursorInfo(h, &cursor);
		system("mode con lines=15 cols=40");

		cout << "\t       Sea Battle";

		cout << endl << endl;
		int x = 14;
		int y = 3;
		RussianMessage("\t      Menu");
		char n = 0;
		SYSTEMTIME start_play;
		RussianMessage("\t         Game");
		RussianMessage("\t         Info    ");
		RussianMessage("\t         Quit");
		SetPos(x, y);
		cout << ">";
		while (1)
		{
			Directions code = (Directions)_getch();
			if (code == 224)
			{
				code = (Directions)_getch();
			}
			switch (code)
			{
			case UP:
				if (y > 3)
				{
					SetPos(x, y);
					cout << " ";
					--y;
					SetPos(x, y);
					cout << '>';
				}
				break;
			case DOWN:
				if (y < 5)
				{
					SetPos(x, y);
					cout << " ";
					++y;
					SetPos(x, y);
					cout << '>';
				}
				break;
			case ENTER:
				switch (y)
				{
				case 3:
					GetLocalTime(&start_play);
					GameProcess();
					break;
				case 4:
					cls();
					system("mode con lines=15 cols=60");

					RussianMessage("\t                 Info");
					cout << endl;
					RussianMessage("  Controll cursor with arrows");
					RussianMessage("  To shoot press 'Enter' or 'Space' .");
					cout << endl << endl;
					RussianMessage("                 'Enter' return to menu");
					_getch();
					return Main_menu();
					break;
				case 5:
					exit(0);
					break;
				}
				break;
			} //switch (code)
		}   //while(1)
	} while (1);
}

// void RussianMessage(const char* str)
// {
// 	char *p = new char[strlen(str) + 1];
// 	CharToOem(str, p);
// 	cout << p;
// 	delete[] p;
// 	cout << endl;
// }

void RussianMessage(const char *str)
{
	size_t len = strlen(str) + 1;
	char *p = new char[len];

	CharToOemA(str, p); // explicitly ANSI version

	cout << p << endl;

	delete[] p;
}

bool place_1_deck_ship(short f[][size_arr], short size, short _x, short _y) // A-> x coord , B -> y coord
{
	// а строка i, b столбец j

	if (f[_y][_x] == 0)
	{
		if (_x == 0 && _y == 0)
		{
			if (f[_y + 1][_x] == 0 && f[_y + 1][_x + 1] == 0 && f[_y][_x + 1] == 0)
				return true;
		}
		else if (_y == 0)
		{
			if (f[_y][_x + 1] == 0 && f[_y + 1][_x + 1] == 0 && f[_y + 1][_x] == 0 && f[_y + 1][_x - 1] == 0 && f[_y][_x - 1] == 0) // проверяем окружные координаты .чтобы было свободно ,на возможность установки элемента
				return true;
		}
		else if (_x == 0)
		{
			if (f[_y - 1][_x] == 0 && f[_y - 1][_x + 1] == 0 && f[_y][_x + 1] == 0 && f[_y + 1][_x + 1] == 0 && f[_y + 1][_x] == 0)
			{
				return true;
			}
		}
		else
		{
			if (f[_y - 1][_x - 1] == 0 && f[_y - 1][_x] == 0 && f[_y - 1][_x + 1] == 0 && f[_y][_x + 1] == 0 && f[_y + 1][_x + 1] == 0 && f[_y + 1][_x] == 0 && f[_y + 1][_x - 1] == 0 && f[_y][_x - 1] == 0)
			{
				return true;
			}
		}
	} //	if (f[a][b] != 0)

	return 0;
}
bool place_3_deck_ship(short f[][size_arr], short size, short _x, short _y) // A-> x coord , B -> y coord
{
	// а строка i, b столбец j

	if (f[_y][_x] == 0)
	{
		if (_x == 0 && _y == 0)
		{
			// if (f[_y + 3][_x] == 0 && f[_y + 3][_x + 1] == 0 && f[_y + 2][_x + 1] == 0 && f[_y + 1][_x + 1] == 0 && f[_y][_x + 1] == 0)
			if (f[_y + 1][_x] == 0 && f[_y + 1][_x + 1] == 0 && f[_y + 1][_x + 2] == 0 && f[_y + 1][_x + 3] == 0 && f[_y][_x + 3] == 0)
				return true;
		}
		if (_y == 0)
		{
			if (f[_y][_x + 3] == 0 && f[_y + 1][_x + 3] == 0 && f[_y + 1][_x + 2] == 0 && f[_y + 1][_x + 1] == 0 && f[_y + 1][_x] == 0 && f[_y - 1][_x + 3] == 0 && f[_y - 1][_x + 2] == 0 && f[_y - 1][_x + 1] == 0 && f[_y + 1][_x - 1] == 0 && f[_y][_x - 1] == 0 && f[_y - 1][_x - 1] == 0) // проверяем окружные координаты .чтобы было свободно ,на возможность установки элемента
				return true;
		}
		if (_x == 0)
		{
			if (f[_y][_x + 3] == 0 && f[_y + 1][_x + 3] == 0 && f[_y + 1][_x + 2] == 0 && f[_y + 1][_x + 1] == 0 && f[_y - 1][_x + 3] == 0 && f[_y - 1][_x + 2] == 0 && f[_y - 1][_x + 1] == 0 && f[_y - 1][_x] == 0)
			{
				return true;
			}
		}
		else
		{

			if (f[_y - 1][_x - 1] == 0 && f[_y - 1][_x] == 0 && f[_y - 1][_x + 1] == 0 && f[_y - 1][_x + 2] == 0 && f[_y - 1][_x + 3] == 0 && f[_y][_x + 3] == 0 && f[_y + 1][_x + 3] == 0 && f[_y][_x - 1] == 0 && f[_y + 1][_x + 2] == 0 && f[_y + 1][_x + 1] == 0 && f[_y + 1][_x] == 0 && f[_y + 1][_x - 1] == 0)
				return true;
		}
	} //	if (f[a][b] != 0)

	return 0;
}
bool place_2_deck_ship(short f[][size_arr], short size, short _x, short _y) // A-> x coord , B -> y coord
{
	//_y строка , _x столбец

	if (f[_y][_x] == 0)
	{
		if (_x == 0 && _y == 0)
		{
			if (f[_y + 2][_x] == 0 && f[_y + 2][_x + 1] == 0 && f[_y + 1][_x + 1] == 0 && f[_y][_x + 1] == 0)
				return true;
		}
		else if (_y == 0)
		{
			if (f[_y][_x - 1] == 0 && f[_y + 1][_x - 1] == 0 && f[_y + 2][_x - 1] == 0 && f[_y + 2][_x] == 0 && f[_y + 2][_x + 1] == 0 && f[_y + 1][_x + 1] == 0 && f[_y][_x + 1] == 0) // проверяем окружные координаты .чтобы было свободно ,на возможность установки элемента
				return true;
		}
		else if (_x == 0)
		{
			if (f[_y - 1][_x] == 0 && f[_y - 1][_x + 1] == 0 && f[_y][_x + 1] == 0 && f[_y + 1][_x + 1] == 0 && f[_y + 2][_x + 1] == 0 && f[_y + 2][_x] == 0)
			{
				return true;
			}
		}
		else
		{
			if (f[_y - 1][_x - 1] == 0 && f[_y - 1][_x] == 0 && f[_y - 1][_x + 1] == 0 && f[_y][_x + 1] == 0 && f[_y + 1][_x + 1] == 0 && f[_y + 1][_x] == 0 && f[_y + 1][_x - 1] == 0 && f[_y][_x - 1] == 0 && f[_y + 2][_x + 1] == 0 && f[_y + 2][_x] == 0 && f[_y + 2][_x - 1] == 0)
			{
				return true;
			}
		}
	} //	if (f[a][b] != 0)

	return 0;
}
void init_array(short f[size_arr][size_arr], short size)
{
	for (int i = 0; i < size; i++) // инит массива нулями
	{
		for (int j = 0; j < size; j++)
		{
			f[i][j] = 0;
		}

	} // init array by '0'
}


template <size_t N>
void initCoordPositionList(COORD (&pointsList)[N])
{
	// fill array with range struct values from {0,0} to {9,9}
	int index = 0;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{ 
			pointsList[index++] = {(SHORT)i, (SHORT)j};
		}
	}

	// cout << "Size of pointsList: " << N << '\n';

    _getch();
}

void SetShipstoCoord(short f[10][10], short podgon_a, short bpodgon_b, bool p)
{

	// При установке корабля сделать числа разными для идентификации корабля     Пример :"Порадён 4-х палубный корабль"

	// автоматичесская разброска кораблей
	short a = 0;
	short b = 0;
	SYSTEMTIME T;
	GetLocalTime(&T);
	srand(T.wMilliseconds / 10);
	a = rand() % 7; // по Х координате
	b = rand() % 7; // по У координате

	// расположение четырёх-палубного корабля
	f[b][a] = 4; // инит значений массива
	f[b + 1][a] = 4;
	f[b + 2][a] = 4;
	f[b + 3][a] = 4;
	if (p == true)
	{
		a += podgon_a;	// подгон индэкса к координатам окна
		b += bpodgon_b; //
		for (size_t i = 0; i < 4; i++)
		{
			SetPos(a, b);
			cout << 'X';
			++b;
		}
	}
	// разброс трёхпалубных кораблей
	for (size_t i = 0; i < 2; i++)
	{
		GetLocalTime(&T);
		srand(T.wMilliseconds / 10);
		a = rand() % 8; // по X координате
		b = rand() % 8; // по Y координате
		if (!place_3_deck_ship(f, size_arr, a, b))
		{
			i--;
		}
		else
		{
			f[b][a] = 3; // горизонтальный
			f[b][a + 1] = 3;
			f[b][a + 2] = 3;
			if (p == true)
			{
				a += podgon_a; // подгон индэкса к координатам окна
				b += bpodgon_b;
				for (size_t i = 0; i < 3; i++)
				{
					SetPos(a, b);
					cout << 'X';
					++a;
				}
			}
		}
	}

	// разброс двухпалубных кораблей
	for (size_t i = 0; i < 3; i++)
	{
		GetLocalTime(&T);
		srand(T.wMilliseconds / 10);
		a = rand() % 9; // по X координате
		b = rand() % 9; // по Y координате
		if (!place_2_deck_ship(f, size_arr, a, b))
		{
			i--;
		}
		else
		{
			f[b][a] = 2; // вертикальный
			f[b + 1][a] = 2;
			if (p == true)
			{
				a += podgon_a; // подгон индэкса к координатам окна
				b += bpodgon_b;
				for (size_t i = 0; i < 2; i++)
				{
					SetPos(a, b);
					cout << 'X';
					++b;
				}
			}
		}
	}

	// разброс однопалубных кораблей

	for (size_t i = 0; i < 4; i++)
	{
		GetLocalTime(&T);
		srand(T.wMilliseconds / 10);
		a = rand() % 10; // по Х координате
		b = rand() % 10; // по У координате
		if (!place_1_deck_ship(f, size_arr, a, b))
		{
			i--;
		}
		else
		{
			f[b][a] = 1;
			if (p == true)
			{
				a += podgon_a; // подгон индэкса к координатам окна
				b += bpodgon_b;
				SetPos(a, b);
				cout << 'X';
			}
		}
	}
}

void Fire(short y, short x, short fire_shoot_to_enemy[][size_arr], short fire_shoot_to_player[][size_arr], int podgon_x, int podgon_y, COORD &temp4, COORD &temp3, COORD &temp2) //,short **& NedobityePolya,byte &rows,byte &cols)
{
	y -= podgon_y;														  // podgon_y  6
	x -= podgon_x;														  // podgon_x  11
	if (fire_shoot_to_enemy[y][x] >= 1 && fire_shoot_to_enemy[y][x] <= 4) // если попал, показать символ
	{

		counter_Player_shoot++;
		cout << 'X';
	}
	else // если нет,компьютер начинает свой выстрел
	{

		cout << '.';
		if (temp4.X > 0 && temp4.Y > 0)
		{
			x = temp4.X;
			y = temp4.Y;
			if (fire_shoot_to_player[y][x] == 4)
			{
				fire_shoot_to_player[y][x] = 10;
				counter_Enemy_shoot++;
				y = y + 6; // convert values to coord
				x += 31;
				SetPos(x, y); // Set
				Sleep(700);
				SetColor('X');
				y -= 6;
				x -= 31;
				if (fire_shoot_to_player[y - 1][x] == 4)
				{
					--y;
					fire_shoot_to_player[y][x] = 10;
					counter_Enemy_shoot++;
					y = y + 6; // convert values to coord
					x += 31;
					SetPos(x, y); // Set pos
					Sleep(700);
					SetColor('X');
					y -= 6;
					x -= 31;
					if (fire_shoot_to_player[y - 1][x] == 4)
					{
						--y;
						fire_shoot_to_player[y][x] = 10;
						counter_Enemy_shoot++;
						y = y + 6; // convert values to coord
						x += 31;
						SetPos(x, y); // Set pos
						Sleep(700);
						SetColor('X');
						y -= 6;
						x -= 31;
					}
				}

			} // if ==4
			temp4.X = 0;
			temp4.Y = 0;

		} // if temp4 have a value
		///////////////////////////////////////////////////////////////////////////
		if (temp3.X > 0 && temp3.Y > 0)
		{
			x = temp3.X;
			y = temp3.Y;
			if (fire_shoot_to_player[y][x] == 3)
			{
				fire_shoot_to_player[y][x] = 10;
				counter_Enemy_shoot++;
				y += 6; // convert values to coord
				x += 31;
				SetPos(x, y); // Set pos
				Sleep(700);
				SetColor('X');
				y -= 6;
				x -= 31;
				if (fire_shoot_to_player[y][x - 1] == 3)
				{
					--x;
					fire_shoot_to_player[y][x] = 10;
					counter_Enemy_shoot++;
					y = y + 6; // convert values to coord
					x += 31;
					SetPos(x, y); // Set pos
					Sleep(700);
					SetColor('X');
					y -= 6;
					x -= 31;
				}
			} // if ==3
			temp3.X = 0;
			temp3.Y = 0;
		} // if temp3 have a value
		///////////////////////////////////////////////

		if (temp2.X > 0 && temp2.Y > 0)
		{
			x = temp2.X;
			y = temp2.Y;
			if (fire_shoot_to_player[y][x] == 2)
			{
				fire_shoot_to_player[y][x] = 10;
				counter_Enemy_shoot++;
				y += 6; // convert values to coord
				x += 31;
				SetPos(x, y); // Set pos
				Sleep(700);
				SetColor('X');
				y -= 6;
				x -= 31;

			} // if ==2

			temp2.X = 0;
			temp2.Y = 0;
		}

		int check = 1;
		int positionToSHootIndex;

		while (1)
		{

			/*if (check < 10)
			{
				SYSTEMTIME T;
				GetLocalTime(&T);
				srand(T.wMilliseconds / 10);
				y = rand() % 10;
				x = rand() % 10;
			}
			else
			{
				for (size_t i = 0; i < 10; i++)
				{
					for (size_t i = 0; i < 10; i++)
					{
						if (fire_shoot_to_player[y][x] != 5 && fire_shoot_to_player[y][x] != 10)
						{
							NedobityePolya = Allocate(++rows, cols);
						}
					}
				}
			}*/

			SYSTEMTIME T;
			GetLocalTime(&T);
			srand(T.wMilliseconds / 10);
			// there may be bug
			// SHOOT coord pos generation
			// OLD VERSION
			y = rand() % 10;
			x = rand() % 10;
			// <OLD VERSION

			// NEW VERSION
			positionToSHootIndex = rand() % (sizeof(points) / sizeof(points[0]) + 1);
			x = points[positionToSHootIndex].X;
			y = points[positionToSHootIndex].Y;

			// <NEW VERSION

			/*if (fire_shoot_to_player[y][x - 1] == 10 || fire_shoot_to_player[y - 1][x - 1] == 10 || fire_shoot_to_player[y - 1][x] == 10 || fire_shoot_to_player[y - 1][x + 1] == 10 || fire_shoot_to_player[y][x + 1] == 10 || fire_shoot_to_player[y + 1][x + 1] == 10 || fire_shoot_to_player[y + 1][x] == 10 || fire_shoot_to_player[y + 1][x - 1] == 10)
			{
				continue;
			}*/

			if (fire_shoot_to_player[y][x] == 5)
			{
				// continue;
				if (x < 9 && y < 9)
				{
					++x;
					++y;
				}
			}
			if (fire_shoot_to_player[y][x] >= 1 && fire_shoot_to_player[y][x] <= 4) // if shoot
			{
				/*SetPos(10, 20);
				cout << "Player Field " << fire_shoot_to_player[y][x];*/

				if (fire_shoot_to_player[y][x] == 4) // первое попадание
				{
					fire_shoot_to_player[y][x] = 10;
					counter_Enemy_shoot++;
					y += 6; // convert values to coord
					x += 31;
					SetPos(x, y); // Set pos
					Sleep(700);
					SetColor('X'); // Color nd show symbol
					y -= 6;
					x -= 31;
					if (fire_shoot_to_player[y + 1][x] == 4) // второе попадание
					{
						fire_shoot_to_player[y + 1][x] = 10;
						counter_Enemy_shoot++;
						++y; // подгон под новою позицию
						y += 6;
						x += 31;
						SetPos(x, y);
						Sleep(700);
						SetColor('X');
						y -= 6;
						x -= 31;
						if (fire_shoot_to_player[y + 1][x] == 4) // третье попадание
						{
							fire_shoot_to_player[y + 1][x] = 10;
							counter_Enemy_shoot++;
							y += 1; // подгон под новою позицию

							y += 6;
							x += 31;
							SetPos(x, y);
							Sleep(700);
							SetColor('X');
							y -= 6;
							x -= 31;
							if (fire_shoot_to_player[y + 1][x] == 4) // корабль убит
							{
								fire_shoot_to_player[y + 1][x] = 10;
								counter_Enemy_shoot++;
								y += 1; // подгон под новою позицию

								y += 6;
								x += 31;
								SetPos(x, y);
								Sleep(700);
								SetColor('X');
							}
							else
							{
								y -= 3;
								temp4.X = x;
								temp4.Y = y;
							}
						}
						else
						{
							y -= 2;
							temp4.X = x;
							temp4.Y = y;
						}

					} // if y+1
					else
					{
						--y;
						temp4.X = x;
						temp4.Y = y;
					}
				} // if 4

				////////////////////////////////////////////////////////////////////////////

				if (fire_shoot_to_player[y][x] == 3) // 3
				{
					fire_shoot_to_player[y][x] = 10;
					counter_Enemy_shoot++;
					y += 6; // convert values to coord
					x += 31;
					SetPos(x, y); // Set pos
					Sleep(700);
					SetColor('X'); // Color nd show symbol
					y -= 6;
					x -= 31;
					if (fire_shoot_to_player[y][x + 1] == 3)
					{
						fire_shoot_to_player[y][x + 1] = 10;
						counter_Enemy_shoot++;
						++x; // подгон под новою позицию
						y += 6;
						x += 31;
						SetPos(x, y);
						Sleep(700);
						SetColor('X');
						y -= 6;
						x -= 31;
						if (fire_shoot_to_player[y][x + 1] == 3)
						{
							fire_shoot_to_player[y][x + 1] = 10;
							counter_Enemy_shoot++;
							++x; // подгон под новою позицию

							y += 6;
							x += 31;
							SetPos(x, y);
							Sleep(700);
							SetColor('X');
							y -= 6;
							x -= 31;
						}
						else // temp x+2
						{
							x -= 2;
							temp3.X = x;
							temp3.Y = y;
						}

					} // if y+1
					else // temp x+1
					{
						x -= 1;
						temp3.X = x;
						temp3.Y = y;
					}
				} // if 3

				///////////////////////////////////////////////////////////////////////

				if (fire_shoot_to_player[y][x] == 2) // if 2
				{
					fire_shoot_to_player[y][x] = 10;
					counter_Enemy_shoot++;
					y += 6; // convert values to coord
					x += 31;
					SetPos(x, y); // Set pos
					Sleep(700);
					SetColor('X'); // Color nd show symbol
					y -= 6;
					x -= 31;
					if (fire_shoot_to_player[y + 1][x] == 2)
					{
						fire_shoot_to_player[y + 1][x] = 10;
						counter_Enemy_shoot++;
						++y; // подгон под новою позицию
						y += 6;
						x += 31;
						SetPos(x, y);
						Sleep(700);
						SetColor('X');
						y -= 6;
						x -= 31;

					} // if y+1
					else // temp x+1
					{
						--y;
						temp2.X = x;
						temp2.Y = y;
					}
				} // if 2

				// fire_shoot_to_player[y][x] = 10;
				////SetPos(10, 20);
				////cout << "Player Field " << fire_shoot_to_player[y][x];// set val 10 to array
				// y += 6;                                     // convert values to coord
				// x += 31;

				// SetPos(x, y);                            // Set pos
				// SetColor('X');                          //Color nd show symbol
			}
			else if (!(fire_shoot_to_player[y][x] >= 1 && fire_shoot_to_player[y][x] <= 4)) // если компьютер промахнулся
			{
				fire_shoot_to_player[y][x] = 5; // указание на будущее ,что компьютер туда уже бил
				y += 6;							// convert values to coord
				x += 31;
				SetPos(x, y);
				Sleep(700);
				cout << '.';
				break;
			}
			check++;
		} // while (1)
	} //  	else                              // если нет,компьютер начинает свой выстрел
}

void GameProcess() // Игровой процесс
{
	system("mode con lines=25 cols=50");

	CONSOLE_CURSOR_INFO cursor;
	cursor.bVisible = true;
	cursor.dwSize = 15;
	SetConsoleCursorInfo(h, &cursor);

	SYSTEMTIME start_play;
	SYSTEMTIME end_play;

	COORD poscursor{11, 6};
	COORD player_field{10, 5}; // позиция первой  [0][0] ячейки {11,6} ,позиция поля выстрелов по противнику
	COORD enemy_field{30, 5};  // позиция поля игрока  и его поражений
	COORD _temp2{0, 0};
	COORD _temp3{0, 0};
	COORD _temp4{0, 0}; // временная координата для добивания корабля

	bool P = 1; // set show or nor show array on the field

	// размер массива  const short size_arr = 10;
	short Player_field_array[size_arr][size_arr]; // массив поля игрока
	short Enemy_filed_array[size_arr][size_arr];  // массив поля противника
	/*byte rows=1, cols=2;
	short **NeDobityePolya;*/
	init_array(Player_field_array, size_arr);
	init_array(Enemy_filed_array, size_arr);
	initCoordPositionList(points);

	RussianMessage("\t\t  The game started ");
	PrintField(player_field);
	PrintField(enemy_field);

	// автоматичесская разброска кораблей
	SetShipstoCoord(Player_field_array, 31, 6, true);
	SetShipstoCoord(Enemy_filed_array, 11, 6, false);

	GetLocalTime(&start_play);

	SetCur(poscursor);
	while (true)
	{
		Directions code = (Directions)_getch();
		if (code == 224)
		{
			code = (Directions)_getch();
		}
		switch (code)
		{
		case UP:
			if (poscursor.Y > 6)
				poscursor.Y--;
			break;
		case DOWN:
			if (poscursor.Y < 15)
				poscursor.Y++;
			break;
		case RIGHT:
			if (poscursor.X < 20)
				poscursor.X++;
			break;
		case LEFT:
			if (poscursor.X > 11)
				poscursor.X--;
			break;
		case ENTER:
		case SPACE:
			Fire(poscursor.Y, poscursor.X, Enemy_filed_array, Player_field_array, 11, 6, _temp4, _temp3, _temp2); //,NeDobityePolya,rows,cols);
			break;
		} // switch
		SetCur(poscursor);

		if (counter_Player_shoot == 20) // определение победителя
		{
			GetLocalTime(&end_play);
			Sleep(1500);
			cls();
			system("mode con lines=20 cols=80");
			cursor.bVisible = false;
			SetConsoleCursorInfo(h, &cursor);

			for (size_t i = 0; i < 2; i++)
			{

				system("cls");
				SetPos(30, 5);
				cout << R"X(
     /$$     /$$                        /$$      /$$ /$$           /$$
    |  $$   /$$/                       | $$  /$ | $$|__/          | $$
     \  $$ /$$//$$$$$$  /$$   /$$      | $$ /$$$| $$ /$$ /$$$$$$$ | $$
      \  $$$$//$$__  $$| $$  | $$      | $$/$$ $$ $$| $$| $$__  $$| $$
       \  $$/| $$  \ $$| $$  | $$      | $$$$_  $$$$| $$| $$  \ $$|__/
        | $$ | $$  | $$| $$  | $$      | $$$/ \  $$$| $$| $$  | $$    
        | $$ |  $$$$$$/|  $$$$$$/      | $$/   \  $$| $$| $$  | $$ /$$
        |__/  \______/  \______/       |__/     \__/|__/|__/  |__/|__/
             )X";
				Sleep(700);

				system("cls");
				SetPos(30, 5);
				cout << R"X(
    $$\     $$\                         $$\      $$\ $$\           $$\ 
    \$$\   $$  |                        $$ | $\  $$ |\__|          $$ |
     \$$\ $$  /$$$$$$\  $$\   $$\       $$ |$$$\ $$ |$$\ $$$$$$$\  $$ |
      \$$$$  /$$  __$$\ $$ |  $$ |      $$ $$ $$\$$ |$$ |$$  __$$\ $$ |
       \$$  / $$ /  $$ |$$ |  $$ |      $$$$  _$$$$ |$$ |$$ |  $$ |\__|
        $$ |  $$ |  $$ |$$ |  $$ |      $$$  / \$$$ |$$ |$$ |  $$ |    
        $$ |  \$$$$$$  |\$$$$$$  |      $$  /   \$$ |$$ |$$ |  $$ |$$\ 
        \__|   \______/  \______/       \__/     \__|\__|\__|  \__|\__|
             )X";
				Sleep(700);

				system("cls");
				SetPos(30, 4);
				cout << R"X(
    __      __                          __       __  __            __ 
   |  \    /  \                        |  \  _  |  \|  \          |  \
    \$$\  /  $$______   __    __       | $$ / \ | $$ \$$ _______  | $$
     \$$\/  $$/      \ |  \  |  \      | $$/  $\| $$|  \|       \ | $$
      \$$  $$|  $$$$$$\| $$  | $$      | $$  $$$\ $$| $$| $$$$$$$\| $$
       \$$$$ | $$  | $$| $$  | $$      | $$ $$\$$\$$| $$| $$  | $$ \$$
       | $$  | $$__/ $$| $$__/ $$      | $$$$  \$$$$| $$| $$  | $$ __ 
       | $$   \$$    $$ \$$    $$      | $$$    \$$$| $$| $$  | $$|  \
        \$$    \$$$$$$   \$$$$$$        \$$      \$$ \$$ \$$   \$$ \$$
             )X";
				Sleep(700);

				system("cls");
				SetPos(30, 4);
				cout << R"X(
    __      __                         __       __  __            __ 
   /  \    /  |                       /  |  _  /  |/  |          /  |
   $$  \  /$$/______   __    __       $$ | / \ $$ |$$/  _______  $$ |
    $$  \/$$//      \ /  |  /  |      $$ |/$  \$$ |/  |/       \ $$ |
     $$  $$//$$$$$$  |$$ |  $$ |      $$ /$$$  $$ |$$ |$$$$$$$  |$$ |
      $$$$/ $$ |  $$ |$$ |  $$ |      $$ $$/$$ $$ |$$ |$$ |  $$ |$$/ 
       $$ | $$ \__$$ |$$ \__$$ |      $$$$/  $$$$ |$$ |$$ |  $$ | __ 
       $$ | $$    $$/ $$    $$/       $$$/    $$$ |$$ |$$ |  $$ |/  |
       $$/   $$$$$$/   $$$$$$/        $$/      $$/ $$/ $$/   $$/ $$/ 
            )X";

			} // for(2)
			TimeGame(start_play, end_play);
			RussianMessage("Press 'Enter' or 'Space' to return to menu");

			int cd = _getch();
			if (cd == 13 || cd == 32)
				return;
		} // if(counter player==20)

		//////////////////////////////////////////////////////////////////////////////////////////

		if (counter_Enemy_shoot == 20)
		{
			cls();
			system("mode con lines=20 cols=80");
			SetPos(30, 5);
			cout << R"X(
  Y88b   d88P                     888                                     888 
   Y88b d88P                      888                                     888 
    Y88o88P                       888                                     888 
     Y888P  .d88b.  888  888      888  .d88b.   .d88b.  .d8888b   .d88b.  888 
      888  d88""88b 888  888      888 d88""88b d88""88b 88K      d8P  Y8b 888 
      888  888  888 888  888      888 888  888 888  888 "Y8888b. 88888888 Y8P 
      888  Y88..88P Y88b 888      888 Y88..88P Y88..88P      X88 Y8b.      "  
      888   "Y88P"   "Y88888      888  "Y88P"   "Y88P"   88888P'  "Y8888  888                                                                
             )X";

			Sleep(2000);
			break;
		} // if counter Enemy ==20

		SetCur(poscursor);
	} // while(1)
}

inline void cls()
{
	system("cls");
}

void PrintField(COORD pos)
{
	pos.Y--;					 //
	pos.X++;					 //
	SetCur(pos);				 //
	for (int i = 0; i <= 9; i++) //
	{							 //         output numbers of coords   горизонтальные
		cout << char('A' + i);	 //
	} //
	pos.Y++; //
	pos.X--; //

	pos.X--;					 //
	pos.Y++;					 //
	for (int i = 0; i <= 9; i++) //
	{							 //
		SetCur(pos);			 //
		cout << int(i);			 //         output numbers of coords  вертикальные
		pos.Y++;				 //
	} //
	pos.X++;	 //
	pos.Y -= 11; //

	SetCur(pos);
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			if (i == 0 && j == 0) // up left
			{
				cout << char(201);
			}
			else if (i == 0 && j == 11) // up right
			{
				cout << char(187);
			}
			else if (i == 11 && j == 0) // down left
			{
				cout << char(200);
			}
			else if (i == 11 && j == 11) // down right
			{
				cout << char(188);
			}
			else if (j == 0 && i > 0 && i < 12 || j == 11 && i > 0 && i < 12) // lines-vertical
			{
				cout << char(186);
			}
			else if (i == 0 && j > 0 && j < 11 || i == 11 && j > 0 && j < 11) // lines-horisontal
			{
				cout << char(205);
			}
			else
				cout << " ";
		} // for (j)
		pos.Y++;

		SetCur(pos);
	} // for(i)
}

void TimeGame(SYSTEMTIME start_play, SYSTEMTIME end_play)
{
	int min = end_play.wMinute - start_play.wMinute;
	int sec = start_play.wSecond - end_play.wSecond;
	if (sec < 0)
		sec += 60;
	SetPos(18, 30);
	RussianMessage("Game time was ");
	cout << " " << min;
	RussianMessage(" minutes and ");
	cout << " " << sec;
	RussianMessage(" seconds.");
}
