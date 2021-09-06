#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

Actor::Actor(int imageID, double startX, double startY, int startDir, double size, int depth, StudentWorld* stWorld)
	: GraphObject(imageID, startX, startY, startDir, size, depth)
{
	m_stWorld = stWorld;
	m_status = true;
	m_vspeed = 0;

	m_depth = depth;

}


StudentWorld* Actor::getWorld() const
{
	return m_stWorld;
}


bool Actor::isAlive() const
{
	return m_status;
}

void Actor::setDead()
{
	m_status = false;
}

int Actor::get_vspeed() const
{
	return m_vspeed;
}




void Actor::set_vspeed(int vspeed)
{
	m_vspeed = vspeed;
}

bool Actor::beSprayedIfAppropriate()
{
	return false;
}

bool Actor::isCollisionAvoidanceWorthy() const
{
	return false;
}

//================== Agent ==================================//
//==================================================================//

Agent::Agent(int imageID, double startX, double startY, int startDir, double size, int depth, StudentWorld* stWorld, int startPoints)
	: Actor(imageID, startX, startY, startDir, size, depth, stWorld)
{
	m_hPoints = startPoints;
}

int Agent::getHPoints()
{
	return m_hPoints;
}

void Agent::dec_hPoints(int value)
{
	m_hPoints = m_hPoints - value;
}

void Agent::inc_hPoints(int value)
{
	m_hPoints = m_hPoints + value;
}

bool Agent::isCollisionAvoidanceWorthy() const
{
	return true;
}


//==============GHOSTRACER'S CLASS=================================//
//=================================================================//
GhostRacer::GhostRacer(StudentWorld* stWorld)
	: Agent(IID_GHOST_RACER, 128, 32, 90, 4.0, 0, stWorld, 100)
{

	m_numSprays = 10;
}


void GhostRacer::doSomething()
{

	if (!isAlive())
		return;

	// check if the car goes out of the boundary


	if (getX() <= (double)ROAD_CENTER - ROAD_WIDTH / 2)
	{
		if (getDirection() > 90)
			dec_hPoints(10);

		setDirection(82);
		//play sound
		getWorld()->playSound(SOUND_VEHICLE_CRASH);
	}

	if (getX() >= (double)ROAD_CENTER + ROAD_WIDTH / 2)
	{
		if (getDirection() < 90)
			inc_hPoints(10);


		setDirection(98);
		// play sound

		getWorld()->playSound(SOUND_VEHICLE_CRASH);
	}

	// getting user input & changing speed and direction
	int ch;
	if (getWorld()->getKey(ch))
	{
		switch (ch)
		{
		case KEY_PRESS_LEFT:
			if (getDirection() < 114)
				setDirection(getDirection() + 8);
			break;
		case KEY_PRESS_RIGHT:
			if (getDirection() > 66)
				setDirection(getDirection() - 8);
			break;
		case KEY_PRESS_UP:
			if (get_vspeed() < 5)
				set_vspeed(get_vspeed() + 1);
			break;
		case KEY_PRESS_DOWN:
			if (get_vspeed() > -1)
				set_vspeed(get_vspeed() - 1);
			break;
		case KEY_PRESS_SPACE:
			if (getNumSprays() >= 1)
			{
				// Adding spray

				int dir = getDirection(); 

				if (dir == 90)
				{
					getWorld()->addActor(new Spray(getX() , getY() + SPRITE_HEIGHT , dir, getWorld()));
				}
				else if (dir < 90)
					getWorld()->addActor(new Spray(getX() + SPRITE_WIDTH * cos(dir/180), getY() + SPRITE_HEIGHT, dir, getWorld()));
				
				else 
					getWorld()->addActor(new Spray(getX() - SPRITE_WIDTH * cos(dir / 180), getY() + SPRITE_HEIGHT, dir, getWorld()));
				
				// Play Sound
				getWorld()->playSound(SOUND_PLAYER_SPRAY);

				// Decrease Spray
				increaseSprays(-1);
			}
			break;
		default:
			break;


		}



	}

	double max_shift_per_tick = 4.0;
	int direction = getDirection();
	double pi = 3.14159;
	double delta_x = cos(direction * pi / 180) * max_shift_per_tick;
	double cur_x = getX();
	double cur_y = getY();

	cur_x = cur_x + delta_x;
	moveTo(cur_x, cur_y);


	if (this->getHPoints() <= 0)
		setDead();


}

