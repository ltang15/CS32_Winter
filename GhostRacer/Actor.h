#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include <cmath>

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp


class StudentWorld;


class Actor :public GraphObject
{
public:
	Actor(int imageID, double startX, double startY, int startDir, double size, int depth, StudentWorld* stWorld);
	virtual ~Actor() {};


	// Actor do something for each tick
	virtual void doSomething() = 0;

	// get Student world
	StudentWorld* getWorld() const;

	// Is this Actor alive
	bool isAlive() const;

	// Set the actor dead
	void setDead();

	// Get the actor's vertical speed
	int get_vspeed() const;



	// Set the actor's vertical speed
	void set_vspeed(int vspeed);

	// If this actor is affected by holy water projectiles, then inflict that
	 // affect on it and return true; otherwise, return false.

	virtual bool beSprayedIfAppropriate();

	// Does this object affect zombie cab placement and speed?

	virtual bool isCollisionAvoidanceWorthy() const;


private:
	StudentWorld* m_stWorld;
	bool m_status;
	int m_vspeed;

	int m_depth;

};






//**********************************************************************************//
//================ Agent ===============//
class Agent :public Actor
{
public:
	Agent(int imageID, double startX, double startY, int startDir, double size, int depth, StudentWorld* stWorld, int startPoints);
	virtual ~Agent() {};
	virtual void doSomething() = 0;

	// Get hit points
	int getHPoints();

	// Increase and decrease hit points by a value
	void dec_hPoints(int value);
	void inc_hPoints(int value);

	virtual bool isCollisionAvoidanceWorthy() const;

	// What sound should play when this agent is damaged but does not die?
	virtual int soundWhenHurt()
	{
		return SOUND_NONE;
	}

	// What sound should play when this agent is damaged and dies?
	virtual int soundWhenDie() {
		return SOUND_NONE;
	};



private:

	int m_hPoints;


};






//=============================================//
//================GHOST'S RACER================//
class GhostRacer : public Agent
{
public:
	GhostRacer(StudentWorld* stWorld);
	virtual ~GhostRacer() {};
	virtual void doSomething();

	virtual int soundWhenDie() const;

	// How many holy water projectiles does the object have?
	int getNumSprays() const;

	// Increase the number of holy water projectiles the object has.
	void increaseSprays(int amt);

	// Spin as a result of hitting an oil slick.
	void spin();

private:

	int m_numSprays;



};





//===================================================//
//===============ZOMBIE CAB==========================//

class ZombieCab :public Agent
{
public:
	ZombieCab(double startX, double startY, StudentWorld* stWorld);
	virtual ~ZombieCab() {};

	virtual void doSomething();

	virtual bool beSprayedIfAppropriate();
	int get_planLength() const;

	void setPlan(int s)
	{
		m_planLength = s;
	}

	int get_hspeed() const
	{
		return m_hspeed;
	}

	void set_hspeed(int s)
	{
		m_hspeed = s;
	}

	bool get_damaged() const
	{
		return m_hasDamaged;
	}

	virtual bool isCollisionAvoidanceWorthy() const;

private:

	int m_planLength;
	int m_hspeed;
	bool m_hasDamaged;

};






//===================================================//
//===============PEDESTRIAN==========================//

class Pedestrian : public Agent
{
public:
	Pedestrian(int imageID, double x, double y, double size, StudentWorld* sw);
	virtual ~Pedestrian() {};

	// GEt movement plan

	int get_movement_plan() const;

	// Get the pedestrian's horizontal speed
	int getHorizSpeed() const;

	// Set the pedestrian's horizontal speed
	void setHorizSpeed(int s);

	// Move the pedestrian.  If the pedestrian doesn't go off screen and
	// should pick a new movement plan, pick a new plan.
	void moveAndPossiblyPickPlan();

	virtual int soundWhenHurt()
	{
		return SOUND_PED_HURT;
	}

	// What sound should play when this agent is damaged and dies?
	virtual int soundWhenDie()
	{
		return SOUND_PED_DIE;
	};

private:
	int m_hspeed;
	int m_movement_plan;
};





//===================================================//
//=============== Human Pedestrians ==========================//

class HumanPedestrian : public Pedestrian
{
public:
	HumanPedestrian(double x, double y, StudentWorld* sw);
	virtual ~HumanPedestrian() {};
	virtual void doSomething();
	virtual bool beSprayedIfAppropriate();
	
};





