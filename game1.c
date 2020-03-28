#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#undef main

// The man or Alien man
//--------------------------
typedef struct
{
    int x, y;
    int lifetime;
    int dy;
    char *name;

}Alien;
//--------------------------


//The monster which will face the man
//--------------------------
typedef struct
{
    int x, y;

}Monster;
//-------------------------



//The brick or wall
//-------------------------
typedef struct
{
    int x, y, w, h;

}Ledge;
//-------------------------


// Here all the Objects are.
//----------------------------------
typedef struct
{
    Alien alien;
    Monster monster[100];
    Ledge ledge[100];

    SDL_Renderer *renderer;

    SDL_Texture *alienFrames;
    SDL_Texture *brickFrames;
    SDL_Texture *monsterFrame;


}GameStat;
//-----------------------------------


int processEvent(SDL_Window *window, GameStat *gameState)
{

    SDL_Event event;
    int done = 0;

    //Check for event
    while(SDL_PollEvent(&event))
    {
       switch(event.type)
       {
        case SDL_WINDOWEVENT_CLOSE:     //window quite icon.
        {
            if(window)                  // if window exist
            {
             SDL_DestroyWindow(window);
             done = 1;
            }
        }
        break;
        case SDL_KEYDOWN:               // if any key is clicked down.
        {
            switch(event.key.keysym.sym)
            {
              case SDLK_ESCAPE:
                done = 1;
                break;
            }
        }
        break;
        case SDL_QUIT:
            done = 1;
            break;
       }
    }
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if(state[SDL_SCANCODE_LEFT])
    {
        gameState->alien.x -= 10;
    }
    if(state[SDL_SCANCODE_RIGHT])
    {
        gameState->alien.x += 10;
    }
     if(state[SDL_SCANCODE_UP])
    {
        gameState->alien.y -= 10;
    }
    if(state[SDL_SCANCODE_DOWN])
    {
        gameState->alien.y += 10;
    }
    return done;
}
void collisionDetection(GameStat *game)
{
	int i = 0;
	for(i = 0; i < 100; i++)
	{
		int mx = game->alien.x;
		int my = game->alien.y;
		int mh = 64;
		int mw = 64;

		int bx = game->ledge[i].x;
		int by = game->ledge[i].y;
		int bw = game->ledge[i].w;
		int bh = game->ledge[i].h;

	}
}
void loadGame(GameStat *game)
{
    SDL_Surface *alienSurface;
    SDL_Surface *brickSurface;
    int i;

  //-----------------------------------------------------------------------------------

    alienSurface = NULL;
    //Load image to surface
    alienSurface = IMG_Load("images//warrior.gif");

      if(alienSurface == NULL)
    {
        printf("Cannot find the image 0000...\n");
        SDL_Quit();
        exit(1);
    }

    game->alienFrames = SDL_CreateTextureFromSurface(game->renderer, alienSurface);
    SDL_FreeSurface(alienSurface);
  //---------------------------------------------------------------------------------------




   // Loading Brick image to all brickFrames
  //---------------------------------------------------------------------------------------
    brickSurface = IMG_Load("images//brick.png");
      if(brickSurface == NULL)
    {
        printf("Cannot find the image...\n");
        SDL_Quit();
        exit(1);
    }

    game->brickFrames = SDL_CreateTextureFromSurface(game->renderer, brickSurface);
    SDL_FreeSurface(brickSurface);
  //----------------------------------------------------------------------------------------



    //alien x and y
    game->alien.x = 320 - 40;
    game->alien.y = 280;

    for(i = 0; i < 100; i++)
    {
        game->ledge[i].w = 256;
        game->ledge[i].h = 130;
        game->ledge[i].x = i*256;
        game->ledge[i].y = 450;

    }
    game->ledge[99].x = 350;
    game->ledge[99].y = 200;

}
void doRenderer(SDL_Renderer *renderer, GameStat *gameState)
{
    int i = 0;
    //set the window background to blue.
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

    //clear the screen to blue like apply
    SDL_RenderClear(renderer);

    //set drawing color to white.
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  //-------------------------------------------------------------------------


  //----------------------------------------------------------------------------------------------------------------------
    for(i = 0; i < 100; i++)
    {
        SDL_Rect ledgeRec = {gameState->ledge[i].x, gameState->ledge[i].y, gameState->ledge[i].w, gameState->ledge[i].h};
        SDL_RenderCopy(renderer, gameState->brickFrames, NULL, &ledgeRec);
    }
  //----------------------------------------------------------------------------------------------------------------------



    //draw a rectangle.
    //for(int i = 0; i < 100; i++)
    //{
        SDL_Rect rec = {gameState->alien.x, gameState->alien.y, 64, 64};
        SDL_RenderCopyEx(renderer, gameState->alienFrames, NULL, &rec, 0, NULL, 0);
    //}

    //show the rectangle in the window.
    SDL_RenderPresent(renderer);

}
int main(int argc, char* argv[])
{
    SDL_Window *window;
    SDL_Renderer *renderer;

    GameStat gameState;

    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("window1.0",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              640,
                              580,
                              0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    gameState.renderer = renderer;

    //The game starts when its enters the loop
    int done = 0;

  //--------------------
    loadGame(&gameState);
  //---------------------


    srand(time(NULL));py

    while(!done)
    {
        done = processEvent(window, &gameState);

        doRenderer(renderer, &gameState);

       // snake(&man, window, &done);


       // SDL_Delay(10);
    }

    //Free the texture
    SDL_DestroyTexture(gameState.brickFrames);
    SDL_DestroyTexture(gameState.alienFrames);
    //SDL_DestroyTexture(gameState.brickFrames);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    SDL_Quit();

    return 0;
}
