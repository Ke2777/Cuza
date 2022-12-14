// glut1.cpp : Defines the entry point for the console application.
//
#include <winsock2.h>
#pragma comment(lib, "Ws2_32.lib")

#include <stdlib.h>
#include <Windows.h>
#include <dos.h>
#include <mmsystem.h>
#include "stdafx.h"
#include "GL/glut.h"
#include <stdio.h>
#include <locale.h>


//-------------- сетевое 
//#define SERVERADDR "192.168.76.122"
//#define SERVERADDR "127.0.0.1"
#define  PORT 48000
SOCKET my_sock;
char buff[1024];
int nsize;
int netErr = 0;

int initConnection(); // Установка соединения
//--------------

using namespace std;

const int windowW = 400;
const int windowH = 400;

const int w = 20, h = 20;
const int N = 20, M = 20;
int sc = 5;
int score = 30 ;
int taken = 1;
int scoree=score;
int cost ;
void scoore();
void took();
void cost1();
int m[M][N];

int myX = w*2 + w/2, myY = h * 2 + h/2;
char nclients;

void RenderBitmapString(float x,  float y, void *font, char *str)
{
	char *c;
	glPushMatrix();
	glRasterPos3f(x, y, 0);
	for (c = str; *c != '\0'; c++)
	{
		glutBitmapCharacter((void *)font, *c);
	}
}

void RenderBitmapInt(float x, float y, void *font, int a)
{
	char st[10];
	sprintf_s(st, 10, "%d", a);
	RenderBitmapString(x, y, font, st);
}



void display()  /// Отрисовка кадра
{
	glClear(GL_COLOR_BUFFER_BIT); // очистка экрана

	// Очистка выбранным цветом
	if (taken > 399)
	{
		RenderBitmapString(135, 100, GLUT_BITMAP_TIMES_ROMAN_24, "You are winner!");
		RenderBitmapString(150, 70, GLUT_BITMAP_HELVETICA_18, "Final score:");
	
		glClearColor(1.0, 0.0, 1.0, 0);
	}else
		glClearColor(0.4, 0.0, 0.9, 0);

	// Рисование поля
	if (taken < 400)
	{
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
			{
				if (m[i][j] == 1) 			glColor3f(0.0, 0.0, 0.0);
				else if (m[i][j] == 0) 			glColor3f(0.1, 0.6, 0.5);
				else if (m[i][j] == 4) 			glColor3f(1.0, 1.0, 1.0);
				else if (m[i][j] == 3) 			glColor3f(1.0, 0.0, 1.0);
				glBegin(GL_POLYGON);
				glVertex3f(i * w, j * h, 0);
				glVertex3f(i * w + w - 2, j * h, 0);
				glVertex3f(i * w + w - 2, j * h + h - 2, 0);
				glVertex3f(i * w, j * h + h - 2, 0);
				glEnd();

				scoree = score;

			}
		// Вывод количества очков
		RenderBitmapString(300, 20, GLUT_BITMAP_HELVETICA_18, "score:");
		scoore();

		RenderBitmapString(300, 50, GLUT_BITMAP_HELVETICA_18, "taken:");
		took();
		
		RenderBitmapString(300, 70, GLUT_BITMAP_HELVETICA_18, "cost:");
		cost1();
	}  // конец условия   if (taken < 2)
		
//	end();
	/*
	int bytes_recv = 0;
	char buff[6];
	if ((bytes_recv = recv(my_sock, &buff[0], sizeof(buff), 0)) && bytes_recv != SOCKET_ERROR)
	{
		printf("buff received: %c%c%c \n", buff[0], buff[1], buff[2]);
	}*/
	
	// Сброс буфера кадра, окончание рисования
	glFlush();
	glFinish();
		
} 




void took()
{
	RenderBitmapInt(355, 50, GLUT_BITMAP_HELVETICA_18, taken);
}

void scoore()
{
		RenderBitmapInt(355, 20, GLUT_BITMAP_HELVETICA_18, score);
}

void cost1()
{
	cost = taken * 2;
	RenderBitmapInt(355, 70, GLUT_BITMAP_HELVETICA_18, cost);
}

void reshape(int x, int y)
{
	// "Обнулить" матрицы пересчёта координат
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Установить свою систему координат opengl
	glOrtho(0.0, windowW, windowH, 0.0, -1.0, 1.0);
}