//===================================================//
//=============== Zombie Pedestrians ==========================//

class ZombiePedestrian : public Pedestrian
{
public:
	ZombiePedestrian(double x, double y, StudentWorld* sw);
	virtual void doSomething();
	virtual bool beSprayedIfAppropriate();
private:
	bool has_damaged;
	int m_ticks;

};






//**********************************************************************************//
//=============== Spray (Holy Water) ==========================//

class Spray : public Actor
{
public:
	Spray(double x, double y, int dir, StudentWorld* sw);
	virtual ~Spray() {};
	virtual void doSomething();
private:
	
	int m_pixels;
};







//**********************************************************************************//
//=============== Activated objects ==========================//

class GhostRacerActivatedObject : public Actor
{
public:
	GhostRacerActivatedObject(int imageID, double x, double y, double size, int depth, StudentWorld* sw)
		: Actor(imageID, x, y, 0, size, depth, sw)
	{
		set_vspeed(-4);
	}
	virtual ~GhostRacerActivatedObject() {};

	virtual bool beSprayedIfAppropriate()
	{
		return true;
	}

	// Do the object's special activity (increase health, spin Ghostracer, etc.)
	virtual void doActivity(GhostRacer* gr) = 0;

	// Return the object's increase to the score when activated.
	virtual int getScoreIncrease() const = 0;

	// Return the sound to be played when the object is activated.
	virtual int getSound() const
	{
		return SOUND_GOT_GOODIE;
	}

	// Return whether the object dies after activation.
	virtual bool selfDestructs() const = 0;

	// Return whether the object is affected by a holy water projectile.
	virtual bool isSprayable() const = 0;

};





//=============================================//
//================OIL SLICK================//
class OilSlick : public GhostRacerActivatedObject
{
public:
	OilSlick(double x, double y, StudentWorld* sw);
	virtual ~OilSlick() {};
	virtual void doSomething();
	virtual void doActivity(GhostRacer* gr);
	virtual int getScoreIncrease() const
	{
		return -1;
	}
	virtual int getSound() const;
	virtual bool selfDestructs() const
	{
		return false;
	}
	virtual bool isSprayable() const;
};





//=================================================//
//================ Holy water Goodie =======================//

class HolyWaterGoodie : public GhostRacerActivatedObject
{
public:
	HolyWaterGoodie(double x, double y, StudentWorld* sw);
	virtual ~HolyWaterGoodie() {};
	virtual void doSomething();

	virtual void doActivity(GhostRacer* gr);
	virtual int getScoreIncrease() const;
	virtual bool selfDestructs() const;
	virtual bool isSprayable() const;
};




//=================================================
//================ Soul Goodie =======================

class SoulGoodie : public GhostRacerActivatedObject
{
public:
	SoulGoodie(double x, double y, StudentWorld* sw);

	virtual ~SoulGoodie() {};
	virtual void doSomething();
	virtual void doActivity(GhostRacer* gr);
	virtual int getScoreIncrease() const;
	virtual int getSound() const;
	virtual bool selfDestructs() const;
	virtual bool isSprayable() const;
};



//=================================================//
//================ Healing Goodie =======================//

class HealingGoodie : public GhostRacerActivatedObject
{
public:
	HealingGoodie(double x, double y, StudentWorld* sw);
	virtual ~HealingGoodie() {};
	virtual void doSomething();
	virtual void doActivity(GhostRacer* gr);
	virtual int getScoreIncrease() const;
	virtual bool selfDestructs() const;
	virtual bool isSprayable() const;
};





//**********************************************************************************//
//================BORDERLINE================//

class BorderLine :public Actor
{
public:
	BorderLine(int imageID, double startX, double startY, StudentWorld* stWorld);
	virtual ~BorderLine() {};
	void doSomething();

private:



};




//=============================================//
//================YELLOWLINE================//

class YellowLine :public BorderLine
{
public:
	YellowLine(double startX, double startY, StudentWorld* stWorld);
	virtual ~YellowLine() {};

private:

};




//=============================================//
//================WHITELINE================//

class WhiteLine :public BorderLine
{
public:
	WhiteLine(double startX, double startY, StudentWorld* stWorld);
	virtual ~WhiteLine() {};

private:

};







#endif // ACTOR_H_
