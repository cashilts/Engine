#include "Player.h"
#include "GameObject.h"


//Player class holds information about player actions and character
class Player : public GameObject {

	

	enum ControlScheme {
		firstPerson,
		strategic
	};

	
	ControlScheme curControl;
	


	Player()
	{
		xPos = 0;
		yPos = 0;
		zPos = 0;
	}

	void setPlayerPosition(float x = 0, float y = 0, float z = 0)
	{
		xPos = x;
		yPos = y;
		zPos = z;
	}
};
