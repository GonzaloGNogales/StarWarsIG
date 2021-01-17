#include <iostream>
#include <ogl/glew.h>
#include <ogl/freeglut.h>
#include "Shaders.h"
#include "Model.h"

#define I glm::mat4(1.0)

void funInit();
void funReshape(int w, int h);
void funDisplay();
void cameraZoom(int key, int status, int x, int y);
void cameraMovement(int x, int y);
void HologramAutoRotation(int value);
void moveModel(unsigned char key, int x, int y);
void moveR2D2(float avanz);
void moveTieF(float avanz);
void traslation(int key, int x, int y);


void drawObject(Model model, glm::vec3 color, glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawPlane(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawTriangle(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawCylinder(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawTruncPyramid(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawHexagone(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawHexagoneR(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawTorus(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawDome(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawCube(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawRectangle(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawMotor(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawRidgedTorus(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawTie_Fighter(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawTie_Fighter_Body(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawTie_Fighter_Window(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawTie_Fighter_Weapon(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawR2D2(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawHollowCylinder(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawHalfSphere(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawR2D2_Camera(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawBabyYodaHologram(glm::mat4 P, glm::mat4 V, glm::mat4 M);

 // Shaders variable
    Shaders shaders;

 // Model variables
    Model plane;
    Model cone;
    Model cylinder;
    Model sphere;
    Model triangle;
    Model TruncPyramid;
    Model torus;
    Model dome;
    Model cube;
    Model r2d2;
    Model ridgedTorus;
    Model motor;
    Model hollowCylinder;
    Model halfSphere;
    Model bodyR2D2;
    Model armR2D2;
    Model wheelR2D2;
    Model articulationR2D2;
    Model bbYoda;

 // Viewport variables
    int w = 600;
    int h = 600;

 // Animation variables
    GLint speed = 20;  // 20 ms
                                //Variables globales para animar el holograma de baby Yoda
    float levitatingY= 0.875;
    bool subeHolo=false;
    float rotatingHolo= 1.0;
                                //Variables globales para animar a Tie Fighter
    float aperturaAlasTieF= 0.0;
    float vueloTieF_Y= 1.18;
    float avanzaTieF_Z= 0.0;
    float orientaTieF_Y= 0.0;
    float avanzaTieF_X= 0.0;
    float orientaTieF_UpDown=0.0;


                                //Variables globales para animar a R2D2
    float inclinaCuerpoR2D2= 22.0;
    float colocaCuerpoR2D2= 0.0;
    float giraCabezaR2D2= 0.0;
    float avanzaR2D2_X= 0.0;
    float avanzaR2D2_Z= 0.0;
    float orientaR2D2_Y= 0.0;

                                //Variables globales para animar la cámara
    float zoom = 60.0;
    float alphaX = 0.0;
    float alphaY = 0.0;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int main(int argc, char** argv) {

 // GLUT init
    glutInit(&argc, argv);
    glutInitContextVersion(3,3);
    glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
    glutInitContextProfile(GLUT_CORE_PROFILE);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(w,h);
    glutInitWindowPosition(50,50);
    glutCreateWindow("Práctica Final");

 // GLEW init
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if(GLEW_OK != err) {
        std::cout << "Error: " << glewGetErrorString(err) << std::endl;
        return 0;
    }
    std::cout << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;
    const GLubyte *oglVersion = glGetString(GL_VERSION);
    std::cout <<"This system supports OpenGL Version: " << oglVersion << std::endl;

 // Specific initializations
    funInit();

 // CallBacks configuration
    glutReshapeFunc(funReshape);
    glutDisplayFunc(funDisplay);
    glutTimerFunc(speed, HologramAutoRotation, 0);
    glutKeyboardFunc(moveModel);
    glutSpecialFunc(traslation);
    glutMouseFunc(cameraZoom);
    glutMotionFunc(cameraMovement);


 // Main loop
    glutMainLoop();

    return 0;
}

void funInit() {

 // Depth test
    glEnable(GL_DEPTH_TEST);
    glPolygonOffset(1.0,1.0);

 // Shaders
    shaders.initShaders("resources/shaders/vshader.glsl","resources/shaders/fshader.glsl");

 // Models
    plane.initModel("resources/models/plane.obj");
    cone.initModel("resources/models/cone.obj");
    cylinder.initModel("resources/models/cylinder.obj");
    sphere.initModel("resources/models/sphere.obj");
    triangle.initModel("resources/models/triangle.obj");
    r2d2.initModel("resources/models/r2d2.obj");
    TruncPyramid.initModel("resources/models/Truncated_pyramid.obj");
    torus.initModel("resources/models/torus.obj");
    dome.initModel("resources/models/dome.obj");
    cube.initModel("resources/models/cube.obj");
    ridgedTorus.initModel("resources/models/Ridged Torus.obj");
    motor.initModel("resources/models/motor.obj");
    hollowCylinder.initModel("resources/models/Hollow_Cylinder.obj");
    halfSphere.initModel("resources/models/Half Sphere.obj");
    bodyR2D2.initModel("resources/models/bodyR2D2.obj");
    armR2D2.initModel("resources/models/armR2D2.obj");
    wheelR2D2.initModel("resources/models/wheelR2D2.obj");
    articulationR2D2.initModel("resources/models/articulationR2D2.obj");
    bbYoda.initModel("resources/models/babyYoda.obj");

}

void funReshape(int wnew, int hnew) {

 // Viewport configuration
    glViewport(0, 0, wnew, hnew);

 // w & h update
    w = wnew;
    h = hnew;

}

void funDisplay() {

 // Erase the color buffer
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

 // Declare the shaders
    shaders.useShaders();

// ----------------------------------------------      MATRIX     ----------------------------------------------

 // Matrix P
    float fovy   = zoom;
    float nplane = 0.1;
    float fplane = 25.0;
    float aspect = (float)w/(float)h;
    glm::mat4 P = glm::perspective(glm::radians(fovy), aspect, nplane, fplane);

 // Matrix V
    float x = 5.0f*glm::cos(glm::radians(alphaY))*glm::sin(glm::radians(alphaX));
    float y = 5.0f*glm::sin(glm::radians(alphaY));
    float z = 5.0f*glm::cos(glm::radians(alphaY))*glm::cos(glm::radians(alphaX));
    glm::vec3 pos(x,y,z);
    glm::vec3 lookat(0.0, 0.0, 0.0);
    glm::vec3 up(0.0, 1.0,  0.0);
    glm::mat4 V = glm::lookAt(pos, lookat, up);

 // Matrix M1
    glm::mat4 T1 = glm::translate(I, glm::vec3(2.0, 0.0, 2.0));
    glm::mat4 R18y_1 = glm::rotate(I, glm::radians(18.0f), glm::vec3(0, 1, 0));
    glm::mat4 M1 = T1*R18y_1;

 // Matrix M2
    glm::mat4 T2 = glm::translate(I, glm::vec3(1.0, 0.0, 1.0));
    glm::mat4 R45xz_2 = glm::rotate(I, glm::radians(45.0f), glm::vec3(-1, 0, 1));
    glm::mat4 R45y_2 = glm::rotate(I, glm::radians(45.0f), glm::vec3(0, 1, 0));
    glm::mat4 M2 = T2*R45xz_2*R45y_2;

// ------------------------------------------------------------------------------------------------------------------ \\

 // Draw the scene
    drawPlane(P,V,I);
    glm::mat4 T= glm::translate(I, glm::vec3(avanzaTieF_X, vueloTieF_Y, avanzaTieF_Z));

	
    glm::mat4 RtiefY= glm::rotate(I, glm::radians(orientaTieF_Y), glm::vec3(0.0, 1.0, 0.0));
    glm::mat4 RtiefUpDown= glm::rotate(I, glm::radians(orientaTieF_UpDown), glm::vec3(0.0, 0.0, 1.0));
    glm::mat4 R= glm::rotate(I, glm::radians(-90.0f), glm::vec3(0.0, 1.0, 0.0));
    drawTie_Fighter(P,V,I*T*RtiefY*RtiefUpDown*R);

    glm::mat4 Rr2d2Y= glm::rotate(I, glm::radians(orientaR2D2_Y), glm::vec3(0.0, 1.0, 0.0));
    glm::mat4 Tr2d2= glm::translate(I, glm::vec3(avanzaR2D2_X, 0.0, avanzaR2D2_Z));
    //drawR2D2(P,V,I*Tr2d2*Rr2d2Y);


    //drawBabyYodaHologram(P,V,I);

 // Swap buffers
    glutSwapBuffers();

}

void drawObject(Model model, glm::vec3 color, glm::mat4 P, glm::mat4 V, glm::mat4 M) {

    shaders.setMat4("uPVM",P*V*M);

    glEnable(GL_POLYGON_OFFSET_FILL);
        shaders.setVec3("uColor",color);
        model.renderModel(GL_FILL);
    glDisable(GL_POLYGON_OFFSET_FILL);

    shaders.setVec3("uColor",glm::vec3(0.75*color[0], 0.75*color[1], 0.75*color[2]));
    model.renderModel(GL_LINE);

}

// ----------------------------------------------      Drawing Models Functions     ----------------------------------------------

void drawPlane(glm::mat4 P, glm::mat4 V, glm::mat4 M) {

    glm::mat4 S = glm::scale(I, glm::vec3(2.0, 1.0, 2.0));
    drawObject(plane,glm::vec3(0.5, 0.5, 0.5),P,V,M*S);

}

void drawTriangle(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    drawObject(triangle, glm::vec3(0.2,0.2,0.2),P,V,M);
}

void drawTriangleR(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    drawObject(triangle, glm::vec3(0.9,0.9,0.9),P,V,M);
}

void drawSphere(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    drawObject(sphere, glm::vec3(0.75,0.75,0.75),P,V,M);
}

void drawHalfSphere(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    drawObject(halfSphere, glm::vec3(0.75,0.75,0.75),P,V,M);
}

void drawCylinder(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    glm::mat4 T = glm::translate(I, glm::vec3(0.0, 1.0, 0.0));
    drawObject(cylinder, glm::vec3(0.75,0.75,0.75),P,V,M*T);
}

void drawCube2(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    drawObject(cube, glm::vec3(1.0,0.0,0.0),P,V,M);
}

void drawRectangle(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    glm::mat4 S= glm::scale(I, glm::vec3(0.5, 1.0, 0.5));
    drawObject(cube, glm::vec3(0.8,0.8,0.8),P,V,M*S);
}

void drawTruncPyramid(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    glm::mat4 R270= glm::rotate(I, glm::radians(270.0f), glm::vec3(1.0,0.0,0.0));
    drawObject(TruncPyramid, glm::vec3(1.0,1.0,1.0),P,V,M*R270);
}

void drawTorus(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    drawObject(torus, glm::vec3(0.0,0.3,0.9),P,V,M);
}

void drawDome(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    drawObject(dome, glm::vec3(0.0,0.0,1.0),P,V,M);
}

void drawBodyR2D2(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    drawObject(bodyR2D2, glm::vec3(0.8,0.8,0.8),P,V,M);
}

void drawMotor(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    drawObject(motor, glm::vec3(0.0,0.0,0.0),P,V,M);
}

void drawMotorSmall(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    drawObject(motor, glm::vec3(0.35,0.35,0.35),P,V,M);
}

void drawRidgedTorus(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    drawObject(ridgedTorus, glm::vec3(0.2,0.2,0.2),P,V,M);
}

void drawHexagone(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    glm::mat4 R180= glm::rotate(I, glm::radians(180.0f), glm::vec3(0.0,0.0,1.0));
    glm::mat4 T= glm::translate(I, glm::vec3(0.0, -1.0, 0.0));
    glm::mat4 T2= glm::translate(I, glm::vec3(1.0, 2.0, 0.0));
    glm::mat4 T3= glm::translate(I, glm::vec3(-1.0, 2.0, 0.0));
    glm::mat4 T4= glm::translate(I, glm::vec3(1.0, -2.0, 0.0));
    glm::mat4 T5= glm::translate(I, glm::vec3(-1.0, -2.0, 0.0));

    drawTriangle(P,V,M*T);
    drawTriangle(P,V,M*T2*T);
    drawTriangle(P,V,M*T3*T);
    drawTriangle(P,V,M*R180*T);
    drawTriangle(P,V,M*T4*R180*T);
    drawTriangle(P,V,M*T5*R180*T);

}

void drawTie_Fighter_Ala_Panel_TriangleNormal(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    glm::mat4 Scube= glm::scale(I, glm::vec3(1.05, 0.05, 0.05));
    glm::mat4 Tcube= glm::translate(I, glm::vec3(0.0, -1.0, 0.0));

    drawCube2(P,V,M*Tcube*Scube);
    drawTriangleR(P,V,M);
}

void drawTie_Fighter_Ala_Panel_TriangleLateral(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    glm::mat4 Slateral= glm::scale(I, glm::vec3(1.15, 0.05, 0.05));
    glm::mat4 R65= glm::rotate(I, glm::radians(65.0f), glm::vec3(0.0,0.0,-1.0));
    glm::mat4 Tcube= glm::translate(I, glm::vec3(0.5, 0.0, 0.0));

    drawCube2(P,V,M*Tcube*R65*Slateral);
    drawTriangleR(P,V,M);
}

void drawTie_Fighter_Ala_Panel(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    glm::mat4 R45= glm::rotate(I, glm::radians(53.5f), glm::vec3(0.0,0.0,1.0));
    glm::mat4 R180= glm::rotate(I, glm::radians(180.0f), glm::vec3(0.0,0.0,1.0));
    glm::mat4 T= glm::translate(I, glm::vec3(0.0, -1, 0.0));
    glm::mat4 T2= glm::translate(I, glm::vec3(1.0, 2.0, 0.0));
    glm::mat4 T5= glm::translate(I, glm::vec3(-1.0, -2.0, 0.0));
    glm::mat4 SinverseX= glm::scale(I, glm::vec3(-1.0, 1.0, 1.0));

    glm::mat4 RaperturaAbajo= glm::rotate(I, glm::radians(aperturaAlasTieF), glm::vec3(1.0, 0.0, 0.0));
    glm::mat4 RaperturaArriba= glm::rotate(I, glm::radians(-aperturaAlasTieF), glm::vec3(1.0, 0.0, 0.0));

    //Parte de abajo
    drawTie_Fighter_Ala_Panel_TriangleNormal(P,V,M*RaperturaAbajo*T);
    drawTie_Fighter_Ala_Panel_TriangleLateral(P,V,M*RaperturaArriba*T2*T);
    drawTie_Fighter_Ala_Panel_TriangleLateral(P,V,M*RaperturaArriba*SinverseX*T2*T);

    //Parte de arriba
    drawTie_Fighter_Ala_Panel_TriangleNormal(P,V,M*RaperturaArriba*R180*T);
    drawTie_Fighter_Ala_Panel_TriangleLateral(P,V,M*RaperturaAbajo*SinverseX*T5*R180*T);
    drawTie_Fighter_Ala_Panel_TriangleLateral(P,V,M*RaperturaAbajo*T5*R180*T);

}

void drawTie_Fighter_Ala(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    glm::mat4 Ssmall= glm::scale(I, glm::vec3(0.05, 0.05, 0.05));
    glm::mat4 Sbig= glm::scale(I, glm::vec3(0.5, 0.575, 0.5));

    drawHexagone(P,V,M*Ssmall);
    drawTie_Fighter_Ala_Panel(P,V,M*Sbig);
}

void drawTie_Fighter_Body(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    glm::mat4 SS= glm::scale(I, glm::vec3(0.5, 0.5, 0.5));
    drawSphere(P,V,M*SS);

    glm::mat4 T= glm::translate(I, glm::vec3(0.0, 0.0, -0.4));
    glm::mat4 R90Y= glm::rotate(I, glm::radians(90.0f), glm::vec3(0.0,-1.0,0.0));
    drawTie_Fighter_Window(P,V,M*R90Y*T);

}

void drawTie_Fighter_Window(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    glm::mat4 S= glm::scale(I, glm::vec3(0.005, 0.002, 0.005));
    glm::mat4 T= glm::translate(I, glm::vec3(0.0, 0.3, 0.0));
    glm::mat4 R90X= glm::rotate(I, glm::radians(90.0f), glm::vec3(-1.0,0.0,0.0));
    drawDome(P,V,M*T*R90X*S);

    glm::mat4 ST= glm::scale(I, glm::vec3(0.3, 0.5, 0.3));
    glm::mat4 TT= glm::translate(I, glm::vec3(0.0, 0.0, 0.12));
    drawTorus(P,V,M*TT*R90X*ST);
}

void drawTie_Fighter_ArmP1(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    glm::mat4 S= glm::scale(I, glm::vec3(0.08, 0.075, 0.08));
    glm::mat4 S2= glm::scale(I, glm::vec3(0.05, 0.075, 0.12));

    drawTruncPyramid(P,V,M*S);
    drawTruncPyramid(P,V,M*S2);
}

void drawTie_Fighter_ArmP2(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    glm::mat4 Ttop= glm::translate(I, glm::vec3(0.0, 0.15, 0.0));
    glm::mat4 Stop= glm::scale(I, glm::vec3(0.5, 1.2, 0.5));

    drawTie_Fighter_ArmP1(P, V, M);
    drawTie_Fighter_ArmP1(P, V, M*Ttop*Stop);
}

void drawTie_Fighter_ArmP3(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    glm::mat4 Sbottom= glm::scale(I, glm::vec3(0.045, 0.25, 0.045));
    glm::mat4 Stop= glm::scale(I, glm::vec3(0.085, 0.015, 0.085));
    glm::mat4 Ttop= glm::translate(I, glm::vec3(0.0, 0.5, 0.0));

    drawCylinder(P,V,M*Sbottom);
    drawCylinder(P,V,M*Ttop*Stop);
    drawTie_Fighter_ArmP2(P, V, M);
    drawTie_Fighter_ArmP2(P, V, M);
}

void drawTie_Fighter_Arm(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    glm::mat4 R90= glm::rotate(I, glm::radians(90.0f), glm::vec3(1.0,0.0,0.0));
    glm::mat4 TAla= glm::translate(I, glm::vec3(0.0, 0.53, 0.0));

    drawTie_Fighter_ArmP3(P,V,M);
    drawTie_Fighter_Ala(P,V,M*TAla*R90);

}

void drawTie_Fighter_Motor(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    glm::mat4 RY90= glm::rotate(I, glm::radians(90.0f), glm::vec3(0.0,1.0,0.0));
    glm::mat4 S= glm::scale(I, glm::vec3(0.025, 0.05, 0.05));
    glm::mat4 TMotor= glm::translate(I, glm::vec3(-0.25, 0.0, 0.0));

    drawMotor(P,V,M*TMotor*S*RY90);

    glm::mat4 RYN180= glm::rotate(I, glm::radians(90.0f), glm::vec3(0.0,-1.0,0.0));
    glm::mat4 SS= glm::scale(I, glm::vec3(0.025, 0.025, 0.025));
    glm::mat4 T= glm::translate(I, glm::vec3(-0.58, 0.0, 0.0));

    drawMotorSmall(P,V,M*T*SS*RYN180);

    glm::mat4 TT= glm::translate(I, glm::vec3(-3.0, -0.5, -2.0));    //Centrado en -2.-0.5.-2
    glm::mat4 ST= glm::scale(I, glm::vec3(0.4, 0.6, 0.6));

    drawRidgedTorus(P,V,M*ST*TT);
}

void drawTie_Fighter_Weapon(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    glm::mat4 SR= glm::scale(I, glm::vec3(0.5, 0.5, 0.5));
    glm::mat4 TR= glm::translate(I, glm::vec3(0.0, 1.5, 0.0));

    drawRectangle(P,V,M);
    drawRectangle(P,V,M*TR*SR);

    glm::mat4 SC= glm::scale(I, glm::vec3(0.3, 0.3, 0.3));
    glm::mat4 TC= glm::translate(I, glm::vec3(0.0, 2.25, 0.0));

    drawCube2(P,V,M*TC*SC);
}

void drawTie_Fighter(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    glm::mat4 RL90= glm::rotate(I, glm::radians(-90.0f), glm::vec3(1.0,0.0,0.0));
    glm::mat4 TLArm= glm::translate(I, glm::vec3(0.0, 0.0, -0.43));
    glm::mat4 Sinverse= glm::scale(I, glm::vec3(1.0, 1.0, -1.0));

    drawTie_Fighter_Arm(P,V,M*TLArm*RL90);
    drawTie_Fighter_Body(P,V,M);
    drawTie_Fighter_Arm(P,V,M*Sinverse*TLArm*RL90);

    glm::mat4 SM= glm::scale(I, glm::vec3(0.75, 0.95, 0.95));
    glm::mat4 TM= glm::translate(I, glm::vec3(-0.125, 0.0, 0.0));

    drawTie_Fighter_Motor(P,V,M*TM*SM);

    glm::mat4 SW= glm::scale(I, glm::vec3(0.1, 0.1, 0.1));
    glm::mat4 RW90= glm::rotate(I, glm::radians(90.0f), glm::vec3(0.0,0.0,-1.0));
    glm::mat4 TW= glm::translate(I, glm::vec3(0.25, -0.35, 0.25));

    drawTie_Fighter_Weapon(P,V,M*TW*SW*RW90);
    drawTie_Fighter_Weapon(P,V,M*Sinverse*TW*SW*RW90);
    //Para que esté arriba: glm::mat4 T= glm::translate(I, glm::vec3(0.0, 1.15, 0.0));
}

// ___________________________________________________________    R2D2    ___________________________________________________________ //

void drawHollowCylinder(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    drawObject(hollowCylinder, glm::vec3(0.2,0.2,0.2),P,V,M);
}

void drawR2D2_Camera(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    glm::mat4 SC= glm::scale(I, glm::vec3(0.05625, 0.05625, 0.07125));
    glm::mat4 TC= glm::translate(I, glm::vec3(0.0, 0.0, -0.30));

    drawHollowCylinder(P,V,M*TC*SC);

    glm::mat4 SSmall= glm::scale(I, glm::vec3(0.07125, 0.07125, 0.07125));
    glm::mat4 Tsmall= glm::translate(I, glm::vec3(0.0, 0.0, -0.075));
    drawSphere(P,V,M*Tsmall*SSmall);

    glm::mat4 SBig= glm::scale(I, glm::vec3(0.1875, 0.1875, 0.1875));
    glm::mat4 Tbig= glm::translate(I, glm::vec3(0.0, 0.0, -0.325));

    drawSphere(P,V,M*Tbig*SBig);
}

void drawR2D2_Head(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    glm::mat4 SHS= glm::scale(I, glm::vec3(1.5, 1.7, 1.5));
    glm::mat4 THS= glm::translate(I, glm::vec3(3.0, 0.0, 3.0));

    drawHalfSphere(P,V,M*THS*SHS);

    glm::mat4 TCfrontal= glm::translate(I, glm::vec3(0.55, 0.6, 1.55));
    glm::mat4 R15= glm::rotate(I, glm::radians(15.0f), glm::vec3(0.0,1.0,0.0));

    drawR2D2_Camera(P,V,M*TCfrontal*R15);

    glm::mat4 TCupper= glm::translate(I, glm::vec3(0.55, 1.8, -0.55));
    glm::mat4 R100= glm::rotate(I, glm::radians(100.0f), glm::vec3(-1.0,0.0,0.0));

    drawR2D2_Camera(P,V,M*TCupper*R100);

    glm::mat4 TCback= glm::translate(I, glm::vec3(-0.55, 0.6, -1.6));
    glm::mat4 R175= glm::rotate(I, glm::radians(175.0f), glm::vec3(0.0,-1.0,0.0));

    drawR2D2_Camera(P,V,M*TCback*R175);

    glm::mat4 STP= glm::scale(I, glm::vec3(0.3, 0.3, 0.3));
    glm::mat4 TTP= glm::translate(I, glm::vec3(0.0, 0.7, 0.7));
    glm::mat4 R60= glm::rotate(I, glm::radians(60.0f), glm::vec3(1.0,0.0,0.0));

    drawTruncPyramid(P,V,M*TTP*R60*STP);
}

void drawR2D2_Arm(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    glm::mat4 T= glm::translate(I, glm::vec3(0.0, 0.7, 0.1225));
    drawObject(armR2D2, glm::vec3(0.0,0.3,0.9),P,V,M*T);
    drawObject(wheelR2D2, glm::vec3(0.0,0.3,0.9),P,V,M);
}

void drawR2D2_Base(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    glm::mat4 T= glm::translate(I, glm::vec3(0.0, 0.0, -0.8));

    glm::mat4 Rinclinacion= glm::rotate(I, glm::radians((float)(inclinaCuerpoR2D2-22.0)), glm::vec3(-1.0,0.0,0.0));
    glm::mat4 Tcolocacion= glm::translate(I, glm::vec3(0.0, 0.0, colocaCuerpoR2D2));    //Sirve para colocar el "palo" que va unido a la base.
    drawObject(articulationR2D2, glm::vec3(0.0,0.3,0.9),P,V,M*Tcolocacion*Rinclinacion*T);
    drawObject(wheelR2D2, glm::vec3(0.0,0.3,0.9),P,V,M);
}

void drawR2D2_Top(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    glm::mat4 TH= glm::translate(I, glm::vec3(0.0, 0.82, 0.1));
    glm::mat4 SH= glm::scale(I, glm::vec3(0.16, 0.14, 0.16));
    glm::mat4 RH= glm::rotate(I,glm::radians(giraCabezaR2D2), glm::vec3(0.0, 1.0, 0.0));        //Rotamos la cabeza de R2D2

    drawR2D2_Head(P,V,M*TH*RH*SH);

    glm::mat4 TB= glm::translate(I, glm::vec3(0.0, 0.25, 0.095));
    glm::mat4 SB= glm::scale(I, glm::vec3(0.2, 0.2, 0.2));

    drawBodyR2D2(P,V,M*TB*SB);
}

void drawR2D2(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    glm::mat4 Rinclinacion= glm::rotate(I, glm::radians(inclinaCuerpoR2D2), glm::vec3(-1.0,0.0,0.0));
    glm::mat4 Tcolocacion= glm::translate(I, glm::vec3(0.0, 0.0, colocaCuerpoR2D2));
    drawR2D2_Top(P,V,M*Tcolocacion*Rinclinacion);

    glm::mat4 TcolocacionEspecial= glm::translate(I, glm::vec3(0.0, 0.0, colocaCuerpoR2D2/1.5));    //Sirve para terminar de colocar la rueda del centro y que no quede más atrás
    glm::mat4 SBase= glm::scale(I, glm::vec3(0.2, 0.2, 0.2));
    drawR2D2_Base(P,V,M*TcolocacionEspecial*SBase);

    glm::mat4 SArm= glm::scale(I, glm::vec3(0.2, 0.2, 0.2));
    glm::mat4 TArm= glm::translate(I, glm::vec3(0.28, 0.0, -0.2));
    drawR2D2_Arm(P,V,M*TArm*SArm);

    glm::mat4 SArmInverse= glm::scale(I, glm::vec3(-1.0, 1.0, 1.0));
    drawR2D2_Arm(P,V,M*SArmInverse*TArm*SArm);
}

void moveModel(unsigned char key, int x, int y){
    switch (key) {
        case 'o':
            orientaR2D2_Y += 5;
            break;
        case 'O':
            orientaR2D2_Y -= 5;
            break;
        case 'h':
            if (giraCabezaR2D2 < 90) giraCabezaR2D2 += 3;
            break;
        case 'H':
            if (giraCabezaR2D2 > -90) giraCabezaR2D2 -= 3;
            break;
        case 'c':
            if (inclinaCuerpoR2D2 < 22 && inclinaCuerpoR2D2 >= 0){
                inclinaCuerpoR2D2 += 2;
                colocaCuerpoR2D2 += 0.025;
            }
            break;
        case 'C':
            if (inclinaCuerpoR2D2 <= 22 && inclinaCuerpoR2D2 > 0){
                inclinaCuerpoR2D2 -= 2;
                colocaCuerpoR2D2 -= 0.025;
            }
            break;
        case 't':
            orientaTieF_Y += 5;
            break;
        case 'T':
            orientaTieF_Y -= 5;
            break;
        case 'y':
            orientaTieF_UpDown += 5;
            break;
        case 'Y':
            orientaTieF_UpDown -= 5;
            break;
        case 'a':
            if (aperturaAlasTieF < 65) aperturaAlasTieF += 3;
            break;
        case 'A':
            if (aperturaAlasTieF > 0) aperturaAlasTieF -= 3;
            break;
        default:
            break;
    }
    glutPostRedisplay();
}
void traslation(int key, int x, int y){
    switch (key) {
        case GLUT_KEY_UP:
            moveR2D2(0.05);
            vueloTieF_Y+= 0.05;
            break;
        case GLUT_KEY_DOWN:
            moveR2D2(-0.05);
            vueloTieF_Y-= 0.05;
            break;
        case GLUT_KEY_RIGHT:
            moveTieF(0.05);
            break;
        case GLUT_KEY_LEFT:
            moveTieF(-0.05);
            break;
        default:
            break;
    }
    glutPostRedisplay();
}


void moveR2D2(float avanz){
    //Comprobamos en qué "cuadrante" estamos

    avanzaR2D2_X += avanz *sin(glm::radians(orientaR2D2_Y));
    avanzaR2D2_Z += avanz*cos(glm::radians(orientaR2D2_Y));


}

void moveTieF(float avanz){
    //Comprobamos en qué "cuadrante" estamos

    avanzaTieF_X += avanz *sin(glm::radians(orientaTieF_Y));
    avanzaTieF_Z += avanz*cos(glm::radians(orientaTieF_Y));

}

// ___________________________________________________________    Hologram    ___________________________________________________________ //

void drawHologram_Base(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    glm::mat4 Supper= glm::scale(I, glm::vec3(0.25, 0.325, 0.25));
    glm::mat4 Slower= glm::scale(I, glm::vec3(0.375, 0.03, 0.375));
    glm::mat4 ThSphere= glm::translate(I, glm::vec3(2.0, 2.15, 2.0));
    glm::mat4 ShSphere= glm::scale(I, glm::vec3(0.225, 0.225, 0.225));

    drawHalfSphere(P,V,M*ShSphere*ThSphere);
    drawCylinder(P,V,M*Supper);
    drawCylinder(P,V,M*Slower);
}

void drawBabyYodaHologram(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    glm::mat4 T= glm::translate(I, glm::vec3(0.0, levitatingY, 0.0));
    glm::mat4 S= glm::scale(I, glm::vec3(0.225, 0.225, 0.225));
    glm::mat4 R= glm::rotate(I, glm::radians(rotatingHolo), glm::vec3(0.0, 1.0,0.0));

    drawObject(bbYoda,glm::vec3(0.85, 0.85, 1.0),P,V,M*R*T*S);
    drawHologram_Base(P,V,M);
}

void HologramAutoRotation(int value) {
    if(not subeHolo){
        levitatingY -= 0.005;
        if(levitatingY <= 0.775)
            subeHolo=true;
    }
    else{
        levitatingY += 0.005;
        if(levitatingY >= 0.975)
            subeHolo=false;
    }

    rotatingHolo += 0.5;
    glutPostRedisplay();
    glutTimerFunc(speed, HologramAutoRotation ,0);

}

void cameraZoom(int key, int status, int x, int y) {

    switch (key) {
        case 4:
            if (zoom < 60) zoom += 1;
            break;
        case 3:
            if (zoom > 10) zoom -= 1;
            break;
        default:
            break;
    }
    glutPostRedisplay();

}

void cameraMovement(int x, int y) {

    int ax = x - w / 2;
    int ay = y - h / 2;

    int px2degX = ax * 180 / w;
    int px2degY = ay * 90 / (h/2);

    if(px2degX < 180 && px2degX > -180) alphaX = px2degX;
    if(px2degY < 90 && px2degY > -90) alphaY = -px2degY;
    glutPostRedisplay();

}

