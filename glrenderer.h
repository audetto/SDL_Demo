#include "common.h"

#include <SDL.h>

class GLRenderer : public Renderer
{
public:
  GLRenderer();
  ~GLRenderer() override;
  
  void show() override;

protected:
  SDL_GLContext glContext;
  float red;
};