int GhostRacer::soundWhenDie() const
{
	return SOUND_PLAYER_DIE;
}
int GhostRacer::getNumSprays() const
{
	return m_numSprays;
}

// Increase the number of holy water projectiles the object has.
void GhostRacer::increaseSprays(int amt)
{
	m_numSprays = m_numSprays + amt;
}

void  GhostRacer::spin()
{
	
	

	int turn = randInt(0, 1);

	int rand;
	rand = (turn == 0) ? (rand = randInt(5, 20)) : (rand = randInt(-20, -5));

	// change direction
	int dir = getDirection() + rand;

	if (dir < 60)
		setDirection(60);
	else if (dir > 120)
		setDirection(120);
	else
		setDirection(dir);

}

//=======================================//
//=============BORDERLINE================//

BorderLine::BorderLine(int imageID, double startX, double startY, StudentWorld* stWorld)
	: Actor(imageID, startX, startY, 0, 2.0, 1, stWorld)
{

	set_vspeed(-4);


}

void BorderLine::doSomething()
{
	GhostRacer* car = getWorld()->getCar();
	int v_speed = get_vspeed() - car->get_vspeed();
	int h_speed = 0;
	double new_y = getY() + v_speed;
	double new_x = getX() + h_speed;
	moveTo(new_x, new_y);

	if (getY() < 0 || getY() > VIEW_HEIGHT)
		setDead();
}


//=============================================//
//================YELLOWLINE================//

YellowLine::YellowLine(double startX, double startY, StudentWorld* stWorld)
	:BorderLine(IID_YELLOW_BORDER_LINE, startX, startY, stWorld)
{}

//=============================================//
//================WHITELINE================//

WhiteLine::WhiteLine(double startX, double startY, StudentWorld* stWorld)
	:BorderLine(IID_WHITE_BORDER_LINE, startX, startY, stWorld)
{}

//=================================================//
//================OIL-SLICk=======================//

OilSlick::OilSlick(double startX, double startY, StudentWorld* stWorld)
	: GhostRacerActivatedObject(IID_OIL_SLICK, startX, startY, (double)randInt(2, 5), 1, stWorld)

{
	set_vspeed(-4);
}

void OilSlick::doSomething()
{


	GhostRacer* car = getWorld()->getCar();
	int v_speed = get_vspeed() - car->get_vspeed();
	int h_speed = 0;
	double new_y = getY() + v_speed;
	double new_x = getX() + h_speed;
	moveTo(new_x, new_y);

	if (getY() < 0 || getY() > VIEW_HEIGHT)
		setDead();

	// oil slicks overlap GhostRacer

	if (getWorld()->overlaps(car, this) == true)
	{
		doActivity(car);
	}
}

void OilSlick::doActivity(GhostRacer* gr)
{

	getWorld()->playSound(getSound());
	gr->spin();
	

}



int OilSlick::getSound() const
{
	return SOUND_OIL_SLICK;
}



bool OilSlick::isSprayable() const
{
	return false;
}

//=================================================//
//================ Holy water Goodie =======================//

HolyWaterGoodie::HolyWaterGoodie(double x, double y, StudentWorld* sw)
	: GhostRacerActivatedObject(IID_HOLY_WATER_GOODIE, x, y, 2.0, 0, sw)
{
	setDirection(90);
}

