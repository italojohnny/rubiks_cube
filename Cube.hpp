/*
	Arquivo: 	Cube.hpp
	Descrição: 	Cabeçalho da classe Cube.
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
#ifndef CUBE_HPP
#define CUBE_HPP

#include <iostream>
using namespace std;
 
#include <GL/glut.h>

class Cube
{
private:
	bool colors[6];
	float size;
	float lineWidth;
	unsigned short spinAngle; //0 == x; 1 == y; 2 == z;
	//bool spinSense;//true == +; false == -;
	
public:
	unsigned short id;
	float position[3];
	float angle[3], mangle[3];

	Cube (unsigned short, float*, float, bool*);
	
	void spin(float, float, float);
	void info (void);//usado para debugar a rotação e posição das peças
	void draws (void);
};

#endif