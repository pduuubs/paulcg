#include "paulcg.h"
#include <SDL/SDL.h>
#include <cstdlib>
#include <iostream>
#include <string>

namespace PaulCG {
  int w;
  int h;
  SDL_Surface* scr;
  SDL_Event event = {0};

  ColorRGB::ColorRGB(Uint8 r, Uint8 g, Uint8 b)
  {
    this->r = r;
    this->g = g;
    this->b = b;
  }

  //initialisation de la fenetre
  void screen(int height, int width, bool fullscreen, const std::string& title){
    int colorDepth = 32;
    w = width;
    h = height;

    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
      printf("Problème dans l'initialisation de la SDL : ERREUR : %s\n", SDL_GetError());
      SDL_Quit();
      std::exit(1);
    }
    std::atexit(SDL_Quit);
    if(fullscreen){
      scr = SDL_SetVideoMode(width, height, colorDepth, SDL_SWSURFACE | SDL_FULLSCREEN);
      lock();
    }else{
      scr = SDL_SetVideoMode(width, height, colorDepth, SDL_HWSURFACE | SDL_HWPALETTE);
    }

    if(screen == 0){
      printf("Problème dans l'initialisation de la vidéo : ERREUR : %s\n", SDL_GetError());
      SDL_Quit();
      std::exit(1);
    }
    SDL_WM_SetCaption(title.c_str(), NULL);

    SDL_EnableUNICODE(1);
  }


  void redraw(){
    SDL_UpdateRect(scr, 0, 0, 0, 0);
  }

  void plot(int x, int y, const ColorRGB& color){
    if(x < 0 || y < 0 || x >= w || y >= h) return;
    Uint32 colorSDL = SDL_MapRGB(scr->format, color.r, color.g, color.b);
    Uint32* bufp;
    bufp = (Uint32*)scr->pixels + y * scr->pitch / 4 + x;
    *bufp = colorSDL;
  }

  void lock(){
    if(SDL_MUSTLOCK(scr))
    if(SDL_LockSurface(scr) < 0)
    return;
  }

  void unlock()
  {
    if(SDL_MUSTLOCK(scr))
    SDL_UnlockSurface(scr);
  }

  void sleep(){
    int done = 0;
    SDL_PollEvent(&event);
    while(done == 0)
    {
      while(SDL_PollEvent(&event))
      {
        if(event.type == SDL_QUIT) end();
        if(event.type == SDL_KEYDOWN) done = 1;
      }
      SDL_Delay(5); //so it consumes less processing power
    }
  }

  void end()
  {
    SDL_Quit();
    std::exit(1);
  }
}
