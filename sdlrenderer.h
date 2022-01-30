#include "common.h"

#include <vector>
#include <memory>

class SDLRenderer : public Renderer
{
public:
  SDLRenderer();
  void show() override;

protected:
  std::shared_ptr<SDL_Renderer> ren;
  std::shared_ptr<SDL_Texture> tex;

  SDL_Rect srect;

  std::vector<uint8_t> buffer;
};
