#pragma once

#include "OrthographicCamera.h"

namespace Kraken
{
    class Game
    {
    public:
        //Game() : m_Running(false) {}
        Game()
        {}

        virtual ~Game()
        {}

        virtual void Run() = 0;

        virtual void Stop() = 0; //{ m_Running = false; };

    protected:
        //bool m_Running;
        OrthographicCamera m_Camera;
    };
}