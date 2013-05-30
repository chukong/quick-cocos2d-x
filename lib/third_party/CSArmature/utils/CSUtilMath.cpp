/*
 * Copyright (c) 2012 Chukong Technologies, Inc.
 *
 * http://www.cocostudio.com
 * http://tools.cocoachina.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to permit
 * persons to whom the Software is furnished to do so, subject to the
 * following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
 * NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "CSUtilMath.h"

using namespace cocos2d;

#if CS_DEBUG_FOR_EDIT
#include "CSEditorTween.h"
#include "CSEditorDisplayManager.h"
#endif

namespace cs {

bool isSpriteContainPoint(CCSprite *_sprite, CCPoint _point, CCPoint &_outPoint)
{
    _outPoint = _sprite->convertToNodeSpace(_point);
    
    CCSize _s  = _sprite->getContentSize();
    CCRect _r(0, 0, _s.width, _s.height);
    
    return _r.containsPoint(_outPoint);
}

bool isSpriteContainPoint(CCSprite *_sprite, CCPoint _point)
{
    CCPoint _p = ccp(0, 0);
    return isSpriteContainPoint(_sprite, _point, _p);
}


CCPoint bezierTo(float t, CCPoint &point1, CCPoint &point2, CCPoint &point3)
{
    
    CCPoint p;
    
    p.x = pow((1 - t), 2)*point1.x + 2*t*(1-t)*point2.x + pow(t, 2)*point3.x;
    p.y = pow((1 - t), 2)*point1.y + 2*t*(1-t)*point2.y + pow(t, 2)*point3.y;
    
    return p;
}

CCPoint bezierTo(float t, CCPoint &point1, CCPoint &point2, CCPoint &point3, CCPoint &point4)
{
    CCPoint p;
    
    p.x = point1.x*pow((1 - t), 3) + 3*t*point2.x*pow((1-t), 2) + 3*point3.x*pow(t, 2)*(1-t) + point4.x*pow(t,3);
    p.y = point1.y*pow((1 - t), 3) + 3*t*point2.y*pow((1-t), 2) + 3*point3.y*pow(t, 2)*(1-t) + point4.y*pow(t,3);
    
    return p;
}

CCPoint circleTo(float t, CCPoint &center, float radius, float fromRadian, float radianDif)
{
    CCPoint p;
    
    p.x = center.x + radius*cos(fromRadian+radianDif*t);
    p.y = center.y + radius*sin(fromRadian+radianDif*t);
    
    return p;
}



//! IK Function

//! Set an epsilon value to prevent division by small numbers
const double epsilon = 0.0001;

// Set max arc length a bone can move the end effector an be considered no motion
// so that we can detect a failure state.
const double trivialArcLength = 0.00001; 

///***************************************************************************************
/// SimplifyAngle
/// This function will convert an angle to the equivalent rotation in the range [-pi,pi]
///***************************************************************************************
double simplifyAngle(double angle)
{
	angle = fmod(angle, 2.0 * CS_PI);
	if( angle < -CS_PI )
		angle += (2.0 * CS_PI);
	else if( angle > CS_PI )
		angle -= (2.0 *CS_PI);
	return angle;
}

float simplifyAngle(float angle)
{
	angle = fmodf(angle, 2.0 * CS_PI);
	if( angle < -CS_PI )
		angle += (2.0 * CS_PI);
	else if( angle > CS_PI )
		angle -= (2.0 *CS_PI);
	return angle;
}

///***************************************************************************************
/// CalcIK_2D_CCD
/// Given a bone chain located at the origin, this function will perform a single cyclic
/// coordinate descent (CCD) iteration. This finds a solution of bone angles that places
/// the final bone in the given chain at a target position. The supplied bone angles are
/// used to prime the CCD iteration. If a valid solution does not exist, the angles will
/// move as close to the target as possible. The user should resupply the updated angles 
/// until a valid solution is found (or until an iteration limit is met).
///  
/// returns: CCD_Result.Success when a valid solution was found.
///          CCD_Result.Processing when still searching for a valid solution.
///          CCD_Result.Failure when it can get no closer to the target.
///***************************************************************************************
CCD_Result CalcIK_CCD(Bone *startBone, Bone *endBone, CCPoint &targetPoint, float arrivalDist)
{

	double arrivalDistSqr = arrivalDist * arrivalDist;

	//===
	// Track the end effector position (the final bone)
	CCPoint endPoint = ccp(startBone->m_tWorldTransform.tx, startBone->m_tWorldTransform.ty);
	
	CCPoint currentPoint = ccp(0, 0); 

	//===
	// Perform CCD on the bones by optimizing each bone in a loop 
	// from the final bone to the root bone
	bool modifiedBones = false;

	Bone *currentBone = startBone->getParentBone();
	Bone *lastCurrentBone = startBone;

	while(!currentBone->getParentBone() == NULL)
	{
		currentPoint = ccp(currentBone->m_tWorldTransform.tx, currentBone->m_tWorldTransform.ty);

		// Get the vector from the current bone to the end effector position.
 		double curToEndX = endPoint.x - currentPoint.x;
		double curToEndY = endPoint.y - currentPoint.y;
		double curToEndMag = ccpDistance(endPoint, currentPoint);

		// Get the vector from the current bone to the target position.
		double curToTargetX = targetPoint.x - currentPoint.x;
		double curToTargetY = targetPoint.y - currentPoint.y;
		double curToTargetMag = ccpDistance(targetPoint, currentPoint);

		// Get rotation to place the end effector on the line from the current
		// joint position to the target postion.
		double cosRotAng;
		double sinRotAng;
		double endTargetMag = (curToEndMag*curToTargetMag);
		if( endTargetMag <= epsilon )
		{
			cosRotAng = 1;
			sinRotAng = 0;
		}
		else
		{
			cosRotAng = (curToEndX*curToTargetX + curToEndY*curToTargetY) / endTargetMag;
			sinRotAng = (curToEndX*curToTargetY - curToEndY*curToTargetX) / endTargetMag;
		}

        
		// Clamp the cosine into range when computing the angle (might be out of range
		// due to floating point error).
		double rotAng = acos( MAX(-1, MIN(1, cosRotAng) ) );
		if( sinRotAng < 0.0 )
			rotAng = -rotAng;

		// Rotate the end effector position.
		endPoint.x = currentPoint.x + cosRotAng*curToEndX - sinRotAng*curToEndY;
		endPoint.y = currentPoint.y + sinRotAng*curToEndX + cosRotAng*curToEndY;

#if CS_DEBUG_FOR_EDIT
		// Rotate the current bone in local space (this value is output to the user)
		if (dynamic_cast<EditorTween*>(currentBone->getTween()) != 0)
		{


			EditorTween *tween = ((EditorTween*)currentBone->getTween());

			if(currentBone == endBone || currentBone->getChildren()->count() > 1)
			{
				CCPoint p = ccpRotateByAngle(ccp(lastCurrentBone->m_tWorldTransform.tx, lastCurrentBone->m_tWorldTransform.ty), currentPoint, rotAng);

				((EditorDisplayManager*)currentBone->getDisplayManager())->convertPointToSpace(p);

				((EditorTween*)lastCurrentBone->getTween())->editPosition(p.x, p.y);
			}
			else
			{
				rotAng = tween->getRotation() - rotAng;
				rotAng = simplifyAngle(rotAng);

				((EditorTween*)currentBone->getTween())->editRotation(rotAng);
			}



		}
		else
		{
// 			if(currentBone == endBone || currentBone->getChildren()->count() > 1)
// 			{
// 				CCPoint p = rotatePointByPoint(currentPoint, ccp(lastCurrentBone->m_tWorldTransform.tx, lastCurrentBone->m_tWorldTransform.ty), rotAng);
// 				lastCurrentBone->setPosition(p.x, p.y);
// 			}
// 			else
// 			{
// 				currentBone->setRotation(simplifyAngle(currentBone->getRotation() - rotAng));
// 			}
			
		}
#endif
		

		// Check for termination
		double endToTargetX = (targetPoint.x-endPoint.x);
		double endToTargetY = (targetPoint.y-endPoint.y);
		if( endToTargetX*endToTargetX + endToTargetY*endToTargetY <= arrivalDistSqr )
		{
			// We found a valid solution.
			return Success;
		}

		// Track if the arc length that we moved the end effector was
		// a nontrivial distance.
		if( !modifiedBones && abs(rotAng)*curToEndMag > trivialArcLength )
		{
			modifiedBones = true;
		}

		if (currentBone == endBone || currentBone->getChildren()->count() > 1)
		{
			break;
		}

		lastCurrentBone = currentBone;
		currentBone = currentBone->getParentBone();
	}


	// We failed to find a valid solution during this iteration.
	if( modifiedBones )
		return Processing;
	else
		return Failure;

}

}