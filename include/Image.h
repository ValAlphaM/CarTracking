/*************************************************************************
                           Image  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Image> (fichier Image.h) ----------------
#if ! defined ( IMAGE_H )
#define IMAGE_H

#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>

//------------------------------------------------------------------------
// Rôle de la classe <Image>
//      Cette classe permet de représenter une image et de faire des opérations dessus
//      Elle permet notamment de faire la corrélation entre deux images et d'extraire le résultat
//
//------------------------------------------------------------------------

class Image
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    void Correlation ( Image & imageTemplate, bool affinage = false );
    // Mode d'emploi :
    //     Correlation de l'image courante avec l'image template
    //     Si affinage est vrai, on applique la méthode d'affinage
    //     permettant de mettre à jour le template à chaque image.

    void ExtractCorrelationImage ( string outputDirectory ) const;
    // Mode d'emploi :
    //     Cette méthode permet d'extraire l'image courante avec le rectangle de corrélation maximale
    //     et de l'enregistrer dans le dossier outputDirectory

    void ExtractCurrentImage ( string outputDirectory, bool correlation = false ) const;
    // Mode d'emploi :
    //     Cette méthode permet d'extraire l'image courante et de l'enregistrer dans le dossier outputDirectory
    //     Si correlation est vrai, on ajoute "corr_" au début du nom de l'image

    // Getters
    cv::Mat getImageMat ( ) const;
    // Mode d'emploi :
    //     Retourne la matrice de l'image courante

    Image * getCorrelationImage ( ) const;
    // Mode d'emploi :
    //     Retourne un pointeur vers l'image de corrélation de l'image courante

//-------------------------------------------- Constructeurs - destructeur
    Image ( string imageName, string imagePath, cv::Mat imageMatrice = cv::Mat());
    // Mode d'emploi :
    //      Constructeur de la classe Image
    //      imageName : nom de l'image
    //      imagePath : chemin vers l'image
    //      imageMatrice : matrice de l'image (si elle est déjà chargée)
    // Contrat :
    //      si imageName = "" alors imageMatrice doit contenir les données de l'image

    virtual ~Image ( );
    // Mode d'emploi :
    //      Destructeur de la classe Image

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Attributs protégés
    cv::Mat coloredImage;
    string path;
    string name;
    Image * correlationImage;
};

#endif // IMAGE_H

