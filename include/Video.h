/*************************************************************************
                           Video  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Video> (fichier Video.h) ----------------
#if ! defined ( VIDEO_H )
#define VIDEO_H

#include <iostream>
#include <vector>
using namespace std;

#include <opencv2/opencv.hpp>
#include "../include/Image.h"

//------------------------------------------------------------------------
// Rôle de la classe <Video>
//     Cette classe permet de représenter une vidéo et de faire des opérations dessus
//     Elle permet notamment de faire la corrélation entre une image et la vidéo
//     et d'extraire le résultat sous deux formes : une vidéo ou une liste d'images
//
//------------------------------------------------------------------------

class Video
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    void Correlation ( Image & imageTemplate, bool affinage = false );
    // Mode d'emploi :
    //     Correlation de la vidéo avec l'image template
    //     Si affinage est vrai, on applique la méthode d'affinage
    //     permettant de mettre à jour le template à chaque image.
    //

    void ExtractCorrelationVideo ( string outputDirectory = "", int fps = 30 ) const;
    // Mode d'emploi :
    //     Cette méthode permet d'extraire la vidéo courante avec le rectangle de corrélation maximale
    //     et de l'enregistrer dans le dossier outputDirectory
    //     On enregistre la vidéo avec le nombre d'images par seconde fps souhaité
    //

    void ExtractCorrelationImages ( string outputDirectory = "" ) const;
    // Mode d'emploi :
    //     Cette méthode permet d'extraire les images de la vidéo courante avec le rectangle de corrélation maximale
    //     et de les enregistrer dans le dossier outputDirectory
    //

//-------------------------------------------- Constructeurs - destructeur
    Video ( string videoPath = "", string videoName = "video", bool framesCreation = false, cv::VideoCapture videoInput = cv::VideoCapture ( ) );
    // Mode d'emploi :
    //      Constructeur de la classe Video
    //      videoPath : chemin vers la vidéo
    //      videoName : nom de la vidéo
    //      framesCreation : si vrai, on crée les images de la vidéo
    //      videoInput : si on a déjà une vidéo, on peut la passer en paramètre
    //

    virtual ~Video ( );
    // Mode d'emploi :
    //      Destructeur de la classe Video
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Attributs protégés
    string path;
    string name;
    vector < Image * > listImage;
    cv::VideoCapture video;

};
#endif // VIDEO_H

