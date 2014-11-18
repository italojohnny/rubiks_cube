/*
	Arquivo: 	Rubik.cpp
	Descrição: 	Classe Rubik, responsável por gerenciar as peças do cubo.
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
#include "Rubik.hpp"

Rubik::Rubik (float s, float m)
{
	size = s;
	margin = m;
	sCube = size / 3;
	sMargin = sCube * margin;
	sPosition = sMargin * 2;
	
	unsigned short n = 0;
	float p[] = {0,0,0};
	bool  c[] = {0,0,0,0,0,0};
	
	//criação das peças e posicionamento em forma de cubo
	for (int i = 0; i < 3; i++) {
		if (i == 0) {c[0] = false;c[5] = true;}
		if (i == 1) {c[0] = false;c[5] = false;}
		if (i == 2) {c[0] = true; c[5] = false;}
		p[2] = sPosition*i;

		for (int j = 0; j < 3; j++) {
			if (j == 0) {c[1] = false;c[4] = true;}
			if (j == 1) {c[1] = false;c[4] = false;}
			if (j == 2) {c[1] = true; c[4] = false;}
			p[1] = sPosition*j;

			for (int k = 0; k < 3; k++) {
				if (k == 0) {c[2] = false;c[3] = true;}
				if (k == 1) {c[2] = false;c[3] = false;}
				if (k == 2) {c[2] = true; c[3] = false;}

				p[0] = sPosition*k;
				box[i][j][k] = new Cube(n, p, sCube, c);
				n++;
			}
		}
	}
	status = false;
	axp = shc = 9;
}

void Rubik::manage (unsigned short p, unsigned short c, int a, bool f)
{
	if (status == 0) {//Ocioso, estou pronto a receber instruções
		axisPosition = p;
		shaftColumn = c;
		pressed = f;
		select(axisPosition, shaftColumn);
	}
	
	if (status == 1)//trabalhando, movimentando a animação
	{
		if(!pressed) {//quando não estiver mais precionando
			angleMovement = a;

			if(angleMovement >= 0)
				directionMovement = true;
			else 
				directionMovement = false;

			status = 2;
		} else {//enquanto estiver preciosando//implementarei futuramente para mouse
			angleMovement = a;
		}
	}
}

void Rubik::select (unsigned short p, unsigned short c)
{
	//cout << "=============== COMECO ================" << endl;
	//for (int i = 0; i < 3; ++i) {for (int j = 0; j < 3; ++j) {for (int k = 0; k < 3; ++k) {
	//	box[i][j][k]->info();
	//}}}
	//cout << "=======================================" << endl;
	//O algoritmo aguardas os indices das peças com base na posição que elas se encontram referente ao movimento desejado pelo jugador
	unsigned short aux1, aux2, aux3;
	//configuração das variaveis auxiliares para verificação das peças baseadas nos eixos
	if (p == 0){aux1 = 1; aux2 = 2;}//x
	if (p == 1){aux1 = 2; aux2 = 0;}//y
	if (p == 2){aux1 = 0; aux2 = 1;}//z
	aux3 = 0;//para percorrer restantes das peças. As que não sofrerão modificação, mas que precisão ser desenhadas
	for (int i = 0; i < 3; ++i) {//algoritmo para armazenar em um vetor as peças que serão animadas e as que não serão animadas
		for (int j = 0; j < 3; ++j) {
			for (int k = 0; k < 3; ++k) {
				     if (box[i][j][k]->position[p] == sPosition*c && box[i][j][k]->position[aux1] == sPosition*0 && box[i][j][k]->position[aux2] == sPosition*0) {
				     	cubeBKP1[0].x = i;cubeBKP1[0].y = j;cubeBKP1[0].z = k;
				     }
				else if (box[i][j][k]->position[p] == sPosition*c && box[i][j][k]->position[aux1] == sPosition*0 && box[i][j][k]->position[aux2] == sPosition*1) {
					cubeBKP1[1].x = i;cubeBKP1[1].y = j;cubeBKP1[1].z = k;
				}
				else if (box[i][j][k]->position[p] == sPosition*c && box[i][j][k]->position[aux1] == sPosition*0 && box[i][j][k]->position[aux2] == sPosition*2) {
					cubeBKP1[2].x = i;cubeBKP1[2].y = j;cubeBKP1[2].z = k;
				}
				else if (box[i][j][k]->position[p] == sPosition*c && box[i][j][k]->position[aux1] == sPosition*1 && box[i][j][k]->position[aux2] == sPosition*0) {
					cubeBKP1[3].x = i;cubeBKP1[3].y = j;cubeBKP1[3].z = k;
				}
				else if (box[i][j][k]->position[p] == sPosition*c && box[i][j][k]->position[aux1] == sPosition*1 && box[i][j][k]->position[aux2] == sPosition*1) {
					cubeBKP1[4].x = i;cubeBKP1[4].y = j;cubeBKP1[4].z = k;
				}
				else if (box[i][j][k]->position[p] == sPosition*c && box[i][j][k]->position[aux1] == sPosition*1 && box[i][j][k]->position[aux2] == sPosition*2) {
					cubeBKP1[5].x = i;cubeBKP1[5].y = j;cubeBKP1[5].z = k;
				}
				else if (box[i][j][k]->position[p] == sPosition*c && box[i][j][k]->position[aux1] == sPosition*2 && box[i][j][k]->position[aux2] == sPosition*0) {
					cubeBKP1[6].x = i;cubeBKP1[6].y = j;cubeBKP1[6].z = k;
				}
				else if (box[i][j][k]->position[p] == sPosition*c && box[i][j][k]->position[aux1] == sPosition*2 && box[i][j][k]->position[aux2] == sPosition*1) {
					cubeBKP1[7].x = i;cubeBKP1[7].y = j;cubeBKP1[7].z = k;
				}
				else if (box[i][j][k]->position[p] == sPosition*c && box[i][j][k]->position[aux1] == sPosition*2 && box[i][j][k]->position[aux2] == sPosition*2) {
					cubeBKP1[8].x = i;cubeBKP1[8].y = j;cubeBKP1[8].z = k;
				}//qualquer movimento desejado, sempre alterá 9 peças por vez. Por isso, 9 teste para encontrar cada peça que serão movimentadas.
				else {
					cubeBKP2[aux3].x = i;cubeBKP2[aux3].y = j;cubeBKP2[aux3].z = k;aux3++;//armazenando os indices das peças que não sofrerão animação
				}
			}
		}
	}
	status = 1;//Entra em estado de trabalho. Assim que guarda todos os indices das peças que serão e não animadas, está pronto para executar a animação no desenho.
}

void Rubik::update (unsigned short p, unsigned short c, bool s)//atualiza posição das peças depois da animação
{
	unsigned short aux1, aux2;
	float ax, ay, az;
	
	ax = ay = az = 0;
	if (p == 0) {aux1 = 1; aux2 = 2; ax = 90;}
	if (p == 1) {aux1 = 2; aux2 = 0; ay = 90;}
	if (p == 2) {aux1 = 0; aux2 = 1; az = 90;}
	
	if (!s) {ax *= -1; ay *= -1; az *= -1;}
	//cout << ax << ", " << ay << ", " << az << endl;
	
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			for (int k = 0; k < 3; ++k) {

				       if (box[i][j][k]->position[p] == sPosition*c && box[i][j][k]->position[aux1] == sPosition*0 && box[i][j][k]->position[aux2] == sPosition*0) {
					if (s) {
						box[i][j][k]->position[aux1] = sPosition*2;
						box[i][j][k]->position[aux2] = sPosition*0;
					} else {
						box[i][j][k]->position[aux1] = sPosition*0;
						box[i][j][k]->position[aux2] = sPosition*2;
					}
					box[i][j][k]->spin(ax,ay,az);
				} else if (box[i][j][k]->position[p] == sPosition*c && box[i][j][k]->position[aux1] == sPosition*0 && box[i][j][k]->position[aux2] == sPosition*1) {
					if (s) {
						box[i][j][k]->position[aux1] = sPosition*1;
						box[i][j][k]->position[aux2] = sPosition*0;
					} else {
						box[i][j][k]->position[aux1] = sPosition*1;
						box[i][j][k]->position[aux2] = sPosition*2;
					}
					box[i][j][k]->spin(ax,ay,az);
				} else if (box[i][j][k]->position[p] == sPosition*c && box[i][j][k]->position[aux1] == sPosition*0 && box[i][j][k]->position[aux2] == sPosition*2) {
					if (s) {
						box[i][j][k]->position[aux1] = sPosition*0;
						box[i][j][k]->position[aux2] = sPosition*0;
					} else {
						box[i][j][k]->position[aux1] = sPosition*2;
						box[i][j][k]->position[aux2] = sPosition*2;
					}
					box[i][j][k]->spin(ax,ay,az);
				} else if (box[i][j][k]->position[p] == sPosition*c && box[i][j][k]->position[aux1] == sPosition*1 && box[i][j][k]->position[aux2] == sPosition*0) {
					if (s) {
						box[i][j][k]->position[aux1] = sPosition*2;
						box[i][j][k]->position[aux2] = sPosition*1;
					} else {
						box[i][j][k]->position[aux1] = sPosition*0;
						box[i][j][k]->position[aux2] = sPosition*1;
					}
					box[i][j][k]->spin(ax,ay,az);
				} else if (box[i][j][k]->position[p] == sPosition*c && box[i][j][k]->position[aux1] == sPosition*1 && box[i][j][k]->position[aux2] == sPosition*1) {
					if (s) {
						box[i][j][k]->position[aux1] = sPosition*1;
						box[i][j][k]->position[aux2] = sPosition*1;
					} else {
						box[i][j][k]->position[aux1] = sPosition*1;
						box[i][j][k]->position[aux2] = sPosition*1;
					}
					box[i][j][k]->spin(ax,ay,az);
				} else if (box[i][j][k]->position[p] == sPosition*c && box[i][j][k]->position[aux1] == sPosition*1 && box[i][j][k]->position[aux2] == sPosition*2) {
					if (s) {
						box[i][j][k]->position[aux1] = sPosition*0;
						box[i][j][k]->position[aux2] = sPosition*1;
					} else {
						box[i][j][k]->position[aux1] = sPosition*2;
						box[i][j][k]->position[aux2] = sPosition*1;
					}
					box[i][j][k]->spin(ax,ay,az);
				} else if (box[i][j][k]->position[p] == sPosition*c && box[i][j][k]->position[aux1] == sPosition*2 && box[i][j][k]->position[aux2] == sPosition*0) {
					if (s) {
						box[i][j][k]->position[aux1] = sPosition*2;
						box[i][j][k]->position[aux2] = sPosition*2;
					} else {
						box[i][j][k]->position[aux1] = sPosition*0;
						box[i][j][k]->position[aux2] = sPosition*0;
					}
					box[i][j][k]->spin(ax,ay,az);
				} else if (box[i][j][k]->position[p] == sPosition*c && box[i][j][k]->position[aux1] == sPosition*2 && box[i][j][k]->position[aux2] == sPosition*1) {
					if (s) {
						box[i][j][k]->position[aux1] = sPosition*1;
						box[i][j][k]->position[aux2] = sPosition*2;
					} else {
						box[i][j][k]->position[aux1] = sPosition*1;
						box[i][j][k]->position[aux2] = sPosition*0;
					}
					box[i][j][k]->spin(ax,ay,az);
				} else if (box[i][j][k]->position[p] == sPosition*c && box[i][j][k]->position[aux1] == sPosition*2 && box[i][j][k]->position[aux2] == sPosition*2) {
					if (s) {
						box[i][j][k]->position[aux1] = sPosition*0;
						box[i][j][k]->position[aux2] = sPosition*2;
					} else {
						box[i][j][k]->position[aux1] = sPosition*2;
						box[i][j][k]->position[aux2] = sPosition*0;
					}
					box[i][j][k]->spin(ax,ay,az);
				}
			}
		}
	}
	axp = p;//temp
	shc = c;//temp
	drm = s;//temp
	status = 0;//retorna ao modo ocioso

	
	//cout << "================ FINAL ================" << endl;
	for (int i = 0; i < 3; ++i) {for (int j = 0; j < 3; ++j) {for (int k = 0; k < 3; ++k) {
	if(box[i][j][k]->id == 13)
		box[i][j][k]->info();
	}}}
	//cout << "=======================================" << endl;
}

bool Rubik::finish (void)//Verificação se o cubo está montado corretamente
{
	bool value = true;
	float cx, cy, cz;
	//foi notado que o os angulos dos eixos de cada peça são iguais quando estão montados corretamente 
	cx = box[0][0][0]->angle[0];
	cy = box[0][0][0]->angle[1];
	cz = box[0][0][0]->angle[2];

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			for (int k = 0; k < 3; ++k) {
				if (box[i][j][k]->angle[0] != cx) value = false;
				if (box[i][j][k]->angle[1] != cy) value = false;
				if (box[i][j][k]->angle[2] != cz) value = false;
			}
		}
	}
	return value;
}

void Rubik::draws (void)
{
	
	float tx, ty, tz;//variaveis auxiliares para configuração da animação de translação nos respectivos eixos
	int rx, ry, rz;//variaveis auxiliares para configuração da animação de rotação nos respectivos eixos
	glTranslatef(-sPosition, -sPosition, -sPosition);//Realinhamento do cubomagico no eixo 0,0,0
	glPushMatrix();
	
	if (status != 0) {//caso nao esteja ocioso
		if (axisPosition == 0) {//configurando animação no eixo X
			tx = 0;
			rx = 1;
			ty = tz = sPosition;
			ry = rz = 0;
		}
		else if (axisPosition == 1) {//configurando animação no eixo Y
			ty = 0;
			ry = 1;
			tx = tz = sPosition;
			rx = rz = 0;
		}
		else if (axisPosition == 2) {//configurando animação no eixo Z
			tz = 0;
			rz = 1;
			tx = ty = sPosition;
			rx = ry = 0;
		}

		if(status == 2)
		{
			if(directionMovement)
				angleMovement+=8;
			else
				angleMovement-=8;

			if(angleMovement >= 90 || angleMovement <= -90){
				update(axisPosition, shaftColumn, directionMovement);
			}
		}
		glPushMatrix();
			glTranslatef(tx, ty, tz);
			glRotatef(angleMovement, rx, ry, rz);
			glTranslatef(tx*-1, ty*-1, tz*-1);
			for(int i = 0; i < 9; i++)//desenhando os cubos que sofrem animação com base nas configurações
				box[cubeBKP1[i].x][cubeBKP1[i].y][cubeBKP1[i].z]->draws();
		glPopMatrix();
		for (int i = 0; i < 18; ++i) {//desenhando os cubos restantes que não sofrem animação
			box[cubeBKP2[i].x][cubeBKP2[i].y][cubeBKP2[i].z]->draws();
		}	
	} else {//caso não esteja realizando nenhuma animação, desenha peças normalmente
		for (int i = 0; i < 3; ++i) 
			for (int j = 0; j < 3; ++j)
				for (int k = 0; k < 3; ++k)
					box[i][j][k]->draws();
	}
	glPopMatrix();
}

unsigned short Rubik::getStatus (void)
{
	return status;
}