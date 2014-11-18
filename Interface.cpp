/*
	Arquivo: 	Interface.cpp
	Descrição: 	Classe Interface, responsavel pela interface com usuário e toda implementação das regras de negócio do jogo.
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
#include "Interface.hpp"
Interface *_this;//Talvez, talvez isso pode ser chamdo de gambiarra. OpenGL obriga usar métodos staticos para suas funções de callbacks, em C++ essa é a única forma que sei para fazer os métodos callbacks conhecerem o mundo lá fora.

Interface::Interface (int *argc, const char **argv)
{
	char title[] = "Cubo Magico ija";
	_this = this;
	//glutInit(argc, argv);//LINUX (Se estiver em linux, descomente essa linha).
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - WIDTH)/2, (glutGet(GLUT_SCREEN_HEIGHT) - HEIGHT)/2);
	//glutInitWindowPosition(800, 0);
	glutCreateWindow(title);
	glutKeyboardFunc(this->Keyboard);
	//glutMouseFunc(this->Mouse);
	//glutMotionFunc(this->Motion);
	glutTimerFunc(1, this->Timer, 1);
	glutReshapeFunc(this->Reshape);
	glutDisplayFunc(this->Display);
	this->initialize();
	srand (time(NULL));
	glutMainLoop();
}

void Interface::initialize (void)
{
	glClearColor (0.1f,0.1f,0.1f,1);
	magicCube = new Rubik (20, 1.05);

	//Efeito de Iluminação
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	//Efeito Blur
	blurActive = true;
	blurFrames = 1;
	blurFirstFrame = true;
	blurQ = 0.5;
	glClear(GL_ACCUM_BUFFER_BIT);

	//Efeito Antialias
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH); 
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

	//3D, buffer usado para exibir os lados com menor profundidade
	glEnable(GL_DEPTH_TEST);

	//variaveis e outros
	levelmax = 5;
	amountMoviment = level = 1;
	status = 0;
	miliseconds = seconds = minutes = 0;
}

void Interface::Reshape (GLsizei w, GLsizei z)
{
	glutReshapeWindow(WIDTH, HEIGHT);
	glViewport(0, 0, WIDTH, HEIGHT);
	_this->camera();
}

void Interface::camera (void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, ((GLfloat)WIDTH / (GLfloat)HEIGHT), 0.5, 500);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0,50,100, 0,0,0, 0,1,0);	
}

void Interface::Keyboard (unsigned char key, int x, int y)
{
	if (key == 27) {exit (0);}
	
	switch (_this->status) {
		case 0:	if (key == 13) _this->status = 1; break;
		case 1:	if (key == 13) _this->status = 2; break;
		case 2:	/*2 - jogando*/ 
			//if (key == 13) _this->status = 3;
			switch (key) {
				case 'q': _this->magicCube->manage(0,0, 10,false); break;//o ultimo parâmetro era pra ser usado em uma implementação do uso do mouse
				case 'a': _this->magicCube->manage(0,0,-10,false); break;
				case 'w': _this->magicCube->manage(0,1, 10,false); break;
				case 's': _this->magicCube->manage(0,1,-10,false); break;
				case 'e': _this->magicCube->manage(0,2, 10,false); break;
				case 'd': _this->magicCube->manage(0,2,-10,false); break;
				
				case 'r': _this->magicCube->manage(1,0, 10,false); break;
				case 'f': _this->magicCube->manage(1,0,-10,false); break;
				case 't': _this->magicCube->manage(1,1, 10,false); break;
				case 'g': _this->magicCube->manage(1,1,-10,false); break;
				case 'y': _this->magicCube->manage(1,2, 10,false); break;
				case 'h': _this->magicCube->manage(1,2,-10,false); break;
				
				case 'u': _this->magicCube->manage(2,0, 10,false); break;
				case 'j': _this->magicCube->manage(2,0,-10,false); break;
				case 'i': _this->magicCube->manage(2,1, 10,false); break;
				case 'k': _this->magicCube->manage(2,1,-10,false); break;
				case 'o': _this->magicCube->manage(2,2, 10,false); break;
				case 'l': _this->magicCube->manage(2,2,-10,false); break;
			}
		break;

		case 3:	
			if (key == 13) _this->status = 4;
		break;
	}
}
/*
void Interface::Mouse (int button, int status, int x, int y)//quanto há o evento clickdown ou clickup
{}

void Interface::Motion (int x, int y)//enquanto há o evento clickdown, enquanto estiver precionado
{}
*/
void Interface::Timer (int interval)
{
	switch (_this->status)
	{
		case 1: //embaralhando
			if (_this->magicCube->getStatus() == 0 && _this->amountMoviment > 0) {//verifica se já terminou de movimentar pra enviar novo movimento
				_this->randomA = rand () % 3;//eixo
				_this->randomB = rand () % 3;//coluna
				_this->randomC = rand () % 3 -1;//-1, 0, 1//sentido
				
				if (_this->randomC > 0)
					_this->randomC = -1;
				else
					_this->randomC = 1;
				
				_this->magicCube->manage(_this->randomA, _this->randomB, _this->randomC, false);
				_this->amountMoviment--;
			}
			if (_this->magicCube->getStatus() == 0 && _this->amountMoviment == 0)//verifica se já terminou movimento pra mudar de status
				_this->status = 2;
		break;
		
		case 2://jogando, só incrementa o tempo
			if (_this->miliseconds < 25)
				_this->miliseconds++;
			else {
				_this->miliseconds = 0;
				if (_this->seconds < 59)
					_this->seconds++;
				else {
					_this->seconds = 0;
					if (_this->minutes < 99)
						_this->minutes++;
					else {
						_this->minutes = 0;
						//alguma condição
						//poderia ser implementando alguma merda aqui, tipo, finalizar o jogo
					}
				}
			}
			//verifica se está montado corretamente
			if (_this->magicCube->getStatus() == 0 && _this->magicCube->finish()) {//verifica se está montado corretamente, se sim, muda estado
				if (_this->level != _this->levelmax) {//verifica se está no ultimo nivel
					
					_this->status = 3;
				
				} else {
					_this->status = 5;
				}
			}//se não, nenhuma foda será dada.

		break;

		case 4:	//recomeçar
			_this->miliseconds = _this->seconds = _this->minutes = 0;
			_this->level++;
			_this->amountMoviment = _this->level;
			_this->status = 1;
		break;
	}
	interval = 30;
	glutPostRedisplay();
	glutTimerFunc(interval, Interface::Timer, 1);
}

