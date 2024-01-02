#include <opencv2/opencv.hpp>
#include <iostream>
#include <filesystem>

using namespace std;

#include "include/Image.h"
#include "include/Video.h"

int main () 
{
    // Génération de l’objet Image template
    Image motoTemplate ("moto_template", "../templates/moto_template.png");
    // Génération de l’objet Video 
    Video autorouteCamera ("../videos/moto_recognition.mov", "moto_recognition", false);

    // Reconnaissance du Template sur la Video
    autorouteCamera.Correlation ( motoTemplate, true);

    // Extraction de la Video en 15 fps
    autorouteCamera.ExtractCorrelationVideo ( "", 15 );    

    return 0;
}