void HolyWaterGoodie::doSomething()
{
	GhostRacer* car = getWorld()->getCar();
	int v_speed = get_vspeed() - car->get_vspeed();
	int h_speed = 0;
	double new_y = getY() + v_speed;
	double new_x = getX() + h_speed;
	moveTo(new_x, new_y);

	if (getY() < 0 || getY() > VIEW_HEIGHT)
	{
		setDead();
		return;
	}

	if (getWorld()->overlaps(this, car))
		doActivity(car);
}
void HolyWaterGoodie::doActivity(GhostRacer* gr)
{
	// increase holy water
	gr->increaseSprays(10);

	// set it dead
	this->setDead();

	// play sound
	getWorld()->playSound(SOUND_GOT_GOODIE);

	// increse score
	getWorld()->increaseScore(getScoreIncrease());

}
int HolyWaterGoodie::getScoreIncrease() const
{
	return 50;
}
bool HolyWaterGoodie::selfDestructs() const
{
	return true;
}
bool HolyWaterGoodie::isSprayable() const
{
	return true;
}


//=================================================//
//================Soul Goodie =======================//


SoulGoodie::SoulGoodie( double x, double y, StudentWorld* sw)
	:GhostRacerActivatedObject(IID_SOUL_GOODIE, x, y, 4.0, 2, sw)
{

}

void SoulGoodie::doSomething()
{
	// move
	GhostRacer* car = getWorld()->getCar();
	int v_speed = get_vspeed() - car->get_vspeed();
	int h_speed = 0;
	double new_y = getY() + v_speed;
	double new_x = getX() + h_speed;
	moveTo(new_x, new_y);


	// out of the boundary
	if (getY() < 0 || getY() > VIEW_HEIGHT)
	{
		setDead();
		return;
	}

	// if it overlaps with GhostRacer
	if (getWorld()->overlaps(this, car))
	{
		doActivity(car);
	}


	// rotate 10 deg clockwise
	setDirection(getDirection() - 10);
}
void SoulGoodie::doActivity(GhostRacer* gr)
{
	
		// tell the world record
		getWorld()->recordSoulSaved();

		// set it dead
		setDead();

		// play sound
		getWorld()->playSound(getSound());
		
		// increase score
		getWorld()->increaseScore(getScoreIncrease());
}
int SoulGoodie::getScoreIncrease() const
{
	return 100;

}
int SoulGoodie::getSound() const
{
	return SOUND_GOT_SOUL;
}
bool SoulGoodie::selfDestructs() const
{
	return true;
}
bool SoulGoodie::isSprayable() const
{
	return false;
}

//=================================================//
//================Healing goodie =======================//
HealingGoodie::HealingGoodie(double x, double y, StudentWorld* sw)
	: GhostRacerActivatedObject (IID_HEAL_GOODIE, x, y, 1.0, 2, sw)
{

}



void HealingGoodie::doSomething()
{
	// move
	GhostRacer* car = getWorld()->getCar();
	int v_speed = get_vspeed() - car->get_vspeed();
	int h_speed = 0;
	double new_y = getY() + v_speed;
	double new_x = getX() + h_speed;
	moveTo(new_x, new_y);


	// out of the boundary
	if (getY() < 0 || getY() > VIEW_HEIGHT)
	{
		setDead();
		return;
	}

	// if it overlaps with GhostRacer
	if (getWorld()->overlaps(this, car))
	{
		doActivity(car);
	}

}
void HealingGoodie::doActivity(GhostRacer* gr)
{
	gr->inc_hPoints(10);
	this->setDead();

	getWorld()->playSound(SOUND_GOT_GOODIE);

	getWorld()->increaseScore(getScoreIncrease());
	

}
int HealingGoodie::getScoreIncrease() const
{
	return 250;
}
bool HealingGoodie::selfDestructs() const
{
	return true;
}
bool HealingGoodie::isSprayable() const
{
	return true;
}

//=================================================//
//================Zombie's cab =======================//

