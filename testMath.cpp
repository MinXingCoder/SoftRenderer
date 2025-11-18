//
// Created by scc on 2025/11/12.
//
#include <iostream>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "math/mathFunctions.h"

void printMatrix(const glm::mat4x4& matrix)
{
    for(int col = 0; col < 4; ++col)
    {
        for(int row = 0; row < 4; ++row)
        {
            std::cout << matrix[col][row] << "\t";
        }

        std::cout << "\n";
    }
}

int main()
{
    float angle = 0.01f;
    glm::mat4x4 modelMatrix = glm::rotate(glm::mat4x4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));
    std::cout << "model matrix: " << std::endl;
    printMatrix(modelMatrix);
    std::cout << std::endl;

    auto cameraMatrix = glm::translate(glm::mat4x4(1.0f), glm::vec3(0.0f, 0.0f, 5.01f));
    std::cout << "camera matrix: " << std::endl;
    printMatrix(cameraMatrix);
    glm::mat4x4 viewMatrix = glm::inverse(cameraMatrix);
    std::cout << "view matrix: " << std::endl;
    printMatrix(viewMatrix);
    std::cout << std::endl;

    float angleRad = DEG2RAD(60.0f);
    glm::mat4x4 perspectiveMatrix = glm::perspective(angleRad, 800.f / 600.f, 0.1f, 100.0f);
    std::cout << "perspective matrix: " << std::endl;
    printMatrix(perspectiveMatrix);

    glm::mat4x4 screenMatrix = math::screenMatrix(800, 600);
    std::cout << "screen matrix: " << std::endl;
    printMatrix(screenMatrix);
}