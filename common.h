#pragma once

#include <SDL.h>
#include <memory>

class Renderer
{
public:
  virtual ~Renderer() {}
  virtual void show() = 0;

  std::shared_ptr<SDL_Window> win;

protected:
  // values from AppleWin
  static constexpr int width = 600;  // GetFrameBufferWidth();
  static constexpr int height = 420; // GetFrameBufferHeight();
  static constexpr int sx = 20;      // GetFrameBufferBorderWidth();
  static constexpr int sy = 18;      // GetFrameBufferBorderHeight();
  static constexpr int sw = 560;     // GetFrameBufferBorderlessWidth();
  static constexpr int sh = 384;     // GetFrameBufferBorderlessHeight();
};
