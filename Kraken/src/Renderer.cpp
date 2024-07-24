//
// Created by etc on 24/07/24.
//

#include "Renderer.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Kraken
{
    void Renderer::Clear(GLbitfield additionalArgs)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | additionalArgs);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    }
} // Kraken