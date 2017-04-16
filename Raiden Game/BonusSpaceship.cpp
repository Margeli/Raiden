#include "Application.h"
#include "BonusSpaceship.h"
#include "ModuleCollision.h"

Bonus_Spaceship::Bonus_Spaceship (int x, int y) : Enemy(x, y) 
{
	fly.PushBack({ 45,43,59,50 });
	fly.PushBack({ 116,43,59,50 });
	fly.PushBack({ 184,43,59,50 });
	fly.PushBack({ 252,43,59,50 });
	fly.PushBack({ 319,43,59,50 });
	animation = &fly;

	
	collider = App->collision->AddCollider({ 0, 0, 35, 28 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

}

