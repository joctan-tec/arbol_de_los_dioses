#ifndef _LECTURA_JSON_ 
#define _LECTURA_JSON_ 1

#include <iostream>
#include "Dioses.h"
#include "priority.h"

#include "json-develop/include/nlohmann/json.hpp"   // https://github.com/nlohmann/json/tree/develop/single_include/nlohmann/json.hpp
#include <fstream>                           
#include <string> 
#include <vector>
#include <stack>
 
using json = nlohmann::json;
using namespace std;

class LeeJson{
    private:
        json archivoJson;

    public:
        ColaPrioridad leerArchivo(string path) {
            // leer configuración desde el archivo
            ifstream lecturaArchivo (path);  // Nota aquí es una ruta relativa
            lecturaArchivo >> archivoJson;  
            lecturaArchivo.close();

            ColaPrioridad colaP;
            vector<string> nombres = archivoJson["nombre"];
            vector<int> fieles = archivoJson["fieles"];

            for (int elementos = 0; elementos < nombres.size(); elementos++){
                colaP.add(new Dios(fieles[elementos],nombres[elementos]));
            }
            return colaP;
        }

        stack<string> leerArchivoConStack(string path){
            // leer configuración desde el archivo
            ifstream lecturaArchivo (path);  // Nota aquí es una ruta relativa
            lecturaArchivo >> archivoJson; 
            lecturaArchivo.close();

            stack<string> pilaNombres;
            vector<string> nombres = archivoJson["nombresDioses"];

            for (int elementos = 0; elementos < nombres.size(); elementos++){
                pilaNombres.push(nombres[elementos]);
            }
            return pilaNombres;
        }
};

#endif