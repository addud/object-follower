#include "Stub.h"

#ifdef _MSC_VER
#include "SDL.h"

#pragma comment(lib, "SDL.lib")
#pragma comment(lib, "SDLmain.lib")

#endif

static SDL_Surface *screen = NULL;
static int timer = 0;

void display_gui()
{
	bool fullscreen = false;

	// Initialize SDL's subsystems - in this case, only video.
	if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) 
	{
		fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
		exit(1);
	}

	timer = SDL_GetTicks();

	// Register SDL_Quit to be called at exit; makes sure things are
	// cleaned up when we quit.
	 atexit(SDL_Quit);
	if (fullscreen)
		screen = SDL_SetVideoMode(100,64,16, SDL_DOUBLEBUF | SDL_SWSURFACE | SDL_FULLSCREEN);
	else
		screen = SDL_SetVideoMode(100,64,16, SDL_DOUBLEBUF | SDL_SWSURFACE);
  // If we fail, return error.
  if ( screen == NULL ) 
  {
    fprintf(stderr, "Unable to set 100x64 video: %s\n", SDL_GetError());
    exit(1);
  }
}

void display_bitmap_copy(const unsigned char* lcd, int width, int height, int x, int y)
{
	if (SDL_MUSTLOCK(screen) != 0)
	{
		if (SDL_LockSurface(screen) < 0)
		{
			fprintf(stderr, "screen locking failed\n");
			return;
		}
	}

	int tpitch = screen->pitch / 2;

	Uint16* tp = (Uint16*) screen->pixels;

	SDL_Rect rect;

	rect.x = 0;
	rect.y = 0;
	rect.w = 100;
	rect.h = 64;

	SDL_FillRect(SDL_GetVideoSurface(), &rect, 0xffffffff);

	for (int j = 0; j < 64; ++j)
	{
		for (int i = 0; i < 100; ++i)
		{
			if(lcd[((j*100) + i)/8] & (1<<(((j*100) + i)%8)))
			{
				tp[i] = 0x0000;
			}
		}
		tp += tpitch;
	}

	if (SDL_MUSTLOCK(screen))
	{
		SDL_UnlockSurface(screen);
	}
}

void display_update()
{
	SDL_Event event;

	while (SDL_PollEvent(&event)) 
	{
		switch (event.type) 
		{
			case SDL_KEYUP:
			// If escape is pressed, return (and thus, quit)
			if (event.key.keysym.sym == SDLK_ESCAPE)
			  exit(0);
				break;
		}
	}
	while(SDL_GetTicks() - timer < 15)
	{
	}

	timer = SDL_GetTicks();
	SDL_Flip(screen);   
}