#include "stdafx.h"
#include "../soccer/soccer.h"

void Soccer::Pos(int id[], int size) {
	
	/*
	rcsc::Vector2D BR[4];
	rcsc::Vector2D YR[4];
	rcsc::Rect2D r[4];
	rcsc::Vector2D k[4];
	/////blue robots
	BR[2] = rcsc::Vector2D(-70, -40);
	BR[3] = rcsc::Vector2D(-70,  40);
	BR[0] = rcsc::Vector2D(70, -60);
	BR[1] = rcsc::Vector2D(70, 60);
	//////yellow robots
	YR[0] = rcsc::Vector2D(-Field::width / 4 + 5, 0);
	YR[2] = rcsc::Vector2D(-Field::width / 4 + 5, 20);
	YR[1] = rcsc::Vector2D(-Field::width / 4 + 5,-20);
	YR[3] = rcsc::Vector2D(-Field::width / 4 + 5,-40);
	///////area of working for ballBoys robots
	r[2] = rcsc::Rect2D{ -110 , -90, 110, 90 };
	r[3] = rcsc::Rect2D{ -110 , 0, 110, 90 };
	r[0] = rcsc::Rect2D{  0, -90, 110, 90 };
	r[1] = rcsc::Rect2D{  0,  0, 110, 90 };
	///////targets for ballBoys to kick the ball
	k[3] = rcsc::Vector2D(0, 0);
	k[2] = rcsc::Vector2D(0, 0);
	k[1] = rcsc::Vector2D(0, 20);
	k[0] = rcsc::Vector2D(0, -20);
	gotoPoint(id[0], rcsc::Vector2D(0, -20), rcsc::Vector2D(1000, 0));
	if (!firstflag) {
		gotoPoint(id[1], rcsc::Vector2D(-20, 0), rcsc::Vector2D(1000, 0));
	}
	if (!secondflag) {
		gotoPoint(id[2], rcsc::Vector2D(0, 0), rcsc::Vector2D(1000, 0));
	}
	if (!thirdflag && ) {
		gotoPoint(id[3], rcsc::Vector2D(0, 20), rcsc::Vector2D(1000, 0));
	}
	
	if (wm->ourRobot(id[1]).pos.dist(rcsc::Vector2D(-20, 0)) < 3 && !firstflag) {
		firstflag = true;
		gotoPoint(id[1], rcsc::Vector2D(-80, 0), rcsc::Vector2D(1000, 0));
	}
	if (wm->ourRobot(id[2]).pos.dist(rcsc::Vector2D(0, 0)) < 3 && !secondflag) {
		secondflag = true;
		gotoPoint(id[2], rcsc::Vector2D(-80, 20), rcsc::Vector2D(1000, 0));
	}
	if (wm->ourRobot(id[2]).pos.dist(rcsc::Vector2D(-80, 20)) < 3) flag = true;
	if (wm->ourRobot(id[3]).pos.dist(rcsc::Vector2D(0, 20)) < 3 && flag) {
		gotoPoint(id[3], rcsc::Vector2D(-80, 25), rcsc::Vector2D(1000, 0));
	}
	
	
	rcsc::Vector2D BR[2];
	BR[0] = rcsc::Vector2D(-20, -20);
	BR[1] = rcsc::Vector2D(-20,  20);
	switch (size) {
		case 1:
		{
			LOG("case 1");
			gotoPoint(id[0], BR[0], rcsc::Vector2D(1000, 0));
			break;
		}
		case 2:
		{
			LOG("case 2");
			gotoPoint(id[0], BR[0], rcsc::Vector2D(1000, 0));
			gotoPoint(id[1], BR[1], rcsc::Vector2D(1000, 0));
			break;
		}
	}
	*/
	rcsc::Vector2D ballPos = wm->getBall().pos + wm->getBall().vel*0.2;
	if (ballPos.x > 100) ballPos.x = 100;
	if (ballPos.x < -75) ballPos.x = -75;
	switch (size)
	{
	case 1:
	{
		double dist0{ wm->getBall().pos.dist(wm->ourRobot(id[0]).pos) };
		if (ballPos.y < -Field::height / 4 + 20)
			gotoPointAvoid(id[0], rcsc::Vector2D(ballPos.x, 0), rcsc::Vector2D(1000, 0));
		else if (ballPos.y > Field::height / 4 - 20)
			gotoPointAvoid(id[0], rcsc::Vector2D(ballPos.x, 0), rcsc::Vector2D(1000, 0));
		else
			if (wm->ourRobot(id[0]).pos.y > 0)
				gotoPointAvoid(id[0], rcsc::Vector2D(ballPos.x, 60), rcsc::Vector2D(1000, 0));
			else
				gotoPointAvoid(id[0], rcsc::Vector2D(ballPos.x, -60), rcsc::Vector2D(1000, 0));

		break;
	}
	case 2:
	{
		double dist0{ wm->getBall().pos.dist(wm->ourRobot(id[0]).pos) };
		double dist1{ wm->getBall().pos.dist(wm->ourRobot(id[1]).pos) };
		if (dist1 < 40)
			spin(id[1], Field::oppGoal(), 30);
		if (dist0 < 40)
			spin(id[0], Field::oppGoal(), 30);
		if (wm->getBall().pos.x < -20) {
			// matching
			int lower = -1, upper = -1;
			if (wm->ourRobot(id[0]).pos.y > 0) {
				upper = id[0];
				lower = id[1];
			}
			else {
				upper = id[1];
				lower = id[0];
			}

			if (wm->getBall().pos.y > 0) {
				gotoPointAvoid(upper, rcsc::Vector2D(ballPos.x, Field::penaltyBheight / 2 + 25), rcsc::Vector2D(1000, 0));
				gotoPointAvoid(lower, rcsc::Vector2D(60, 0), rcsc::Vector2D(0, 1000));
			}
			else {
				gotoPointAvoid(lower, rcsc::Vector2D(ballPos.x, -Field::penaltyBheight / 2 - 25), rcsc::Vector2D(1000, 0));
				gotoPointAvoid(upper, rcsc::Vector2D(60, 0), rcsc::Vector2D(0, 1000));

			}

		}
		if (wm->getBall().pos.x > -20) {
			///rcsc::Vector2D(ballPos.x, Field::penaltyBheight / 2 + 25)
			///rcsc::Vector2D(ballPos.x, -Field::penaltyBheight / 2 - 25)
			if (ballPos.y < -Field::height / 4) {
				gotoPointAvoid(id[0], rcsc::Vector2D(30, -40), rcsc::Vector2D(1000, 0));///////
				gotoPointAvoid(id[1], rcsc::Vector2D(74, 0), rcsc::Vector2D(1000, 0));
			}
			else if (ballPos.y > Field::height / 4) {
				gotoPointAvoid(id[0], rcsc::Vector2D(30, 40), rcsc::Vector2D(1000, 0));//////
				gotoPointAvoid(id[1], rcsc::Vector2D(74, 0), rcsc::Vector2D(1000, 0));
			}
			else {
				// matching
				int lower = -1, upper = -1;
				if (wm->ourRobot(id[0]).pos.y > 0) {
					upper = id[0];
					lower = id[1];
				}
				else {
					upper = id[1];
					lower = id[0];
				}
				gotoPointAvoid(upper, rcsc::Vector2D(ballPos.x, Field::penaltyBheight / 2 + 10), rcsc::Vector2D(1000, 0));
				gotoPointAvoid(lower, rcsc::Vector2D(ballPos.x, -Field::penaltyBheight / 2 - 10), rcsc::Vector2D(1000, 0));
			}
		}
		break;
	}
	default:
		break;
	}
	
	
}
