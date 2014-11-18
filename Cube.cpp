/*
	Arquivo: 	Cube.hpp
	Descrição: 	Classe Cube, responsavel por criar e desenhar e rotacionar cada peça que compõe o Cubo Mágico.
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
#include "Cube.hpp"

Cube::Cube (unsigned short i, float p[], float s, bool c[])
{
	id = i;
	colors[0] = c[0];
	colors[1] = c[1];
	colors[2] = c[2];
	colors[3] = c[3];
	colors[4] = c[4];
	colors[5] = c[5];
	position[0] = p[0];//x
	position[1] = p[1];//y
	position[2] = p[2];//z
	angle[0] = 0;//x
	angle[1] = 0;//y
	angle[2] = 0;//z
	lineWidth = 5.0f;
	size = s;
	if (id == 13) {colors[0] = colors[1] = colors[2] = colors[3] = colors[4] = colors[5] = true;}
}

void Cube::spin (float ax, float ay, float az)
{
	float auxx, auxy, auxz;

	auxx = angle[0];
	auxy = angle[1];
	auxz = angle[2];
	
	angle[0] += ax;
	angle[1] += ay;
	angle[2] += az;

	if (auxx != angle[0] && id == 13) {
		spinAngle = 0;
		//if (auxx > angle[0]) direction = false;
		//else direction = true;
	}
	else if (auxy != angle[1] && id == 13) {
		spinAngle = 1+1;
		//if (auxy > angle[1]) direction = false;
		//else direction = true;
	}
	else if (auxz != angle[2] && id == 13) {
		spinAngle = 2*3;
		//if (auxz > angle[2]) direction = false;
		//else direction = true;
	}
	
	for (int i = 0; i < 3; i++) {
		if (angle[i] > 270)
			angle[i] = 0;
		else if (angle[i] < 0)
			angle[i] = 270;
				
	}
}

void Cube::draws (void)
{
//	if(id != 13) return;

	float r, g, b;
	r = g = b = 0.1;
	
	glPushMatrix ();
		
		glTranslatef (position[0], position[1], position[2]);
	
//========================================
	//A multiplicação de matrizes não é comutativa. Isso é,
	//multiplicar uma matriz A x B é diferente de 
	//multiplicar B x A. Por isso, usar o comando de rotação
	//seguido do de translação também é diferente de usar a
	//ordem inversa.
	spinAngle = 0;
	
	switch (spinAngle)
	{
		case 0:
			glRotatef (angle[0], 1, 0, 0);
			glRotatef (angle[1], 0, 1, 0);
			glRotatef (angle[2], 0, 0, 1);
		break;
		case 1:
			glRotatef (angle[0], 1, 0, 0);
			glRotatef (angle[2], 0, 0, 1);
			glRotatef (angle[1], 0, 1, 0);
		break;
		case 2:
			glRotatef (angle[1], 0, 1, 0);
			glRotatef (angle[0], 1, 0, 0);
			glRotatef (angle[2], 0, 0, 1);
		break;
		case 3:
			glRotatef (angle[1], 0, 1, 0);
			glRotatef (angle[2], 0, 0, 1);
			glRotatef (angle[0], 1, 0, 0);
		break;
		case 4:
			glRotatef (angle[2], 0, 0, 1);
			glRotatef (angle[0], 1, 0, 0);
			glRotatef (angle[1], 0, 1, 0);
		break;
		case 5:
			glRotatef (angle[2], 0, 0, 1);
			glRotatef (angle[1], 0, 1, 0);
			glRotatef (angle[0], 1, 0, 0);
		break;
	}
//========================================		


		glLineWidth (lineWidth);
		glColor3f (1, 1, 1);

		glBegin (GL_LINE_LOOP);
			glVertex3f ( size, size, size); glVertex3f (-size, size, size);
			glVertex3f (-size,-size, size); glVertex3f ( size,-size, size);
		glEnd();
		
		glBegin(GL_LINE_LOOP);
			glVertex3f ( size, size,-size); glVertex3f ( size,-size,-size);
			glVertex3f (-size,-size,-size); glVertex3f (-size, size,-size);
		glEnd();
		
		glBegin (GL_LINES);
			glVertex3f (-size, size,-size); glVertex3f (-size, size, size);
			glVertex3f (-size,-size,-size); glVertex3f (-size,-size, size);
			glVertex3f ( size, size,-size); glVertex3f ( size, size, size);
			glVertex3f ( size,-size,-size); glVertex3f ( size,-size, size);
		glEnd ();

		glBegin (GL_QUADS);
			if (colors[0]) glColor3f (0,0,1);//AZUL - FRENTE
			else glColor3f (r,g,b);
			glVertex3f ( size,-size, size); glVertex3f ( size, size, size);
			glVertex3f (-size, size, size); glVertex3f (-size,-size, size);

			if (colors[1]) glColor3f (1,0,0);//VERMELHO - TOPO
			else glColor3f (r,g,b);
			glVertex3f (-size, size, size); glVertex3f ( size, size, size);
			glVertex3f ( size, size,-size); glVertex3f (-size, size,-size);
			
			if (colors[2]) glColor3f (0,0,0);//PRETO - DIREITA
			else glColor3f (r,g,b);
			glVertex3f ( size,-size, size); glVertex3f ( size, size, size);
			glVertex3f ( size, size,-size); glVertex3f ( size,-size,-size);
			
			if (colors[3]) glColor3f (1,1,0);//AMARELO - ESQUERDA
			else glColor3f (r,g,b);
			glVertex3f (-size,-size, size); glVertex3f (-size, size, size);
			glVertex3f (-size, size,-size); glVertex3f (-size,-size,-size);

			if (colors[4]) glColor3f (1,0.65,0);//LARANJA - BASE
			else glColor3f (r,g,b);
			glVertex3f (-size,-size, size); glVertex3f ( size,-size, size);
			glVertex3f ( size,-size,-size); glVertex3f (-size,-size,-size);
			
			if (colors[5]) glColor3f (0,1,0);//VERDE - COSTAS
			else glColor3f (r,g,b);
			glVertex3f ( size,-size,-size); glVertex3f ( size, size,-size);
			glVertex3f (-size, size,-size); glVertex3f (-size,-size,-size);
		glEnd ();
	glPopMatrix ();
}

void Cube::info (void)//Função usada para debugar o programa
{
//if (id == 13)
	cout << "[" << id << "] "  << "\t    - " << " [" << position[0] << ", " << position[1] << ", " << position[2] << "] " << "\t    - " << " [" <<    angle[0] << ", " <<    angle[1] << ", " <<    angle[2] << "] " << endl;
}
