#include <string>
#include "Robots_Modified.h"
#include "miniFW_Modified.h"
#include "strutils.h"


using namespace std;

int main()
{
	Robot r1 (0, 4, east, 0);
	r1.SetColor(green);

	Robot monster1 (3, 8, south);
	monster1.SetColor(red);
	Robot monster2 (6, 2, east);
	monster2.SetColor(blue);
	Robot monster3 (13, 5, east);
	monster3.SetColor(blue);
	Robot monster4 (13, 0, north);
	monster4.SetColor(red);



	for (int lives=3; lives>0; lives--)
	{
		int i = lives;
		if (i==2)
		{
			ShowMessage ("You have 2 lives left!");
			r1.SetColor(green);		
		}
		if (i==1)
		{
			ShowMessage ("You have only 1 life left!");
			r1.SetColor(green);	
		}
		while (r1.IsAlive())
		{

			r1.PickAllThings();


			if (IsPressed(keySpace))
			{
				if(r1.GetBagCount() >= 20)
				{ 
					if (monster1.IsAlive() || monster2.IsAlive() || monster3.IsAlive() || monster4.IsAlive())
					{
						r1.SetBagCount();
						r1.Freeze(monster1, monster2, monster3, monster4);
						if (monster2.GetXCoordinate() == 14 && monster2.GetYCoordinate() == 4 )
						{
							ShowMessage ("You blocked the target… You lost the Game!");
							return 0;
						}
						else if(monster3.GetXCoordinate() == 14 && monster3.GetYCoordinate() == 4)
						{
							ShowMessage ("You blocked the target… You lost the Game!");
							return 0;
						}
					}
				}
			}

			r1.RandomMonsterMove(monster1, monster2, monster3, monster4);	


			if (monster1.FacingWall())
			{
				monster1.TurnRight();
				monster1.TurnRight();
			}

			if (monster2.FacingWall())
			{
				monster2.TurnRight();
				if (monster2.FacingWall())
				{
					monster2.TurnRight();
				}
			}

			if (monster3.FacingWall())
			{
				monster3.TurnRight();
			}

			if (monster4.FacingWall())
			{
				monster4.TurnRight();
				monster4.TurnRight();
			}

			if (IsPressed(keyRightArrow))
			{				
				r1.TurnFace(east);
				r1.Move();
			}
			else if (IsPressed(keyUpArrow))
			{
				r1.TurnFace(north);
				r1.Move();
			}
			else if (IsPressed(keyDownArrow))
			{
				r1.TurnFace(south);		
				r1.Move();
			}

			if (r1.GetXCoordinate() == 14 && r1.GetYCoordinate() == 4)
			{
				if (r1.GetBagCount() >= 50)
				{
					ShowMessage ("Congratulations, you win!");
					return 0;
				}
				if (r1.GetBagCount() < 50)
				{
					ShowMessage ("You reached the end but could not gather enough things… You lost the Game!");
					return 0;
				}
			}

			if (monster1.IsAlive() || monster2.IsAlive() || monster3.IsAlive() || monster4.IsAlive() )
			{
				monster3.Resurrect();
				monster3.SetColor(blue);
				monster4.Resurrect();
				monster4.SetColor(red);
				monster2.Resurrect();
				monster2.SetColor(blue);
				monster1.Resurrect();
				monster1.SetColor(red);
			}
		}
		r1.Resurrect();

	}
	ShowMessage ("You have no lives left");
	ShowMessage ("You run out of lives… You lost the Game!");

}
