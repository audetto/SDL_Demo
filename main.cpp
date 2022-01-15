#include <iostream>
#include <SDL.h>
#include <memory>
#include <vector>

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

void run_sdl()
{
  // values from AppleWin
  const int width = 600;  // GetFrameBufferWidth();
  const int height = 420; // GetFrameBufferHeight();
  const int sx = 20;      // GetFrameBufferBorderWidth();
  const int sy = 18;      // GetFrameBufferBorderHeight();
  const int sw = 560;     // GetFrameBufferBorderlessWidth();
  const int sh = 384;     // GetFrameBufferBorderlessHeight();

  std::shared_ptr<SDL_Window> win(SDL_CreateWindow("Demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, sw, sh, SDL_WINDOW_RESIZABLE), SDL_DestroyWindow);
  if (!win)
  {
    std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
    return;
  }

  std::shared_ptr<SDL_Renderer> ren(SDL_CreateRenderer(win.get(), -1, SDL_RENDERER_PRESENTVSYNC), SDL_DestroyRenderer);
  if (!ren)
  {
    std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
    return;
  }
  debuginfo_renderer(ren.get());

  const Uint32 format = SDL_PIXELFORMAT_ARGB8888;
  std::shared_ptr<SDL_Texture> tex(SDL_CreateTexture(ren.get(), format, SDL_TEXTUREACCESS_STREAMING, width, height), SDL_DestroyTexture);

  SDL_Rect srect;
  srect.x = sx;
  srect.y = sy;
  srect.w = sw;
  srect.h = sh;

  std::vector<char> buffer(width * height * 4);

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
          SDL_SetWindowFullscreen(win.get(), 0);
          int w, h;
          SDL_GetWindowSize(win.get(), &w, &h);
          start = SDL_GetTicks();
          frames = 0;
          std::cout << "Window: " << w << "x" << h << std::endl;
          break;
        }
        case SDLK_f:
        {
          SDL_SetWindowFullscreen(win.get(), SDL_WINDOW_FULLSCREEN);
          start = SDL_GetTicks();
          frames = 0;
          std::cout << "FULLSCREEN" << std::endl;
          break;
        }
        case SDLK_d:
        {
          SDL_SetWindowFullscreen(win.get(), SDL_WINDOW_FULLSCREEN_DESKTOP);
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
    for (size_t i = 0; i < buffer.size(); ++i)
    {
      // just loop and increment all greys;
      ++buffer[i];
    }

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
