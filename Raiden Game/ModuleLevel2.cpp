#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleLevel1.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleLevel2.h"
#include "ModuleFadeToBlack.h"
#include "ModuleIntro.h"
#include "ModuleAudio.h"


// Reference at https://youtu.be/6OlenbCC4WI?t=382

ModuleLevel2::ModuleLevel2()
{

	
	// Background / sky
	background.x = 0;
	background.y = 0;
	background.w = 302;
	background.h = 5362;
}
ModuleLevel2::~ModuleLevel2()
{}

// Load assets
bool ModuleLevel2::Start()
{
	App->render->camera.x = 0; //initial pos
	App->render->camera.y = 0;

	LOG("Loading background assets");

	bool ret = true;
	graphics = App->textures->Load("Assets/Images/lvl2_tilemap.png");

	
	
	App->player->Enable();
	music_lvl2 = App->audio->Load_Music("Assets/Audio/00_Raiden.ogg");
	if (!music_lvl2) {
		LOG("Error loading lvl1 music: %s", Mix_GetError)
	}
	App->audio->Play_Music(music_lvl2);

	return ret;
}

// Load assets
bool ModuleLevel2::CleanUp()
{
	
	LOG("Unloading level 2");

	App->textures->Unload(graphics);

	App->player->Disable();

	


	return true;
}

// Update: draw background
update_status ModuleLevel2::Update()
{
	int scroll_speed = 0.5f;

	App->player->position.y += 1;
	App->render->camera.y += 2;
	
	App->render->Blit(graphics, -50,-5100 , &background, 0.75f); // back of the room
	

	if (App->input->keyboard[SDL_SCANCODE_TAB] && fading == false) {

		App->fade->FadeToBlack(this, App->intro);
		fading = true;
	}

	return UPDATE_CONTINUE;
}