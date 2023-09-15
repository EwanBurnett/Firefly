#include "../include/World.h"
#include <cstdint>
#include <map>
#include <stdexcept>
#include <tinyxml2.h>
#include "../include/Objects/Sphere.h"
#include "../include/ColourRGBA.h"
#include "../include/Material.h"
#include "../include/Materials/Lambert.h"
#include "../include/Materials/Metal.h"
#include "../include/Materials/Dielectric.h"
#include "../include/Camera.h"

using namespace tinyxml2;

Firefly::World::World(){

}

Firefly::World::~World(){
    for(IObject* obj : m_Objects){
        delete obj;
    }
}

const std::vector<Firefly::IObject*>& Firefly::World::GetScene() const{
    return m_Objects;
}

const std::vector<Firefly::Camera>& Firefly::World::GetCameras() const{
    return m_Cameras;
}

void Firefly::World::LoadFromFile(const std::string& filePath, const Viewport& viewport){
    //Load each element from the file
    //and instantiate them in the world. 
    
    XMLDocument document;
    XMLError error;
    error = document.LoadFile(filePath.c_str());
    if(error != tinyxml2::XML_SUCCESS)
    {
        char errorBuffer[256];
        sprintf(errorBuffer, "Error parsing document %s: %s", filePath.c_str(), document.ErrorStr());
        throw std::runtime_error(errorBuffer);
    }

    //Document Structure
    //- Element "World"
    //-- Element "Views"
    //--- Element "Camera" id
    //---- Element "Position" xyz
    //---- Element "Orientation" xyz
    //---- Element "FocalLength"
    //-- Element "Scene"
    //--- Element "Object"
    //---- Element "ID" 
    //---- Element "Type"
    //---- ...
    //--- ...
    //-- Element "Timeline"
    //--- Element "KeyFrame"
    //---- Element "Transform"
    //---- ...
    //--- ...
    XMLElement* pRoot = document.RootElement();

    //TODO: Fix Segfault on accessing null XMLElement pointers
    if(pRoot){
        //Load the Camera Views
        XMLElement* pViews = pRoot->FirstChildElement("Views");
        if(pViews){
            //Load each Camera
            XMLElement* pCamera = pViews->FirstChildElement("Camera");
            while(pCamera){
                //ID
                const char* id = "DEFAULT_CAMERA_ID"; 
                error = pCamera->QueryStringAttribute("id", &id);

                //Position
                float pos_x = 0.0f;
                float pos_y = 0.0f;
                float pos_z = 0.0f;

                XMLElement* pPosition = pCamera->FirstChildElement("Position");
                if(pPosition != nullptr){
                    pPosition->QueryFloatAttribute("x", &pos_x);
                    pPosition->QueryFloatAttribute("y", &pos_y);
                    pPosition->QueryFloatAttribute("z", &pos_z);
                }

                //Orientation
                float rot_x = 0.0f;
                float rot_y = 0.0f;
                float rot_z = 0.0f;

                XMLElement* pOrientation = pCamera->FirstChildElement("Orientation");
                if(pOrientation != nullptr){
                    pOrientation->QueryFloatAttribute("x", &rot_x);
                    pOrientation->QueryFloatAttribute("y", &rot_y);
                    pOrientation->QueryFloatAttribute("z", &rot_z);
                }

                float focalLength = 1.0f; 
                XMLElement* pFocalLength = pCamera->FirstChildElement("FocalLength");
                if(pFocalLength != nullptr){
                    focalLength = pFocalLength->FloatText(1.0f);
                }

                float fov = 90.0f;
                XMLElement* pFoV = pCamera->FirstChildElement("FoV");
                if(pFoV != nullptr){
                    fov = pFoV->FloatText(90.0f);
                }

                float defocusAngle = 0.0f;
                XMLElement* pDefocusAngle = pCamera->FirstChildElement("DefocusAngle");
                if(pDefocusAngle != nullptr){
                    defocusAngle = pDefocusAngle->FloatText(0.0f);
                }

                //TODO: Camera Method SetViewPort() to avoid passing it through here
                m_Cameras.push_back(Camera({pos_x, pos_y, pos_z}, viewport, focalLength, defocusAngle, fov, {rot_x, rot_y, rot_z}));
                
                printf("\n[XML] Loaded Camera <%s>:\n\tPosition: (%f, %f, %f)\n\tOrientation: (%f, %f, %f)\n\tFocal Length: %f\nDefocus Angle: %f\nFoV: %f\n", id, pos_x, pos_y, pos_z, rot_x, rot_y, rot_z, focalLength, defocusAngle, fov);

                pCamera = pCamera->NextSiblingElement("Camera"); //Load the next Camera
            }
        }

        //Load the Scene
        XMLElement* pScene = pRoot->FirstChildElement("Scene");
        if(pScene){
            XMLElement* pObject = pScene->FirstChildElement("Object");
            while(pObject){

                const char* id = "OBJECT_DEFAULT_ID";
                pObject->QueryStringAttribute("id", &id);

                const char* type = "FF_NULL";
                pObject->QueryStringAttribute("type", &type);

                printf("[XML] Loaded Object <%s>:\n\tType: %s\n", id, type);
                
                m_Objects.push_back(ObjectFactory(type, (void*)pObject));

                pObject = pObject->NextSiblingElement("Object");
            }
        }

        

    }
}


