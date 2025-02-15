#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <bits/stdc++.h>

#include "./header/Object.h"
#include "./header/stb_image.h"

void framebufferSizeCallback(GLFWwindow *window, int width, int height);
void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
unsigned int createShader(const string &filename, const string &type);
unsigned int createProgram(unsigned int vertexShader, unsigned int fragmentShader);
unsigned int modelVAO(Object &model);
unsigned int loadTexture(const char *tFileName);
void init();

// settings
int SCR_WIDTH = 800;
int SCR_HEIGHT = 600;

// Shader
unsigned int vertexShader, fragmentShader, shaderProgram;

// Texture
unsigned int airplaneTexture, earthTexture;

// VAO, VBO
unsigned int airplaneVAO, earthVAO,cubeVAO;

// Objects to display
Object *airplaneObject, *earthObject,*cubeObject;

// Constants you may need
const int airplaneHeight = 27;
const int rotateEarthSpeed = 30;
const int rotateAirplaneSpeed = 90;
const int squeezeSpeed = 90;
const int rainbowSpeed = 72;

// You can use these parameters
float rotateEarthDegree = 0;
float rotateAirplaneDegree = 0;
int rotateAxisDegree = 180;
bool useSqueeze = false;
float squeezeFactor = 0;
bool useRainbowColor = false;
bool useplane = true;
float rainbowDegree = 0;
float helicopter_rotation_angle=0;
glm::vec3 rainbowColor = glm::vec3(1.0f, 1.0f, 1.0f);

