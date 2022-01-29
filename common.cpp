#include "common.h"

#include <string>
#include <stdexcept>

Renderer::Renderer()
{
  win.reset(SDL_CreateWindow("Demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, sw, sh, SDL_WINDOW_RESIZABLE), SDL_DestroyWindow);
  if (!win)
  {
    throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
  }

  buffer.resize(width * height * 4);
}
