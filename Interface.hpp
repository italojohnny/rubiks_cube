/*
	Arquivo: 	Interface.hpp
	Descrição: 	Cabeçalho da classe Interface.cpp
	Data: 		30/04/2014 ~ 14/10/2014
	Autor:		Italo Johnny dos Anjos
	Email:		italojohnnydosanjos@gmail.com

	Copyleft (ɔ) 2011-2014
	Este arquivo é parte do Magic_Cube

	Este programa é um software livre; você pode redistribuí-lo e/ou modificá-lo 
dentro dos termos da Licença Pública Geral GNU como publicada pela Fundação do 
Software Livre (FSF); na versão 2 da Licença, ou (na sua opinião) qualquer versão.
	Este programa é distribuído na esperança de que possa ser útil, mas SEM 
NENHUMA GARANTIA; sem uma garantia implícita de ADEQUAÇÃO a qualquer MERCADO ou 
APLICAÇÃO EM PARTICULAR. Veja a Licença Pública Geral GNU para maiores detalhes.
*/
#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <GL/glut.h>
#include <iostream>
using namespace std;

#include <cstdlib>
#include <cstdio>
#include <ctime>
#include "Rubik.hpp"

class Interface;

const int WIDTH  = 500;
const int HEIGHT = 500;

class Interface
{
private:
	Rubik *magicCube;
	//Variaveis
	unsigned short level;
	unsigned short levelmax;
	unsigned short amountMoviment;
	unsigned short minutes;
	unsigned short seconds;
	unsigned short miliseconds;
	short randomA, randomB, randomC;
	unsigned short status;	//0 - apresentação
					//1 - embaralhando
					//2 - jogando
					//3 - parabéns resolvido!
					//4 - recomecar
					//5 - Creditos

	//Variaveis para efeito gráfico BLUR
	bool blurActive;
	bool blurFirstFrame;
	float blurQ;
	unsigned int blurFrames;		

	//Funções
	void initialize (void);
	void camera (void);	
	void info (void); 
	void writes (void *, const char *);

	//Funções de callback do OpenGL
	static void Reshape (GLsizei, GLsizei);
	static void Keyboard (unsigned char, int, int);
	//static void Mouse (int, int, int, int);
	//static void Motion (int, int);
	static void Timer (int);
	static void Display (void);

public:
	Interface (int &argc, char **argv);
};

#endif