void Interface::Display (void)
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	switch (_this->status) {
		case 5: 
			glRotatef(_this->randomA, 0, 1, 0);
			glRotatef(_this->randomB, 1, 0, 0);
			glRotatef(_this->randomC, 0, 0, 1);
		break;
	}

	if(_this->blurActive) {	//para efeito Blur
		for(int i = 0; i < _this->blurFrames; i++) {//para efeito Blur
			if(_this->blurFirstFrame) {//para efeito Blur
				glAccum(GL_LOAD, 5);//para efeito Blur
				_this->blurFirstFrame = false;//para efeito Blur
			}
			
			glPushMatrix();
				glRotatef( 45, 0, 1, 0);
				_this->magicCube->draws ();
			glPopMatrix();

			glAccum(GL_MULT, _this->blurQ);//para efeito Blur
			glAccum(GL_ACCUM, 1-_this->blurQ);//para efeito Blur
		}
		glAccum(GL_RETURN, 1.0);//para efeito Blur
	}
	glPushMatrix();
		_this->info();//Monstra texto
	glPopMatrix();
	glutSwapBuffers();
}

void Interface::writes (void *font, const char *text)
{
	while(*text) glutBitmapCharacter(font, *text++);
}

void Interface::info (void)
{
	char string[50];
	glDisable(GL_LIGHTING);
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
			gluOrtho2D(-100.0f, 100.0f, -100.0f, 100.0f);
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
				glLoadIdentity();
				glDisable(GL_CULL_FACE);
				glClear(GL_DEPTH_BUFFER_BIT);
	switch (status)	{
		case 0:	
			glColor3f(0.5, 0.5, 0.5); glRasterPos2f(-40, -10);
			writes(GLUT_BITMAP_HELVETICA_18, "Pressione ENTER para iniciar");
			glColor3f(0, 0, 0);	glRasterPos2f(-40.2, -10.2);
			writes(GLUT_BITMAP_HELVETICA_18, "Pressione ENTER para iniciar");

			glColor3f(1, 1, 1); glRasterPos2f(-75, 84);
			writes(GLUT_BITMAP_8_BY_13, "Movimente o cubo usando as teclas de cada eixo"); 
			glRasterPos2f(-80, -89);
			writes(GLUT_BITMAP_8_BY_13, "  X");glRasterPos2f(-80, -94);
			writes(GLUT_BITMAP_8_BY_13, "q w e");glRasterPos2f(-80, -99);
			writes(GLUT_BITMAP_8_BY_13, "a s d");
			
			glRasterPos2f(-8, -89);
			writes(GLUT_BITMAP_8_BY_13, "  Y");glRasterPos2f(-8, -94);
			writes(GLUT_BITMAP_8_BY_13, "r t y");glRasterPos2f(-8, -99);
			writes(GLUT_BITMAP_8_BY_13, "f g h");

			glRasterPos2f(65, -89);
			writes(GLUT_BITMAP_8_BY_13, "  Z");glRasterPos2f(65, -94);
			writes(GLUT_BITMAP_8_BY_13, "u i o");glRasterPos2f(65, -99);
			writes(GLUT_BITMAP_8_BY_13, "j k l");
		break;

		case 1:	
			glColor3f(1, 1, 1);	glRasterPos2f(-15, 92);
			writes(GLUT_BITMAP_HELVETICA_18, "Aguarde");
			glRasterPos2f(-35, -98);
			sprintf(string, "...embaralhando x%d", _this->amountMoviment);
			writes(GLUT_BITMAP_HELVETICA_18, string);
		break;

		case 2:
			glColor3f(1, 1, 1);	glRasterPos2f(-98, 92);
			sprintf(string, "Nivel: %d de %d", _this->level, _this->levelmax);
			writes(GLUT_BITMAP_HELVETICA_18, string);
			glRasterPos2f(-9, -98);
			sprintf(string, "%.2d:%.2d", _this->minutes, _this->seconds);
			writes(GLUT_BITMAP_HELVETICA_18, string);
		break;

		case 3:
			glColor3f(1, 1, 1);	glRasterPos2f(-70, -88);
			writes(GLUT_BITMAP_HELVETICA_18, "pressione ENTER para ir ao proximo nivel");
			glColor3f(1, 1, 1);	glRasterPos2f(-98, 92);
			sprintf(string, "NIVEL %d SUPERADO!", _this->level);
			writes(GLUT_BITMAP_HELVETICA_18, string);
			glRasterPos2f(-9, -98);
			sprintf(string, "%.2d:%.2d", _this->minutes, _this->seconds);
			writes(GLUT_BITMAP_HELVETICA_18, string);
		break;

		default:
			glColor3f(1, 1, 1);	glRasterPos2f(-70, 80);
			writes(GLUT_BITMAP_8_BY_13, "Creditos:");
			glRasterPos2f(-60, 75);
			writes(GLUT_BITMAP_8_BY_13, "Desenvolvedor: Italo Johnny dos Anjos");
			glRasterPos2f(-60, 70);
			writes(GLUT_BITMAP_8_BY_13, "E-mail: italojohnnydosanjos@gmail.com");
			
			glColor3f(0.8, 0.8, 0.8); glRasterPos2f(-25, 0);
			writes(GLUT_BITMAP_HELVETICA_18, "VOCE VENCEU!");
			glColor3f(0, 0, 0); glRasterPos2f(-25.5, 0.5);
			writes(GLUT_BITMAP_HELVETICA_18, "VOCE VENCEU!");

			glColor3f(0.8, 0.8, 0.8); glRasterPos2f(-35, -10);
			writes(GLUT_BITMAP_HELVETICA_18, "pressione ESC para sair");
			glColor3f(0, 0, 0); glRasterPos2f(-35.5, -10.5);
			writes(GLUT_BITMAP_HELVETICA_18, "pressione ESC para sair");	
			glColor3f(0.3, 0.3, 0.3); glRasterPos2f(-83, -95);
			writes(GLUT_BITMAP_8_BY_13, "...em memoria de Marluce Aparecida dos Anjos Santos");
			glColor3f(0, 0, 0);	glRasterPos2f(-83.5, -95.5);
			writes(GLUT_BITMAP_8_BY_13, "...em memoria de Marluce Aparecida dos Anjos Santos");
	}
			glPopMatrix();
		glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
	_this->camera();
}