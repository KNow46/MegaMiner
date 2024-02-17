#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "Global.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "GameObject.h"
#include "Image.h"
#include "InterfaceObject.h"
#include "TestObject.h"
#include "InterfaceManager.h"
#include "Camera.h"
#include "Machine.h"
#include "World.h"

//transforms to range (-1,1)
//if transforming point set length to 0
//(isX == 1) if you are transforming x coordinate
float transformToOpenGl(const float &position, const float &length, const bool &isX)
{
    float result = 0.0f;
    if (isX == false)
    {
        result = -((position + length / 2.0) / windowHeight * 2.0 - 1.0);
    }
    else
    {
        result = (position + length / 2.0) / windowWidth * 2.0 - 1.0;
    }
    return result;
}

template<typename T>
void rendererScene(std::vector<std::shared_ptr<T>> &sceneObjects, Renderer& renderer, Shader& shader, 
    VertexArray& va, VertexBuffer& vb, VertexBufferLayout& layout, IndexBuffer& ib, GLFWwindow* window, Camera *camera, bool areObjectsInterface)
{

    for (const auto& sceneObject : sceneObjects)
    {
        if (sceneObject->getIsDestroyed() == false  && sceneObject->getIsVisible())
        {
            //float angle = 1.0;

            glEnable(GL_SCISSOR_TEST);

            glScissor(0, 0, camera->getXrange(), camera->getYrange());

            float positionsTransformed[] = {
            transformToOpenGl(sceneObject->getX() - (areObjectsInterface ? 0 : camera->getX()), 0, 1),  transformToOpenGl(sceneObject->getY() - (areObjectsInterface ? 0 : camera->getY())  + sceneObject->getHeight(),0,0), 0.0f, 0.0f,
            transformToOpenGl(sceneObject->getX() - (areObjectsInterface ? 0 : camera->getX()) + sceneObject->getWidth(), 0, 1) , transformToOpenGl(sceneObject->getY() - (areObjectsInterface ? 0 : camera->getY()) + sceneObject->getHeight(),0,0), 1.0f, 0.0f,
            transformToOpenGl(sceneObject->getX() - (areObjectsInterface ? 0 : camera->getX()) + sceneObject->getWidth(), 0, 1) , transformToOpenGl(sceneObject->getY() - (areObjectsInterface ? 0 : camera->getY()), 0, 0) , 1.0f, 1.0f,
            transformToOpenGl(sceneObject->getX() - (areObjectsInterface ? 0 : camera->getX()), 0, 1), transformToOpenGl(sceneObject->getY() - (areObjectsInterface ? 0 : camera->getY()), 0, 0), 0.0f, 1.0f
            };

           vb.changeData(positionsTransformed, 4 * 4 * sizeof(float));
;           
            sceneObject->getTexture().Bind(1);

            renderer.Draw(va, ib, shader);

            rendererScene(sceneObject->getAggregatedObjects(), renderer, shader, va, vb, layout, ib, window, camera, areObjectsInterface);


            glDisable(GL_SCISSOR_TEST);
        }

    }	
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        
        InterfaceManager::getInstance().handleLeftClick(xpos, ypos);
    }
}
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
 
}
void updateMachineState(GLFWwindow* window)
{
    Machine::State newState = Machine::State::STANDING;

    bool isWPressed = glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_W) == GLFW_REPEAT;
    bool isAPressed = glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_A) == GLFW_REPEAT;
    bool isDPressed = glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_D) == GLFW_REPEAT;
    bool isSPressed = glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_S) == GLFW_REPEAT;

    if (isWPressed)
    {
        newState = Machine::State::FLYING;
        if (isAPressed && !isDPressed)
        {
            newState = Machine::State::FLYING_LEFT;
        }
        else if (isDPressed && !isAPressed)
        {
            newState = Machine::State::FLYING_RIGHT;
        }
    }
    else if (isSPressed)
    {
        if (isAPressed && !isDPressed)
        {
            newState = Machine::State::DRILLING_LEFT;
        }
        else if (isDPressed && !isAPressed)
        {
            newState = Machine::State::DRILLING_RIGHT;
        }
        else
        {
            newState = Machine::State::DRILLING_DOWN;
        }
    }
    else if (isAPressed && !isDPressed)
    {
        newState = Machine::State::DRILLING_LEFT;
    }
    else if (isDPressed && !isAPressed)
    {
        newState = Machine::State::DRILLING_RIGHT;
    }

    World::getInstance().getMachine()->setCurrentState(newState);
}



int main(void)
{

    GLFWwindow* window;

    Camera *basicCamera = new Camera(0, 0, -windowWidth/2, -windowHeight/2,  windowWidth, windowHeight);

    /* Initialize the library */
    if (!glfwInit())   
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(windowWidth, windowHeight, "name", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        std::cout << "glew error";
    else
        std::cout << "glew initialized properly\n";

    std::cout << glGetString(GL_VERSION) << std::endl;

	
        float positions[] = {
            -1.0f, -1.0f, 0.0f, 0.0f,
            1.0f, -1.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 0.0f, 1.0f
        };
        unsigned int indicies[] = {
            0,1,2,
            2,3,0
        };

        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        GLCall(glEnable(GL_BLEND));

        VertexArray va;
        VertexBuffer vb(positions, 4 * 4  * sizeof(float));

        VertexBufferLayout layout;

        layout.Push<float>(2);
        layout.Push<float>(2);

        va.AddBuffer(vb, layout);
        IndexBuffer ib(indicies, 6);
        Shader shader("res/shaders/Basic.shader");
        Renderer renderer;

		shader.Bind();
		shader.SetUniform1i("u_Texture", 1);

        glfwSetMouseButtonCallback(window, mouse_button_callback);

        glfwSetKeyCallback(window, keyCallback);


        double xpos, ypos;
        /* Loop until the user closes the window */
        double lastTime = glfwGetTime();
        int nbFrames = 0;

        while (!glfwWindowShouldClose(window))
        {
            
            double currentTime = glfwGetTime();
            nbFrames++;
            if (currentTime - lastTime >= 1.0) {
    
                std::cout << nbFrames << " frames per second" << std::endl;
                nbFrames = 0;
                lastTime += 1.0;
            }
            

            updateMachineState(window);

            basicCamera->followObject(World::getInstance().getMachine());

             /* Poll for and process events */
             GLCall(glfwPollEvents());
                
             glfwGetCursorPos(window, &xpos, &ypos);

            World::getInstance().update();

            InterfaceManager::getInstance().handleHover(xpos, ypos);

            renderer.Clear();

            rendererScene(World::getInstance().getVisibleBlocks(), renderer, shader, va, vb, layout, ib, window, basicCamera, false);
            std::vector<std::shared_ptr <GameObject>> noBlockObjectsToRender;
            noBlockObjectsToRender.push_back(World::getInstance().getShop());
            noBlockObjectsToRender.push_back(World::getInstance().getMachine());
            

            rendererScene(noBlockObjectsToRender, renderer, shader, va, vb, layout, ib, window, basicCamera, false);
            rendererScene(InterfaceManager::getInstance().getAllInterfaceObjects(), renderer, shader, va, vb, layout, ib, window, basicCamera, true);

            /* Swap front and back buffers */
            GLCall(glfwSwapBuffers(window));

        }
    glfwTerminate();
    return 0;
}
