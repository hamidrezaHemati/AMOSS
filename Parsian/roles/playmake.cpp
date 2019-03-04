#include "stdafx.h"
#include "../soccer/soccer.h"

void Soccer::PlayMake(int id) {
	rcsc::Rect2D avoidArea = rcsc::Rect2D(-110, -90, 45, 180);
	rcsc::Rect2D sag = rcsc::Rect2D{ -Field::width / 2, -Field::height / 2, Field::width / 2, Field::height };
	double margin{20};
	if (rcsc::Rect2D{ Field::width / 2 - Field::penaltyAwidth - margin, -Field::penaltyAheight / 2 - margin, Field::penaltyAwidth, Field::penaltyAheight + margin }.contains(wm->getBall().pos)
		&& wm->ourRobot(id).pos.dist(wm->getBall().pos) < 7) {
		spin(id, Field::oppGoal(), 40);
	}
	else if (avoidArea.contains(wm->getBall().pos)) {
		gotoPoint(id, rcsc::Vector2D(0, 0), rcsc::Vector2D(1000, 0));
	}
	else  {
		kick(id, Field::oppGoal() + rcsc::Vector2D(15, 0));
	}
}