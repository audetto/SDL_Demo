#include "glrenderer.h"

#include <stdexcept>
#include <string>
#include <iostream>

#include <GLES3/gl3.h>

namespace
{

  std::string safeGlGetString(GLenum name)
  {
    const char * str = reinterpret_cast<const char *>(glGetString(name));
    if (str)
    {
      return str;
    }
    else
    {
      return "<MISSING>";
    }
  }

}

GLRenderer::GLRenderer()
{
  red = 0.0;
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

  // Create window with graphics context
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

  const SDL_WindowFlags windowFlags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

  win.reset(SDL_CreateWindow("Demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, sw, sh, windowFlags), SDL_DestroyWindow);
  if (!win)
  {
    throw std::runtime_error(SDL_GetError());
  }

  glContext = SDL_GL_CreateContext(win.get());
  if (!glContext)
  {
    throw std::runtime_error(SDL_GetError());
  }

  SDL_GL_MakeCurrent(win.get(), glContext);

  // Setup Platform/Renderer backends
  std::cerr << "GL_VENDOR: " << safeGlGetString(GL_VENDOR) << std::endl;
  std::cerr << "GL_RENDERER: " << safeGlGetString(GL_RENDERER) << std::endl;
  std::cerr << "GL_VERSION: " << safeGlGetString(GL_VERSION) << std::endl;
  std::cerr << "GL_SHADING_LANGUAGE_VERSION: " << safeGlGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}

GLRenderer::~GLRenderer()
{
  SDL_GL_DeleteContext(glContext);
}

void GLRenderer::show()
{
  red += 0.013;
  if (red > 1.0)
  {
    red -= 1.0;
  }

  glClearColor(red, 0.55, 0.60, 1.00);
  glClear(GL_COLOR_BUFFER_BIT);
  
  SDL_GL_SwapWindow(win.get());
}
