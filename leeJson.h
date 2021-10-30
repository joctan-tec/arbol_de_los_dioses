#include <iostream>
#include "Dioses.h"     //Esta en el Joctan_Branch
#include "priority.h"

#include "json-develop/include/nlohmann/json.hpp"   // https://github.com/nlohmann/json/tree/develop/single_include/nlohmann/json.hpp
#include <fstream>              // ifstream, ofstream
#include <iomanip>              // std::setw()
#include <string>
#include <vector>

 
using json = nlohmann::json;
using namespace std;
 
ColaPrioridad leerArchivo() {
    // leer configuración desde el archivo
    ifstream lol ("infoDioses.json");  // Nota aquí es una ruta relativa
    json j;
    lol >> j; 
    lol.close();

    ColaPrioridad colaP;
    vector<string> nombres = j["nombre"];
    vector<int> fieles = j["fieles"];

    for (int i = 0; i < nombres.size(); i++){
        colaP.add(new Dios(fieles[i],nombres[i]));
    }

         // Aviso: 
         // JSON Standard define objetos como "cero o más pares de nombre / valor".
         // Si desea mantener la orden de inserción, puede usar TSL :: Ordered_map (integración) o Nlohmann :: FIFO_MAP (integración) y otros contenedores.
    
    return colaP;
    //getchar();
}