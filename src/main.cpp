#include <iostream>
#include <ogl/glew.h>
#include <ogl/freeglut.h>

#include "Shaders.h"
#include "Model.h"
#include "Texture.h"

#include <sstream>

#define I glm::mat4(1.0)
#define N_MODELS 5

std::string toString(const int &i) {
    std::stringstream ss;
    ss << i;
    return ss.str();
}

// Textures and Light Functions
void setLights(glm::mat4 P, glm::mat4 V);
void drawObjectMat(Model model, Material material, glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawObjectTex(Model model, Textures textures, glm::mat4 P, glm::mat4 V, glm::mat4 M);

// Model Building Functions
void funInit();
void funReshape(int w, int h);
void funDisplay();
void cameraZoom(int key, int status, int x, int y);
void cameraMovement(int x, int y);
void animateModel(unsigned char key, int x, int y);
void moveDeathStar (float movement);
void moveBattleship (float movement);
void moveXFighter (float movement);
void moveR2D2(float movement);
void moveTieFighter(float movement);
void hologramAutoRotation(int value);
void modelMovementAndSelection(int key, int x, int y);
void modelMovementExtra(int key, int x, int y);
void cameraRepositioning(float x, float y, float z, float alpha_x, float alpha_y);
void cameraCenter();

// Death Star Model Functions Headers
void drawDeathStarBottom(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawDeathStarTop(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawDeathStar(glm::mat4 P, glm::mat4 V, glm::mat4 M);

// Battleship Model Functions Headers
void drawBattleshipFoot(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawBattleshipJoint(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawBattleshipCalf(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawBattleshipTreadAndCalf(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawBattleshipUnderLeg(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawBattleshipLeg(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawBattleshipTread(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawBattleshipBodyAux(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawBattleshipBody(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawBattleshipHead(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawBattleshipUp(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawBattleship(glm::mat4 P, glm::mat4 V, glm::mat4 M);

// X-Fighter Model Functions Headers
void drawXFighterWing(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawXFighterBody(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawXFighterEngines(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawXFighter(glm::mat4 P, glm::mat4 V, glm::mat4 M);

// R2D2 Model Functions Headers
void drawR2D2Camera(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawR2D2Head(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawR2D2Arm(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawR2D2Base(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawR2D2Top(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawR2D2(glm::mat4 P, glm::mat4 V, glm::mat4 M);

// Tie Fighter Model Functions Headers
void drawTieFighterDetail(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawTieFighterWingPanelTriangleNormal(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawTieFighterWingPanelTriangleLateral(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawTieFighterWingPanel(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawTieFighterWing(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawTieFighterWindow(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawTieFighterBody(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawTieFighterArmLowerBase(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawTieFighterArmUpperBase(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawTieFighterArmConnection(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawTieFighterArm(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawTieFighterWeapon(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawTieFighter(glm::mat4 P, glm::mat4 V, glm::mat4 M);

// Baby Yoda Hologram Model Function Header
void drawHologramBase(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawBabyYodaHologram(glm::mat4 P, glm::mat4 V, glm::mat4 M);

// Terrain-Scenario Model Functions Headers
void drawPlane(glm::mat4 P, glm::mat4 V, glm::mat4 M);


 // Shaders variable
    Shaders shaders;

 // Model variables
     // Terrain Scenario
        Model plane;

     // General + common
        Model sphere;
        Model cylinder;
        Model cube;
        Model triangle;
        Model halfSphere;
        Model truncatedPyramid;

     // Death Star
        Model deathStarBottom;
        Model deathStarTop;

     // Battleship
        Model battleshipFoot;
        Model battleshipJoint;
        Model battleshipCalf;
        Model battleshipBodyAux;
        Model battleshipBody;
        Model battleshipHead;

     // X-Fighter Wing
        Model xfighterWing;
        Model xfighterBody;

     // R2D2
        Model R2D2hollowCylinder;
        Model R2D2Body;
        Model R2D2Arm;
        Model R2D2Wheel;
        Model R2D2Articulation;
        Model R2D2BigCamera;

     // Tie Fighter
        Model tieFighterEngine;
        Model tieFighterWindowStructure;
        Model tieFighterWindowGlass;
        Model tieFighterWingDetail;

     // Baby Yoda Hologram
        Model babyYoda;

 // Texture variables
    Texture imgNoEmissive;
    Texture imgPurpleMarble;
    Texture imgTiefWingSpecular;
    Texture imgTiefWingDiffuse;
    Texture imgTiefWingNormal;
    Texture imgMetallicSpecularTief;
    Texture imgBodyDiffuseTief;
    Texture imgWindow;

    Texture imgDiffuseBigCamera;
    Texture imgDiffuseHeadR2D2;
    Texture imgDiffuseBodyR2D2;
    Texture imgDiffuseArmR2D2;

    Texture imgDiffuseHologram;
    Texture imgSpecularHologram;

 // Lights and Materials
     // Lights
        #define NLD 1
        #define NLP 1
        #define NLF 1

        Light lightG;
        Light lightD[NLD];
        Light lightP[NLP];
        Light lightF[NLF];

     // Materials
        Material  ruby;
        Material  metallicWhite;
        Material  matHolo;
        Material  obsidian;

 // Textures
    Textures  texFloor;
    Textures  texTieFighterWingPanel;
    Textures  texTieFighterBody;
    Textures  texTieFighterWindow;
    Textures  texTieFighterOuterWindow;
    Textures  texLights;
    Textures  texFloorInverse;
    Textures  texBigCamera;
    Textures  texHeadR2D2;
    Textures  texBodyR2D2;
    Textures  texArmR2D2;
    Textures  texHoloBase;
    Textures  texHoloSphere;

 // Viewport variables
    int w = 1024;
    int h = 768;

 // Model camera selection
    // selectDeathStar -> [0]
    // selectBattleship -> [1]
    // selectXFighter -> [2]
    // selectR2D2 -> [3]
    // selectTieFighter -> [4]
    bool selectedModel[N_MODELS];
    bool keyStates[256];

 // Death Star animation variables
    float deathStarMovX = 0.0;
    float deathStarMovY = 3.0;
    float deathStarMovZ = 0.0;
    float deathStarOrientateY = 0.0;
    float deathStarOrientateYTOP = 0.0;
    // float deathStarOrientateXZ = 0.0; -> hablar con Ana

 // Battleship animation variables
    float battleshipMovX = 0.0;
    float battleshipMovY = 0.0;
    float battleshipMovZ = 0.0;
    float battleshipOrientateY = 0.0;

 // X-Fighter animation variables
    float xFighterMovX = 0.0;
    float xFighterMovY = 2.5;
    float xFighterMovZ = 0.0;
    float xFighterOrientateY = 0.0;
    float xFighterWingAperture = 15.0;

 // R2D2 animation variables
    float r2d2MovX = 0.0;
    float r2d2MovY = 0.0;
    float r2d2MovZ = 0.0;
    float r2d2OrientateY = 0.0;
    float r2d2TurnHead = 0.0;
    float r2d2BowBody = 22.0;
    float r2d2PlaceBody = 0.0;

 // Tie Fighter animation variables
    float tieFighterMovX = 0.0;
    float tieFighterMovY = 1.2;
    float tieFighterMovZ = 0.0;
    float tieFighterOrientateY = 0.0;
    float tieFighterWingAperture = 0.0;
    float tieFighterOrientateVertical = 0.0;

 // Baby Yoda Holo animation variables
    GLint speed = 20;  // 20 ms
    float holoLevitatingY = 0.875;
    bool holoUp = false;
    float holoRotating = 1.0;

 // Camera animation variables
    float bufferAlphaXDeathStar = 0.0;
    float bufferAlphaYDeathStar = 0.0;
    float bufferAlphaXBattleship = 0.0;
    float bufferAlphaYBattleship = 0.0;
    float bufferAlphaXXFighter = 0.0;
    float bufferAlphaYXFighter = 0.0;
    float bufferAlphaXR2D2 = 0.0;
    float bufferAlphaYR2D2 = 0.0;
    float bufferAlphaXTieFighter = 0.0;
    float bufferAlphaYTieFighter = 0.0;
    float alphaX = 0.0;
    float alphaY = 0.0;
    float alphaXDeathStar = 0.0;
    float alphaYDeathStar = 0.0;
    float alphaXBattleship = 0.0;
    float alphaYBattleship = 0.0;
    float alphaXXFighter = 0.0;
    float alphaYXFighter = 0.0;
    float alphaXR2D2 = 0.0;
    float alphaYR2D2 = 0.0;
    float alphaXTieFighter = 0.0;
    float alphaYTieFighter = 0.0;
    float center_x = 0.0;
    float center_y = 0.0;
    float center_z = 0.0;
    float eye_x;
    float eye_y;
    float eye_z;
    float zoom = 60.0;
    bool centerAtOrigin = true;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int main(int argc, char** argv) {

 // GLUT init
    glutInit(&argc, argv);
    glutInitContextVersion(3,3);
    glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
    glutInitContextProfile(GLUT_CORE_PROFILE);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(w,h);
    glutInitWindowPosition(425,150);
    glutCreateWindow("Trabajo Final");

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
    glutMouseFunc(cameraZoom);
    glutMotionFunc(cameraMovement);
    glutKeyboardFunc(animateModel);
    glutSpecialFunc(modelMovementAndSelection);
    glutSpecialUpFunc(modelMovementExtra);
    glutTimerFunc(speed, hologramAutoRotation, 0);

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
    cylinder.initModel("resources/models/Cylinder.obj");
    sphere.initModel("resources/models/Sphere.obj");
    triangle.initModel("resources/models/Triangle.obj");
    cube.initModel("resources/models/Cube.obj");
    halfSphere.initModel("resources/models/HalfSphere.obj");
    truncatedPyramid.initModel("resources/models/TruncatedPyramid.obj");

    deathStarBottom.initModel("resources/models/DeathStarUnder.obj");
    deathStarTop.initModel("resources/models/DeathStarTop.obj");

    battleshipFoot.initModel("resources/models/BattleshipFoot.obj");
    battleshipJoint.initModel("resources/models/BattleshipJoint.obj");
    battleshipCalf.initModel("resources/models/BattleshipCalf.obj");
    battleshipBodyAux.initModel("resources/models/BattleshipBodyAux.obj");
    battleshipBody.initModel("resources/models/BattleshipBody.obj");
    battleshipHead.initModel("resources/models/BattleshipHead.obj");

    xfighterWing.initModel("resources/models/XFighterWing.obj");
    xfighterBody.initModel("resources/models/XFighterBody.obj");

    R2D2hollowCylinder.initModel("resources/models/HollowCylinder.obj");
    R2D2Body.initModel("resources/models/R2D2Body.obj");
    R2D2Arm.initModel("resources/models/R2D2Arm.obj");
    R2D2Wheel.initModel("resources/models/R2D2Wheel.obj");
    R2D2Articulation.initModel("resources/models/R2D2Articulation.obj");
    R2D2BigCamera.initModel("resources/models/R2D2BigCamera.obj");

    tieFighterEngine.initModel("resources/models/TieFighterEngine.obj");
    tieFighterWindowStructure.initModel("resources/models/TieFighterWindow.obj");
    tieFighterWindowGlass.initModel("resources/models/TieFighterWindowGlass.obj");
    tieFighterWingDetail.initModel("resources/models/TieFighterWingDetail.obj");

    babyYoda.initModel("resources/models/BabyYoda.obj");

    plane.initModel("resources/models/Plane.obj");

 // Textures (images)
    imgNoEmissive.initTexture("resources/textures/img1.png");

    // R2D2
    imgDiffuseBigCamera.initTexture("resources/textures/diffuseBigCameraR2D2.png");
    imgDiffuseHeadR2D2.initTexture("resources/textures/diffuseHeadR2D2.png");
    imgDiffuseBodyR2D2.initTexture("resources/textures/diffuseBodyR2D2.png");
    imgDiffuseArmR2D2.initTexture("resources/textures/diffuseArmR2D2.png");

    // TieFighter
    imgTiefWingDiffuse.initTexture("resources/textures/TiefWingDiffuse.png");
    imgTiefWingSpecular.initTexture("resources/textures/TiefWingSpecular.png");
    imgMetallicSpecularTief.initTexture("resources/textures/MetallicSpecular.png");
    imgBodyDiffuseTief.initTexture("resources/textures/TiefBodyDiffuse.png");
    imgTiefWingNormal.initTexture("resources/textures/TiefWingNormal.png");
    imgWindow.initTexture("resources/textures/TiefWindow.png");

    // Baby Yoda Hologram
    imgDiffuseHologram.initTexture("resources/textures/diffuseSphereHologramBase.png");
    imgSpecularHologram.initTexture("resources/textures/specularSphereHologramBase.png");
    imgPurpleMarble.initTexture("resources/textures/purpleMarble.png");

 // Materials initializations
    ruby.ambient   = glm::vec4(0.1745f, 0.01175f, 0.01175f, 1.0f);
    ruby.diffuse   = glm::vec4(0.61424f, 0.04136f, 0.04136f, 1.0f);
    ruby.specular  = glm::vec4(0.727811f, 0.626959f, 0.626959f, 1.0f);
    ruby.emissive  = glm::vec4(0.000000f, 0.000000f, 0.000000f, 1.00f);
    ruby.shininess = 76.8f;

    metallicWhite.ambient   = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
    metallicWhite.diffuse   = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
    metallicWhite.specular  = glm::vec4(0.71f, 0.71f, 0.71f, 1.0f);
    metallicWhite.emissive  = glm::vec4(0.000000f, 0.000000f, 0.000000f, 1.00f);
    metallicWhite.shininess = 10.0f;

    matHolo.ambient   = glm::vec4(0.105882f, 0.058824f, 0.113725f, 1.2f);
    matHolo.diffuse   = glm::vec4(0.427451f, 0.470588f, 0.541176f, 1.2f);
    matHolo.specular  = glm::vec4(0.333333f, 0.333333f, 0.521569f, 1.2f);
    matHolo.emissive  = glm::vec4(0.000000f, 0.000000f, 0.000000f, 1.2f);
    matHolo.shininess = 10.0f;

    obsidian.ambient   = glm::vec4(0.05375f, 0.05f, 0.06625f, 0.82f);
    obsidian.diffuse   = glm::vec4(0.18275f, 0.17f, 0.22525f, 0.82f);
    obsidian.specular  = glm::vec4(0.332741f, 0.328634f, 0.346435f, 0.82f);
    obsidian.emissive  = glm::vec4(0.000000f, 0.000000f, 0.000000f, 1.2f);
    obsidian.shininess = 38.4f;

    // R2D2
    texBigCamera.diffuse = imgDiffuseBigCamera.getTexture();
    texBigCamera.specular = imgMetallicSpecularTief.getTexture();
    texBigCamera.emissive  = imgNoEmissive.getTexture();
    texBigCamera.normal    = 0;
    texBigCamera.shininess = 10.0;

    texHeadR2D2.diffuse = imgDiffuseHeadR2D2.getTexture();
    texHeadR2D2.specular = imgMetallicSpecularTief.getTexture();
    texHeadR2D2.emissive  = imgNoEmissive.getTexture();
    texHeadR2D2.normal    = 0;
    texHeadR2D2.shininess = 10.0;

    texBodyR2D2.diffuse = imgDiffuseBodyR2D2.getTexture();
    texBodyR2D2.specular = imgMetallicSpecularTief.getTexture();
    texBodyR2D2.emissive  = imgNoEmissive.getTexture();
    texBodyR2D2.normal    = 0;
    texBodyR2D2.shininess = 10.0;

    texArmR2D2.diffuse = imgDiffuseArmR2D2.getTexture();
    texArmR2D2.specular = imgMetallicSpecularTief.getTexture();
    texArmR2D2.emissive  = imgNoEmissive.getTexture();
    texArmR2D2.normal    = 0;
    texArmR2D2.shininess = 10.0;

    // Tie Fighter
    texTieFighterWingPanel.diffuse   = imgTiefWingDiffuse.getTexture();
    texTieFighterWingPanel.specular  = imgTiefWingSpecular.getTexture();
    texTieFighterWingPanel.emissive  = imgNoEmissive.getTexture();
    texTieFighterWingPanel.normal    = imgTiefWingNormal.getTexture();
    texTieFighterWingPanel.shininess = 10.0;

    texTieFighterBody.diffuse   = imgBodyDiffuseTief.getTexture();
    texTieFighterBody.specular  = imgMetallicSpecularTief.getTexture();
    texTieFighterBody.emissive  = imgNoEmissive.getTexture();
    texTieFighterBody.normal    = 0;
    texTieFighterBody.shininess = 10.0;

    texTieFighterWindow.diffuse = imgWindow.getTexture();
    texTieFighterWindow.specular = imgMetallicSpecularTief.getTexture();
    texTieFighterWindow.emissive  = imgNoEmissive.getTexture();
    texTieFighterWindow.normal    = 0;
    texTieFighterWindow.shininess = 10.0;

    texTieFighterOuterWindow.diffuse = imgBodyDiffuseTief.getTexture();
    texTieFighterOuterWindow.specular = imgMetallicSpecularTief.getTexture();
    texTieFighterOuterWindow.emissive  = imgNoEmissive.getTexture();
    texTieFighterOuterWindow.normal    = 0;
    texTieFighterOuterWindow.shininess = 10.0;

    // Baby Yoda
    texHoloSphere.diffuse = imgDiffuseHologram.getTexture();
    texHoloSphere.specular = imgNoEmissive.getTexture();
    texHoloSphere.emissive  = imgPurpleMarble.getTexture();
    texHoloSphere.normal    = 0;
    texHoloSphere.shininess = 10.0;

    texHoloBase.diffuse = imgMetallicSpecularTief.getTexture();
    texHoloBase.specular = imgSpecularHologram.getTexture();
    texHoloBase.emissive  = imgNoEmissive.getTexture();
    texHoloBase.normal    = 0;
    texHoloBase.shininess = 10.0;

 // Global Ambient Light
    lightG.ambient = glm::vec3(0.4, 0.4, 0.4);

 // Directional Lights
    lightD[0].direction = glm::vec3(0.0, -1.0, 0.0);
    lightD[0].ambient = glm::vec3( 0.1, 0.1, 0.1);
    lightD[0].diffuse = glm::vec3( 0.7, 0.7, 0.7);
    lightD[0].specular = glm::vec3( 0.7, 0.7, 0.7);

 // Positional Lights
    lightP[0].position = glm::vec3(-1.5,0.2,0.0);
    lightP[0].ambient = glm::vec3(0.2, 0.2, 0.2);
    lightP[0].diffuse = glm::vec3(0.9, 0.9, 0.9);
    lightP[0].specular = glm::vec3(0.9, 0.9, 0.9);
    lightP[0].c0 = 1.00;
    lightP[0].c1 = 0.22;
    lightP[0].c2 = 0.20;

 // Focal Lights
    lightF[0].position = glm::vec3(3.0,  3.0,  4.0);
    lightF[0].direction = glm::vec3(-3.0, -3.0, -4.0);
    lightF[0].ambient = glm::vec3(0.2,  0.2,  0.2);
    lightF[0].diffuse = glm::vec3(0.9,  0.9,  0.9);
    lightF[0].specular = glm::vec3(0.9,  0.9,  0.9);
    lightF[0].innerCutOff = 7.75;
    lightF[0].outerCutOff = lightF[0].innerCutOff + 0.25;
    lightF[0].c0 = 1.000;
    lightF[0].c1 = 0.090;
    lightF[0].c2 = 0.032;

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
    if (centerAtOrigin) cameraCenter();
    glm::vec3 pos(eye_x,eye_y,eye_z);
    glm::vec3 lookat(center_x, center_y, center_z);
    glm::vec3 up(0.0, 1.0,  0.0);
    glm::mat4 V = glm::lookAt(pos, lookat, up);

// ------------------------------------------------------------------------------------------------------------------ \\

 // Set Lights
    setLights(P,V);

 // Draw the scene
    drawPlane(P,V,I);
    drawDeathStar(P,V,I);
    drawBattleship(P,V,I);
    drawXFighter(P,V,I);
    drawR2D2(P,V,I);
    drawTieFighter(P,V,I);
    drawBabyYodaHologram(P,V,I);

 // Swap buffers
    glutSwapBuffers();

}


// ------------------------------------------     Lights and Textures Creation Functions     ----------------------------------------------

void setLights(glm::mat4 P, glm::mat4 V) {

    shaders.setLight("ulightG",lightG);
    for (int i = 0; i < NLD; i++) shaders.setLight("ulightD["+toString(i)+"]",lightD[i]);
    for (int i = 0; i < NLP; i++) shaders.setLight("ulightP["+toString(i)+"]",lightP[i]);
    for (int i = 0; i < NLF; i++) shaders.setLight("ulightF["+toString(i)+"]",lightF[i]);

    for (int i = 0; i < NLP; i++) {
        glm::mat4 M = glm::translate(I,lightP[i].position) * glm::scale(I,glm::vec3(0.025));
        // drawObjectTex(sphere,texLights,P,V,M);
    }

    for (int i = 0; i < NLF; i++) {
        glm::mat4 M = glm::translate(I,lightF[i].position) * glm::scale(I,glm::vec3(0.025));
        // drawObjectTex(sphere,texLights,P,V,M);
    }

}

void drawObjectMat(Model model, Material material, glm::mat4 P, glm::mat4 V, glm::mat4 M) {

    shaders.setMat4("uN"  ,glm::transpose(glm::inverse(M)));
    shaders.setMat4("uM"  ,M);
    shaders.setMat4("uPVM",P*V*M);
    shaders.setBool("uWithMaterials",true);
    shaders.setMaterial("umaterial",material);
    model.renderModel(GL_FILL);

}

void drawObjectTex(Model model, Textures textures, glm::mat4 P, glm::mat4 V, glm::mat4 M) {

    shaders.setMat4("uN"  ,glm::transpose(glm::inverse(M)));
    shaders.setMat4("uM"  ,M);
    shaders.setMat4("uPVM",P*V*M);
    shaders.setBool("uWithMaterials", false);
    shaders.setTextures("utextures",textures);
    if(textures.normal!=0) shaders.setBool("uWithNormals",true);
    else                   shaders.setBool("uWithNormals",false);
    model.renderModel(GL_FILL);

}


// ----------------------------------------------      Drawing Models Functions     ----------------------------------------------

// ----------------------------------------------            Death Star             ----------------------------------------------

void drawDeathStarBottom(glm::mat4 P, glm::mat4 V, glm::mat4 M) {

    glm::mat4 S = glm::scale(I, glm::vec3(0.75, 0.75, 0.75));
    drawObjectTex(deathStarBottom, texTieFighterOuterWindow,P,V,M*S);

}

void drawDeathStarTop(glm::mat4 P, glm::mat4 V, glm::mat4 M) {

    glm::mat4 S = glm::scale(I, glm::vec3(0.75, 0.75, 0.75));
    drawObjectTex(deathStarTop,texTieFighterOuterWindow,P,V,M*S);

}

void drawDeathStar(glm::mat4 P, glm::mat4 V, glm::mat4 M) {

    // glm::mat4 R_xz = glm::rotate(I, glm::radians(deathStarOrientateXZ), glm::vec3(1, 0, 0)); -> hablar con Ana

    glm::mat4 R_y = glm::rotate(I, glm::radians(deathStarOrientateY), glm::vec3(0, 1, 0));
    glm::mat4 R_y_TOP = glm::rotate(I, glm::radians(deathStarOrientateYTOP), glm::vec3(0, 1, 0));
    glm::mat4 T = glm::translate(I, glm::vec3(deathStarMovX, deathStarMovY, deathStarMovZ));
    glm::mat4 R90 = glm::rotate(I, glm::radians(-90.0f), glm::vec3(0, 1, 0));
    drawDeathStarBottom(P,V,M*T*R_y);
    drawDeathStarTop(P,V,M*T*R_y_TOP*R_y*R90);

}


// ----------------------------------------------            Battleship             ----------------------------------------------

void drawBattleshipFoot(glm::mat4 P, glm::mat4 V, glm::mat4 M) {

    glm::mat4 S = glm::scale(I, glm::vec3(0.2, 0.2, 0.2));
    glm::mat4 T = glm::translate(I, glm::vec3(0.0, 0.9, 0.0));
    drawObjectTex(battleshipFoot,texTieFighterOuterWindow,P,V,M*S*T);

}

void drawBattleshipJoint(glm::mat4 P, glm::mat4 V, glm::mat4 M) {

    glm::mat4 S = glm::scale(I, glm::vec3(0.2, 0.2, 0.2));
    glm::mat4 T = glm::translate(I, glm::vec3(0.0, 2.7, 0.0));
    drawObjectTex(battleshipJoint,texTieFighterOuterWindow,P,V,M*S*T);

}

void drawBattleshipCalf(glm::mat4 P, glm::mat4 V, glm::mat4 M) {

    glm::mat4 S = glm::scale(I, glm::vec3(0.2, 0.2, 0.2));
    glm::mat4 T = glm::translate(I, glm::vec3(0.0, 5.5, 0.0));
    glm::mat4 R180_xz = glm::rotate(I, glm::radians(180.0f), glm::vec3(1, 0, 1));
    glm::mat4 R180_x = glm::rotate(I, glm::radians(180.0f), glm::vec3(1, 0, 0));
    drawObjectTex(battleshipCalf,texTieFighterOuterWindow,P,V,M*S*T*R180_x*R180_xz);

}

void drawBattleshipTread(glm::mat4 P, glm::mat4 V, glm::mat4 M) {

    glm::mat4 R90 = glm::rotate(I, glm::radians(90.0f), glm::vec3(0, 1, 0));
    drawBattleshipFoot(P,V,M);
    drawBattleshipJoint(P,V,M);
    drawBattleshipJoint(P,V,M*R90);

}

void drawBattleshipTreadAndCalf(glm::mat4 P, glm::mat4 V, glm::mat4 M) {

    drawBattleshipTread(P,V,M);
    drawBattleshipCalf(P,V,M);

}

void drawBattleshipUnderLeg(glm::mat4 P, glm::mat4 V, glm::mat4 M) {

    glm::mat4 T = glm::translate(I, glm::vec3(0.0, 1.0, 0.0));
    drawBattleshipTreadAndCalf(P,V,M);
    drawBattleshipJoint(P,V,M*T);

}

void drawBattleshipLeg(glm::mat4 P, glm::mat4 V, glm::mat4 M) {

    glm::mat4 T_calf = glm::translate(I, glm::vec3(0.0, 3.0, 0.0));
    glm::mat4 R180_x = glm::rotate(I, glm::radians(180.0f), glm::vec3(1, 0, 0));
    glm::mat4 T_joint = glm::translate(I, glm::vec3(0.0, 2.0, 0.0));
    glm::mat4 S = glm::scale(I, glm::vec3(1.5, 0.9, 1.5));
    drawBattleshipUnderLeg(P,V,M);
    drawBattleshipCalf(P,V,M*T_calf*R180_x);
    drawBattleshipJoint(P,V,M*T_joint*S);

}

void drawBattleshipBodyAux(glm::mat4 P, glm::mat4 V, glm::mat4 M) {

    glm::mat4 S = glm::scale(I, glm::vec3(0.485, 0.485, 0.485));
    drawObjectTex(battleshipBodyAux,texTieFighterOuterWindow,P,V,M*S);

}

void drawBattleshipBody(glm::mat4 P, glm::mat4 V, glm::mat4 M) {

    glm::mat4 S = glm::scale(I, glm::vec3(0.5, 0.5, 0.5));
    drawObjectTex(battleshipBody,texTieFighterOuterWindow,P,V,M*S);

}

void drawBattleshipHead(glm::mat4 P, glm::mat4 V, glm::mat4 M) {

    glm::mat4 S = glm::scale(I, glm::vec3(0.4, 0.4, 0.4));
    glm::mat4 R90_y = glm::rotate(I, glm::radians(-90.0f), glm::vec3(0, 1, 0));
    glm::mat4 T_y = glm::translate(I, glm::vec3(0.0, -0.3, 0.0));
    drawObjectTex(battleshipHead,texTieFighterOuterWindow,P,V,M*T_y*S*R90_y);

}

void drawBattleshipUp(glm::mat4 P, glm::mat4 V, glm::mat4 M) {

    glm::mat4 T_front = glm::translate(I, glm::vec3(0.0, 0.0, -1.0));
    glm::mat4 T_back = glm::translate(I, glm::vec3(0.0, 0.0, 1.0));
    glm::mat4 T_head = glm::translate(I, glm::vec3(0.0, 0.0, 2.0));
    glm::mat4 R180_y = glm::rotate(I, glm::radians(180.0f), glm::vec3(0, 1, 0));
    drawBattleshipBodyAux(P,V,M*T_front);
    drawBattleshipBodyAux(P,V,M*T_back*R180_y);
    drawBattleshipBody(P,V,M);
    drawBattleshipHead(P,V,M*T_head);

}

void drawBattleship(glm::mat4 P, glm::mat4 V, glm::mat4 M) {

    glm::mat4 T = glm::translate(I, glm::vec3(battleshipMovX, battleshipMovY, battleshipMovZ));
    glm::mat4 R_y = glm::rotate(I, glm::radians(battleshipOrientateY), glm::vec3(0, 1, 0));

    glm::mat4 T_up = glm::translate(I, glm::vec3(0.0, 3.1, 0.0));
    glm::mat4 R90_y = glm::rotate(I, glm::radians(90.0f), glm::vec3(0, 1, 0));

    glm::mat4 T_leg1 = glm::translate(I, glm::vec3(1.15, 0.0, 0.55));
    glm::mat4 T_leg2 = glm::translate(I, glm::vec3(1.15, 0.0, -0.55));
    glm::mat4 T_leg3 = glm::translate(I, glm::vec3(-1.15, 0.0, 0.55));
    glm::mat4 T_leg4 = glm::translate(I, glm::vec3(-1.15, 0.0, -0.55));

    drawBattleshipUp(P,V,M*T*R_y*T_up);
    drawBattleshipLeg(P,V,M*T*R_y*R90_y*T_leg1);
    drawBattleshipLeg(P,V,M*T*R_y*R90_y*T_leg2);
    drawBattleshipLeg(P,V,M*T*R_y*R90_y*T_leg3);
    drawBattleshipLeg(P,V,M*T*R_y*R90_y*T_leg4);

}


// ----------------------------------------------            X-Fighter Wing             ----------------------------------------------

void drawXFighterWing(glm::mat4 P, glm::mat4 V, glm::mat4 M) {

    glm::mat4 R90_y = glm::rotate(I, glm::radians(-90.0f), glm::vec3(0, 1, 0));
    glm::mat4 T = glm::translate(I, glm::vec3(1.65, 0.15, -2.0));
    drawObjectTex(xfighterWing,texTieFighterWingPanel,P,V,M*T*R90_y);

}

void drawXFighterBody(glm::mat4 P, glm::mat4 V, glm::mat4 M) {

    glm::mat4 S = glm::scale(I, glm::vec3(0.3, 0.3, 0.3));
    drawObjectTex(xfighterBody,texTieFighterBody,P,V,M*S);

}

void drawXFighterEngines(glm::mat4 P, glm::mat4 V, glm::mat4 M) {

    glm::mat4 R = glm::rotate(I, glm::radians(xFighterWingAperture), glm::vec3(0, 0, 1));
    glm::mat4 S_upper_left = glm::scale(I, glm::vec3(-0.8, 0.8, 0.8));
    glm::mat4 S_upper_right = glm::scale(I, glm::vec3(0.8, 0.8, 0.8));
    glm::mat4 S_under_left = glm::scale(I, glm::vec3(-0.8, -0.8, 0.8));
    glm::mat4 S_under_right = glm::scale(I, glm::vec3(0.8, -0.8, 0.8));
    drawXFighterWing(P,V,M*S_upper_left*R);
    drawXFighterWing(P,V,M*S_upper_right*R);
    drawXFighterWing(P,V,M*S_under_left*R);
    drawXFighterWing(P,V,M*S_under_right*R);

}

void drawXFighter(glm::mat4 P, glm::mat4 V, glm::mat4 M) {

    glm::mat4 R = glm::rotate(I, glm::radians(xFighterOrientateY), glm::vec3(0, 1, 0));
    glm::mat4 T = glm::translate(I, glm::vec3(xFighterMovX, xFighterMovY, xFighterMovZ));
    drawXFighterEngines(P,V,M*T*R);
    drawXFighterBody(P,V,M*T*R);

}


// ----------------------------------------------         R2D2        ----------------------------------------------

void drawR2D2Camera(glm::mat4 P, glm::mat4 V, glm::mat4 M) {

    //Camera sphere eye transformation matrix
    glm::mat4 Seye = glm::scale(I, glm::vec3(0.07125, 0.07125, 0.07125));
    glm::mat4 Teye = glm::translate(I, glm::vec3(0.0, 0.0, -0.075));
    drawObjectMat(sphere,ruby,P,V,M*Teye*Seye);

    //Camera cylindric base transformation matrix
    glm::mat4 SC = glm::scale(I, glm::vec3(0.05625, 0.05625, 0.07125));
    glm::mat4 TC = glm::translate(I, glm::vec3(0.0, 0.0, -0.30));
    drawObjectMat(R2D2hollowCylinder, metallicWhite, P, V, M * TC * SC);

    //Camera sphere base transformation matrix
    glm::mat4 Sbase = glm::scale(I, glm::vec3(0.1875, 0.1875, 0.1875));
    glm::mat4 Tbase = glm::translate(I, glm::vec3(0.0, 0.0, -0.325));
    drawObjectMat(sphere,metallicWhite,P,V,M*Tbase*Sbase);

}

void drawR2D2Head(glm::mat4 P, glm::mat4 V, glm::mat4 M) {

    //Head (principal model) transformation matrix
    glm::mat4 SHS = glm::scale(I, glm::vec3(1.5, 1.7, 1.5));
    glm::mat4 THS = glm::translate(I, glm::vec3(3.0, 0.0, 3.0));
    drawObjectTex(halfSphere, texHeadR2D2, P, V, M * THS * SHS);

    //The next transformations are for the placement of the different "camera" that R2D2 has on his head
    //Transformation matrix of the frontal small "camera"
    glm::mat4 TCfrontal = glm::translate(I, glm::vec3(0.6, 0.5, 1.55));
    glm::mat4 R15 = glm::rotate(I, glm::radians(15.0f), glm::vec3(0.0,1.0,0.0));
    drawR2D2Camera(P, V, M * TCfrontal * R15);

    //Transformation matrix of the upper small "camera"
    glm::mat4 TCupper = glm::translate(I, glm::vec3(0.55, 1.8, -0.55));
    glm::mat4 R100 = glm::rotate(I, glm::radians(100.0f), glm::vec3(-1.0,0.0,0.0));
    drawR2D2Camera(P, V, M * TCupper * R100);

    //Transformation matrix of the back small "camera"
    glm::mat4 TCback = glm::translate(I, glm::vec3(-0.55, 0.6, -1.6));
    glm::mat4 R175 = glm::rotate(I, glm::radians(175.0f), glm::vec3(0.0,-1.0,0.0));
    drawR2D2Camera(P, V, M * TCback * R175);

    //Setting the frontal detail of the head that looks like a big camera
    glm::mat4 STP = glm::scale(I, glm::vec3(1.7, 1.7, 1.7));
    glm::mat4 TTP = glm::translate(I, glm::vec3(0.0, 0.9, 1.15));
    glm::mat4 R30 = glm::rotate(I, glm::radians(-30.0f), glm::vec3(1.0,0.0,0.0));
    drawObjectTex(R2D2BigCamera, texBigCamera, P, V, M * TTP * R30 * STP);

}

void drawR2D2Arm(glm::mat4 P, glm::mat4 V, glm::mat4 M) {

    //Arm transformation matrix
    glm::mat4 T = glm::translate(I, glm::vec3(0.0, 0.165, 0.025));
    drawObjectTex(R2D2Arm, texArmR2D2, P, V, M * T);

    //Arm's wheel transformation matrix
    glm::mat4 S = glm::scale(I, glm::vec3(0.2, 0.2, 0.2));
    drawObjectMat(R2D2Wheel, metallicWhite, P, V, M * S);

}

void drawR2D2Base(glm::mat4 P, glm::mat4 V, glm::mat4 M) {

    //Base's articulation transformation matrix --> it's the part that conects the central wheel with the R2D2 body
    glm::mat4 T = glm::translate(I, glm::vec3(0.0, 0.0, -0.8)); //Principal translation
    glm::mat4 Rinclination = glm::rotate(I, glm::radians((float)(r2d2BowBody - 22.0)), glm::vec3(-1.0, 0.0, 0.0)); //Animation transformation (it inclinates the articulation)
    glm::mat4 Tajustments = glm::translate(I, glm::vec3(0.0, 0.0, r2d2PlaceBody));    //It sets the articulation model connected to the base when the inclination is applicated
    drawObjectMat(R2D2Articulation, metallicWhite, P, V, M * Tajustments * Rinclination * T);
    drawObjectMat(R2D2Wheel, metallicWhite, P, V, M);

}

void drawR2D2Top(glm::mat4 P, glm::mat4 V, glm::mat4 M) {

    //Head trnsformation matrix
    glm::mat4 TH = glm::translate(I, glm::vec3(0.0, 0.82, 0.1));
    glm::mat4 SH = glm::scale(I, glm::vec3(0.16, 0.14, 0.16));
    //Head Animation --> head rotating (looking side to side)
    glm::mat4 RH = glm::rotate(I, glm::radians(r2d2TurnHead), glm::vec3(0.0, 1.0, 0.0));
    drawR2D2Head(P, V, M * TH * RH * SH);

    //Body trnasformation matrix
    glm::mat4 TB = glm::translate(I, glm::vec3(0.0, 0.25, 0.095));
    drawObjectTex(R2D2Body, texBodyR2D2, P, V, M * TB);

}

void drawR2D2(glm::mat4 P, glm::mat4 V, glm::mat4 M) {

    glm::mat4 Rr2d2Y = glm::rotate(I, glm::radians(r2d2OrientateY), glm::vec3(0.0, 1.0, 0.0));
    glm::mat4 Tr2d2 = glm::translate(I, glm::vec3(r2d2MovX, r2d2MovY, r2d2MovZ));

    // Base transformation matrix (it's needed a different placement of the inclination than the articulation that connects the central wheel with the body in "drawR2D2Base")
    glm::mat4 SBase = glm::scale(I, glm::vec3(0.2, 0.2, 0.2));
    glm::mat4 TSpecialPlacement = glm::translate(I, glm::vec3(0.0, 0.0, r2d2PlaceBody/1.5));    // It places the wheel in the cetre
    drawR2D2Base(P,V,M*Tr2d2*Rr2d2Y*TSpecialPlacement*SBase);

    // R2D2 top part (head and principal body) animation transformation matrix
    glm::mat4 RBow = glm::rotate(I, glm::radians(r2d2BowBody), glm::vec3(-1.0,0.0,0.0));
    glm::mat4 TPlacement = glm::translate(I, glm::vec3(0.0, 0.0, r2d2PlaceBody));
    drawR2D2Top(P,V,M*Tr2d2*Rr2d2Y*TPlacement*RBow);

    // Draws the right arm
    glm::mat4 TArm = glm::translate(I, glm::vec3(0.28, 0.0, -0.2));
    drawR2D2Arm(P,V,M*Tr2d2*Rr2d2Y*TArm);

    // Draws the left arm applicating a negative scale in the X axis
    glm::mat4 SArmInverse = glm::scale(I, glm::vec3(-1.0, 1.0, 1.0));
    drawR2D2Arm(P,V,M*Tr2d2*Rr2d2Y*SArmInverse*TArm);

}


// ----------------------------------------------         Tie Fighter         ----------------------------------------------

void drawTieFighterDetail(glm::mat4 P, glm::mat4 V, glm::mat4 M) {

    //Animation
    glm::mat4 RlowerAperture= glm::rotate(I, glm::radians(-tieFighterWingAperture), glm::vec3(0.0, 0.0, 1.0));
    glm::mat4 RupperAperture= glm::rotate(I, glm::radians(tieFighterWingAperture), glm::vec3(0.0, 0.0, 1.0));

    glm::mat4 S= glm::scale(I, glm::vec3(0.25, 0.25, 0.25));
    //Draw the wing detail (is the lower part)
    drawObjectTex(tieFighterWingDetail, texTieFighterBody, P, V, M * RlowerAperture * S);

    glm::mat4 Sinverse= glm::scale(I, glm::vec3(0.25, -0.25, 0.25));
    //Draw the wing detail but inversed (is the upper part)
    drawObjectTex(tieFighterWingDetail, texTieFighterBody, P, V, M * RupperAperture * Sinverse);

}

void drawTieFighterWingPanelTriangleNormal(glm::mat4 P, glm::mat4 V, glm::mat4 M) {

    glm::mat4 Scube= glm::scale(I, glm::vec3(1.05, 0.05, 0.05));
    glm::mat4 Tcube= glm::translate(I, glm::vec3(0.0, -1.0, 0.0));
    drawObjectTex(cube, texTieFighterBody, P, V, M * Tcube * Scube);   //It turns into a rectangle that's going to be the border of the wing structure

    drawObjectTex(triangle, texTieFighterWingPanel, P, V, M);    //This triangle is part of the Tie Fighter's wing pannels

}

void drawTieFighterWingPanelTriangleLateral(glm::mat4 P, glm::mat4 V, glm::mat4 M) {

    glm::mat4 Slateral= glm::scale(I, glm::vec3(1.15, 0.05, 0.05));
    glm::mat4 R65= glm::rotate(I, glm::radians(65.0f), glm::vec3(0.0,0.0,-1.0));
    glm::mat4 Tcube= glm::translate(I, glm::vec3(0.5, 0.0, 0.0));
    drawObjectTex(cube, texTieFighterBody, P, V, M * Tcube * R65 * Slateral);    //It turns into a rectangle that's going to be the border of the wing structure

    drawObjectTex(triangle, texTieFighterWingPanel, P, V, M);    //This triangle is part of the Tie Fighter's wing pannels

}

void drawTieFighterWingPanel(glm::mat4 P, glm::mat4 V, glm::mat4 M) {

    glm::mat4 R45= glm::rotate(I, glm::radians(53.5f), glm::vec3(0.0,0.0,1.0));
    glm::mat4 R180= glm::rotate(I, glm::radians(180.0f), glm::vec3(0.0,0.0,1.0));
    glm::mat4 T= glm::translate(I, glm::vec3(0.0, -1, 0.0));
    glm::mat4 T2= glm::translate(I, glm::vec3(1.0, 2.0, 0.0));
    glm::mat4 T5= glm::translate(I, glm::vec3(-1.0, -2.0, 0.0));
    glm::mat4 SinverseX= glm::scale(I, glm::vec3(-1.0, 1.0, 1.0));

    //Animation
    glm::mat4 RaperturaAbajo= glm::rotate(I, glm::radians(tieFighterWingAperture), glm::vec3(1.0, 0.0, 0.0));
    glm::mat4 RaperturaArriba= glm::rotate(I, glm::radians(-tieFighterWingAperture), glm::vec3(1.0, 0.0, 0.0));

    //Lower part of the hexagone
    drawTieFighterWingPanelTriangleNormal(P, V, M * RaperturaAbajo * T);
    drawTieFighterWingPanelTriangleLateral(P, V, M * RaperturaArriba * T2 * T);
    drawTieFighterWingPanelTriangleLateral(P, V, M * RaperturaArriba * SinverseX * T2 * T);

    //Upper part of the hexagone
    drawTieFighterWingPanelTriangleNormal(P, V, M * RaperturaArriba * R180 * T);
    drawTieFighterWingPanelTriangleLateral(P, V, M * RaperturaAbajo * SinverseX * T5 * R180 * T);
    drawTieFighterWingPanelTriangleLateral(P, V, M * RaperturaAbajo * T5 * R180 * T);

}

void drawTieFighterWing(glm::mat4 P, glm::mat4 V, glm::mat4 M) {

    glm::mat4 R90= glm::rotate(I, glm::radians(90.0f), glm::vec3(0.0,1.0,0.0));
    glm::mat4 Sbig= glm::scale(I, glm::vec3(0.5, 0.575, 0.5));

    drawTieFighterDetail(P, V, M * R90);
    drawTieFighterWingPanel(P, V, M * Sbig);

}

void drawTieFighterWindow(glm::mat4 P, glm::mat4 V, glm::mat4 M) {

    glm::mat4 Tglass= glm::translate(I, glm::vec3(0.0, 0.0, 0.075));
    drawObjectTex(tieFighterWindowGlass, texTieFighterWindow, P, V, M * Tglass);
    drawObjectMat(tieFighterWindowStructure, obsidian, P, V, M);

}

void drawTieFighterBody(glm::mat4 P, glm::mat4 V, glm::mat4 M) {

    glm::mat4 R90= glm::rotate(I, glm::radians(90.0f), glm::vec3(0.0,1.0,0.0));

    //Motor transformation matrix
    glm::mat4 Smotor= glm::scale(I, glm::vec3(0.5, 0.5, 0.95));
    glm::mat4 Tmotor= glm::translate(I, glm::vec3(0.0, 0.0, -0.425));

    drawObjectMat(tieFighterEngine, obsidian, P, V, M * R90 * Tmotor * Smotor);

    //Window transformation matrix
    glm::mat4 Swindow= glm::scale(I, glm::vec3(0.5, 0.5, 0.5));
    glm::mat4 Twindow= glm::translate(I, glm::vec3(0.0, 0.0, 0.335));

    drawTieFighterWindow(P, V, M * R90 * Twindow * Swindow);

    //Sphere (principal part of the body) transformation matrix
    glm::mat4 SS= glm::scale(I, glm::vec3(0.4, 0.4, 0.4));

    drawObjectTex(sphere, texTieFighterBody , P, V, M * SS);

}

void drawTieFighterArmLowerBase(glm::mat4 P, glm::mat4 V, glm::mat4 M) {

    glm::mat4 R270= glm::rotate(I, glm::radians(270.0f), glm::vec3(1.0,0.0,0.0));
    glm::mat4 S= glm::scale(I, glm::vec3(0.08, 0.075, 0.08));
    glm::mat4 S2= glm::scale(I, glm::vec3(0.05, 0.075, 0.12));

    drawObjectTex(truncatedPyramid, texTieFighterBody, P, V, M * R270 * S);
    drawObjectTex(truncatedPyramid, texTieFighterBody, P, V, M * R270 * S2);

}

void drawTieFighterArmUpperBase(glm::mat4 P, glm::mat4 V, glm::mat4 M) {

    glm::mat4 Ttop= glm::translate(I, glm::vec3(0.0, 0.15, 0.0));
    glm::mat4 Stop= glm::scale(I, glm::vec3(0.5, 1.2, 0.5));

    drawTieFighterArmLowerBase(P, V, M * Ttop * Stop);

    drawTieFighterArmLowerBase(P, V, M);

}

void drawTieFighterArmConnection(glm::mat4 P, glm::mat4 V, glm::mat4 M) {

    //Cylinder transformation matrix
    glm::mat4 T = glm::translate(I, glm::vec3(0.0, 0.51, 0.0));
    glm::mat4 S= glm::scale(I, glm::vec3(0.085, 0.015, 0.085));
    drawObjectTex(cylinder, texTieFighterBody, P, V, M * T * S);

    drawTieFighterArmUpperBase(P, V, M);
    drawTieFighterArmUpperBase(P, V, M);

}

void drawTieFighterArm(glm::mat4 P, glm::mat4 V, glm::mat4 M) {

    //Wing transformation matrix
    glm::mat4 R90= glm::rotate(I, glm::radians(90.0f), glm::vec3(1.0,0.0,0.0));
    glm::mat4 Twing= glm::translate(I, glm::vec3(0.0, 0.53, 0.0));

    drawTieFighterWing(P, V, M * Twing * R90);

    drawTieFighterArmConnection(P, V, M);

}

void drawTieFighterWeapon(glm::mat4 P, glm::mat4 V, glm::mat4 M) {

    //Parts of the base transformation matrix
    glm::mat4 S= glm::scale(I, glm::vec3(0.5, 1.0, 0.5));   //This turns the cube into a rectangle
    glm::mat4 SR= glm::scale(I, glm::vec3(0.25, 0.5, 0.25));  //This turns the cube into a rectangle but with different dimensions
    glm::mat4 TR= glm::translate(I, glm::vec3(0.0, 1.5, 0.0));
    drawObjectTex(cube, texTieFighterBody, P, V, M * S);       //Base of the weapon structure that's connected to the body
    drawObjectTex(cube, texTieFighterBody, P, V, M * TR * SR); //Second part of the base of the weapong structure that its between the previous rectangle and the lihgting part

    //Lighting cube transformation matrix
    glm::mat4 SC= glm::scale(I, glm::vec3(0.3, 0.3, 0.3));
    glm::mat4 TC= glm::translate(I, glm::vec3(0.0, 2.25, 0.0));
    drawObjectMat(cube, ruby,P,V,M*TC*SC);  //"Lighting" red part of the weapon

}

void drawTieFighter(glm::mat4 P, glm::mat4 V, glm::mat4 M) {

    glm::mat4 T = glm::translate(I, glm::vec3(tieFighterMovX, tieFighterMovY, tieFighterMovZ));
    glm::mat4 RtiefY = glm::rotate(I, glm::radians(tieFighterOrientateY), glm::vec3(0.0, 1.0, 0.0));
    glm::mat4 RtiefUpDown = glm::rotate(I, glm::radians(tieFighterOrientateVertical), glm::vec3(0.0, 0.0, 1.0));
    glm::mat4 R = glm::rotate(I, glm::radians(-90.0f), glm::vec3(0.0, 1.0, 0.0));

    //Arms transformation matrix
    glm::mat4 RL90= glm::rotate(I, glm::radians(-90.0f), glm::vec3(1.0,0.0,0.0));
    glm::mat4 TLArm= glm::translate(I, glm::vec3(0.0, 0.0, -0.35));
    //Inverserd arm and weapon transformation matrix
    glm::mat4 Sinverse= glm::scale(I, glm::vec3(1.0, 1.0, -1.0));

    drawTieFighterArm(P,V,M*T*RtiefY*RtiefUpDown*R*TLArm*RL90);
    drawTieFighterBody(P,V,M*T*RtiefY*RtiefUpDown*R);
    drawTieFighterArm(P,V,M*T*RtiefY*RtiefUpDown*R*Sinverse*TLArm*RL90); //The second wing is the same as the other but reflected in Z (with the SCALE)

    //Weapon transformation matrix
    glm::mat4 SW= glm::scale(I, glm::vec3(0.08, 0.08, 0.08));
    glm::mat4 RW90= glm::rotate(I, glm::radians(-90.0f), glm::vec3(0.0,0.0,1.0));
    glm::mat4 TW= glm::translate(I, glm::vec3(0.2, -0.3, 0.2));

    drawTieFighterWeapon(P,V,M*T*RtiefY*RtiefUpDown*R*TW*SW*RW90);
    drawTieFighterWeapon(P,V,M*T*RtiefY*RtiefUpDown*R*Sinverse*TW*SW*RW90);  //The second weapon is the same as the other but reflected in Z (with the SCALE)

}


// ----------------------------------------------         Hologram         ----------------------------------------------

void drawHologramBase(glm::mat4 P, glm::mat4 V, glm::mat4 M) {

    // Cylinder transformation matrix in order to make the base of the platform
    glm::mat4 Supper = glm::scale(I, glm::vec3(0.25, 0.325, 0.25));
    glm::mat4 Slower = glm::scale(I, glm::vec3(0.375, 0.03, 0.375));
    glm::mat4 T = glm::translate(I, glm::vec3(0.0, 1.0, 0.0));
    drawObjectTex(cylinder, texHoloBase,P,V,M*Supper*T);
    drawObjectTex(cylinder, texHoloBase,P,V,M*Slower*T);

    // Sphere transformation matrix th's going to be set in the middle of the upper part of the platform created previously
    glm::mat4 ThSphere = glm::translate(I, glm::vec3(2.0, 2.15, 2.0));
    glm::mat4 ShSphere = glm::scale(I, glm::vec3(0.225, 0.225, 0.225));
    drawObjectTex(halfSphere, texHoloSphere ,P,V,M*ShSphere*ThSphere);

}

void drawBabyYodaHologram(glm::mat4 P, glm::mat4 V, glm::mat4 M) {

    drawHologramBase(P, V, M);

    // Hologram transformation matrix and animation matrix for the auto rotation and translation in Y axis
    glm::mat4 T = glm::translate(I, glm::vec3(0.0, holoLevitatingY, 0.0));
    glm::mat4 S = glm::scale(I, glm::vec3(0.225, 0.225, 0.225));
    glm::mat4 R = glm::rotate(I, glm::radians(holoRotating), glm::vec3(0.0, 1.0, 0.0));

    // Transparencies for the hologram
    glDepthMask(GL_FALSE);
    drawObjectMat(babyYoda, matHolo, P, V, M * R * T * S);
    glDepthMask(GL_TRUE);

}


// ----------------------------------------------         Terrain - Scenario         ----------------------------------------------

void drawPlane(glm::mat4 P, glm::mat4 V, glm::mat4 M) {

    glm::mat4 S = glm::scale(I, glm::vec3(8.0, 1.0, 8.0));
    drawObjectTex(plane,texTieFighterBody,P,V,M*S);

}


// ----------------------------------------------      Animation Functions     ----------------------------------------------

void hologramAutoRotation(int value) {

    if (not holoUp) {
        holoLevitatingY -= 0.005;
        if(holoLevitatingY <= 0.775)
            holoUp = true;
    } else {
        holoLevitatingY += 0.005;
        if(holoLevitatingY >= 0.975)
            holoUp = false;
    }

    holoRotating += 0.5;
    glutPostRedisplay();
    glutTimerFunc(speed, hologramAutoRotation ,0);

}

void cameraZoom(int key, int status, int x, int y) {

    switch (key) {
        case 4:
            if (zoom < 120) zoom += 1;
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

    if (selectedModel[0]) {
        if(px2degX < 180 && px2degX > -180) alphaXDeathStar = px2degX;
        if(px2degY < 90 && px2degY > -90) alphaYDeathStar = -px2degY;
        cameraRepositioning(deathStarMovX,deathStarMovY,deathStarMovZ,alphaXDeathStar,alphaYDeathStar);
    }
    else if (selectedModel[1]) {
        if(px2degX < 180 && px2degX > -180) alphaXBattleship = px2degX;
        if(px2degY < 90 && px2degY > -90) alphaYBattleship = -px2degY;
        cameraRepositioning(battleshipMovX,battleshipMovY,battleshipMovZ,alphaXBattleship,alphaYBattleship);
    }
    else if (selectedModel[2]) {
        if(px2degX < 180 && px2degX > -180) alphaXXFighter = px2degX;
        if(px2degY < 90 && px2degY > -90) alphaYXFighter = -px2degY;
        cameraRepositioning(xFighterMovX,xFighterMovY,xFighterMovZ,alphaXXFighter,alphaYXFighter);
    }
    else if (selectedModel[3]) {
        if(px2degX < 180 && px2degX > -180) alphaXR2D2 = px2degX;
        if(px2degY < 90 && px2degY > -90) alphaYR2D2 = -px2degY;
        cameraRepositioning(r2d2MovX,r2d2MovY,r2d2MovZ,alphaXR2D2,alphaYR2D2);
    }
    else if (selectedModel[4]) {
        if(px2degX < 180 && px2degX > -180) alphaXTieFighter = px2degX;
        if(px2degY < 90 && px2degY > -90) alphaYTieFighter = -px2degY;
        cameraRepositioning(tieFighterMovX,tieFighterMovY,tieFighterMovZ,alphaXTieFighter,alphaYTieFighter);
    }
    else {
        if(px2degX < 180 && px2degX > -180) alphaX = px2degX;
        if(px2degY < 90 && px2degY > -90) alphaY = -px2degY;
    }

    glutPostRedisplay();

}

void animateModel(unsigned char key, int x, int y) {

    switch (key) {
        // Death Star Animations
        case 'u':
            deathStarMovY -= 0.1;
            break;
        case 'U':
            deathStarMovY += 0.1;
            break;
        case 'd':
            deathStarOrientateYTOP += 5;
            break;
        case 'D':
            deathStarOrientateYTOP -= 5;
            break;
        /*case 'o':
            deathStarOrientateXZ += 5;
            break;
        case 'O':
            deathStarOrientateXZ -= 5;
            break;*/

        // Battleship Animations

        // X-Fighter Animations
        case 'x':
            if (xFighterWingAperture > 0)
                xFighterWingAperture -= 1;
            break;
        case 'X':
            if (xFighterWingAperture < 30)
                xFighterWingAperture += 1;
            break;

        // R2D2 Animations
        case 'h':
            if (r2d2TurnHead < 90) r2d2TurnHead += 3;
            break;
        case 'H':
            if (r2d2TurnHead > -90) r2d2TurnHead -= 3;
            break;
        case 'c':
            if (r2d2BowBody < 22 && r2d2BowBody >= 0){
                r2d2BowBody += 2;
                r2d2PlaceBody += 0.025;
            }
            break;
        case 'C':
            if (r2d2BowBody <= 22 && r2d2BowBody > 0){
                r2d2BowBody -= 2;
                r2d2PlaceBody -= 0.025;
            }
            break;

        // Tie Fighter Animations
        case 'y':
            tieFighterOrientateVertical += 5;
            break;
        case 'Y':
            tieFighterOrientateVertical -= 5;
            break;
        case 'a':
            if (tieFighterWingAperture < 65) tieFighterWingAperture += 3;
            break;
        case 'A':
            if (tieFighterWingAperture > 0) tieFighterWingAperture -= 3;
            break;

        default:
            break;
    }
    glutPostRedisplay();

}

void modelMovementAndSelection(int key, int x, int y) {

 // Reset alphaX and alphaY with stored values
    if (selectedModel[0]) {
        alphaXDeathStar = bufferAlphaXDeathStar;
        alphaYDeathStar = bufferAlphaYDeathStar;
    }
    if (selectedModel[1]) {
        alphaXBattleship = bufferAlphaXBattleship;
        alphaYBattleship = bufferAlphaYBattleship;
    }
    if (selectedModel[2]) {
        alphaXXFighter = bufferAlphaXXFighter;
        alphaYXFighter = bufferAlphaYXFighter;
    }
    if (selectedModel[3]) {
        alphaXR2D2 = bufferAlphaXR2D2;
        alphaYR2D2 = bufferAlphaYR2D2;
    }
    if (selectedModel[4]) {
        alphaXTieFighter = bufferAlphaXTieFighter;
        alphaYTieFighter = bufferAlphaYTieFighter;
    }
    keyStates[key] = true;

    switch (key) {
        case GLUT_KEY_UP:
            if (selectedModel[0]) {
                moveDeathStar(0.1);
                cameraRepositioning(deathStarMovX, deathStarMovY, deathStarMovZ, alphaXDeathStar, alphaYDeathStar);
            }
            if (selectedModel[1]) {
                moveBattleship(0.1);
                cameraRepositioning(battleshipMovX, battleshipMovY, battleshipMovZ, alphaXBattleship, alphaYBattleship);
            }
            if (selectedModel[2]) {
                moveXFighter(0.4);
                cameraRepositioning(xFighterMovX, xFighterMovY, xFighterMovZ, alphaXXFighter, alphaYXFighter);
            }
            if (selectedModel[3]) {
                moveR2D2(0.1);
                cameraRepositioning(r2d2MovX, r2d2MovY, r2d2MovZ, alphaXR2D2, alphaYR2D2);
            }
            if (selectedModel[4]) {
                moveTieFighter(0.4);
                cameraRepositioning(tieFighterMovX, tieFighterMovY, tieFighterMovZ, alphaXTieFighter, alphaYTieFighter);
            }
            break;
        case GLUT_KEY_DOWN:
            if (selectedModel[0]) {
                moveDeathStar(-0.1);
                cameraRepositioning(deathStarMovX,deathStarMovY,deathStarMovZ,alphaXDeathStar,alphaYDeathStar);
            }
            if (selectedModel[1]) {
                moveBattleship(-0.1);
                cameraRepositioning(battleshipMovX,battleshipMovY,battleshipMovZ,alphaXBattleship,alphaYBattleship);
            }
            if (selectedModel[2]) {
                moveXFighter(-0.2);
                cameraRepositioning(xFighterMovX,xFighterMovY,xFighterMovZ,alphaXXFighter,alphaYXFighter);
            }
            if (selectedModel[3]) {
                moveR2D2(-0.1);
                cameraRepositioning(r2d2MovX,r2d2MovY,r2d2MovZ,alphaXR2D2,alphaYR2D2);
            }
            if (selectedModel[4]) {
                moveTieFighter(-0.2);
                cameraRepositioning(tieFighterMovX,tieFighterMovY,tieFighterMovZ,alphaXTieFighter,alphaYTieFighter);
            }
            break;
        case GLUT_KEY_RIGHT:
            if (selectedModel[0]) {
                if (!centerAtOrigin) alphaXDeathStar -= 5;
                deathStarOrientateY -= 5;
                cameraRepositioning(deathStarMovX,deathStarMovY,deathStarMovZ,alphaXDeathStar,alphaYDeathStar);
                if (keyStates[GLUT_KEY_UP]) {
                    moveDeathStar(0.1);
                    cameraRepositioning(deathStarMovX,deathStarMovY,deathStarMovZ,alphaXDeathStar,alphaYDeathStar);
                }
            }
            if (selectedModel[1]) {
                if (!centerAtOrigin) alphaXBattleship -= 5;
                battleshipOrientateY -= 5;
                cameraRepositioning(battleshipMovX,battleshipMovY,battleshipMovZ,alphaXBattleship,alphaYBattleship);
                if (keyStates[GLUT_KEY_UP]) {
                    moveBattleship(0.1);
                    cameraRepositioning(battleshipMovX,battleshipMovY,battleshipMovZ,alphaXBattleship,alphaYBattleship);
                }
            }
            if (selectedModel[2]) {
                if (!centerAtOrigin) alphaXXFighter -= 5;
                xFighterOrientateY -= 5;
                cameraRepositioning(xFighterMovX,xFighterMovY,xFighterMovZ,alphaXXFighter,alphaYXFighter);
                if (keyStates[GLUT_KEY_UP]) {
                    moveXFighter(0.4);
                    cameraRepositioning(xFighterMovX,xFighterMovY,xFighterMovZ,alphaXXFighter,alphaYXFighter);
                }
            }
            if (selectedModel[3]) {
                if (!centerAtOrigin) alphaXR2D2 -= 5;
                r2d2OrientateY -= 5;
                cameraRepositioning(r2d2MovX,r2d2MovY,r2d2MovZ,alphaXR2D2,alphaYR2D2);
                if (keyStates[GLUT_KEY_UP]) {
                    moveR2D2(0.1);
                    cameraRepositioning(r2d2MovX,r2d2MovY,r2d2MovZ,alphaXR2D2,alphaYR2D2);
                }
            }
            if (selectedModel[4]) {
                if (!centerAtOrigin) alphaXTieFighter -= 5;
                tieFighterOrientateY -= 5;
                cameraRepositioning(tieFighterMovX,tieFighterMovY,tieFighterMovZ,alphaXTieFighter,alphaYTieFighter);
                if (keyStates[GLUT_KEY_UP]) {
                    moveTieFighter(0.4);
                    cameraRepositioning(tieFighterMovX,tieFighterMovY,tieFighterMovZ,alphaXTieFighter,alphaYTieFighter);
                }
            }
            break;
        case GLUT_KEY_LEFT:
            if (selectedModel[0]) {
                if (!centerAtOrigin) alphaXDeathStar += 5;
                deathStarOrientateY += 5;
                cameraRepositioning(deathStarMovX,deathStarMovY,deathStarMovZ,alphaXDeathStar,alphaYDeathStar);
                if (keyStates[GLUT_KEY_UP]) {
                    moveDeathStar(0.1);
                    cameraRepositioning(deathStarMovX,deathStarMovY,deathStarMovZ,alphaXDeathStar,alphaYDeathStar);
                }
            }
            if (selectedModel[1]) {
                if (!centerAtOrigin) alphaXBattleship += 5;
                battleshipOrientateY += 5;
                cameraRepositioning(battleshipMovX,battleshipMovY,battleshipMovZ,alphaXBattleship,alphaYBattleship);
                if (keyStates[GLUT_KEY_UP]) {
                    moveBattleship(0.1);
                    cameraRepositioning(battleshipMovX,battleshipMovY,battleshipMovZ,alphaXBattleship,alphaYBattleship);
                }
            }
            if (selectedModel[2]) {
                if (!centerAtOrigin) alphaXXFighter += 5;
                xFighterOrientateY += 5;
                cameraRepositioning(xFighterMovX,xFighterMovY,xFighterMovZ,alphaXXFighter,alphaYXFighter);
                if (keyStates[GLUT_KEY_UP]) {
                    moveXFighter(0.4);
                    cameraRepositioning(xFighterMovX,xFighterMovY,xFighterMovZ,alphaXXFighter,alphaYXFighter);
                }
            }
            if (selectedModel[3]) {
                if (!centerAtOrigin) alphaXR2D2 += 5;
                r2d2OrientateY += 5;
                cameraRepositioning(r2d2MovX,r2d2MovY,r2d2MovZ,alphaXR2D2,alphaYR2D2);
                if (keyStates[GLUT_KEY_UP]) {
                    moveR2D2(0.1);
                    cameraRepositioning(r2d2MovX,r2d2MovY,r2d2MovZ,alphaXR2D2,alphaYR2D2);
                }
            }
            if (selectedModel[4]) {
                if (!centerAtOrigin) alphaXTieFighter += 5;
                tieFighterOrientateY += 5;
                cameraRepositioning(tieFighterMovX,tieFighterMovY,tieFighterMovZ,alphaXTieFighter,alphaYTieFighter);
                if (keyStates[GLUT_KEY_UP]) {
                    moveTieFighter(0.4);
                    cameraRepositioning(tieFighterMovX,tieFighterMovY,tieFighterMovZ,alphaXTieFighter,alphaYTieFighter);
                }
            }
            break;
        case GLUT_KEY_F1:
            // Death Star Selection
            if (!selectedModel[0] && !centerAtOrigin) {
                for (int i = 0; i < N_MODELS; ++i) {
                    if (selectedModel[i]) {
                        selectedModel[i] = false;
                        selectedModel[0] = true;
                    }
                }
            } else if (centerAtOrigin) {
                selectedModel[0] = true;
                centerAtOrigin = false;
            }
            cameraRepositioning(deathStarMovX,deathStarMovY,deathStarMovZ,alphaXDeathStar,alphaYDeathStar);
            zoom = 90.0;
            break;
        case GLUT_KEY_F2:
            // Battleship Selection
            if (!selectedModel[1] && !centerAtOrigin) {
                for (int i = 0; i < N_MODELS; ++i) {
                    if (selectedModel[i]) {
                        selectedModel[i] = false;
                        selectedModel[1] = true;
                    }
                }
            } else if (centerAtOrigin) {
                selectedModel[1] = true;
                centerAtOrigin = false;
            }
            cameraRepositioning(battleshipMovX,battleshipMovY,battleshipMovZ,alphaXBattleship,alphaYBattleship);
            zoom = 90.0;
            break;
        case GLUT_KEY_F3:
            // X-Fighter Selection
            if (!selectedModel[2] && !centerAtOrigin) {
                for (int i = 0; i < N_MODELS; ++i) {
                    if (selectedModel[i]) {
                        selectedModel[i] = false;
                        selectedModel[2] = true;
                    }
                }
            } else if (centerAtOrigin) {
                selectedModel[2] = true;
                centerAtOrigin = false;
            }
            cameraRepositioning(xFighterMovX,xFighterMovY,xFighterMovZ,alphaXXFighter,alphaYXFighter);
            zoom = 90.0;
            break;
        case GLUT_KEY_F4:
            // R2D2 Selection
            if (!selectedModel[3] && !centerAtOrigin) {
                for (int i = 0; i < N_MODELS; ++i) {
                    if (selectedModel[i]) {
                        selectedModel[i] = false;
                        selectedModel[3] = true;
                    }
                }
            } else if (centerAtOrigin) {
                selectedModel[3] = true;
                centerAtOrigin = false;
            }
            cameraRepositioning(r2d2MovX,r2d2MovY,r2d2MovZ,alphaXR2D2,alphaYR2D2);
            zoom = 60.0;
            break;
        case GLUT_KEY_F5:
            // Tie Fighter Selection
            if (!selectedModel[4] && !centerAtOrigin) {
                for (int i = 0; i < N_MODELS; ++i) {
                    if (selectedModel[i]) {
                        selectedModel[i] = false;
                        selectedModel[4] = true;
                    }
                }
            } else if (centerAtOrigin) {
                selectedModel[4] = true;
                centerAtOrigin = false;
            }
            cameraRepositioning(tieFighterMovX,tieFighterMovY,tieFighterMovZ,alphaXTieFighter,alphaYTieFighter);
            zoom = 90.0;
            break;
        case GLUT_KEY_F6:
            // Disable Selection and move camera center to the scene origin
            for (int i = 0; i < N_MODELS; ++i)
                selectedModel[i] = false;
            centerAtOrigin = true;
            // Camera Positioning
            cameraRepositioning(0.0,0.0,0.0,alphaX,alphaY);
            zoom = 60.0;
            break;
        default:
            break;
    }

 // Save alphaX and alphaY in the buffer
    if (selectedModel[0]) {
         bufferAlphaXDeathStar = alphaXDeathStar;
         bufferAlphaYDeathStar = alphaYDeathStar;
    }
    if (selectedModel[1]) {
        bufferAlphaXBattleship = alphaXBattleship;
        bufferAlphaYBattleship = alphaYBattleship;
    }
    if (selectedModel[2]) {
         bufferAlphaXXFighter = alphaXXFighter;
         bufferAlphaYXFighter = alphaYXFighter;
    }
    if (selectedModel[3]) {
         bufferAlphaXR2D2 = alphaXR2D2;
         bufferAlphaYR2D2 = alphaYR2D2;
    }
    if (selectedModel[4]) {
         bufferAlphaXTieFighter = alphaXTieFighter;
         bufferAlphaYTieFighter = alphaYTieFighter;
    }
    glutPostRedisplay();

}

void modelMovementExtra(int key, int x, int y) {

    keyStates[key] = false;
    glutPostRedisplay();

}

void moveDeathStar(float movement) {

    deathStarMovX += movement * sin(glm::radians(deathStarOrientateY));
    deathStarMovZ += movement * cos(glm::radians(deathStarOrientateY));

}

void moveBattleship(float movement) {

    battleshipMovX += movement * sin(glm::radians(battleshipOrientateY));
    battleshipMovZ += movement * cos(glm::radians(battleshipOrientateY));

}

void moveXFighter(float movement) {

    xFighterMovX += movement * sin(glm::radians(xFighterOrientateY));
    xFighterMovZ += movement * cos(glm::radians(xFighterOrientateY));

}

void moveR2D2(float movement) {

    r2d2MovX += movement * sin(glm::radians(r2d2OrientateY));
    r2d2MovZ += movement * cos(glm::radians(r2d2OrientateY));

}

void moveTieFighter(float movement) {

    tieFighterMovX += movement * sin(glm::radians(tieFighterOrientateY));
    tieFighterMovZ += movement * cos(glm::radians(tieFighterOrientateY));

}

void cameraRepositioning(float x, float y, float z, float alpha_x, float alpha_y) {

    center_x = x;
    center_y = y;
    center_z = z;
    eye_x = x+(-5.0f*glm::cos(glm::radians(alpha_y))*glm::sin(glm::radians(alpha_x)));
    if (selectedModel[3] || selectedModel[1] || selectedModel[0])
        eye_y = (y+5.0f)+(-5.0f*glm::sin(glm::radians(alpha_y)));
    else eye_y = (y+1.5f)+(-5.0f*glm::sin(glm::radians(alpha_y)));
    eye_z = z+(-5.0f*glm::cos(glm::radians(alpha_y))*glm::cos(glm::radians(alpha_x)));

}

void cameraCenter() {

    eye_x = -5.0f*glm::cos(glm::radians(alphaY))*glm::sin(glm::radians(alphaX));
    eye_y = -5.0f*glm::sin(glm::radians(alphaY));
    eye_z = -5.0f*glm::cos(glm::radians(alphaY))*glm::cos(glm::radians(alphaX));

}
