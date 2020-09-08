#include <iostream>
#include <ogl/glew.h>
#include <ogl/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shaders.h"
#include "Model.h"

#include <sstream>
std::string toString(const int &i) {
    std::stringstream ss;
    ss << i;
    return ss.str();
}

#define I glm::mat4(1.0)

void funInit();
void funReshape(int w, int h);
void funDisplay();
void funRotar(int key, int x, int y);
void keyFunc(unsigned char key, int x, int y);
void funTimer(int value);
void funZoom(int key,int status, int x, int y);
void SpecialKeyHandler(int key, int x, int y);
void funMotion(int x, int y);

void setLights(glm::mat4 P, glm::mat4 V);
void drawObjectMat(Model model, Material material, glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawObjectTex(Model model, Textures textures, glm::mat4 P, glm::mat4 V, glm::mat4 M);

void drawObject(Model model, glm::vec3 color, glm::mat4 P, glm::mat4 V, glm::mat4 M);

void drawSuelo (glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawSkyline (glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawSuelo2 (glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawSkyline2 (glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawHelipuerto (glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawEdificio(glm::mat4 P, glm::mat4 V, glm::mat4 M);

void drawArticulacion(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawSoporte(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawCabina(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawCristal(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawCola(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawCilindro(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawAspasSuperior(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawPatas(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawHelicoptero(glm::mat4 P, glm::mat4 V, glm::mat4 M);

void drawAspaCola(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawHeliceCola(glm::mat4 P, glm::mat4 V, glm::mat4 M);
// Shaders
   Shaders shaders;
   
// Modelos
   Model modelPlane;
   Model modelCone;
   Model modelCylinder;
   Model modelSphere;

// Texturas
   Texture textureBaldosas;
   Texture textureHelipuerto;
   Texture textureHelicoptero;
   Texture textureHelicoptero1;
   Texture textureHelicoptero2;
   Texture textureSkyline;
   Texture textureSkyline2;
   Texture textureEdificio;
   Texture textureEstrellas;
   
// Viewport
   int w = 600;
   int h = 600;

   float rotZ = 0.0;
   float rotX = 0.0;
   GLint speed = 20;
   float rotHelice = 5.0;
   float rotHelice2 = 3.0;
   bool rotar = true;
   float rotY = 0.0;
   float desY = 0.225;
   float fov = 30.0;
   float desZ = 0.0;
   float desX = 0.0;
   
   bool helices = false;
   
   float luzDambient = 0.1;
   float luzDdifusa = 0.7;
   float luzDesp = 0.7;
   
   bool luzF = true;
   float luzF1 = 0.2;
   float luzF2 = 0.9;

   bool luzP = true;
   float luzP1 = 0.0;
   float luzP2 = 0.0;

//Camara 
   
   float alphaX = 10.0;
   float alphaY = -10.0;
   
// Luces y materiales
   
   #define   NLD 1
   #define   NLP 1
   #define   NLF 1
   Light     lightG;
   Light     lightD[NLD];
   Light     lightP[NLP];
   Light     lightF[NLF];
   Material  matRuby;
   Material  matBrass;
   Material  matCromado;
   Material  matSilver;
   Material  matLuces;
   Material  matGold;
   Material  matBronze;
   
   Textures   texBaldosas;
   Textures   texHelipuerto;
   Textures   texHelicoptero;
   Textures   texSkyline;
   Textures   texSkyline2;
   Textures   texEdificio;

   
   
int main(int argc, char** argv) {

 // Inicializamos GLUT
    glutInit(&argc, argv);
    glutInitContextVersion(3,3);  
    glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
    glutInitContextProfile(GLUT_CORE_PROFILE);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(w,h);
    glutInitWindowPosition(50,50);
    glutCreateWindow("Practica4");
   
 // Inicializamos GLEW
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if(GLEW_OK != err) {
        std::cout << "Error: " << glewGetErrorString(err) << std::endl;
        return false;
    }
    std::cout << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;
    const GLubyte *oglVersion = glGetString(GL_VERSION);
    std::cout <<"This system supports OpenGL Version: " << oglVersion << std::endl;
   
 // Inicializaciones específicas
    funInit();
   
 // Configuración CallBacks
    glutReshapeFunc(funReshape);
    glutDisplayFunc(funDisplay);
    glutTimerFunc(speed,funTimer,0);
    glutKeyboardFunc(keyFunc);
    glutMouseFunc(funZoom);
    glutSpecialFunc(SpecialKeyHandler);
    glutMotionFunc(funMotion);
             
 // Bucle principal
    glutMainLoop();
   
    return 0;
}

void funInit() {
     
 // Test de profundidad
    glEnable(GL_DEPTH_TEST);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    
 // Transparencias
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(GL_FALSE); 

 // Shaders
    shaders.initShaders("resources/shaders/vshader.glsl","resources/shaders/fshader.glsl");
   
 // Modelos
    modelPlane.initModel("resources/models/plane.obj");
    modelCone.initModel("resources/models/cone.obj");
    modelCylinder.initModel("resources/models/cylinder.obj");
    modelSphere.initModel("resources/models/sphere.obj");
    
 // Texturas
    textureBaldosas.initTexture("resources/textures/Baldosas.png");
    textureHelipuerto.initTexture("resources/textures/Helipuerto.png");
    textureHelicoptero1.initTexture("resources/textures/Helicoptero1.png");
    textureSkyline.initTexture("resources/textures/Skyline.png");
    textureSkyline2.initTexture("resources/textures/Skyline2.png");
    textureEdificio.initTexture("resources/textures/Edificio.png");
    textureEstrellas.initTexture("resources/textures/Estrellas.png");
    
    
// Luz ambiental global
    lightG.ambient        = glm::vec3(0.5, 0.5, 0.5);
     
 // Luces direccionales
    lightD[0].direction   = glm::vec3( -3.0,-1.0, -3.0);
    lightD[0].ambient     = glm::vec3( luzDambient, luzDambient, luzDambient);
    lightD[0].diffuse     = glm::vec3( luzDdifusa, luzDdifusa, luzDdifusa);
    lightD[0].specular    = glm::vec3( luzDesp, luzDesp, luzDesp);
    
 // Luces posicionales
    lightP[0].position    = glm::vec3(desX, desY, desZ);
    lightP[0].ambient     = glm::vec3(luzP1, luzP1, luzP1);
    lightP[0].diffuse     = glm::vec3(luzP2, luzP2, luzP2);
    lightP[0].specular    = glm::vec3(luzP2, luzP2, luzP2);
    lightP[0].c0          = 1.00;
    lightP[0].c1          = 0.22;
    lightP[0].c2          = 0.20;    
    
 // Luces focales
    lightF[0].position    = glm::vec3( -3.0,  4.0, -3.0);
    lightF[0].direction   = glm::vec3( desX,  desY,  desZ);
    lightF[0].ambient     = glm::vec3( luzF1,  luzF1,  luzF1);
    lightF[0].diffuse     = glm::vec3( luzF2,  luzF2,  luzF2);
    lightF[0].specular    = glm::vec3( luzF2,  luzF2,  luzF2);
    lightF[0].innerCutOff = 15.0;
    lightF[0].outerCutOff = lightF[0].innerCutOff + 5.0;
    lightF[0].c0          = 1.000;
    lightF[0].c1          = 0.090;
    lightF[0].c2          = 0.032;
	
    
 // Materiales
    matLuces.ambient      = glm::vec4(0.0, 0.0, 0.0, 1.0);
    matLuces.diffuse      = glm::vec4(0.0, 0.0, 0.0, 1.0);
    matLuces.specular     = glm::vec4(0.0, 0.0, 0.0, 1.0);
    matLuces.emissive     = glm::vec4(1.0, 1.0, 1.0, 1.0);
    matLuces.shininess    = 1.0;
	
    matRuby.ambient       = glm::vec4(0.174500, 0.011750, 0.011750, 1.00);
    matRuby.diffuse       = glm::vec4(0.614240, 0.041360, 0.041360, 1.00);
    matRuby.specular      = glm::vec4(0.727811, 0.626959, 0.626959, 1.00);
    matRuby.emissive      = glm::vec4(0.000000, 0.000000, 0.000000, 1.00);
    matRuby.shininess     = 76.8;
            
    matBrass.ambient       = glm::vec4( 0.329412f, 0.223529f, 0.027451f,1.0f );
    matBrass.diffuse       = glm::vec4(0.780392f, 0.568627f, 0.113725f, 1.0f);
    matBrass.specular      = glm::vec4(0.992157f, 0.941176f, 0.807843f, 1.0f );
    matBrass.emissive      = glm::vec4(0.000000, 0.000000, 0.000000, 1.00);
    matBrass.shininess     = 27.8974f;
    	
    
    matCromado.ambient    = glm::vec4(0.25f, 0.25f, 0.25f, 1.0f );
    matCromado.diffuse    = glm::vec4(0.4f, 0.4f, 0.4f, 1.0f);
    matCromado.specular   = glm::vec4(0.774597f, 0.774597f, 0.774597f, 1.0f );
    matCromado.emissive   = glm::vec4(0.000000, 0.000000, 0.000000, 1.00);
    matCromado.shininess  = 76.8;
    
    matSilver.ambient    = glm::vec4(0.19225f, 0.19225f, 0.19225f, 0.7f);
    matSilver.diffuse    = glm::vec4(0.50754f, 0.50754f, 0.50754f, 0.7f);
    matSilver.specular   = glm::vec4(0.508273f, 0.508273f, 0.508273f, 0.7f);
    matSilver.emissive   = glm::vec4(0.000000, 0.000000, 0.000000, 1.00);
    matSilver.shininess  = 51.2;
    
    matGold.ambient       = glm::vec4(0.247250, 0.199500, 0.074500, 1.00);
    matGold.diffuse       = glm::vec4(0.751640, 0.606480, 0.226480, 1.00);
    matGold.specular      = glm::vec4(0.628281, 0.555802, 0.366065, 1.00);
    matGold.emissive      = glm::vec4(0.000000, 0.000000, 0.000000, 1.00);
    matGold.shininess     = 51.2;
    
    matBronze.ambient       = glm::vec4(0.2125f, 0.1275f, 0.054f, 1.0f );
    matBronze.diffuse       = glm::vec4(0.714f, 0.4284f, 0.18144f, 1.0f);
    matBronze.specular      = glm::vec4(0.393548f, 0.271906f, 0.166721f, 1.0f);
    matBronze.emissive      = glm::vec4(0.000000, 0.000000, 0.000000, 1.00);
    matBronze.shininess     = 25.6f;;
    
//Texturas
    
    texBaldosas.diffuse      = textureBaldosas.getTexture();
    texBaldosas.shininess    = 5.0;
    
    texHelipuerto.diffuse      = textureHelipuerto.getTexture();
    texHelipuerto.shininess    = 10.0;
    
    texHelicoptero.diffuse      = textureHelicoptero1.getTexture();
    texHelicoptero.shininess    = 10.0;
    
    texSkyline.diffuse    =   textureSkyline.getTexture();
    texSkyline.shininess    = 20.0;
    
    texSkyline2.diffuse =   textureSkyline2.getTexture();
    texSkyline2.shininess    = 20.0;
    
    texEdificio.diffuse =   textureEdificio.getTexture();
    texEdificio.shininess    = 50.0;
    
}

void funReshape(int wnew, int hnew) {
   
 // Configuración del Viewport
    glViewport(0, 0, wnew, hnew);

 // Captura de w y h
    w = wnew;
    h = hnew;
   
}

void funDisplay() {
   
 // Borramos el buffer de color
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   
 // Indicamos los shaders a utilizar
    shaders.useShaders();
   
 // Matriz de Proyección P (Perspectiva)
    float fovy   = fov;
    float nplane =  0.1;
    float fplane = 25.0;
    float aspect = (float)w/(float)h;
    glm::mat4 P  = glm::perspective(glm::radians(fov), aspect, nplane, fplane); 

 // Matriz de Vista V (Cámara)
    float x = 10.0*glm::cos(alphaY)*glm::sin(alphaX);
    float y = 10.0*glm::sin(alphaY);
    float z = 10.0*glm::cos(alphaY)*glm::cos(alphaX);
    glm::vec3 pos   (x  , y  , z  );
    glm::vec3 lookat (desX, desY,  desZ);
    glm::vec3 up    (0.0, 1.0,  0.0);
    glm::mat4 V = glm::lookAt(pos, lookat, up);  
    shaders.setVec3 ("ucpos",pos);
    
 // Fijamos las luces
    setLights(P,V);
    
 // Dibujamos la escena
    drawSuelo(P,V,I);
    drawSuelo2(P,V,I);
    drawHelipuerto(P,V,I);
    drawSkyline(P,V,I);
    drawSkyline2(P,V,I);
    drawEdificio(P,V,I);
   
    glm::mat4 T = glm::translate(I, glm::vec3(desX, desY, desZ));
    glm::mat4 Ry = glm::rotate(I, glm::radians(rotY), glm::vec3(0.0, 1.0, 0.0));
    glm::mat4 Rz = glm::rotate(I, glm::radians(rotZ), glm::vec3(0.0, 0.0, 1.0));
    glm::mat4 Rx = glm::rotate(I, glm::radians(rotX), glm::vec3(1.0, 0.0, 0.0));
    drawHelicoptero(P,V,T*Rx*Ry*Rz);

 // Intercambiamos los buffers
    glutSwapBuffers();
}
void setLights(glm::mat4 P, glm::mat4 V) {
    
    shaders.setLight("ulightG",lightG);
    for(int i=0; i<NLD; i++) shaders.setLight("ulightD["+toString(i)+"]",lightD[i]);
    for(int i=0; i<NLP; i++) shaders.setLight("ulightP["+toString(i)+"]",lightP[i]);
    for(int i=0; i<NLF; i++) shaders.setLight("ulightF["+toString(i)+"]",lightF[i]);
    
        for(int i=0; i<NLP; i++) {
        glm::mat4 M = glm::scale(glm::translate(I,lightP[i].position),glm::vec3(0.01));
        drawObjectMat(modelSphere,matLuces,P,V,M);
    }

    for(int i=0; i<NLF; i++) {
        glm::mat4 M = glm::scale(glm::translate(I,lightF[i].position),glm::vec3(0.01));
        drawObjectMat(modelSphere,matLuces,P,V,M);
    }    
    
}

void drawObject(Model model, glm::vec3 color, glm::mat4 P, glm::mat4 V, glm::mat4 M) {
    shaders.setMat4("uPVM",P*V*M);
    glEnable(GL_POLYGON_OFFSET_FILL);
    shaders.setVec3("uColor",color);
    model.renderModel(GL_FILL);
    glDisable(GL_POLYGON_OFFSET_FILL);
    glm::vec3 c = glm:: vec3(0.75 ,0.75,0.75);
    shaders.setVec3("uColor",color*c);
    model.renderModel(GL_LINE);
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
    shaders.setBool("uWithMaterials",false);
    if(textures.normal!=0) shaders.setBool("uNormalMap",true);
    else                   shaders.setBool("uNormalMap",false);
    shaders.setTextures("utextures",textures);
    model.renderModel(GL_FILL);   
}

void drawHelicoptero(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    drawCabina(P,V,M);
    drawCristal(P,V,M);
    
    glm::mat4 T = glm::translate(I, glm::vec3(0.8, 0.0, 0.0));
    drawCola(P,V,M*T);
    
    glm::mat4 T1 = glm::translate(I, glm::vec3(0.05, 0.0, 0.0));
    glm::mat4 R = glm::rotate(I, glm::radians(rotHelice), glm::vec3(0.0, 1.0, 0.0));//rotHelice 5 grados
    drawAspasSuperior(P,V,M*T1*R);
    
    glm::mat4 T3 = glm::translate(I, glm::vec3(0.05, -0.20, -0.10));
    drawPatas(P,V,M*T3);
    glm::mat4 T4 = glm::translate(I, glm::vec3(0.05, -0.20, 0.10));
    drawPatas(P,V,M*T4);
}

void drawCabina(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    glm::mat4 S = glm::scale(I, glm::vec3(0.055, 0.075, 0.075));
    glm::mat4 T1 = glm::translate(I, glm::vec3(0.05, 0.0, 0.0));
    drawObjectTex(modelSphere, texHelicoptero,P,V,M*T1*S);
}
void drawCristal(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    glm::mat4 S = glm::scale(I, glm::vec3(0.075, 0.075, 0.075));
    glDepthMask(GL_FALSE);
        drawObjectMat(modelSphere,matSilver,P,V,M*S);
    glDepthMask(GL_TRUE);
}

void drawPatas(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    glm::mat4 S = glm::scale(I, glm::vec3(0.010, 0.05, 0.010));
    glm::mat4 Ty = glm::translate(I, glm::vec3(0.0, 1.0, 0.0));
    glm::mat4 R90 = glm::rotate(I, glm::radians(90.0f),glm::vec3(0.0, 0.0, 1.0));
    glm::mat4 S1 = glm::scale(I, glm::vec3(0.015, 0.3, 0.015));
    glm::mat4 Tx = glm::translate(I, glm::vec3(0.0, -2.0, 0.0));
    drawObjectMat(modelCylinder,matCromado,P,V,M*S*Ty);
    drawObjectMat(modelCylinder,matCromado,P,V,M*R90*S1*Ty*Ty*Tx);
    
}

void drawCola(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    glm::mat4 R90 = glm::rotate(I, glm::radians(-90.0f), glm::vec3(0.0, 0.0, 1.0));
    glm::mat4 S = glm::scale(I, glm::vec3(0.03, 0.15 ,0.03));
    glm::mat4 T = glm::translate(I, glm::vec3(0.0, -2.75455951691, 0.0));
    // Altura 4.85452914238
    // diametro 5.3740115165
    drawObjectMat(modelCone,matCromado,P,V,M*R90*S*T);
    drawCilindro(P,V,M);
}

void drawCilindro(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    glm::mat4 T = glm::translate(I, glm::vec3(1.0, 0.0, 0.0));
    glm::mat4 S = glm::scale(I, glm::vec3(0.05, 0.05, 0.02));
    glm::mat4 T2 = glm::translate(I, glm::vec3(-0.1, 0.0, 0.0));
    drawObjectMat(modelCylinder,matCromado,P,V,M*T2*S*T);
    
    glm::mat4 T4 = glm::translate(I, glm::vec3(-0.05 ,0.0 , -0.03));
    glm::mat4 T3 = glm::translate(I, glm::vec3(-0.05 ,0.0 , 0.03));
    glm::mat4 R = glm::rotate(I, glm::radians(rotHelice2), glm::vec3(0.0, 0.0, 1.0));
    glm::mat4 R1 = glm::rotate(I, glm::radians(rotHelice2), glm::vec3(0.0, 0.0, -1.0));
    drawHeliceCola(P,V,M*T3*R);
    drawHeliceCola(P,V,M*T4*R1);
    
}

void drawAspasSuperior(glm::mat4 P, glm::mat4 V, glm::mat4 M) {
    glm::mat4 R90 = glm::rotate(I, glm::radians(-90.0f), glm::vec3(0.0, 0.0, 1.0));
    glm::mat4 S = glm::scale(I, glm::vec3(0.005, 0.15 ,0.025));
    glm::mat4 T = glm::translate(I, glm::vec3(0.0, -2.75455951691, 0.0));
    glm::mat4 R2 = glm::rotate(I, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
    glm::mat4 Ty = glm::translate(I, glm::vec3(0.0, 0.2, 0.0));
    drawObjectMat(modelCone,matBrass,P,V,M*Ty*R90*S*T);
    drawObjectMat(modelCone,matBrass,P,V,M*Ty*R2*S*T);
    drawSoporte(P,V,M);
}
void drawArticulacion(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    glm::mat4 S = glm::scale(I, glm::vec3(0.01, 0.01, 0.01));
    drawObjectMat(modelSphere,matRuby,P,V,M*S);  
}

void drawAspaCola(glm::mat4 P, glm::mat4 V, glm::mat4 M) {
    //glm::mat4 S = glm::scale(I, glm::vec3(0.005, 0.03, 0.020));  //tamaño  
    glm::mat4 S = glm::scale(I, glm::vec3(0.01, 0.06, 0.04));  //tamaño  
    glm::mat4 R1 = glm::rotate(I, glm::radians(90.0f), glm::vec3(0.0,0.0,1.0));
    glm::mat4 T = glm::translate(I, glm::vec3(0.0, -2.75455951691, 0.0));
    glm::mat4 R2 = glm::rotate(I, glm::radians(45.0f), glm::vec3(0.0,1.0,0.0));
    glm::mat4 Ry = glm::rotate(I, glm::radians(0.0f), glm::vec3(0.0, 1.0, 0.0));

    drawObjectMat(modelCone,matBrass,P,V,M*Ry*R2*R1*S*T);
}

void drawHeliceCola(glm::mat4 P, glm::mat4 V, glm::mat4 M) {

    glm::mat4 R90 = glm::rotate(I, glm::radians(90.0f),glm::vec3(0.0, 1.0, 0.0));
    glm::mat4 R45 = glm::rotate(I, glm::radians(45.0f), glm::vec3(0.0, 1.0, 0.0));
    glm::mat4 R = glm::rotate(I, glm::radians(rotHelice2), glm::vec3(0.0, 1.0, 0.0));//rotHelice 5 grados

    glm::mat4 S = glm::scale(I, glm::vec3(0.4, 0.4, 0.4));  //tamaño
    glm::mat4 R4 = glm::rotate(I, glm::radians(90.0f),glm::vec3(-1.0, 0.0, 0.0));
    drawArticulacion(P,V,M);
    drawAspaCola(P,V,M*R4*R45*S);
    drawAspaCola(P,V,M*R4*R90*R45*S);
    drawAspaCola(P,V,M*R4*R90*R90*R45*S);
    drawAspaCola(P,V,M*R4*R90*R90*R90*R45*S);
}

void drawSuelo(glm::mat4 P, glm::mat4 V, glm::mat4 M) {
    glm::mat4 S = glm::scale(I, glm::vec3(4.0, 1.0, 4.0));
    drawObjectTex(modelPlane,texBaldosas,P,V,M*S);
}
void drawSuelo2(glm::mat4 P, glm::mat4 V, glm::mat4 M) {
    glm::mat4 S = glm::scale(I, glm::vec3(4.0, 1.0, 4.0));
    glm::mat4 R180 = glm::rotate(I, glm::radians(180.0f), glm::vec3(1.0, 0.0, 0.0));
    drawObjectTex(modelPlane,texBaldosas,P,V,M*R180*S);
}
void drawSkyline(glm::mat4 P, glm::mat4 V, glm::mat4 M) {
    glm::mat4 S = glm::scale(I, glm::vec3(3.0, 1.0, 4.0));
    glm::mat4 R90 = glm::rotate(I, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
    glm::mat4 Ry = glm::rotate(I, glm::radians(180.0f), glm::vec3(1.0, 0.0, 0.0));
    glm::mat4 R180 = glm::rotate(I, glm::radians(180.0f), glm::vec3(0.0, 1.0, 0.0));
    glm::mat4 Tx = glm::translate(I, glm::vec3(-4.0, 0.0, 0.0));
    glm::mat4 Ty = glm::translate(I, glm::vec3(0.0, 3.0, 0.0));
    drawObjectTex(modelPlane,texSkyline,P,V,M*Ty*Tx*R90*R180*Ry*S);
    drawObjectTex(modelPlane,texSkyline,P,V,M*Ty*Tx*R90*R180*S);
    
}
void drawSkyline2(glm::mat4 P, glm::mat4 V, glm::mat4 M) {
    glm::mat4 S = glm::scale(I, glm::vec3(3.0, 1.0, 4.0));
    glm::mat4 R90 = glm::rotate(I, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
    glm::mat4 Ry = glm::rotate(I, glm::radians(-90.0f), glm::vec3(1.0, 0.0, 0.0));
    glm::mat4 R2 = glm::rotate(I, glm::radians(90.0f), glm::vec3(1.0, 0.0, 0.0));
    glm::mat4 R180 = glm::rotate(I, glm::radians(180.0f), glm::vec3(0.0, 1.0, 0.0));
    glm::mat4 Tx = glm::translate(I, glm::vec3(0.0, 0.0, -4.0));
    glm::mat4 Ty = glm::translate(I, glm::vec3(0.0, 3.0, 0.0));
    drawObjectTex(modelPlane,texSkyline2,P,V,M*Ty*Tx*R90*R180*Ry*S);
    drawObjectTex(modelPlane,texSkyline2,P,V,M*Ty*Tx*R90*R180*R2*S);
}
void drawEdificio(glm::mat4 P, glm::mat4 V, glm::mat4 M) {
    glm::mat4 S = glm::scale(I, glm::vec3(2.0, 1.0, 0.5));
    glm::mat4 R90 = glm::rotate(I, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
    glm::mat4 Rx = glm::rotate(I, glm::radians(90.0f), glm::vec3(1.0, 0.0, 0.0));
    glm::mat4 Ry = glm::rotate(I, glm::radians(90.0f), glm::vec3(1.0, 0.0, 0.0));
    glm::mat4 Ty = glm::translate(I, glm::vec3(0.0, 2.0, 0.0));
    glm::mat4 Tz = glm::translate(I, glm::vec3(-3.5, 0.0, -3.5));
    glm::mat4 Tx = glm::translate(I, glm::vec3(-3.0, 0.0, -3.0));
    glm::mat4 T1 = glm::translate(I, glm::vec3(-0.5, 0.0, 0.0));
    glm::mat4 T2 = glm::translate(I, glm::vec3(0.0, 0.0, -0.5));
    
    drawObjectTex(modelPlane,texEdificio,P,V,M*T1*Ty*Tx*R90*Rx*S);
    drawObjectTex(modelPlane,texEdificio,P,V,M*T2*Ty*Tx*R90*Ry*Rx*S);
    drawHelipuerto(P,V,M*Tz*Ty*Ty);
}

void drawHelipuerto(glm::mat4 P, glm::mat4 V, glm::mat4 M) {
    glm::mat4 S = glm::scale(I, glm::vec3(0.5, 1.0, 0.5));
    glm::mat4 Ty = glm::translate(I, glm::vec3(0.0, 0.01, 0.0));
    drawObjectTex(modelPlane,texHelipuerto,P,V,M*Ty*S);
}

void drawSoporte(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    glm::mat4 S = glm::scale(I, glm::vec3(0.025, 0.1, 0.025));
    glm::mat4 Ty = glm::translate(I, glm::vec3(0.0, 1.0, 0.0));
    drawObjectMat(modelCylinder,matGold,P,V,M*S*Ty);  
}

void funZoom(int key, int status, int x, int y) {
    switch(key) {
        case 3:  
            fov += 1.0;  
        break;
        case 4:
            fov -= 1.0;  
        break;
    }
    if (fov >= 90){
        fov = 90;
    }
    if (fov <= 10){
        fov = 10;
    }
    glutPostRedisplay();
}
   
void keyFunc(unsigned char key, int x, int y){
        switch(key) {
        case 'f' :  
            helices = !helices;
            luzP = !luzP;
            if (luzP == true){
                luzP1 = 0.0;
                luzP2 = 0.0;
            }
            if (luzP == false){
              luzP1 = 0.2;
              luzP2 = 0.9;  
            }
        break;

        case 'a' :  
            rotY += 5.0;  
        break;
        case 'd' :
            rotY -= 5.0;  
        break;
        case 'z' :  
            desZ -= 0.1;
            rotX -= 0.5; 
        break;
        case 'x' :
            desZ += 0.1;
            rotX += 0.5; 
        break;
        case 'q' :  
            desY += 0.05;  
        break;
        case 'e' :
            desY -= 0.05;  
        break;
        case 'w' :  
           desX -= 0.1;
           rotZ += 1.0;  
        break;
        case 's' :
           desX += 0.1;
           rotZ -= 1.0; 
        break;
        case 'o': 
            desX = 0.0;
            rotZ = 0.0; 
            desY = 0.225;
            desZ = 0.0;
            rotX = 0.0;
            rotY = 0.0;
            helices = !helices;
            luzP = !luzP;
        break;
    }
        
    lightP[0].position    = glm::vec3(desX, desY, desZ);
    lightP[0].ambient     = glm::vec3(luzP1, luzP1, luzP1);
    lightP[0].diffuse     = glm::vec3(luzP2, luzP2, luzP2);
    lightP[0].specular    = glm::vec3(luzP2, luzP2, luzP2);
    lightP[0].c0          = 1.00;
    lightP[0].c1          = 0.22;
    lightP[0].c2          = 0.20;
        
    if (desY <= 0.225){
        desY = 0.225;
    }
    if (desY >= 4){
        desY = 4;
    }
    if (rotZ <= -45.0){
        rotZ = -45.0;
    }
    if (rotZ >= 45.0){
        rotZ = 45.0;
    }
    if (rotX <= -25.0){
        rotX = -25.0;
    }
    if (rotX >= 25.0){
        rotX = 25.0;
    }
    if (desZ <= -3.5){
        desZ = -3.5;
    }
    if (desZ >= 4.0){
        desZ = 4.0;
    }
   if (desX <= -3.5){
        desX = -3.5;
    }
    if (desX >= 4.0){
        desX = 4.0;
    }
        
    //Actualizo las luces

    lightP[0].position    = glm::vec3(desX, desY, desZ);
    lightP[0].ambient     = glm::vec3(luzP1, luzP1, luzP1);
    lightP[0].diffuse     = glm::vec3(luzP2, luzP2, luzP2);
    lightP[0].specular    = glm::vec3(luzP2, luzP2, luzP2);
    lightP[0].c0          = 1.00;
    lightP[0].c1          = 0.22;
    lightP[0].c2          = 0.20;

    glutPostRedisplay();
}

void SpecialKeyHandler(int key, int x, int y)
{switch(key) {
        case GLUT_KEY_DOWN:
            luzDambient -= 0.03;
                if(luzDambient < 0) luzDambient = 0.0;
            luzDdifusa -= 0.15;
                if(luzDdifusa < 0) luzDdifusa = 0.0;
            luzDesp -= 0.15;
                if(luzDesp < 0) luzDesp = 0.0;
        break; 
        case GLUT_KEY_UP:
            luzDambient += 0.03;
                if(luzDambient > 0.7) luzDambient = 0.7;
            luzDdifusa += 0.15;
                if(luzDdifusa > 0.7) luzDdifusa = 0.7;
            luzDesp += 0.15;
                if(luzDesp > 0.7) luzDesp = 0.7;
        break;
}
    //Actualizo luces
    lightD[0].ambient     = glm::vec3( luzDambient, luzDambient, luzDambient);
    lightD[0].diffuse     = glm::vec3( luzDdifusa, luzDdifusa, luzDdifusa);
    lightD[0].specular    = glm::vec3( luzDesp, luzDesp, luzDesp);
   
}

void funTimer(int ignore) {
  if(helices == true){
    rotHelice += 5.0;
  }
  rotHelice2 +=3.0;
  glutPostRedisplay();
  glutTimerFunc(speed,funTimer,0);
}

void funMotion(int x, int y) {
      
    float pi   = glm::pi<float>();
    float limY = glm::radians( 89.0f);
    
    alphaX = pi*((float)x/(float)w - 0.5f);
    alphaY = pi*(0.5f - (float)y/(float)h);
    if(alphaY<-limY) alphaY = -limY;      
    if(alphaY> limY) alphaY =  limY;
    glutPostRedisplay();

}