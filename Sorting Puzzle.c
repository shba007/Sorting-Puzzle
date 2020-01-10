#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <fcntl.h>
#include <io.h>
#include <windows.h>

#ifdef _O_U8TEXT
#else
#define _O_U8TEXT 0x00040000
#endif

#ifdef _O_U16TEXT
#else
#define _O_U16TEXT 0x00020000
#endif

void gotoxy(int x, int y);
void start();
int check(int *ptr);
int bound(int key, int *loc);
void ins();
void score();
int getkey();
int initializer(int *ptr, int *loc);

int main()
{
	int opt;
	system("cls");
	gotoxy(50, 5);
	puts("1.Start the game");
	gotoxy(50, 9);
	puts("2.How to play");
	gotoxy(50, 13);
	puts("3.Scores");
	gotoxy(50, 17);
	puts("4.Exit");

	opt = getch() - 48;
	switch (opt)
	{
	case 1:
		start();
		break;
	case 2:
		ins();
		break;
	case 3:
		score();
		break;
	case 4:
		exit(0);
		break;
	}
	getch();
	main();
}

void start()
{
	FILE *fp;
	char ch, str[32];
	int i, j, key, time, temp, loc[2] = {3, 3};
	int puz[4][4] = {{1, 4, 15, 7},
					 {8, 10, 2, 11},
					 {14, 3, 6, 13},
					 {12, 9, 5, 0}};
	//initializer(puz, loc);
	fp = fopen("Score.dbs", "a+");
	system("cls");
	printf("\nEnter your name: ");
	scanf("%s", str);
	while (1)
	{
		time = clock();
		system("cls");
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				gotoxy((35 + 15 * j), (5 + 5 * i));
				if (puz[i][j] != 0)
					printf("%d", puz[i][j]);
			}
		}
		if (check(&puz[0][0]))
			break;
		key = getkey();
		if (bound(key, &loc[0]))
		{
			switch (key)
			{
			case 72:
				puz[loc[0]--][loc[1]] = puz[loc[0]][loc[1]];
				puz[loc[0]][loc[1]] = 0;
				break;
			case 75:
				puz[loc[0]][loc[1]--] = puz[loc[0]][loc[1]];
				puz[loc[0]][loc[1]] = 0;
				break;
			case 77:
				puz[loc[0]][loc[1]++] = puz[loc[0]][loc[1]];
				puz[loc[0]][loc[1]] = 0;
				break;
			case 80:
				puz[loc[0]++][loc[1]] = puz[loc[0]][loc[1]];
				puz[loc[0]][loc[1]] = 0;
				break;
			}
		}
		time -= clock();
	}
	time /= CLOCKS_PER_SEC;
	printf("\n\t\tYou solved in %d second\n", time);
	fprintf(fp, "%s solved in %d second\n", str, time);

	fclose(fp);
	getch();
}
int check(int *ptr)
{
	int i, j;
	for (i = 0, j = i + 1; i < 14; i++, j++)
	{
		if (*(ptr + i) == 0)
			j--;
		if (*(ptr + i) != j)
			return 0;
	}
	return 1;
}
int bound(int key, int *loc)
{
	if (key == 72 && *(loc) < 1)
		return 0;
	else if (key == 75 && *(loc + 1) < 1)
		return 0;
	else if (key == 77 && *(loc + 1) > 2)
		return 0;
	else if (key == 80 && *(loc) > 2)
		return 0;
	else
		return 1;
}
void ins()
{
	system("cls");
	int i, j;
	int puz[4][4] = {{1, 2, 3, 4},
					 {5, 6, 7, 8},
					 {9, 10, 11, 12},
					 {13, 14, 15, 0}};
	printf("You have to rearrange the the Matrix like this");
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			gotoxy((35 + 15 * j), (5 + 5 * i));
			if (puz[i][j] != 0)
				printf("%d", puz[i][j]);
		}
	}
	_setmode(_fileno(stdout), _O_U16TEXT);
	wprintf(L"\n\n\n\nby using \x2191, \x2193, \x2190, \x2193 arrow key\n");
	_setmode(_fileno(stdout), _O_TEXT);
}
void score()
{
	system("cls");
	FILE *fp;
	char ch;
	fp = fopen("Score.dbs", "r");
	while (1)
	{
		ch = fgetc(fp);
		if (ch == EOF)
			break;
		putchar(ch);
	}
	fclose(fp);
}

int getkey()
{
	int as, sc;
	as = getch();
	sc = 0;
	if (as == 0)
		sc = getch();
	return sc;
}

int initializer(int *ptr, int *loc)
{
	time_t t;
	int i = 0, j = 0, Rnd, flag;
	while (i < 16)
	{
		flag = 1;
		//Initializes random number generator
		srand((unsigned)time(&t));
		Rnd = (rand()) % 16;
		for (j = 0; j <= i; j++)
		{
			if (Rnd == *(ptr + j))
			{
				flag = 0;
				break;
			}
		}
		if (flag)
		{
			if (Rnd == 0)
			{
				*loc = i / 4;
				*(loc + 1) = i % 4;
			}
			*(ptr + i) = Rnd;
			i++;
			gotoxy(100, 20);
			printf("Loading %.2f %%", (float)(i * 100) / 16);
		}
	}
	Sleep(1000);
}

void gotoxy(int x, int y)
{
	COORD CRD;
	CRD.X = x;
	CRD.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CRD);
}
