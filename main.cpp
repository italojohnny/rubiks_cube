/*
	Arquivo: 	main.cpp
	Descrição: 	Jogo que simula um Cubo Mágico. Escrito utilizando a biblioteca OpenGL
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
#include <iostream>
#include "Interface.hpp"

int main(int argc, char **argv){
	Interface *interface = new Interface(argc, argv);
	return 0;
}
/*

1- INSTALANDO TUDO O QUE É NECESSÁRIO:
	Para compilar e executar o programa você precisa ter 
	instalado no computador o compilador GCC. Ele vem por 
	padrão em qualquer distribuição linux; caso você 
	estiver usando Windows, instale o MinGW.

	Agora você vai precisar instalar as bibliotecas:
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Em linux é bastante fácil, basta digitar no terminal:

	~ # apt-get update && apt-get upgrade
	~ # apt-get install biuld-essential
	~ # apt-get install freeglut3-dev
	
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Em windows...

	Download do compilador MinGW:
		* Outras informações e instruções para instalação:
			http://www.mingw.org/category/wiki/download
		
		* Ou diretamente pelo link:
			http://sourceforge.net/projects/mingw/files/latest/download?source=files

	Depois é necessário o download das bibliotecas do OpenGL:
		
	

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Qualquer dúvida leia isto:
		configuração do opengl em win e linux
		http://www.prinmath.com/csci5229/misc/install.html

		correçao de bug diferença, de opengl em win e linux
		http://ubuntuforums.org/showthread.php?t=1616945

2- FINALMENTE COMPILANDO OS FONTES
	Com as bibliotecas glut, glu e OpenGL devidamente
	instaladas,	abra seu terminal e vá até o diretório
	onde estão salvos os arquivos.

	windows:
	g++ -o Magic_Cube main.cpp Interface.cpp Rubik.cpp Cube.cpp -lglut32cu -lglu32 -lopengl32 -static-libgcc -static-libstdc++ -mwindows && Magic_Cube

	linux:
	g++ -o Magic_Cube main.cpp Interface.cpp Rubik.cpp Cube.cpp -lglut -lGLU -lGL -lm && ./Magic_Cube

3- OUTRAS COISAS:
	Á você aluno, que por alguma razão do destino, entra em contato com este código:
	Quero te aconselhar, com base nos meus sofrimentos e experiências vivenciadas 
	durante a graduação, siga os conselhos se quiser.

	* Nunca faça trabalhos sozinhos, em dupla um incentivará e cobrará o outro.
	Sozinho é muito mais fácil procrastinar.

	* Escreva tudo o que vier na sua cabeça, por mais retardado que possa parecer. 
	O orientador te dirá quando for muito sem noção, esse é o papel dele.

	* Não pare de escrever. Escreva sem vontade. Escreva desde o começo do ano.

	* Mude o titulo do trabalho quantas vezes forem necessárias. 

	* Nunca copie e cole nada da internet, livros ou artigos. Leia, entenda e escreva
	sua explicação sobre o que você entendeu. Referencie o autor que você usou.

	* A parte mais importante do trabalho é a monografia, queira você ou não, seu
	código pode estar um lixo, mas se sua monografia for boa, você certamente será
	aprovado.

	* Nunca brigue com seu orientador em hipótese nenhuma, ele deve ser seu amigo,
	pois ele é quem defenderá você na banca. Se você brigar com ele, tavez tenha 
	um inimigo na banca para te ferrar.

	* É melhor o professor mais exigente como orientador do que como avaliador, o 
	orientador te defenderá dos avaliadores na banca. O nome dele está sendo 
	vinculado no seu trabalho, por isso ele te ajudará a fazer algo bom.

	* Durante a defesa do seu trabalho, nunca discorde com veemência dos
	avaliadores, seja educado, acate TUDO o que for dito e questionado, e se for
	necessário apenas se justifique com muita educação sem confrontar ninguém.

	* A coisa mais importante que você consegue na faculdade são os amigos,
	contatos e o network, o conhecimento é secundário. São os amigos que te 
	ajudarão durante a vida profissional. Seus amigos podem e vão influenciar
	muito na sua carreira. Seja amigo de todos na medida do possível.

	* Qualquer dúvida que você por ventura tiver com relação ao meu código, 
	entre em contato comigo por email. Ficarei bastente feliz em poder ajudar.
*/
