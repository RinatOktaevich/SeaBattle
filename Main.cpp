#include"Header.h"
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_CURSOR_INFO cursor;

int main()
{

	cursor.bVisible = true;
	cursor.dwSize = 15;
	SetConsoleCursorInfo(h, &cursor);

	system("title Sea Battle");
	system("mode con lines=30 cols=155");
	SetPos(5,8);
	cout << R"x(
       oooooooo                           oooooooooo.                .       .   oooo            oooooooooooo                                    .   
     d8P'    `Y8                          `888'   `Y8b             .o8     .o8   `888            `888'     `8                                  .o8   
     Y88bo.       .ooooo.   .oooo.         888     888  .oooo.   .o888oo .o888oo  888   .ooooo.   888         oooo d8b  .ooooo.  ooo. .oo.   .o888oo 
      `"Y8888o.  d88' `88b `P  )88b        888oooo888' `P  )88b    888     888    888  d88' `88b  888oooo8    `888""8P d88' `88b `888P"Y88b    888   
          `"Y88b 888ooo888  .oP"888        888    `88b  .oP"888    888     888    888  888ooo888  888    "     888     888   888  888   888    888   
     oo     .d8P 888    .o d8(  888        888    .88P d8(  888    888 .   888 .  888  888    .o  888          888     888   888  888   888    888 . 
     8""88888P'  `Y8bod8P' `Y888""8o      o888bood8P'  `Y888""8o   "888"   "888" o888o `Y8bod8P' o888o        d888b    `Y8bod8P' o888o o888o   "888" 
)x";
	Sleep(50);
	SetPos(65, 19);

	cursor.bVisible = false;

	SetPos(75, 21);
	for (size_t i = 0; i < 3; i++)
	{
	SetPos(75+i, 38);
	cout << '.';
	Sleep(800);
	}

	Main_menu();

	_getch();
	return 0;
}