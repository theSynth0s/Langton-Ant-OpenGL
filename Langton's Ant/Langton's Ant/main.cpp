#include <iostream>
#include "GL/glut.h"
#include "Ant.h"
using namespace std;

const int NbColonnes = 65; // DOIT être impair
const int NbLignes = 65;   // (pour le zoom)

char** Matrice;

int zoom = 15;

char iteration_result[6];

int iteration = 0;

float vitesse = 8;

Ant MyAnt;

void Affichage();
void Redim(int x, int y);
void DessinerNiveau();
void ClavierSpecial(int key, int x, int y);
void Timer(int value);

int main(void)
{
	// allocation du tableau du niveau
	Matrice = new char*[NbColonnes];

	for (int i = 0; i < NbColonnes; i++)
		Matrice[i] = new char[NbLignes];

	for (int i = 0; i < NbColonnes; i++)
		for (int j = 0; j < NbLignes; j++)
			Matrice[i][j] = '0';

	//position de la fenetre
	glutInitWindowPosition(20, 0 + 40);
	//taille de la fenetre
	glutInitWindowSize(NbColonnes * 12, NbLignes * 12);
	//mode d'affiche
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE); //double tampon graphique
	// création de la fenetre
	glutCreateWindow("Langton's Ant");
	//fonction d'affichage
	glutDisplayFunc(Affichage);
	//fonction de redimensionnement
	glutReshapeFunc(Redim);
	//touches spéciales du clavier
	glutSpecialFunc(ClavierSpecial);

	glutTimerFunc(vitesse, Timer, 0);

	glutMainLoop();
}

void Affichage()
{
	//couleur du fond
	glClearColor(1.0, 1.0, 1.0, 1.0);
	// efface ecran
	glClear(GL_COLOR_BUFFER_BIT);
	//matrice de modélisation
	glMatrixMode(GL_MODELVIEW);

	DessinerNiveau(); //affiche le niveau
	MyAnt.Dessiner();

	glutSwapBuffers(); //acheve l'affichage + swap les deux tampons graphiques
}

void Redim(int x, int y)
{
	glViewport(0, 0, x, y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (double)NbColonnes, (double)NbLignes, 0.0);
	glViewport(-NbColonnes*zoom, -NbLignes*zoom, NbColonnes*(zoom + 6) * 2, NbLignes*(zoom + 6) * 2);
}

void DessinerNiveau()
{
	glColor3d(0.1, 0.1, 0.1); //couleur noir
	//commence l'affichage des quadrilatères
	glBegin(GL_QUADS);
	//parcourt toutes les cellules de la matrice
	for (int i = 0; i < NbColonnes; i++)
		for (int j = 0; j < NbLignes; j++)
			//si c'est un mur, on dessine un carré
			if (Matrice[i][j] == '1')
			{
				//place les points du carré
				glVertex2d(i, j);
				glVertex2d(i, j + 1);
				glVertex2d(i + 1, j + 1);
				glVertex2d(i + 1, j);
			}
	glEnd(); //acheve l'affichage
}

void ClavierSpecial(int key, int x, int y)
{
	if(key == GLUT_KEY_UP && zoom < 35)
	{
		zoom = zoom + 5;
	}
	else if (key == GLUT_KEY_DOWN && zoom > -1)
	{
		zoom = zoom - 5;

		if (zoom < -1) { zoom = -1; }
	}
	else if (key == GLUT_KEY_RIGHT && vitesse > 0)
	{
		if (vitesse > 5) { vitesse--; }
		else { vitesse = vitesse - 0.5; }
	}
	else if (key == GLUT_KEY_LEFT)
	{
		if (vitesse > 5) { vitesse++; }
		else { vitesse = vitesse + 0.5; }
	}

	//cout << "vitesse : " << vitesse << endl;

	glViewport(-NbColonnes*zoom, -NbLignes*zoom, NbColonnes*(zoom+6)*2, NbLignes*(zoom+6)*2); // ZOOM

	glutPostRedisplay(); // rafraîchir l'affichage
}

void Timer(int value)
{
	// Déplacement
	MyAnt.DeplacementAuto();

	iteration++;

	if (iteration == 472) { zoom = 10; glViewport(-NbColonnes*zoom, -NbLignes*zoom, NbColonnes*(zoom + 6) * 2, NbLignes*(zoom + 6) * 2); }
	else if (iteration == 900) { zoom = 5; glViewport(-NbColonnes*zoom, -NbLignes*zoom, NbColonnes*(zoom + 6) * 2, NbLignes*(zoom + 6) * 2); }
	else if (iteration == 2000) { zoom = 0; glViewport(-NbColonnes*zoom, -NbLignes*zoom, NbColonnes*(zoom + 6) * 2, NbLignes*(zoom + 6) * 2); }
	else if (iteration == 10000) { zoom = -1; glViewport(-NbColonnes*zoom, -NbLignes*zoom, NbColonnes*(zoom + 6) * 2, NbLignes*(zoom + 6) * 2); }

	cout << "iteration : " << iteration << endl;
	//cout << "zoom : " << zoom << endl;
	//cout << "vitesse : " << vitesse << endl;

	glutPostRedisplay();

	if (iteration > 10732)
	{
		cout << "Fin de la simulation !\a\a\a" << endl;
		//system("pause");
	}
	else
	{
		glutTimerFunc(vitesse * 20, Timer, 0);
	}
}