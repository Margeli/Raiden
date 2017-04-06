#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 12

class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModuleAudio;
class ModuleIntro;
class ModuleLevel1;
class ModuleLevel2;
class ModulePlayer;
class ModuleFadeToBlack;
class ModuleParticles;
class ModuleStageCompleted;
class Module;


class Application
{
public:

	Module* modules[NUM_MODULES];
	ModuleWindow* window;
	ModuleRender* render;
	ModuleInput* input;
	ModuleTextures* textures;
	ModuleAudio* audio;
	ModuleStageCompleted* StageCleared;
	ModuleIntro* intro;
	ModuleLevel1* level1;
	ModuleLevel2* level2;
	ModulePlayer* player;
	ModuleFadeToBlack* fade;
	ModuleParticles*particles;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__