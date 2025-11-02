#include <application.h>
#include <gpu.h>

void Render()
{
    Point start { 0, 0, RGBA{255, 255, 255, 255} };
    Point end { 100, 799, RGBA{255, 255, 255, 255} };

    sgi->drawLine(start, end);
}

int main()
{
    bool result = winApp->initApplication(800, 800, "SoftRenderer");
    if(!result) return -1;

    result = sgi->initSurface(winApp->getFrameBuffer());
    if(!result) return -1;

    while(!winApp->windowShouldClose())
    {
        winApp->pollEvents();

        Render();

        winApp->beginFrame();
        winApp->render();
        winApp->endFrame();
    }

    winApp->destroy();
}