Firefly::IObject* Firefly::World::ObjectFactory(const std::string& type, void* pElement){

    IObject* pObject;

    //TODO: Multiple Object Types
    //Instantiate the object based on its type. 
    if(strcmp(type.c_str(), "FF_SPHERE") == 0){
        printf("Constructing a Sphere!\n");
        
        //Position
        float pos_x = 0.0f;
        float pos_y = 0.0f;
        float pos_z = 0.0f;

        XMLElement* pPosition = ((XMLElement*)pElement)->FirstChildElement("Position");
        if(pPosition != nullptr)
        {
            pPosition->QueryFloatAttribute("x", &pos_x);
            pPosition->QueryFloatAttribute("y", &pos_y);
            pPosition->QueryFloatAttribute("z", &pos_z);
        }

        float radius = 0.0f; 
        XMLElement* pRadius = ((XMLElement*)pElement)->FirstChildElement("Radius"); 
        if(pRadius != nullptr){
            radius = pRadius->FloatText(0.0f);
        }

        XMLElement* pMatData = ((XMLElement*)pElement)->FirstChildElement("Material");
        std::shared_ptr<IMaterial> pMaterial = nullptr;
        if(pMatData != nullptr){
            const char* matType = "FF_MAT_NULL";
            pMatData->QueryStringAttribute("type", &matType);
            pMaterial = MaterialFactory(matType, pMatData);
        }
        
        pObject = new Sphere({pos_x, pos_y, pos_z}, radius, pMaterial);
    }

    return pObject;
}
    
std::shared_ptr<Firefly::IMaterial> Firefly::World::MaterialFactory(const std::string& type, void* pElement)
{

    std::shared_ptr<IMaterial> pMat = nullptr;
    if(strcmp(type.c_str(), "Lambert") == 0){

        Colour albedo = {};
        XMLElement* pAlbedo = ((XMLElement*)pElement)->FirstChildElement("Albedo");
        if(pAlbedo != nullptr){
            pAlbedo->QueryFloatAttribute("r", &albedo.r);
            pAlbedo->QueryFloatAttribute("g", &albedo.g);
            pAlbedo->QueryFloatAttribute("b", &albedo.b);
            pAlbedo->QueryFloatAttribute("a", &albedo.a);
        }

        printf("Loading Lambert\tAlbedo: (%f, %f, %f, %f)\n", albedo.r, albedo.g, albedo.b, albedo.a);
        pMat = std::make_shared<Lambert>(albedo);
    }

    else if(strcmp(type.c_str(), "Metal") == 0){

        Colour albedo = {};
        XMLElement* pAlbedo = ((XMLElement*)pElement)->FirstChildElement("Albedo");
        if(pAlbedo != nullptr){
            pAlbedo->QueryFloatAttribute("r", &albedo.r);
            pAlbedo->QueryFloatAttribute("g", &albedo.g);
            pAlbedo->QueryFloatAttribute("b", &albedo.b);
            pAlbedo->QueryFloatAttribute("a", &albedo.a);
        }

        float fuzziness = 1.0f; 
        XMLElement* pFuzziness = ((XMLElement*)pElement)->FirstChildElement("Fuzziness");
        if(pFuzziness != nullptr){
            pFuzziness->QueryFloatText(&fuzziness);
        }

        printf("Loading Metal\tAlbedo: (%f, %f, %f, %f)\nfuzziness: %f", albedo.r, albedo.g, albedo.b, albedo.a, fuzziness);

        pMat = std::make_shared<Metal>(albedo, fuzziness);
    }
    else if(strcmp(type.c_str(), "Dielectric") == 0){

        Colour tint = {};
        XMLElement* pTint = ((XMLElement*)pElement)->FirstChildElement("Tint");
        if(pTint != nullptr){
            pTint->QueryFloatAttribute("r", &tint.r);
            pTint->QueryFloatAttribute("g", &tint.g);
            pTint->QueryFloatAttribute("b", &tint.b);
            pTint->QueryFloatAttribute("a", &tint.a);
        }

        float ir  = 1.0f; 
        XMLElement* pIR = ((XMLElement*)pElement)->FirstChildElement("IR");
        if(pIR != nullptr){
            pIR->QueryFloatText(&ir);
        }

        float fresnel  = 1.0f; 
        XMLElement* pFresnel = ((XMLElement*)pElement)->FirstChildElement("Fresnel");
        if(pFresnel != nullptr){
            pFresnel->QueryFloatText(&fresnel);
        }

        printf("Loading Dielectric\tTint(%f, %f, %f, %f)\nIndex of Refraction: %f\nfresnel: %f\n", tint.r, tint.g, tint.g, tint.a, ir, fresnel);

        pMat = std::make_shared<Dielectric>(tint, ir, fresnel);
    }

    return pMat;
}

