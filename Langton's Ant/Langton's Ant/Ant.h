#include <iostream>
using namespace std;
#include "GL/glut.h"

extern const int NbColonnes;
extern const int NbLignes;

class Ant
{
protected:
	int PosC, PosL;
	int Angle;

public:
	int GetPosC()  const { return PosC;  }
	int GetPosL()  const { return PosL;  }
	int GetAngle() const { return Angle; }

	// mutateurs
	void SetPosC(int C)  { PosC = C;  }
	void SetPosL(int L)  { PosL = L;  }
	void SetAngle(int A) { Angle = A; }

	// Constructeur par défaut
	Ant()
	{
		PosC = NbColonnes / 2;
		PosL = NbLignes / 2;

		Angle = 0;
	}

	void Dessiner();

	void Avancer();

	void TournerAGauche();
	void TournerADroite();

	void DeplacementAuto();

	void ChangerCase();
};




