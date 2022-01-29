#include <iostream>
#include <SDL.h>
#include <memory>
#include <vector>

#include "sdlrenderer.h"

void run_sdl()
{
  std::shared_ptr<Renderer> renderer(new SDLRenderer);

  bool quit = false;
  size_t start = SDL_GetTicks();
  size_t frames = 0;
  do
  {
    ++frames;
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0)
    {
      switch (e.type)
      {
      case SDL_QUIT:
      {
        quit = true;
        break;
      }
      case SDL_KEYDOWN:
      {
        switch (e.key.keysym.sym)
        {
        case SDLK_ESCAPE:
        {
          quit = true;
          break;
        }
        case SDLK_w:
        {
          SDL_SetWindowFullscreen(renderer->win.get(), 0);
          int w, h;
          SDL_GetWindowSize(renderer->win.get(), &w, &h);
          start = SDL_GetTicks();
          frames = 0;
          std::cout << "Window: " << w << "x" << h << std::endl;
          break;
        }
        case SDLK_f:
        {
          SDL_SetWindowFullscreen(renderer->win.get(), SDL_WINDOW_FULLSCREEN);
          start = SDL_GetTicks();
          frames = 0;
          std::cout << "FULLSCREEN" << std::endl;
          break;
        }
        case SDLK_d:
        {
          SDL_SetWindowFullscreen(renderer->win.get(), SDL_WINDOW_FULLSCREEN_DESKTOP);
          start = SDL_GetTicks();
          frames = 0;
          std::cout << "FULLSCREEN_DESKTOP" << std::endl;
          break;
        }
        case SDLK_p:
        {
          const size_t now = SDL_GetTicks();
          const size_t fps = 1000 * frames / (now - start);
          std::cout << "FPS: " << fps << " frames: " << frames << std::endl;
          start = now;
          frames = 0;
          break;
        }
        case SDLK_0:
        {
          SDL_GL_SetSwapInterval(0);
          std::cout << "GL swap = 0" << std::endl;
          start = SDL_GetTicks();
          frames = 0;
          break;
        }
        case SDLK_1:
        {
          SDL_GL_SetSwapInterval(1);
          std::cout << "GL swap = 1" << std::endl;
          start = SDL_GetTicks();
          frames = 0;
          break;
        }
        }
        break;
      }
      }
    }

    // applewin fills the buffer
    for (size_t i = 0; i < renderer->buffer.size(); ++i)
    {
      // just loop and increment all greys;
      ++renderer->buffer[i];
    }

    renderer->show();

  } while (!quit);
}

int main()
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
    return 1;
  }

  try
  {
    run_sdl();
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << std::endl;
  }

  SDL_Quit();

  return 0;
}
