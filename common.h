#pragma once

#include <SDL.h>
#include <memory>
#include <vector>

class Renderer
{
public:
  Renderer();
  virtual ~Renderer() {}
  virtual void show() = 0;

  std::shared_ptr<SDL_Window> win;
  std::vector<char> buffer;

protected:
  // values from AppleWin
  static constexpr int width = 600;  // GetFrameBufferWidth();
  static constexpr int height = 420; // GetFrameBufferHeight();
  static constexpr int sx = 20;      // GetFrameBufferBorderWidth();
  static constexpr int sy = 18;      // GetFrameBufferBorderHeight();
  static constexpr int sw = 560;     // GetFrameBufferBorderlessWidth();
  static constexpr int sh = 384;     // GetFrameBufferBorderlessHeight();
};
