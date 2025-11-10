#include <application.h>
#include <gpu.h>

Image* gImage = nullptr;

void initImage()
{
    gImage = Image::createImage("../assets/textures/goku.jpg");
}

void render()
{
    sgi->drawImage(gImage);
}

int main()
{
    bool result = winApp->initApplication(800, 800, "SoftRenderer");
    if(!result) return -1;

    result = sgi->initSurface(winApp->getFrameBuffer());
    if(!result) return -1;

    initImage();

    while(!winApp->windowShouldClose())
    {
        winApp->pollEvents();

        render();

        winApp->beginFrame();
        winApp->render();
        winApp->endFrame();
    }

    winApp->destroy();
}