//
// Created by etc on 24/07/24.
//

#pragma once

#include <GL/glew.h>
#include <vector>

#include "Vertex.h"

namespace Kraken 
{
class Renderer
{
public:
    Renderer() {}
    virtual ~Renderer() = 0;
   
    virtual void Init() = 0;
    virtual void Shutdown() = 0;
    
    static void Clear(GLbitfield additionalArgs);
    //virtual void RenderBuffers(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices) = 0;
   
};

class Renderer2D : public Renderer
{
    //static void Clear(GLbitfield additionalArgs=NULL) override { Renderer.Clear(); }
};

} // Kraken