int main() {
    // glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    /* TODO#0: Change window title to "HW2 - [your student id]"
     *        Ex. HW2 - 312550000
     */

    // glfw window creation
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "HW2 - [your student id]", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetKeyCallback(window, keyCallback);
    glfwSwapInterval(1);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // TODO#1: Finish function createShader
    // TODO#2: Finish function createProgram
    // TODO#3: Finish function modelVAO
    // TODO#4: Finish function loadTexture
    // You can find the above functions right below the main function

    // Initialize Object, Shader, Texture, VAO, VBO
    init();

    // Enable depth test, face culling
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);

    // Set viewport
    glfwGetFramebufferSize(window, &SCR_WIDTH, &SCR_HEIGHT);
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    // render loop variables
    double dt;
    double lastTime = glfwGetTime();
    double currentTime;

    /* TODO#5: Data connection - Retrieve uniform variable locations
     *    1. Retrieve locations for model, view, and projection matrices.
     *    2. Retrieve locations for squeezeFactor, rainbowColor, and other parameters.
     * Hint:
     *    glGetUniformLocation
     */

    int modelLoc = glGetUniformLocation(shaderProgram, "model");
    int viewLoc = glGetUniformLocation(shaderProgram, "view");
    int projectionLoc = glGetUniformLocation(shaderProgram, "projection");

    int squeezeFactorLoc = glGetUniformLocation(shaderProgram, "squeezeFactor");
    int rainbowColorLoc = glGetUniformLocation(shaderProgram, "rainbowColor");

    if (modelLoc == -1) {
        std::cerr << "Warning: Could not find 'model' uniform location!" << std::endl;
    }
    if (viewLoc == -1) {
        std::cerr << "Warning: Could not find 'view' uniform location!" << std::endl;
    }
    if (projectionLoc == -1) {
        std::cerr << "Warning: Could not find 'projection' uniform location!" << std::endl;
    }
    if (squeezeFactorLoc == -1) {
        std::cerr << "Warning: Could not find 'squeezeFactor' uniform location!" << std::endl;
    }
    if (rainbowColorLoc == -1) {
        std::cerr << "Warning: Could not find 'rainbowColor' uniform location!" << std::endl;
    }

    // render loop
    while (!glfwWindowShouldClose(window)) {
        // render
        glClearColor(0 / 255.0, 0 / 255.0, 0 / 255.0, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 50.0f, 90.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);

        glm::mat4 base(1.0f), airplaneModel(1.0f), earthModel(1.0f),cubeModel(1.0f);

        /* TODO#6-1: Render Airplane
         *    1. Set up airplane model matrix.
         *    2. Send model, view, and projection matrices to the program.
         *    3. Send squeezeFactor, rainbowColor, or other parameters to the program.
         *    4. Apply the texture, and render the airplane.
         * Hint:
         *	  rotate, translate, scale
         *    glUniformMatrix4fv, glUniform1f, glUniform3fv
         *    glActiveTexture, glBindTexture, glBindVertexArray, glDrawArrays
         */
        if (useplane){
            ////////////////////////////////////////////////airplane///////////////////////////////////////////////////

            airplaneModel = glm::rotate(airplaneModel, glm::radians((float)rotateAxisDegree), glm::vec3(0.0f, 1.0f, 0.0f));
            airplaneModel = glm::rotate(airplaneModel, glm::radians(rotateAirplaneDegree), glm::vec3(-1.0f, 0.0f, 0.0f));
            airplaneModel = glm::translate(airplaneModel, glm::vec3(0.0f, airplaneHeight, 0.0f)); 
            

            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(airplaneModel));
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
            glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

            glUniform1f(squeezeFactorLoc,0.0f);
            glUniform3fv(rainbowColorLoc, 1, glm::value_ptr(useRainbowColor ? rainbowColor : glm::vec3(1.0f, 1.0f, 1.0f)));


            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, airplaneTexture);

            glBindVertexArray(airplaneVAO);
            glDrawArrays(GL_TRIANGLES, 0, airplaneObject->positions.size() / 3);

            glBindVertexArray(0);
            ////////////////////////////////////////////////airplane///////////////////////////////////////////////////
        }
        else{
            ////////////////////////////////////////////////cube///////////////////////////////////////////////////

            glm::mat4 model_body(1.0f);      
            cubeModel = glm::rotate(cubeModel, glm::radians((float)rotateAxisDegree), glm::vec3(0.0f, 1.0f, 0.0f));
            cubeModel = glm::rotate(cubeModel, glm::radians(rotateAirplaneDegree), glm::vec3(-1.0f, 0.0f, 0.0f));
            cubeModel = glm::translate(cubeModel, glm::vec3(0.0f, airplaneHeight, 0.0f));
            cubeModel = glm::scale(cubeModel, glm::vec3(10.0f));
            glm::mat4 eyes1 = glm::translate(cubeModel, glm::vec3(-0.25f, 0.2f, -0.5f));
            eyes1 = glm::scale(eyes1, glm::vec3(0.2f, 0.2f, 0.2f));
            glm::mat4 eyes2 = glm::translate(cubeModel, glm::vec3(0.25f, 0.2f, -0.5f));
            eyes2 = glm::scale(eyes2, glm::vec3(0.2f, 0.2f, 0.2f));
            glm::mat4 mouth1 = glm::translate(cubeModel, glm::vec3(-0.05f, -0.15f, -0.5f));
            mouth1 = glm::scale(mouth1, glm::vec3(0.17f, 0.17f, 0.17f));
            glm::mat4 water = glm::translate(cubeModel, glm::vec3(-0.08f, -0.3f, -0.49f));
            water = glm::scale(water, glm::vec3(0.09f, 0.3f, 0.17f));
            glm::mat4 model_connector = glm::translate(cubeModel, glm::vec3(0.0f, 0.5f, 0.0f));
            model_connector = glm::rotate(model_connector,glm::radians(helicopter_rotation_angle), glm::vec3(0.0f, 1.0f, 0.0f));
            model_connector = glm::scale(model_connector, glm::vec3(0.5f, 0.5f, 0.5f));
            glm::mat4 model_blade1 = glm::translate(model_connector, glm::vec3(2.0f, 0.4f, 0.0f));
            model_blade1 = glm::scale(model_blade1, glm::vec3(5.0f, 0.1f, 0.8f));
            glm::mat4 model_blade3 = glm::translate(model_connector, glm::vec3(0.0f, 0.4f, 2.0f));
            model_blade3=glm::rotate(model_blade3,glm::radians(90.f),glm::vec3(0.0f, 1.0f, 0.0f));
            model_blade3 = glm::scale(model_blade3, glm::vec3(5.0f, 0.1f, 0.8f));
            glm::mat4 model_blade2 = glm::translate(model_connector, glm::vec3(-2.0f, 0.4f, 0.0f)); 
            model_blade2=glm::rotate(model_blade2,glm::radians(180.f),glm::vec3(0.0f, 1.0f, 0.0f));
            model_blade2 = glm::scale(model_blade2, glm::vec3(5.0f, 0.1f, 0.8f));
            glm::mat4 model_blade4 = glm::translate(model_connector, glm::vec3(0.0f, 0.4f, -2.0f));
            model_blade4=glm::rotate(model_blade4,glm::radians(270.f),glm::vec3(0.0f, 1.0f, 0.0f));
            model_blade4 = glm::scale(model_blade4, glm::vec3(5.0f, 0.1f, 0.8f));

            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(cubeModel));
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
            glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

            unsigned int colorTexture;
            glGenTextures(1, &colorTexture);
            glBindTexture(GL_TEXTURE_2D, colorTexture);

            unsigned char redColor[] = {122, 220, 137};
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, redColor);

            glUniform1f(squeezeFactorLoc, 0.0f);  
            glUniform3fv(rainbowColorLoc, 1, glm::value_ptr(useRainbowColor ? rainbowColor : glm::vec3(1.0f, 1.0f, 1.0f)));

            glBindVertexArray(cubeVAO);
            glDrawArrays(GL_TRIANGLES, 0, cubeObject->positions.size() / 3);
            glBindVertexArray(0);

            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(eyes1));
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
            glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

            unsigned int colorTexture1;
            glGenTextures(1, &colorTexture1);
            glBindTexture(GL_TEXTURE_2D, colorTexture1);

            unsigned char redColor1[] = {49, 167, 66};
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, redColor1);


            glUniform1f(squeezeFactorLoc, 0.0f);  
            glUniform3fv(rainbowColorLoc, 1, glm::value_ptr(useRainbowColor ? rainbowColor : glm::vec3(1.0f, 1.0f, 1.0f)));

            glBindVertexArray(cubeVAO);
            glDrawArrays(GL_TRIANGLES, 0, cubeObject->positions.size() / 3);
            glBindVertexArray(0);

            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(eyes2));
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
            glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

            unsigned int colorTexture2;
            glGenTextures(1, &colorTexture2);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, redColor1);

            glUniform1f(squeezeFactorLoc, 0.0f);  
            glUniform3fv(rainbowColorLoc, 1, glm::value_ptr(useRainbowColor ? rainbowColor : glm::vec3(1.0f, 1.0f, 1.0f)));

            glBindVertexArray(cubeVAO);
            glDrawArrays(GL_TRIANGLES, 0, cubeObject->positions.size() / 3);
            glBindVertexArray(0);

            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mouth1));
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
            glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

            unsigned int colorTexture3;
            glGenTextures(1, &colorTexture3);
            glBindTexture(GL_TEXTURE_2D, colorTexture3);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, redColor1);

            glUniform1f(squeezeFactorLoc, 0.0f);  
            glUniform3fv(rainbowColorLoc, 1, glm::value_ptr(useRainbowColor ? rainbowColor : glm::vec3(1.0f, 1.0f, 1.0f)));

            glBindVertexArray(cubeVAO);
            glDrawArrays(GL_TRIANGLES, 0, cubeObject->positions.size() / 3);
            glBindVertexArray(0);

            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(water));
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
            glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

            unsigned int colorTexture4;
            glGenTextures(1, &colorTexture4);
            glBindTexture(GL_TEXTURE_2D, colorTexture4);

            unsigned char redColor3[] = {84, 245, 255};
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, redColor3);

            glUniform1f(squeezeFactorLoc, 0.0f);  
            glUniform3fv(rainbowColorLoc, 1, glm::value_ptr(useRainbowColor ? rainbowColor : glm::vec3(1.0f, 1.0f, 1.0f)));

            glBindVertexArray(cubeVAO);
            glDrawArrays(GL_TRIANGLES, 0, cubeObject->positions.size() / 3);
            glBindVertexArray(0);

            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model_connector));
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
            glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

            unsigned int colorTexture5;
            glGenTextures(1, &colorTexture5);
            glBindTexture(GL_TEXTURE_2D, colorTexture5);

            unsigned char redColor4[] = {239, 255, 84};
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, redColor4);

            glUniform1f(squeezeFactorLoc, 0.0f);  
            glUniform3fv(rainbowColorLoc, 1, glm::value_ptr(useRainbowColor ? rainbowColor : glm::vec3(1.0f, 1.0f, 1.0f)));

            glBindVertexArray(cubeVAO);
            glDrawArrays(GL_TRIANGLES, 0, cubeObject->positions.size() / 3);
            glBindVertexArray(0);

            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model_blade1));
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
            glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

            unsigned int colorTexture6;
            glGenTextures(1, &colorTexture6);
            glBindTexture(GL_TEXTURE_2D, colorTexture6);

            unsigned char redColor5[] = {169, 34, 5};
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, redColor5);

            glUniform1f(squeezeFactorLoc, 0.0f);  
            glUniform3fv(rainbowColorLoc, 1, glm::value_ptr(useRainbowColor ? rainbowColor : glm::vec3(1.0f, 1.0f, 1.0f)));

            glBindVertexArray(cubeVAO);
            glDrawArrays(GL_TRIANGLES, 0, cubeObject->positions.size() / 3);
            glBindVertexArray(0);

            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model_blade3));
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
            glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

            unsigned int colorTexture7;
            glGenTextures(1, &colorTexture7);
            glBindTexture(GL_TEXTURE_2D, colorTexture7);

            unsigned char redColor6[] = {74, 94, 235};
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, redColor6);

            glUniform1f(squeezeFactorLoc, 0.0f);  
            glUniform3fv(rainbowColorLoc, 1, glm::value_ptr(useRainbowColor ? rainbowColor : glm::vec3(1.0f, 1.0f, 1.0f)));

            glBindVertexArray(cubeVAO);
            glDrawArrays(GL_TRIANGLES, 0, cubeObject->positions.size() / 3);
            glBindVertexArray(0);

            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model_blade2));
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
            glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

            unsigned int colorTexture8;
            glGenTextures(1, &colorTexture8);
            glBindTexture(GL_TEXTURE_2D, colorTexture8);

            unsigned char redColor7[] = {168, 249, 111};
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, redColor7);

            glUniform1f(squeezeFactorLoc, 0.0f);  
            glUniform3fv(rainbowColorLoc, 1, glm::value_ptr(useRainbowColor ? rainbowColor : glm::vec3(1.0f, 1.0f, 1.0f)));

            glBindVertexArray(cubeVAO);
            glDrawArrays(GL_TRIANGLES, 0, cubeObject->positions.size() / 3);
            glBindVertexArray(0);
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model_blade4));
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
            glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

            unsigned int colorTexture9;
            glGenTextures(1, &colorTexture9);
            glBindTexture(GL_TEXTURE_2D, colorTexture9);

            unsigned char redColor8[] = {69, 69, 69};
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, redColor8);

            glUniform1f(squeezeFactorLoc, 0.0f);  
            glUniform3fv(rainbowColorLoc, 1, glm::value_ptr(useRainbowColor ? rainbowColor : glm::vec3(1.0f, 1.0f, 1.0f)));
            glBindVertexArray(cubeVAO);
            glDrawArrays(GL_TRIANGLES, 0, cubeObject->positions.size() / 3);
            glBindVertexArray(0);
            ////////////////////////////////////////////////cube///////////////////////////////////////////////////
        }

        /* TODO#6-2: Render Earth
         *    1. Set up earth model matrix.
         *    2. Send model, view, and projection matrices to the program.
         *    3. Send squeezeFactor, rainbowColor, or other parameters to the program.
         *    4. Apply the texture, and render the earth.
         * Hint:
         *	  rotate, translate, scale
         *    glUniformMatrix4fv, glUniform1f, glUniform3fv
         *    glActiveTexture, glBindTexture, glBindVertexArray, glDrawArrays
         */
        ////////////////////////////////////////////////erath///////////////////////////////////////////////////
        earthModel = glm::rotate(earthModel, glm::radians(rotateEarthDegree), glm::vec3(0.0f, 1.0f, 0.0f));
        earthModel = glm::scale(earthModel, glm::vec3(10.0f));

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(earthModel));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        glUniform1f(squeezeFactorLoc,squeezeFactor);
        glUniform3fv(rainbowColorLoc, 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));


        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, earthTexture);

        glBindVertexArray(earthVAO);
        glDrawArrays(GL_TRIANGLES, 0, earthObject->positions.size() / 3);

        glBindVertexArray(0);
        ////////////////////////////////////////////////erath///////////////////////////////////////////////////

        // Status update
        currentTime = glfwGetTime();
        dt = currentTime - lastTime;
        lastTime = currentTime;

        /* TODO#7: Update "rotateEarthDegree", "rotateAirplaneDegree", "rotateAxisDegree",
         *          "squeezeFactor", "rainbowColor"
         */

        if (useRainbowColor) {
            rainbowDegree += rainbowSpeed * dt;

            if (rainbowDegree >= 360.0f) {
                rainbowDegree -= 360.0f;
            }
            float H = rainbowDegree;
            float C = 1.0f;
            float X = C * (1 - fabs(fmod(H / 60.0f, 2) - 1));
            float m = 0.0f;

            float r, g, b;

            if (0 <= H && H < 60) {
                r = C; g = X; b = 0;
            } else if (60 <= H && H < 120) {
                r = X; g = C; b = 0;
            } else if (120 <= H && H < 180) {
                r = 0; g = C; b = X;
            } else if (180 <= H && H < 240) {
                r = 0; g = X; b = C;
            } else if (240 <= H && H < 300) {
                r = X; g = 0; b = C;
            } else {
                r = C; g = 0; b = X;
            }
            rainbowColor = glm::vec3(r, g, b);
        } else {
            rainbowColor = glm::vec3(1.0f, 1.0f, 1.0f);
        }
        if (useSqueeze) {
            squeezeFactor += glm::radians(float(squeezeSpeed)) * dt;
        } else {
            squeezeFactor = squeezeFactor;
        }
        rotateEarthDegree += rotateEarthSpeed * dt;
        rotateAirplaneDegree += rotateAirplaneSpeed * dt;
        helicopter_rotation_angle ++;
        if (rotateEarthDegree >= 360.0f) {
            rotateEarthDegree -= 360.0f;
        }

        
        if (rotateAirplaneDegree >= 360.0f) {
            rotateAirplaneDegree -= 360.0f;
        }
        if (helicopter_rotation_angle >= 360.0f) {
            helicopter_rotation_angle -= 360.0f;
        }
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