ZombieCab::ZombieCab(double startX, double startY, StudentWorld* stWorld)
	: Agent(IID_ZOMBIE_CAB, startX, startY, 90, 4.0, 0, stWorld, 3)
{
	set_vspeed(0);
	m_planLength = 0;
	m_hspeed = 0;
	m_hasDamaged = false;

}

int ZombieCab::get_planLength() const
{
	return m_planLength;
}
void ZombieCab::doSomething()
{
	if (isAlive() == false)
		return;


	GhostRacer* car = getWorld()->getCar();

	// overlap with GC
	
		if (getWorld()->overlaps(this, car))
		{
			if (get_damaged() == false)
			{

				getWorld()->playSound(SOUND_VEHICLE_CRASH);

				// decrease health
				car->dec_hPoints(20);

				// cab is on the left or same x
				if ( getX() < car->getX() || getX() == car->getX())
				{
					set_hspeed (-5);
					setDirection(60 + randInt(0, 20));
				}

				// cab is on the right 
				if (getX() > car->getX())
				{
					set_hspeed (5);
					setDirection(120 - randInt(0, 20));
				}
				m_hasDamaged = true;
				return;
			}
			

		}
		

	
	// move
	int v_speed = get_vspeed() - car->get_vspeed();
	int h_speed = get_hspeed();
	double new_y = getY() + v_speed;
	double new_x = getX() + h_speed;
	moveTo(new_x, new_y);

	// Out of boundary

	if (getX() < 0 || getX() > VIEW_WIDTH || getY() < 0 || getY() > VIEW_HEIGHT)
	{
		setDead();
		return;
	}

	


	// zombie cab gets damaged

	if (getHPoints() <= 0)
	{
		double x = getX();
		double y = getY();
		setDead();
		getWorld()->playSound(SOUND_PED_DIE);
		if (randInt(1, 5) == 1)
			getWorld()->addActor(new HealingGoodie(x, y, getWorld()));
		getWorld()->increaseScore(200);
		return;
	}

}
bool  ZombieCab::beSprayedIfAppropriate()

{
	dec_hPoints(1);
	return true;
}

bool ZombieCab::isCollisionAvoidanceWorthy() const
{
	return true;
}
//=================================================//
//================ Pedestrian =======================//
Pedestrian::Pedestrian(int imageID, double x, double y, double size, StudentWorld* sw)
	:Agent(imageID, x, y, 0, size, 0, sw, 2)
{
	set_vspeed(-4);
	m_hspeed = 0;
	m_movement_plan = 0;
}

// Get the pedestrian's horizontal speed
int Pedestrian::getHorizSpeed() const
{
	return m_hspeed;
}

// Set the pedestrian's horizontal speed
void Pedestrian::setHorizSpeed(int s)
{
	m_hspeed = s;
}

void Pedestrian::moveAndPossiblyPickPlan()
{
	
	GhostRacer* car = getWorld()->getCar();
	int vert_speed = get_vspeed() - car->get_vspeed();
	int horiz_speed = getHorizSpeed();
	double new_y = getY() + vert_speed;
	double new_x = getX() + horiz_speed;
	moveTo(new_x, new_y);

	if (getX() < 0 || getX() > VIEW_WIDTH || getY() < 0 || getY() > VIEW_HEIGHT)
	{
		setDead();
		return;
	}

	int move_plan = get_movement_plan();
	move_plan--;

	if (move_plan > 0)
	{		
		return;
	}
	else
	{
		// Set  horizontal speed to a random integers -3 -> 3, excluding 0
		int h_speed = randInt(-3, 3);

		if (h_speed != 0)
			setHorizSpeed(h_speed);

		// set the length of the movement plan
		
		m_movement_plan = randInt(4, 32);

		// Set zombie direction

		if (getHorizSpeed() < 0)
			setDirection(180);
		else
			setDirection(0);

	}
}

int  Pedestrian::get_movement_plan() const
{
	return m_movement_plan;
}


//=================================================//
//================ Human Pedestrian =======================//

