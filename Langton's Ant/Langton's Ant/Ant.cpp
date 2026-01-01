#ifndef ANT_H
#define ANT_H

#include "Ant.h"

extern char** Matrice;
extern double zoom;

void Ant::Dessiner()
{
	glPushMatrix();

	glTranslated(PosC + 0.5, PosL + 0.5, 0.0);

	glRotatef(Angle, 0, 0, 1);

	glTranslated(0.0, -0.25, 0.0);

	glColor3d(1.0, 0.0, 0.0);
	glBegin(GL_TRIANGLES);

	glVertex2d(0, 0);
	glVertex2d(-0.25, 0.5);
	glVertex2d(0.25, 0.5);

	glEnd();

	glPopMatrix();
}

void Ant::DeplacementAuto()
{
	if (Matrice[PosC][PosL] == '1') // Case Noir
	{
		ChangerCase();

		TournerAGauche();
		Avancer();
	}
	else // Case Blanche
	{
		ChangerCase();

		TournerADroite();
		Avancer();
	}
}

void Ant::Avancer()
{
	//PosL--;

	switch (Angle)
	{
		case 0:
		{
			PosL--;
			break;
		}
		case 90:
		{
			PosC++;
			break;
		}
		case 180:
		{
			PosL++;
			break;
		}
		case -90:
		{
			PosC--;
			break;
		}
	}
}

void Ant::TournerAGauche()
{
	Angle = Angle - 90;
	if (Angle < -90) { Angle = 180; }
}
void Ant::TournerADroite()
{
	Angle = Angle + 90;
	if (Angle > 180){ Angle = -90; }
}

void Ant::ChangerCase()
{
	if (Matrice[PosC][PosL] == '1')
	{
		Matrice[PosC][PosL] = '0';
	}
	else
	{
		Matrice[PosC][PosL] = '1';
	}
}

#endif