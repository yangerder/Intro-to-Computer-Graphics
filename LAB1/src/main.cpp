#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <bits/stdc++.h>

#include "./header/Shader.h"
#include "./header/Object.h"

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void drawModel(const string& name, const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection, int r, int g, int b);
void init();

// settings
int SCR_WIDTH = 800;
int SCR_HEIGHT = 600;
glm::vec3 helicopter_position(0.0f, 20.0f, 10.0f);

// Shader
Shader *shader;

// Objects to display
Object *cube, *cylinder, *I, *C, *G, *tree_up, *tree_btn;

int main()
{
    // glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "ICG_2024_HW1", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetKeyCallback(window, keyCallback);
    glfwSwapInterval(1);
    
    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }    

    // TODO: Enable depth test, face culling
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
    

    // Display loop
	glfwGetFramebufferSize(window, &SCR_WIDTH, &SCR_HEIGHT);
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    // Initialize Object and Shader
    init();

    float helicopter_rotation_angle = 0.0f;  
    float I_rotation_angle = 0.0f;          
    float G_rotation_angle = 0.0f;          


    // render loop
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(153/255.0, 204/255.0, 255/255.0, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 50.0f, 90.0f),  
                                     glm::vec3(0.0f, 0.0f, 0.0f),   
                                     glm::vec3(0.0f, 1.0f, 0.0f)); 

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);

        shader->use();
        
                /*=================== Example of creating model matrix ======================= 
        1. translate
        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(2.0f, 1.0f, 0.0f));
        drawModel("Cube",model,view,projection,255, 0, 0);
        
        2. scale
        glm::mat4 model(1.0f);
        model = glm::scale(model, glm::vec3(0.5f, 1.0f, 2.0f)); 
        drawModel("Cube",model,view,projection,255, 0, 0);
        
        3. rotate
        glm::mat4 model(1.0f);
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        drawModel("Cube",model,view,projection,255, 0, 0);
        ==============================================================================*/

        // TODO: Create model, view, and perspective matrix

        // TODO: Helicopter (Body + Connector + Rotor Blades)
        // Body (At least 3 different color cubes)
        // Connector (One cube)
        //     - On the body
        //     - Rotate: 5 degrees/frame about +y axis
        // Rotor Blades (4 different color cubes)
        //     - On the connector
        //     - Each cubes is offset by 90 degrees
        // You can be creative in design !!

        // TODO: Draw Ground (Scale: (100, 1, 120))

        // TODO: Draw Tree1 (Position: (-30, 0, -20) relative to the Ground, Scale: (4, 4, 4))

        // TODO: Draw Tree2 (Position: (30, 0, 20) relative to the Ground, Scale: (3.5, 3.5, 3.5))

        // TODO: Draw C

        // TODO: Draw I (Rotate: 0.8 degrees/ frame about +y axis around the C)

        // TODO: Draw G (Rotate: 0.8 degrees/ frame about +y axis around the C)

        // TODO: Control rotation
        
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------

        glm::mat4 model_body(1.0f);
        model_body = glm::translate(model_body, helicopter_position);
        model_body = glm::scale(model_body, glm::vec3(10.0f, 10.0f, 10.0f));
        drawModel("Cube", model_body, view, projection, 122, 220, 137);
        glm::mat4 eyes1 = glm::translate(model_body, glm::vec3(0.25f, 0.2f, 0.5f));
        eyes1 = glm::scale(eyes1, glm::vec3(0.2f, 0.2f, 0.2f));  
        drawModel("Cube", eyes1, view, projection, 49, 167, 66);

        glm::mat4 eyes2 = glm::translate(model_body, glm::vec3(-0.25f, 0.2f, 0.5f));
        eyes2 = glm::scale(eyes2, glm::vec3(0.2f, 0.2f, 0.2f));  
        drawModel("Cube", eyes2, view, projection, 49, 167, 66);

        glm::mat4 mouth1 = glm::translate(model_body, glm::vec3(0.05f, -0.15f, 0.5f));
        mouth1 = glm::scale(mouth1, glm::vec3(0.17f, 0.17f, 0.17f));  
        drawModel("Cube", mouth1, view, projection, 49, 167, 66);

        glm::mat4 water = glm::translate(model_body, glm::vec3(0.08f, -0.3f, 0.49f));
        water = glm::scale(water, glm::vec3(0.09f, 0.3f, 0.17f));  
        drawModel("Cube", water, view, projection, 84, 245, 255);

        
        glm::mat4 model_connector = glm::translate(model_body, glm::vec3(0.0f, 0.5f, 0.0f));
        model_connector = glm::rotate(model_connector,glm::radians(helicopter_rotation_angle), glm::vec3(0.0f, 1.0f, 0.0f));
        model_connector = glm::scale(model_connector, glm::vec3(0.5f, 0.5f, 0.5f));
        drawModel("Cube", model_connector, view, projection, 239, 255, 84);


        glm::mat4 model_blade1 = glm::translate(model_connector, glm::vec3(2.0f, 0.4f, 0.0f));
        model_blade1 = glm::scale(model_blade1, glm::vec3(5.0f, 0.1f, 0.8f));
        drawModel("Cube", model_blade1, view, projection, 169, 34, 5);

        glm::mat4 model_blade3 = glm::translate(model_connector, glm::vec3(0.0f, 0.4f, 2.0f));
        model_blade3=glm::rotate(model_blade3,glm::radians(90.f),glm::vec3(0.0f, 1.0f, 0.0f));
        model_blade3 = glm::scale(model_blade3, glm::vec3(5.0f, 0.1f, 0.8f));
        drawModel("Cube", model_blade3, view, projection, 74, 94, 235);

        glm::mat4 model_blade2 = glm::translate(model_connector, glm::vec3(-2.0f, 0.4f, 0.0f)); 
        model_blade2=glm::rotate(model_blade2,glm::radians(180.f),glm::vec3(0.0f, 1.0f, 0.0f));
        model_blade2 = glm::scale(model_blade2, glm::vec3(5.0f, 0.1f, 0.8f)); 
        drawModel("Cube", model_blade2, view, projection, 168, 249, 111); 
    
        glm::mat4 model_blade4 = glm::translate(model_connector, glm::vec3(0.0f, 0.4f, -2.0f));
        model_blade4=glm::rotate(model_blade4,glm::radians(270.f),glm::vec3(0.0f, 1.0f, 0.0f));
        model_blade4 = glm::scale(model_blade4, glm::vec3(5.0f, 0.1f, 0.8f));
        drawModel("Cube", model_blade4, view, projection, 69, 69, 69); 



        glm::mat4 model_ground(1.0f);
        model_ground = glm::translate(model_ground, glm::vec3(0.0f, 0.0f, 0.0f));
        glm::mat4 ground_scale(1.0f);
        ground_scale = glm::scale(model_ground, glm::vec3(100.0f, 1.0f, 120.0f));
        drawModel("Cube", ground_scale, view, projection, 10, 51, 0);

        glm::mat4 model_tree1(1.0f);
        model_tree1 = glm::translate(model_ground, glm::vec3(-30.0f, 0.0f, -20.0f)); 
        model_tree1 = glm::scale(model_tree1, glm::vec3(4.0f, 4.0f, 4.0f));
        drawModel("Tree_up", model_tree1, view, projection, 0, 255, 150);
        drawModel("Tree_down", model_tree1, view, projection, 102, 51, 0);

        glm::mat4 model_tree2(1.0f);
        model_tree2 = glm::translate(model_ground, glm::vec3(30.0f, 0.0f, 20.0f)); 
        model_tree2 = glm::scale(model_tree2, glm::vec3(3.5f, 3.5f, 3.5f));
        drawModel("Tree_up", model_tree2, view, projection, 0, 255, 150);
        drawModel("Tree_down", model_tree2, view, projection, 102, 51, 0);



        glm::mat4 model_C = glm::translate(glm::mat4(1.0f), glm::vec3(-25.0f, 2.0f, 25.0f));
        drawModel("C", model_C, view, projection, 173, 255, 21);

        glm::mat4 model_I = glm::rotate(model_C,glm::radians(I_rotation_angle), glm::vec3(0.0f, 1.0f, 0.0f));  
        model_I = glm::translate(model_I, glm::vec3(-12.0f, 0.0f, 0.0f)); 
        drawModel("I", model_I, view, projection, 255, 0, 111); 


        glm::mat4 model_G = glm::rotate(model_C,glm::radians(G_rotation_angle), glm::vec3(0.0f, 1.0f, 0.0f)); 
        model_G = glm::translate(model_G, glm::vec3(12.0f, 0.0f, 0.0f));  
        drawModel("G", model_G, view, projection, 77, 55, 255); 

        helicopter_rotation_angle += 5.0f;  
        I_rotation_angle += 0.8f;       
        G_rotation_angle += 0.8f;        

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

