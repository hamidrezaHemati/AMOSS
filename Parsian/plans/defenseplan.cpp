#include "stdafx.h"
#include "../soccer/soccer.h"

/*this function provides the target position for the defenders by the number of defenders*/
void Soccer::DefensePosition(int size, rcsc::Vector2D *first, rcsc::Vector2D *second) {
	const rcsc::Vector2D& bp = wm->getBall().pos + wm->getBall().vel*0.5;
	const double def_w = -Field::width / 2 + Field::penaltyAwidth + 15; ////-80
	double y = bp.y;
	LOG("y is : " << y);
	switch (size) {
	case 1:
		*first = rcsc::Vector2D(def_w, y*0.6);
		/**
		if (y < -Field::penaltyAheight / 2 + 5) y = -Field::penaltyAheight / 2 + 2;  //// y<-20 ,, y=-23 /////sag
		if (y > Field::penaltyAheight / 2 - 5) y = Field::penaltyAheight / 2 - 2;  ////y>20 ,, y=23
		if (wm->getBall().pos.dist(Field::ourGoal()) > 40 && wm->getBall().pos.x > -Field::width / 2 + Field::penaltyAwidth + 10)
			*first = rcsc::Vector2D(def_w, y*0.6);
		else {
			if (wm->getBall().pos.x > -Field::width / 2 + Field::penaltyAwidth + 10) { ////  > -85
				*first = rcsc::Vector2D(def_w, y);
			}
			if (wm->getBall().pos.y > 0) {
				*first = rcsc::Vector2D(bp.x - 10, Field::penaltyAheight / 2 + 25);
			}
			else {
				*first = rcsc::Vector2D(bp.x - 10, -Field::penaltyAheight / 2 - 25);
			}
		}
		*/
		break;
	case 2:
		if (y < -Field::penaltyAheight + 5) y = -Field::penaltyAheight / 2 + 2;
		if (y > Field::penaltyAheight / 2 - 5) y = Field::penaltyAheight / 2 - 2;

		if (wm->getBall().pos.x > -Field::width / 2 + Field::penaltyAwidth + 50) ////pos.x > -45
			*first = rcsc::Vector2D(def_w, y + 5);
		else {                                                                   ////pos.x < -45  defending situation
			if (wm->getBall().pos.y > 0) {
				*first = rcsc::Vector2D(bp.x - 20, Field::penaltyAheight / 2 + 15);
			}
			else {
				*first = rcsc::Vector2D(def_w, y);
			}
		}
		if (wm->getBall().pos.x > -Field::width / 2 + Field::penaltyAwidth + 50)  ////// pos.x > -45
			*second = rcsc::Vector2D(def_w, y - 5);
		else {                                                                    ///// pos.x < -45 defending situation
			if (wm->getBall().pos.y > 0) {
				*second = rcsc::Vector2D(def_w, y);
			}
			else {
				*second = rcsc::Vector2D(bp.x - 20, -Field::penaltyAheight / 2 - 15);
			}
		}
		break;
	}
}

/*this function use the targets of DefensePosition to order defenders to go on their positions*/
void Soccer::Defense(int id[], int size,const rcsc::Vector2D &first, const rcsc::Vector2D &second) {
	
	switch (size)
	{
	case 1:
		gotoPoint(id[0], first, rcsc::Vector2D(1000, 0));
		if (wm->getBall().pos.dist(wm->ourRobot(id[0]).pos) < 8.5) {
			//LOG("SPIN GOALIE");
			double spinnSpid{ 30 };
			#ifndef YELLOW
			spinnSpid *= -1;
			#endif // !YELLOW
			if (wm->getBall().pos.y > 0) setRobotVel(id[0], 0, spinnSpid);
			else setRobotVel(id[0], 0, -spinnSpid);
		}

		break;
	case 2:
		
		gotoPointAvoidPenaltyA(id[0], first, rcsc::Vector2D(1000, 0));
		if (wm->getBall().pos.dist(wm->ourRobot(id[0]).pos) < 8.5 && wm->getBall().pos.x > -Field::width / 2 + Field::penaltyAwidth + 5) {
			//LOG("SPIN GOALIE");
			double spinnSpid{ 30 };
			#ifndef YELLOW
			spinnSpid *= -1;
			#endif // !YELLOW
			if (wm->getBall().pos.y > 0) setRobotVel(id[0], 0, spinnSpid);
			else setRobotVel(id[0], 0, -spinnSpid);
		}
		gotoPointAvoidPenaltyA(id[1], second, rcsc::Vector2D(1000, 0));

		if (wm->getBall().pos.dist(wm->ourRobot(id[0]).pos) < 8.5 && wm->getBall().pos.x > -Field::width / 2 + Field::penaltyAwidth + 5) {
			//LOG("SPIN GOALIE");
			double spinnSpid{ 30 };
			#ifndef YELLOW
			spinnSpid *= -1;
			#endif // !YELLOW
			if (wm->getBall().pos.y > 0) setRobotVel(id[0], 0, spinnSpid);
			else setRobotVel(id[0], 0, -spinnSpid);
		}
		
		break;
	default:
		break;
	}
}
