#include "stdafx.h"
#include "soccer.h"

void Soccer::playon() {
	/**
	int goalie_id = 0;
	Goalie(goalie_id);
	int other[4] = { -1, -1, -1, -1 };
	for (int o = 0; o < 4; o++) {
		for (int i = 1; i < 5; i++) {
			if (i == -1) continue;
			bool same = false;
			for (int j = 0; j < 4; j++) if (other[j] == i) same = true;
			if (same) continue;
			other[o] = i;
		}
	}
	Pos(other, 4);
	*/
	
	int goalie_id = 0;
	Goalie(goalie_id);
	int playmake = -1;
	double pm_cost = 1000000000.0;
	for (int i = 0; i < 5; i++) {
		if (i == goalie_id)	continue;
		double t_cost = wm->ourRobot(i).pos.dist(wm->getBall().pos + wm->getBall().vel + rcsc::Vector2D(-20, 0));
		if (i == last_pm) t_cost -= 10;
		if (wm->ourRobot(i).pos.x > wm->getBall().pos.x + 10) t_cost += 10000;
		if (t_cost < pm_cost) {
			pm_cost = t_cost;
			playmake = i;
		}
	}
	last_pm = playmake;

	PlayMake(playmake);

	int defenseNum = -1;
	if (wm->getBall().pos.x <= -20) defenseNum = 2;
	else if (wm->getBall().pos.x > 30) defenseNum = 1;      ///////i change 2 to 1
	else defenseNum = 1;
	///////////////////////////////////////////////////////////////
	rcsc::Vector2D tempFirst = rcsc::Vector2D(0, 0);
	rcsc::Vector2D tempSecond = rcsc::Vector2D(0, 0);
	DefensePosition(defenseNum, &tempFirst, &tempSecond);
	///////////////////////////////////////////////////////////////
	int defense[2] =  { -1, -1};
	//rcsc::Vector2D poses[3] = { Field::ourGoal(), Field::ourGoalB(), Field::ourGoalT()};
	if (defenseNum == 1) {
		int bestID = -1;
		int worst = 100000000;
		for (int i = 0; i < 5; i++) {
			if (i == playmake || i == goalie_id) continue;
			bool same = false;
			for (int j = 0; j < 2; j++) if (defense[j] == i) same = true;
			if (same) continue;
			double cost = 100000000;
			cost = wm->ourRobot(i).pos.dist(tempFirst);
			if (cost < worst) {
				worst = cost;
				bestID = i;
			}
		}
		defense[0] = bestID;
	}
	else {
		int bestIDFirstTarget = -1;
		int bestIDSecondTarget = -1;
		int worstFirst = 100000000;
		int worstSecond = 100000000;
		for (int i = 0; i < 5; i++) {
			if (i == playmake || i == goalie_id) continue;
			bool same = false;
			for (int j = 0; j < 2; j++) if (defense[j] == i) same = true;
			if (same) continue;
			double costFirst = 100000000;
			double costSecond = 100000000;
			costFirst = wm->ourRobot(i).pos.dist(tempFirst);
			costSecond = wm->ourRobot(i).pos.dist(tempSecond);
			if (costFirst < worstFirst) {
				worstFirst = costFirst;
				bestIDFirstTarget = i;
			}
			if (costSecond < worstSecond) {
				worstSecond = costSecond;
				bestIDSecondTarget = i;
			}
		}
		/**
		if (bestIDFirstTarget == bestIDSecondTarget) {
			worstSecond = 100000000;
			defense[0] = bestIDFirstTarget;
			for (int i = 0; i < 5; i++) {
				if (i == playmake || i == goalie_id || i == bestIDFirstTarget) continue;
				double costSecond = 100000000;
				costSecond = wm->ourRobot(i).pos.dist(tempSecond);
				if (costSecond < worstSecond) {
					worstSecond = costSecond;
					bestIDSecondTarget = i;
				}
			}
			defense[1] = bestIDSecondTarget;
		}
		*/
			defense[0] = bestIDFirstTarget;
			defense[1] = bestIDSecondTarget;
	}
	/*
	for (int d = 0; d < defenseNum; d++) {
		int bestID = -1;
		int worst = 100000000;
		for (int i = 0; i < 5; i++) {
			if (i == playmake || i == goalie_id) continue;
			bool same = false;
			for (int j = 0; j < 2; j++) if (defense[j] == i) same = true;
			if (same) continue;
			double cost = 100000000;
			if (wm->ourRobot(i).pos.dist(tempFirst) > wm->ourRobot(i).pos.dist(tempSecond)) 
				cost = wm->ourRobot(i).pos.dist(tempSecond);
			else
				cost = wm->ourRobot(i).pos.dist(tempFirst);
			if (d == 0) cost = wm->ourRobot(i).pos.dist(tempFirst);
			else if (d == 1) cost = wm->ourRobot(i).pos.dist(tempSecond);
			else break;
			if (cost < worst) {
				worst = cost;
				bestID = i;
			}
		}
		defense[d] = bestID;
	}
	*/
	//LOG("DEF:  " << defense[0] << defense[1]);
	//LOG("PM:   " << playmake);
	Defense(defense, defenseNum, tempFirst, tempSecond);
	int other[2] = { -1, -1 };
	for (int o = 0; o < 2; o++) {
		for (int i = 1; i < 5; i++) {
			if (i == playmake) continue;
			bool same = false;
			for (int j = 0; j < 2; j++) if (defense[j] == i) same = true;
			for (int j = 0; j < 2; j++) if (other[j] == i) same = true;
			if (same) continue;
			other[o] = i;
		}
	}
    Pos(other, 3 - defenseNum);
	//LOG("DEF:  " << defense[0] << "  " << defense[1]);
	//LOG("PM:   " << playmake);
	//LOG("POS:  " << other[0]<<"  " << other[1]);

	//kick(playmake, Field::oppGoal());
	
}