/* TODO#1: createShader
 * input:
 *      filename: shader file name
 *      type: shader type, "vert" means vertex shader, "frag" means fragment shader
 * output: shader object
 * Hint:
 *      glCreateShader, glShaderSource, glCompileShader
 */
unsigned int createShader(const string &filename, const string &type) {
    unsigned int shader;
    if(type == "vert") {
        shader = glCreateShader(GL_VERTEX_SHADER); 
    } else if(type == "frag") {
        shader = glCreateShader(GL_FRAGMENT_SHADER);
    } else {
        std::cout << "Unknown shader type" << std::endl;
        return 0;
    }
    
    FILE *file = fopen(filename.c_str(), "r");
    if (!file) {
        std::cerr << "Could not open shader file: " << filename << std::endl;
        return 0;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    char *shaderCode = new char[fileSize + 1];
    shaderCode[fileSize] = '\0';
    fread(shaderCode, sizeof(char), fileSize, file);
    fclose(file);

    glShaderSource(shader, 1, &shaderCode, nullptr);
    glCompileShader(shader);
    delete[] shaderCode;

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        int infoLogLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

        char *infoLog = new char[infoLogLength];
        glGetShaderInfoLog(shader, infoLogLength, nullptr, infoLog);
        
        std::cerr << "Shader compilation failed for " << filename << ":\n" << infoLog << std::endl;
        delete[] infoLog;

        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

/* TODO#2: createProgram
 * input:
 *      vertexShader: vertex shader object
 *      fragmentShader: fragment shader object
 * output: shader program
 * Hint:
 *      glCreateProgram, glAttachShader, glLinkProgram, glDetachShader
 */
unsigned int createProgram(unsigned int vertexShader, unsigned int fragmentShader) {
    unsigned int program = glCreateProgram();

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);

    int success=0;
    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if (!success) {
        int maxLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

        char* infoLog = (char*)malloc(sizeof(char) * maxLength);
        glGetProgramInfoLog(program, maxLength, &maxLength, infoLog);

        std::cerr << "Shader program linking failed: " << infoLog << std::endl;
        free(infoLog);

        glDeleteProgram(program);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        return 0;
    }

    glDetachShader(program, vertexShader);
    glDetachShader(program, fragmentShader);

    return program;
}

/* TODO#3: modelVAO
 * input:
 *      model: Object you want to render
 * output: VAO
 * Hint:
 *      glGenVertexArrays, glBindVertexArray, glGenBuffers, glBindBuffer, glBufferData,
 *      glVertexAttribPointer, glEnableVertexAttribArray,
 */
unsigned int modelVAO(Object &model) {
    unsigned int VAO, VBO[3];
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(3, VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * model.positions.size(), model.positions.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    if (!model.normals.empty()) {
        glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * model.normals.size(), model.normals.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    if (!model.texcoords.empty()) {
        glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * model.texcoords.size(), model.texcoords.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    glBindVertexArray(0);
    return VAO;
    
}

/* TODO#4: loadTexture
 * input:
 *      filename: texture file name
 * output: texture object
 * Hint:
 *      glEnable, glGenTextures, glBindTexture, glTexParameteri, glTexImage2D
 */
unsigned int loadTexture(const string &filename) {
    glEnable(GL_TEXTURE_2D);

    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);

    int width, height, nrChannels;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    } else {
        cout << "Failed to load texture" << std::endl;
        return 0;
    }

    stbi_image_free(data);

    glBindTexture(GL_TEXTURE_2D, 0);

    return textureID;

}

/* TODO#8: Key callback
 *    1. Press 'd' to increase the "rotateAxisDegree" by 1.
 *    2. Press 'a' to decrease the "rotateAxisDegree" by 1.
 *    3. Press 's' to squeeze the earth.
 *    4. Press 'r' to make the color of the airplane rainbow.
 * Hint:
 *      GLFW_KEY_D, GLFW_KEY_A, GLFW_KEY_S, GLFW_KEY_R
 *      GLFW_PRESS, GLFW_REPEAT
 */
void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
        rotateAxisDegree += 1;
        if (rotateAxisDegree >= 360) {
            rotateAxisDegree -= 360;
        }
    }

    if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
        rotateAxisDegree -= 1;
        if (rotateAxisDegree < 0) {
            rotateAxisDegree += 360;
        }
    }

    if (key == GLFW_KEY_S && action == GLFW_PRESS) {
        useSqueeze = !useSqueeze;
    }

    if (key == GLFW_KEY_R && action == GLFW_PRESS) {
        useRainbowColor = !useRainbowColor;
    }

    if (key == GLFW_KEY_H && action == GLFW_PRESS) {
        useplane = !useplane;
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebufferSizeCallback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
    SCR_WIDTH = width;
    SCR_HEIGHT = height;
}

void init() {
#if defined(__linux__) || defined(__APPLE__)
    string dirShader = "../../src/shaders/";
    string dirAsset = "../../src/asset/obj/";
    string dirTexture = "../../src/asset/texture/";
#else
    string dirShader = "..\\..\\src\\shaders\\";
    string dirAsset = "..\\..\\src\\asset\\obj\\";
    string dirTexture = "..\\..\\src\\asset\\texture\\";
#endif

    // Object
    airplaneObject = new Object(dirAsset + "airplane.obj");
    earthObject = new Object(dirAsset + "earth.obj");
    cubeObject = new Object(dirAsset + "cube.obj");

    // Shader
    vertexShader = createShader(dirShader + "vertexShader.vert", "vert");
    fragmentShader = createShader(dirShader + "fragmentShader.frag", "frag");
    shaderProgram = createProgram(vertexShader, fragmentShader);
    glUseProgram(shaderProgram);

    // Texture
    airplaneTexture = loadTexture(dirTexture + "airplane.jpg");
    earthTexture = loadTexture(dirTexture + "earth.jpg");

    // VAO, VBO
    airplaneVAO = modelVAO(*airplaneObject);
    earthVAO = modelVAO(*earthObject);
    cubeVAO = modelVAO(*cubeObject);
}