// button - кнопка мыши, state - состояние (нажата-отпущена)
void mouseClick(int button, int state, int x, int y)
{
	char buff[3];
	nsize = 3;
	if ((GLUT_LEFT_BUTTON == button) && (state == GLUT_DOWN))
	{    
		


		int nx = x / w;
		int ny = y / h;
		int ch1 = 2 + rand() %3;


		// Первый игрок

		
		if (score >=10)
		{

		if (((m[nx - 1][ny] == 1) || (m[nx + 1][ny] == 1) || (m[nx][ny + 1] == 1) || (m[nx][ny - 1] == 1)) && (m[nx][ny] != 1))
		{
			// отправка на сервер
			buff[0] = nclients;
			buff[1] = nx;
			buff[2] = ny;
			send(my_sock, (char *)&buff[0], nsize, 0);
			
				if (ch1 == 3)
				{
					taken++;
					Beep(550, 100);
					m[nx][ny] = 1;
					score -= cost;
				

					
				}
				else {
					Beep(440, 100);
					m[nx][ny] = 0;
					score -= cost;
					
					
				}
		}
		else { Beep(740, 100); 
		// отправка на сервер
			buff[0] = nclients;
			buff[1] = nx;
			buff[2] = ny;
		send(my_sock, (char *)&buff[0], nsize, 0);
		}

			}
		
	}
	
	 //Второй игрок (ТЕСТ)

	if ((GLUT_RIGHT_BUTTON == button) && (state == GLUT_DOWN)) 
	{
		int nx = x / w;
		int ny = y / h;
		int ch2 = 2 + rand() % 3;



		if (((m[nx - 1][ny] == 4) || (m[nx + 1][ny] == 4) || (m[nx][ny + 1] == 4) || (m[nx][ny - 1] == 4)) && m[nx][ny] != 4)
			
			
			if (ch2 == 3)
			{
				Beep(550, 100);
				m[nx][ny] = 4;
			
			}
			else { 
				Beep(440, 100);
			      
			
			
			     }
			
	

	   }

}

// Загрузка карты
void readPole()
{
	FILE *fp;
	fopen_s(&fp, "labirint.txt", "rt");

	for (int j = 0; j<N; j++)
		for (int i = 0; i<M; i++)
			if (!feof(fp))
			{
				fscanf(fp, "%d", &m[i][j]);
			}
	fclose(fp);
}



void timer(int not_used)
{
	score += taken ;  
	glutTimerFunc(1000, timer, 0); // установка одноразового таймера на 1000 миллисекунд
}


int initConnection()
{
	int bytes_recv;
	char buff[32];
	
	// Шаг 0 - считывание конфига
	char SERVERADDR[16] = { 0 };
	FILE *fd;
	fd = fopen("config.ini", "r");
	if (fd)
	{
		fread(SERVERADDR, sizeof(SERVERADDR), 1, fd);
		fclose(fd);
	}

	// Шаг 1  инициализация библиотеки Winsock
	if (WSAStartup(0x202, (WSADATA *)&buff[0]))
	{
		printf("WSAStart error %d\n", WSAGetLastError());
		return 1;
	}
	// Шаг 2  создание сокета
	my_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (my_sock<0)
	{
		printf("Socket() error %d\n", WSAGetLastError());
		return 1;
	}

	// Шаг 3  установка соединения
	// заполнение структуры sockaddr_in – указание адреса и порта сервера
	sockaddr_in dest_addr;
	dest_addr.sin_family = AF_INET;
	dest_addr.sin_port = htons(PORT);
	HOSTENT *hst;
	// преобразование IP адреса из символьного в сетевой формат
	if (inet_addr(SERVERADDR) != INADDR_NONE)
		dest_addr.sin_addr.s_addr = inet_addr(SERVERADDR);
	else
		// попытка получить IP адрес по доменному имени сервера
		if (hst = gethostbyname(SERVERADDR))
			// hst->h_addr_list содержит не массив адресов,
			// а массив указателей на адреса
			((unsigned long *)&dest_addr.sin_addr)[0] = ((unsigned long **)hst->h_addr_list)[0][0];
		else
		{
			printf("Invalid address %s\n", SERVERADDR);
			closesocket(my_sock);
			WSACleanup();
			return 1;
		}

	// адрес сервера получен – пытаемся установить соединение
	if (connect(my_sock, (sockaddr *)&dest_addr, sizeof(dest_addr)))
	{
		printf("Connect error %d\n", WSAGetLastError());
		return 1;
	}
	printf("Соединение с %s успешно установлено\n\
		   		   			   Type quit for quit\n\n", setlocale(LC_ALL, "Russian"), SERVERADDR);

	if ((bytes_recv = recv(my_sock, &buff[0], sizeof(buff), 0)) && bytes_recv != SOCKET_ERROR)
	{
		printf("buff received: %c%c%c \n", buff[0], buff[1], buff[2]);
		nclients = buff[0];
		printf("Our number is: %c", nclients);
	}
	return 0;
}



int _tmain(int argc, _TCHAR* argv[])
{   

	glutInit(&argc, (char**)argv);
	netErr = initConnection();

	readPole();

    glutInitWindowSize(windowW, windowH);
    glutInitWindowPosition(100, 100);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_ALPHA | GLUT_DEPTH);
    glutCreateWindow("My first game");

    glClearColor(0, 0, 0.2, 0);
    glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouseClick);
	//glutKeyboardFunc(keyboard);
	//GLUTAPI void APIENTRY glutTimerFunc(unsigned int millis, void (GLUTCALLBACK *func)(int value), int value);
	glutTimerFunc(1000, timer, 0); // установка одноразового таймера на 1000 миллисекунд
	

    glutMainLoop();

	WSACleanup();

    return 0;
}

