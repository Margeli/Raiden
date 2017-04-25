#ifndef __BONUS_SPACESHIP_H__
#define __BONUS_SPACESHIP_H__

#include "Enemy.h"
#include "ModuleParticles.h"

class Bonus_Spaceship : public Enemy
{
private:

	
	Animation idle;
	Animation forward;
	Animation boost;
	Particle color_rotatory_shot;

	float hits_life;
	float speed ;
	float increment_y;
	float initial_y;
	int counter_movement;
	bool right;
	void Shot(Particle& shot, iPoint aim_position, fPoint shot_initial_pos);
	//void ShotMovement();
	bool shooting ;
	uint score_points;


	float m;//
	float delta_x;
	float delta_y ;
	float vector_lenght = 0.0f;
	fPoint unitary;

	void OnCollision(Collider* collider, int num_enemy);

	Particle explosion;

	Mix_Chunk* fx_shoot = nullptr;


public:

	Bonus_Spaceship(int x, int y, int count);
	void Move();
	int shoots = 3;



	

};

#endif // __BONUS_SPACESHIP_H__