#ifndef __LIGHTSHOOTER_SPACESHIP_H__
#define __LIGHTSHOOTER_SPACESHIP_H__

#include "Enemy.h"
#include "ModuleParticles.h"

class LightShooter_Spaceship : public Enemy
{
private:


	Animation up;
	Animation down;
	Animation left;
	Animation right;
	Animation down_right;
	Animation right_up;
	Animation up_left;
	Animation left_down;

	float speed;
	float increment_y;
	float initial_y;		
	void Shot(Particle& shot, iPoint aim_position, fPoint shot_initial_pos);	
	bool shooting;

	





public:

	LightShooter_Spaceship(int x, int y, int count);
	void Move();
	



};

#endif //__LIGHTSHOOTER_SPACESHIP__