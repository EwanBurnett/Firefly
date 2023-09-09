#include "../include/World.h"
#include <cstdint>
#include <map>
#include <stdexcept>
#include <tinyxml2.h>

using namespace tinyxml2;

const std::vector<Firefly::IObject*>& Firefly::World::GetScene() const{
    return m_Objects;
}

void Firefly::World::LoadFromFile(const std::string& filePath){
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
                XMLElement* pPosition = pCamera->FirstChildElement("Position");
                float pos_x = 0.0f;
                float pos_y = 0.0f;
                float pos_z = 0.0f;

                pPosition->QueryFloatAttribute("x", &pos_x);
                pPosition->QueryFloatAttribute("y", &pos_y);
                pPosition->QueryFloatAttribute("z", &pos_z);

                //Orientation
                XMLElement* pOrientation = pCamera->FirstChildElement("Orientation");
                float rot_x = 0.0f;
                float rot_y = 0.0f;
                float rot_z = 0.0f;

                pOrientation->QueryFloatAttribute("x", &rot_x);
                pOrientation->QueryFloatAttribute("y", &rot_y);
                pOrientation->QueryFloatAttribute("z", &rot_z);

                XMLElement* pFocalLength = pCamera->FirstChildElement("FocalLength");
                float focalLength = pFocalLength->FloatText(1.0f);

                //TODO: Construct a Camera object in the world using these parameters
                printf("\n[XML] Loaded Camera <%s>:\n\tPosition: (%f, %f, %f)\n\tOrientation: (%f, %f, %f)\n\tFocal Length: %f\n", id, pos_x, pos_y, pos_z, rot_x, rot_y, rot_z, focalLength);

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

    if(strcmp(type.c_str(), "FF_SPHERE") == 0){
        printf("Constructing a Sphere!\n");
        
        //Position
        XMLElement* pPosition = ((XMLElement*)pElement)->FirstChildElement("Position");
        float pos_x = 0.0f;
        float pos_y = 0.0f;
        float pos_z = 0.0f;

        float radius = 0.0f; 

        pPosition->QueryFloatAttribute("x", &pos_x);
        pPosition->QueryFloatAttribute("y", &pos_y);
        pPosition->QueryFloatAttribute("z", &pos_z);

        XMLElement* pRadius = ((XMLElement*)pElement)->FirstChildElement("Radius"); 

        pObject->position = {pos_x, pos_y, pos_z};
        pObject->radius = pRadius->FloatText(0.0f); 

    }


    return pObject;
}