// TODO:
// Add key callback
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT))
        helicopter_position.y += 1.0f;
    if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT))
        helicopter_position.y -= 1.0f;
    if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT))
        helicopter_position.x -= 1.0f;
    if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT))
        helicopter_position.x += 1.0f;

    if (helicopter_position.y < 5.0f) 
        helicopter_position.y = 5.0f;

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);       

}


// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    SCR_WIDTH = width;
    SCR_HEIGHT = height;
}

void drawModel(const string& name, 
               const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection, 
               int r, int g, int b){

    shader->set_uniform("projection",projection);
    shader->set_uniform("view",view);
    shader->set_uniform("model",model);
    shader->set_uniform("objectColor", glm::vec3(r/255.0,g/255.0,b/255.0));
    
    if(name == "Cube"){
        cube->draw();
    }else if(name == "Cylinder"){
        cylinder->draw();
    }else if(name == "I"){
        I->draw();
    }else if(name == "C"){
        C->draw();
    }else if(name == "G"){
        G->draw();
    }else if(name == "Tree_down"){
        tree_btn->draw();
    }else if(name == "Tree_up"){
        tree_up->draw();
    }
}

void init(){
    #if defined(__linux__) || defined(__APPLE__)
        string dirShader = "../../src/shaders/";
        string dirAsset = "../../src/asset/";
    #else
        string dirShader = "..\\..\\src\\shaders\\";
        string dirAsset = "..\\..\\src\\asset\\";
    #endif

    string v = dirShader + "easy.vert";
    string f = dirShader + "easy.frag";
    shader = new Shader(v.c_str(),f.c_str());
    cube = new Object(dirAsset + "cube.obj");
    cylinder = new Object(dirAsset + "cylinder.obj");
    I = new Object(dirAsset + "I.obj");
    C = new Object(dirAsset + "C.obj");
    G = new Object(dirAsset + "G.obj");
    tree_up = new Object(dirAsset + "tree_up.obj");
    tree_btn = new Object(dirAsset + "tree_btn.obj");
}