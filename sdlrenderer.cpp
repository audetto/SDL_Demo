#include "sdlrenderer.h"

#include <iostream>

namespace
{

  void debuginfo_renderer(SDL_Renderer *r)
  {
    int n = SDL_GetNumRenderDrivers();
    std::cout << "* " << n << " drivers:" << std::endl;
    for (int i = 0; i < n; i++)
    {
      SDL_RendererInfo info;
      SDL_GetRenderDriverInfo(i, &info);
      std::cout << "*   '" << info.name << "'" << std::endl;
    }

    SDL_RendererInfo info = {0};
    if (SDL_GetRendererInfo(r, &info) == 0)
    {
      std::cout << "* SDL_RENDERER_SOFTWARE: " << ((info.flags & SDL_RENDERER_SOFTWARE) > 0) << std::endl;
      std::cout << "* SDL_RENDERER_ACCELERATED: " << ((info.flags & SDL_RENDERER_ACCELERATED) > 0) << std::endl;
      std::cout << "* SDL_RENDERER_PRESENTVSYNC: " << ((info.flags & SDL_RENDERER_PRESENTVSYNC) > 0) << std::endl;
      std::cout << "* SDL_RENDERER_TARGETTEXTURE: " << ((info.flags & SDL_RENDERER_TARGETTEXTURE) > 0) << std::endl;
      std::cout << "* active renderer -> '" << info.name << "'" << std::endl;
    }
    else
    {
      std::cout << "NO Renderinfo" << std::endl;
    }
  }

}

SDLRenderer::SDLRenderer()
{
  ren.reset(SDL_CreateRenderer(win.get(), -1, SDL_RENDERER_PRESENTVSYNC), SDL_DestroyRenderer);
  if (!ren)
  {
    throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
  }
  debuginfo_renderer(ren.get());

  const Uint32 format = SDL_PIXELFORMAT_ARGB8888;
  tex.reset(SDL_CreateTexture(ren.get(), format, SDL_TEXTUREACCESS_STREAMING, width, height), SDL_DestroyTexture);

  srect.x = sx;
  srect.y = sy;
  srect.w = sw;
  srect.h = sh;
}

void SDLRenderer::show()
{
#if 0
  // slower: 77% CPU (from top on a Pi3)
  void * pixels;
  int pitch;
  SDL_LockTexture(tex.get(), nullptr, &pixels, &pitch);
  memcpy(pixels, buffer.data(), width * height * 4);
  SDL_UnlockTexture(tex.get());
#else
  // faster: 66% CPU (from top on a Pi3)
  SDL_UpdateTexture(tex.get(), nullptr, buffer.data(), width * 4);
#endif

  SDL_RenderCopyEx(ren.get(), tex.get(), &srect, nullptr, 0.0, nullptr, SDL_FLIP_VERTICAL);
  SDL_RenderPresent(ren.get());
}
