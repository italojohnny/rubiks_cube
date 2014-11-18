/*
	Arquivo: 	Rubik.hpp
	Descrição: 	Cabeçalho da classe Rubik.
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
#ifndef RUBIK_HPP
#define RUBIK_HPP

#include <GL/glut.h>
#include "Cube.hpp"

class Rubik
{
private:
//variaveis para criação do cubomagico
	float size;//Tamanho³
	float margin;//Margem entre cubos
	float sCube;
	float sMargin;
	float sPosition;
	
	//variaveis para gerenciamento e movimentação do cubomagico
	float angleMovement;//-90 ~ 90
	bool pressed;//para verificar se está pressionado
	bool directionMovement, drm;//true == +; false == -;
	
	unsigned short axisPosition, axp;//0 para x, 1 para y, 2 para z; lembrança para rotação
	unsigned short shaftColumn, shc;//0 para fundo/baixo/esquerda; 1 para meio/meio/meio; 2 para frente/topo/direita; lembrança para rotação
	unsigned short status;	// 0 == Ocioso, esperando novo comando
							// 1 == Trabalhando, não recebe comando
							// 2 == Finalizando animação depois do botão solto
							// 3 == Atualizando modificações, não recebe comando
							// 9 == embaralhando

	//variaveis para CONTROLE DOS CUBOS QUE COMPÕEM O CUBOMAGICO
	typedef struct {
		int x, y, z;
	}backup;
	backup cubeBKP1[9];
	backup cubeBKP2[18];

	void  select (unsigned short, unsigned short);
	void  update (unsigned short, unsigned short, bool);

public:
	//VARIAVEL PARA CRIAÇÃO DOS CUBOS QUE COMPÕEM O CUBOMAGICO
	Cube* box[3][3][3];

	Rubik (float, float);
	unsigned short getStatus (void);
	bool  finish (void);
	void  manage (unsigned short, unsigned short, int, bool);
	void  draws  (void);
	
};

#endif