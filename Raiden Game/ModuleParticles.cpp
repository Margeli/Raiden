#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollision.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;	

}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");
		graphics = App->textures->Load("Assets/Images/Particles_Spritesheet.png");

	if (graphics == nullptr) {
		LOG("Error loading particles");
	}	

	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);

	LOG("Unloading fx");
	App->audio->Unload_Fx(fx_shoot);


	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}

// Update: draw background
update_status ModuleParticles::Update()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* p = active[i];

		if (p == nullptr)
			continue;

		if (p->Update() == false)
		{
			delete p;
			active[i] = nullptr;
		}
		else if (SDL_GetTicks() >= p->born)
		{
			App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
			
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(Particle& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay, char* FX_path)
{
	 
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			if (particle.fx_played == false) //Fx sound when shooting
			{

				fx_shoot = App->audio->Load_Fx(FX_path);
				if (!fx_shoot) {
					LOG("Error loading shoot's fx: %s", Mix_GetError)
				}
				App->audio->Play_Fx(fx_shoot);
				particle.fx_played = true;
			}

			Particle* p = new Particle(particle);
			p->born = SDL_GetTicks() + delay;
			p->position.x = x;
			p->position.y = y;
			if (collider_type != COLLIDER_NONE) {
				p->collider = App->collision->AddCollider( p->anim.GetCurrentFrame() , collider_type, this);
				active[i] = p;
				break;
			}
		}
	}
} 
	

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (active[i] != nullptr && active[i]->collider == c1)
		{
			//AddParticle(explosion, active[i]->position.x, active[i]->position.y);
			delete active[i];
			active[i] = nullptr;
			break;
		}
	}
}
// -------------------------------------------------------------
// -------------------------------------------------------------

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) :
	anim(p.anim), position(p.position), speed(p.speed),
	fx(p.fx), born(p.born), life(p.life)
{}

iPoint Particle::GetPos() const {
	return position;
}

Particle::~Particle()
{
	if (collider != nullptr)
		collider->to_delete = true;

}
bool Particle::Update()
{
	bool ret = true;

	if (life > 0)
	{
		if ((SDL_GetTicks() - born) > life)
			ret = false;
	}
	else
		if (anim.Finished())
			ret = false;

	position.x += speed.x;
	position.y += speed.y;
	
	if (collider != nullptr) {
		collider->SetPos(position.x, position.y);
	}

	return ret;
}