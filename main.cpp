#include "application.h"
#include "gpu.h"
#include "gpu/shader/defaultshader.h"
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

uint32_t WIDTH = 800;
uint32_t HEIGHT = 600;

uint32_t positionVbo = 0;
uint32_t colorVbo = 0;
uint32_t uvVbo = 0;

uint32_t ebo = 0;
uint32_t vao = 0;

DefaultShader* shader = nullptr;

glm::mat4x4 modelMatrix;
glm::mat4x4 perspectiveMatrix;
glm::mat4x4 viewMatrix;

void printMat4(const glm::mat4& matrix) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

float angle = 0.0f;
void transform()
{
    angle += 0.01f;
    modelMatrix = glm::rotate(glm::mat4x4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));
}

void render()
{
    transform();
    shader->mModelMatrix = modelMatrix;
    shader->mViewMatrix = viewMatrix;
    shader->mProjectionMatrix = perspectiveMatrix;

    sgl->clear();

    sgl->useProgram(shader);
    sgl->bindVertexArray(vao);
    sgl->bindBuffer(ELEMENT_ARRAY_BUFFER, ebo);
    sgl->drawElement(DRAW_TRIANGLES, 0, 3);
}

void prepare()
{
    shader = new DefaultShader();

    perspectiveMatrix = glm::perspective(glm::radians(60.0f), (float)WIDTH/(float)HEIGHT, 0.1f, 100.0f);

    auto cameraModelMatrix = glm::translate(glm::mat4x4(1.0f), glm::vec3(0.0f, 0.0f, 3.0f));

    viewMatrix = glm::inverse(cameraModelMatrix);

    float positions[] = {
        -0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
    };

    float colors[] = {
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
    };

    float uvs[] = {
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 0.0f,
    };

    uint32_t indices[] = {0, 1, 2};

    ebo = sgl->genBuffer();
    sgl->bindBuffer(ELEMENT_ARRAY_BUFFER, ebo);
    sgl->bufferData(ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * 3, indices);
    sgl->bindBuffer(ELEMENT_ARRAY_BUFFER, 0);

    vao = sgl->getVertexArray();
    sgl->bindVertexArray(vao);

    auto positionVbo = sgl->genBuffer();
    sgl->bindBuffer(ARRAY_BUFFER, positionVbo);
    sgl->bufferData(ARRAY_BUFFER, sizeof(float) * 9, positions);
    sgl->vertexAttributePointer(0, 3, 3 * sizeof(float), 0);

    auto colorVbo = sgl->genBuffer();
    sgl->bindBuffer(ARRAY_BUFFER, colorVbo);
    sgl->bufferData(ARRAY_BUFFER, sizeof(float) * 12, colors);
    sgl->vertexAttributePointer(1, 4, 4 * sizeof(float), 0);

    auto uvVbo = sgl->genBuffer();
    sgl->bindBuffer(ARRAY_BUFFER, uvVbo);
    sgl->bufferData(ARRAY_BUFFER, sizeof(float) * 6, uvs);
    sgl->vertexAttributePointer(2, 2, 2 * sizeof(float), 0);

    sgl->bindBuffer(ARRAY_BUFFER, 0);
    sgl->bindVertexArray(0);
}

int main()
{
    if (!winApp->initApplication(WIDTH, HEIGHT))
    {
        return -1;
    }

    sgl->initSurface(winApp->getWidth(), winApp->getHeight(), winApp->getFrameBuffer());

    prepare();

    while (!winApp->peekMessage())
    {
        winApp->beginFrame();
        render();
        winApp->show();
        winApp->endFrame();
    }

    winApp->close();
}