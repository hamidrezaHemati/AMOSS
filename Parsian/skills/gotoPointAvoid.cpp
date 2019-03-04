#include "stdafx.h"
#include "../soccer/soccer.h"
#include "../util/pid.h"

void Soccer::gotoPointAvoidPenaltyA(int id, const rcsc::Vector2D&  targetPos, const rcsc::Vector2D& targetVel) {
	/*robot vector from robot position till targeted point*/
	rcsc::Segment2D robotVector = rcsc::Segment2D(wm->ourRobot(id).pos, targetPos);
	/*down line of A penalty rectangle*/
	rcsc::Segment2D downAPenaltyVector = rcsc::Segment2D(rcsc::Vector2D(-110, 25), rcsc::Vector2D(-95, 25));
	/*up line of A penalty rectangle*/
	rcsc::Segment2D upAPenaltyVector = rcsc::Segment2D(rcsc::Vector2D(-110, -25), rcsc::Vector2D(-95, -25));
	rcsc::Segment2D rightAPenaltyVector = rcsc::Segment2D(rcsc::Vector2D(-95, -25), rcsc::Vector2D(-75, 25));
	rcsc::Vector2D alterDownAPoint = rcsc::Vector2D(-70, 25); ////alternaive point for down line of A penalty
	rcsc::Vector2D alterUpAPoint = rcsc::Vector2D(-70, -25); ////alternaive point for uper line of A penalty
	if (Field::ourPenaltyARect().contains(targetPos)) {
		if (robotVector.existIntersection(downAPenaltyVector)) {
			double x = targetPos.x;
			double y = robotVector.intersection(downAPenaltyVector, false).y + 5;
			gotoPoint(id, rcsc::Vector2D(x, y), targetVel);
		}
		else if (robotVector.existIntersection(upAPenaltyVector)) {
			double x = targetPos.x;
			double y = robotVector.intersection(downAPenaltyVector, false).y - 5;
			gotoPoint(id, rcsc::Vector2D(x, y), targetVel);
		}
		else {
			double y = targetPos.y;
			double x = robotVector.intersection(rightAPenaltyVector, false).x + 5;
			gotoPoint(id, rcsc::Vector2D(x, y), targetVel);
		}
	}
	else {
		if (robotVector.intersects(downAPenaltyVector) && robotVector.intersects(upAPenaltyVector)) {
			if (wm->ourRobot(id).pos.dist(robotVector.intersection(downAPenaltyVector, false)) <
				wm->ourRobot(id).pos.dist(robotVector.intersection(upAPenaltyVector, false))) {
				gotoPoint(id, alterDownAPoint, targetVel);
				//LOG("intercect with both.....down");
			}
			else {
				gotoPoint(id, alterUpAPoint, targetVel);
				//LOG("intercect with both......up");
			}
		}
		else if (robotVector.intersects(downAPenaltyVector)) {
			gotoPoint(id, alterDownAPoint, targetVel);
			//LOG("intercect with down");
		}
		else if (robotVector.intersects(upAPenaltyVector)) {
			gotoPoint(id, alterUpAPoint, targetVel);
			//LOG("intercect with up");
		}
		else {
			gotoPoint(id, targetPos, targetVel);
			//LOG("no intercect");
		}
	}
}

void Soccer::gotoPointAvoid(int id, const rcsc::Vector2D&  targetPos, const rcsc::Vector2D& targetVel) {
	/*robot vector from robot position till targeted point*/
	rcsc::Segment2D robotVector = rcsc::Segment2D(wm->ourRobot(id).pos, targetPos);
	/*down line of B penalty rectangle*/
	rcsc::Segment2D downBPenaltyVector = rcsc::Segment2D(rcsc::Vector2D(-110, 40), rcsc::Vector2D(-75, 40));
	/*up line of B penalty rectangle*/
	rcsc::Segment2D upBPenaltyVector = rcsc::Segment2D(rcsc::Vector2D(-110, -40), rcsc::Vector2D(-75, -40));
	/*right line of B penalty rectangle*/
	rcsc::Segment2D rightBPenaltyVector = rcsc::Segment2D(rcsc::Vector2D(-75, -40), rcsc::Vector2D(-75, 40));
	rcsc::Vector2D alterDownBPoint = rcsc::Vector2D(-50, 40); ////alternaive point for down line of B penalty
	rcsc::Vector2D alterUpBPoint = rcsc::Vector2D(-50, -40); ////alternaive point for uper line of B penalty
	/*calculating number of robots in B penalty area*/
	int robotsAreInBPenaltyArea = 0;
	for (int i = 0; i <= 4; i++) {
		if (Field::ourPenaltyBRect().contains(wm->ourRobot(i).pos)) {
			robotsAreInBPenaltyArea++;
		}
	}
	/*making decision of how robots should move through B penalty area*/
	if (!Field::ourPenaltyBRect().contains(wm->ourRobot(id).pos)) {
		if (Field::ourPenaltyBRect().contains(targetPos)) {
			if (robotVector.existIntersection(downBPenaltyVector)) {
					double x = targetPos.x;
					double y = robotVector.intersection(downBPenaltyVector, false).y + 5;
					gotoPoint(id, rcsc::Vector2D(x, y), targetVel);
			}
			else if (robotVector.existIntersection(upBPenaltyVector)) {
					double x = targetPos.x;
					double y = robotVector.intersection(downBPenaltyVector, false).y - 5;
					gotoPoint(id, rcsc::Vector2D(x, y), targetVel);
			}
			else {
					double y = targetPos.y;
					double x = robotVector.intersection(rightBPenaltyVector, false).x + 5;
					gotoPoint(id, rcsc::Vector2D(x, y), targetVel);
			}
		}
		else {
			if (robotVector.intersects(downBPenaltyVector) && robotVector.intersects(downBPenaltyVector)) {
				if (wm->ourRobot(id).pos.dist(robotVector.intersection(downBPenaltyVector, false)) <
					wm->ourRobot(id).pos.dist(robotVector.intersection(upBPenaltyVector, false))) {
					gotoPoint(id, alterDownBPoint, targetVel);
				}
				else {
					gotoPoint(id, alterUpBPoint, targetVel);
				}
			}
			else if (robotVector.existIntersection(downBPenaltyVector))
				gotoPoint(id, alterDownBPoint, targetVel);
			else if (robotVector.existIntersection(upBPenaltyVector)) 
				gotoPoint(id, alterUpBPoint, targetVel);
			else 
				gotoPoint(id, targetPos, targetVel);
		}
	}
	else {
		gotoPointAvoidPenaltyA(id, rcsc::Vector2D(0,0), targetVel);
	}
}