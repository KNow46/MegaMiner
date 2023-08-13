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
        if (sceneObject->getIsDestroyed() == false)
        {
            //float angle = 1.0;

            glEnable(GL_SCISSOR_TEST);

            glScissor(camera->getXposAtScreen(), windowHeight - camera->getYposAtScreen() - camera->getYrange(),camera->getXrange(), camera->getYrange());

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


struct UserData
{
   std::shared_ptr<Machine> machine;

   UserData(std::shared_ptr<Machine> machine) : machine(machine) {}
};

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
    if (action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        UserData* userData = static_cast<UserData*>(glfwGetWindowUserPointer(window));

        if(userData)
        {
            std::shared_ptr<Machine> machine = userData->machine;

            if (key == GLFW_KEY_UP)
            {
                machine->setCurrentState(Machine::State::FLYING);
            }
            else if (key == GLFW_KEY_DOWN)
            {
                machine->setCurrentState(Machine::State::DRILLING_DOWN);

            }
            else if (key == GLFW_KEY_LEFT)
            {
                machine->setCurrentState(Machine::State::DRILLING_LEFT);
            }
            else if (key == GLFW_KEY_RIGHT)
            {
                machine->setCurrentState(Machine::State::DRILLING_RIGHT);
            }
        }
    }
    else if (action == GLFW_RELEASE)
    {
        UserData* userData = static_cast<UserData*>(glfwGetWindowUserPointer(window));

        if (userData)
        {
            std::shared_ptr<Machine> machine = userData->machine;
       
            machine->setCurrentState(Machine::State::STANDING);
            
        }
    }

}



int main(void)
{

    GLFWwindow* window;

    Camera *basicCamera = new Camera(0, 0, 0, 0,  windowWidth, windowHeight);

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

    std::cout << glGetString(GL_VERSION);

	
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

        std::shared_ptr<Machine> machine = std::make_shared<Machine>(100, 100, 200, 150);
       // userdata userdata(machine);
      //  glfwsetwindowuserpointer(window, &userdata);
        glfwSetMouseButtonCallback(window, mouse_button_callback);
        glfwSetKeyCallback(window, keyCallback);


        std::vector<std::shared_ptr<GameObject>> gameObjects;

        gameObjects.push_back(std::shared_ptr<Machine>(machine));



        UserData userData(machine);
        glfwSetWindowUserPointer(window, &userData);
 
        gameObjects.emplace_back(std::make_shared<InterfaceObject>(300, 300, windowWidth / 2, windowWidth / 2, "res/textures/board.png", "res/textures/xWon.png"));
        double xpos, ypos;
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        { 
             /* Poll for and process events */
             GLCall(glfwPollEvents());
                
             glfwGetCursorPos(window, &xpos, &ypos);



            
          
          
             
             renderer.Clear();


            InterfaceManager::getInstance().handleHover(xpos, ypos);

            rendererScene(gameObjects, renderer, shader, va, vb, layout, ib, window, basicCamera, true);

            //rendererScene(InterfaceManager::getInstance().getAllInterfaceObjects(), renderer, shader, va, vb, layout, ib, window, basicCamera, false);

            /* Swap front and back buffers */
            GLCall(glfwSwapBuffers(window));

        }
    glfwTerminate();
    return 0;
}
