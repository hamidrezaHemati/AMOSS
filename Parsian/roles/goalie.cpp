#include "stdafx.h"
#include "../soccer/soccer.h"

void Soccer::Goalie(int id) {
	rcsc::Vector2D ballPos{ wm->getBall().pos + wm->getBall().vel };
	rcsc::Line2D ballPath{ wm->getBall().pos, wm->getBall().pos + wm->getBall().vel.normalizedVector() * 1000 };
	rcsc::Line2D goalLine{ Field::ourGoalB(), Field::ourGoalT() };
	rcsc::Vector2D p;
	/*p = ballPath.intersection(goalLine);
	if (wm->getBall().vel.length() < 0.5) p.invalidate();
	else if (ballPos.x < -110 && ballPos.y > Field::goalWidth/2) p.invalidate();
	else if (ballPos.x < -110 && ballPos.y < -Field::goalWidth / 2) p.invalidate();
	else if (ballPos.x > 45) p.invalidate();
	double y;

	p.invalidate();
	if (p.isValid()) {
		y = p.y;
	}
	else {*/
	//LOG("BV: " << wm->getBall().vel.length());
	double y;
	if (wm->getBall().pos.x > -55)
		y = wm->getBall().pos.y + wm->getBall().vel.y * 1;
	else if (wm->getBall().pos.x > -35)
		y = wm->getBall().pos.y + wm->getBall().vel.y * 2;
	else
		y = wm->getBall().pos.y + wm->getBall().vel.y * 4;
	//}

	LOG("ballPoint: " << wm->getBall().pos);
	LOG("ballPos: " << ballPos.x << "," << ballPos.y);

	if (y < -Field::goalWidth / 2 + 1) y = -Field::goalWidth / 2 + 1;
	else if (y > Field::goalWidth / 2 -1) y = Field::goalWidth / 2 - 1;

	rcsc::Vector2D targetVel = rcsc::Vector2D(0, 2000);
	rcsc::Vector2D targetPos = rcsc::Vector2D(-Field::width / 2 + 5, y);
	//if (wm->ourRobot(id).pos.x > -Field::width / 2 ) targetPos = Field::ourGoal();

	if (Field::ourPenaltyBRect().contains(ballPos) && wm->getBall().vel.length() < 5) {
		kick(id, Field::oppGoal());
	}
	else {
		gotoPoint(id, targetPos, targetVel,20);
	}

	// SPIN
	if (wm->getBall().pos.dist(wm->ourRobot(id).pos) < 8.5 && wm->getBall().vel.length() < 20) {
		spin(id, wm->getBall().pos, 100);
	}

}