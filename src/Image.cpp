/*************************************************************************
                           Image  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Image> (fichier Image.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <filesystem>
using namespace std;

//------------------------------------------------------ Include personnel
#include <opencv2/opencv.hpp>
#include "../include/Image.h"

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

void Image::Correlation ( Image & imageTemplate, bool affinage )
// Algorithme :
//      On applique la méthode de corrélation sur l’image courante avec l’image imageTemplate
//      Mise à jour de l’image imageTemplate si affinage est vrai
//      Création de l’image correlationImage avec le rectangle de corrélation maximale
//
{
    cv::Mat source = coloredImage;
    cv::Mat templateImage = imageTemplate.coloredImage;
    
    // corrélation
    cv::Mat result;
    cv::matchTemplate ( source, templateImage, result, cv::TM_CCOEFF_NORMED );

    // application du résultat sur la source en couleur
    double minVal, maxVal;
    cv::Point minLoc, maxLoc;
    cv::minMaxLoc ( result, &minVal, &maxVal, &minLoc, &maxLoc );

    // application du rectangle sur une copie de l’image (source)
    cv::rectangle ( source, maxLoc, cv::Point ( maxLoc.x + templateImage.cols, maxLoc.y + templateImage.rows ), cv::Scalar (0, 255, 0), 2);

    // modification de l’image imageTemplate pour affiner la correlation à chaque itération
    // on prend la même taille que l’imageTemplate initiale, mais on recentre autour du point de correlation maximale
    if ( affinage )
    {
        // déportation du point centrale au coin supérieur gauche
        int x = maxLoc.x;
        int y = maxLoc.y;

        // définition de la taille de l’image
        int width = templateImage.cols;
        int height = templateImage.rows;

        // gestion des cas limites pour les bordures
        if ( x < 0 )
        {
            width += x;
            x = 0;
        }
        if ( y < 0 )
        {
            height += y;
            y = 0;
        }
        if ( x + width > source.cols )
        {
            width = source.cols - x;
        }
        if ( y + height > source.rows )
        {
            height = source.rows - y;
        }
        // création de la nouvelle image
        cv::Mat newTemplateImage = source ( cv::Rect ( x, y, width, height ) );
        // mise à jour de l’image imageTemplate
        imageTemplate.coloredImage = newTemplateImage;
    }
    // création de la nouvelle image avec le rectangle de corrélation maximale
    if ( correlationImage )
    {
        delete correlationImage;
    }
    correlationImage = new Image ( name, "", source );
} //----- Fin de Correlation

void Image::ExtractCurrentImage ( string outputDirectory, bool correlation ) const
// Algorithme :
//      On enregistre l’image courante dans le dossier outputDirectory
//      Si correlation est vrai, on ajoute "corr_" au début du nom de l’image
//
{
    std::filesystem::create_directories ( outputDirectory );
    #ifdef DEBUG
        cout << "Extraction de l’image " << name << endl;
    #endif
    ostringstream filename;
    filename << outputDirectory;
    if ( correlation )
    {
        filename << "corr_";
    }
    filename << name << ".png";
    cv::imwrite ( filename.str ( ), coloredImage );
} //----- Fin de ExtractCurrentImage

void Image::ExtractCorrelationImage ( string outputDirectory ) const
// Algorithme :
//      On enregistre l’image avec le rectangle de corrélation potentiellement significatif
//
{
    
    // enregistrer l’image avec le rectangle de corrélation potentiellement significatif
    if ( correlationImage )
    {
        cout << "extraction image" << endl;
        correlationImage -> ExtractCurrentImage ( outputDirectory, true );
    }
} //----- Fin de ExtractCorrelationImage

cv::Mat Image::getImageMat ( ) const
// Algorithme :
//      On retourne la matrice de l’image courante
//
{
    return coloredImage;
} //----- Fin de getImageMat

Image * Image::getCorrelationImage ( ) const
// Algorithme :
//      On retourne un pointeur vers l’image de corrélation de l’image courante
//
{
    return correlationImage;
} //----- Fin de getCorrelationImage

//-------------------------------------------- Constructeurs - destructeur
Image::Image ( string imageName, string imagePath, cv::Mat imageMatrice )
// Algorithme :
//      On initialise les attributs de la classe
//
{
    #ifdef DEBUG
        cout << "Appel au constructeur de <Image>" << endl;
    #endif
    path = imagePath;
    name = imageName;
    if ( imagePath == "" )
    {
        coloredImage = imageMatrice;
    }
    else 
    {
        coloredImage = cv::imread ( imagePath );
    }

    correlationImage = nullptr;
} //----- Fin de Image


Image::~Image ( )
// Algorithme :
//      On libère la mémoire allouée pour l’image de corrélation
//
{
    #ifdef DEBUG
        cout << "Appel au destructeur de <Image>" << endl;
    #endif
    if ( correlationImage )
    {
        delete correlationImage;
    }
} //----- Fin de ~Image