#include <application.h>
#include <gpu.h>
#include "../math/mathFunctions.h"
#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

uint32_t WIDTH = 800;
uint32_t HEIGHT = 600;

Point p1;
Point p2;
Point p3;

glm::vec4 pos1;
glm::vec4 pos2;
glm::vec4 pos3;

glm::mat4x4 gModelMatrix;
glm::mat4x4 gViewMatrix;
glm::mat4x4 gPerspectiveMatrix;
glm::mat4x4 gScreenMatrix;

float angle = 0.0f;
float cameraPos = 5.0f;

void transform()
{
    angle += 0.01f;
    cameraPos += 0.01f;

    gModelMatrix = glm::rotate(glm::mat4x4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));
    auto cameraModeMatrix = glm::translate(glm::mat4x4(1.0f), glm::vec3(0.0f, 0.0f, cameraPos));
    gViewMatrix = glm::inverse(cameraModeMatrix);

    auto sp1 = gPerspectiveMatrix * gViewMatrix * gModelMatrix * pos1;
    auto sp2 = gPerspectiveMatrix * gViewMatrix * gModelMatrix * pos2;
    auto sp3 = gPerspectiveMatrix * gViewMatrix * gModelMatrix * pos3;

    sp1 /= sp1.w;
    sp2 /= sp2.w;
    sp3 /= sp3.w;

    sp1 = gScreenMatrix * sp1;
    sp2 = gScreenMatrix * sp2;
    sp3 = gScreenMatrix * sp3;

    p1.x = sp1.x;
    p1.y = sp1.y;

    p2.x = sp2.x;
    p2.y = sp2.y;

    p3.x = sp3.x;
    p3.y = sp3.y;
}

void render()
{
    sgi->clear();
    transform();
    sgi->drawTriangle(p1, p2, p3);
}

void prepare()
{
    p1.color = RGBA{255, 0, 0, 255};
    p2.color = RGBA{0, 255, 0, 255};
    p3.color = RGBA{0, 0, 255, 255};

    pos1 = {-1.5f, 0.0f, 0.0f, 1.0f};
    pos2 = {1.5f, 0.0f, 0.0f, 1.0f};
    pos3 = {0.0f, 2.0f, 0.0f, 1.0f};

    float angle_rad = DEG2RAD(60.0f);
    gPerspectiveMatrix = glm::perspective(angle_rad, (float)WIDTH/(float)HEIGHT, 0.1f, 100.0f);
    gScreenMatrix = math::screenMatrix(WIDTH, HEIGHT);
}

int main()
{
    bool result = winApp->initApplication(800, 600, "SoftRenderer");
    if(!result) return -1;

    result = sgi->initSurface(winApp->getFrameBuffer());
    if(!result) return -1;

    prepare();
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