HumanPedestrian::HumanPedestrian(double x, double y, StudentWorld* sw)
	:Pedestrian(IID_HUMAN_PED, x, y, 2.0, sw)
{
	set_vspeed(-4);
}

void HumanPedestrian::doSomething()
{

	// If human is alive

	if (!isAlive())
		return;

	GhostRacer* car = getWorld()->getCar();

	// if human overlap  with GhostRacer

	if (getWorld()->overlaps(this, car))
	{
		getWorld()->playSound(SOUND_PLAYER_DIE);
		getWorld()->decLives();
		car->setDead();
		return;
	}

	// If human is alive
	moveAndPossiblyPickPlan();

	

}


bool HumanPedestrian::beSprayedIfAppropriate()
{
	
	// Changes horiz movement
	setHorizSpeed(getHorizSpeed() * (-1));

	// Changes direction
	if (getDirection() <= 0)
		setDirection(180);
	if (getDirection() >= 180)
		setDirection(0);


	return true;
}


//=================================================//
//================ zombie Pedestrian =======================//

ZombiePedestrian::ZombiePedestrian(double x, double y, StudentWorld* sw)
	:Pedestrian(IID_ZOMBIE_PED, x, y, 3.0, sw)
{
	set_vspeed(-4);
	has_damaged = false;
	m_ticks = 0;
}

void ZombiePedestrian::doSomething()
{

	// If zombie is dead

	if (!isAlive())
		return;


	// If zombie is alive
	GhostRacer* car = getWorld()->getCar();

	// if zombie overlap with GhostRacer
	
	if (getWorld()->overlaps(this, car))
	{
		if (has_damaged == false)
		{
			
			car->dec_hPoints(5);
			this->dec_hPoints(2);
			has_damaged = true;
			return;
		}
		
	}


	// If zombie is either left or right and in front of the GhostRacer

	if (abs(getX() - car->getX()) <= 30.0 && getY() > car->getY())
	{
		// Zomebie faces down
		setDirection(270);

		// Zombie is on the left of GC
		if (getX() < car->getX())
			setHorizSpeed(1);

		// Zombie is on the right of GC
		else if (getX() > car->getX())
			setHorizSpeed(-1);
		else
			setHorizSpeed(0);

		// Ticks next grunts
		m_ticks--;

		if (m_ticks <= 0)
		{
			getWorld()->playSound(SOUND_ZOMBIE_ATTACK);
			m_ticks = 20;
		}
	}


	

	// move and pick Plan
	moveAndPossiblyPickPlan();
	

	if (getHPoints() <= 0)
	{
		setDead();

		getWorld()->playSound(soundWhenDie());

		// if it is alive and 1/15 chance adding Healing Goodie 
		if (isAlive() && randInt(1, 15) == 1)
		{
			getWorld()->addActor(new HealingGoodie(getX(), getY(), getWorld()));
		}


		// increase Score
		getWorld()->increaseScore(150);

	}



}
bool ZombiePedestrian::beSprayedIfAppropriate()
{
	// decrease 1 point;
	dec_hPoints(1);

	return true;
}

//===================================================//
//=============== Spray (Holy Water) ==========================//

Spray::Spray(double x, double y, int dir, StudentWorld* sw)
	:Actor(IID_HOLY_WATER_PROJECTILE, x, y, dir, 1.0, 1, sw)
{
	m_pixels = 0;
}

void Spray::doSomething()
{
	if (!isAlive())
		return;


	// Check if it is activated
	if (getWorld()->sprayFirstAppropriateActor(this) == true)
	{
		setDead();
		return;
	}


	// Otherwise, the spray moves forward

	moveForward(SPRITE_HEIGHT);
	m_pixels = m_pixels + SPRITE_HEIGHT;

	// go off the screen
	if (getX() < 0 || getX() > VIEW_WIDTH || getY() < 0 || getY() > VIEW_HEIGHT)
	{
		setDead();
		return;
	}



	// Travel over 160 pix
	if (m_pixels == 160)
		setDead();
}


