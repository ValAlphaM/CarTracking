/*************************************************************************
                           Video  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Video> (fichier Video.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <filesystem>
using namespace std;

//------------------------------------------------------ Include personnel
#include <opencv2/opencv.hpp>
#include "../include/Video.h"
//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void Video::Correlation ( Image & imageTemplate, bool affinage )
// Algorithme :
//      On applique la méthode de corrélation sur la vidéo courante avec l’image imageTemplate
//      Mise à jour de l’image imageTemplate si affinage est vrai
//
{
    // Pour chaque image, de la liste, on applique la corrélation avec l’imageTemplate
    #ifdef DEBUG
        int frameNumber = 0;
    #endif
    vector < Image * >::iterator iImage;
    for ( iImage = listImage.begin ( ); iImage != listImage.end ( ); ++iImage )
    {
        #ifdef DEBUG
            cout << frameNumber << endl;
            frameNumber++;
        #endif
        Image * currImage = (*iImage);
        currImage -> Correlation ( imageTemplate, affinage );
    }
}

void Video::ExtractCorrelationVideo ( string outputDirectory, int fps ) const
// Algorithme :
//      Création d’une vidéo à partir des images de correlation avec le nombre de fps souhaité
// 
{
    // Cette méthode permet de recréer une vidéo à partir des images de correlation
    // paramètres de la vidéo
    int videoWidth = listImage[0] -> getImageMat ( ).cols;
    int videoHeight = listImage[0] -> getImageMat ( ).rows;
    cout << videoWidth << "x" << videoHeight << endl;
    
    if ( outputDirectory == "" )
    {
        outputDirectory = "../videos";
    }
    string filename = outputDirectory + "/corr_" + name + ".mp4";
    cv::VideoWriter videoWriter(filename, cv::VideoWriter::fourcc('m', 'p', '4', 'v'), fps, cv::Size(videoWidth, videoHeight));

    // Écriture de toutes les images dans la vidéo
    for ( auto iCorrImage = listImage.begin ( ); iCorrImage != listImage.end ( ); ++iCorrImage )
    {
        videoWriter.write ( (*iCorrImage) -> getImageMat ( ) );
    }

    videoWriter.release ( );
}

void Video::ExtractCorrelationImages ( string outputDirectory ) const
// Algorithme :
//      On extrait toutes les images de la vidéo avec le rectangle de corrélation
//      et on les met dans un dossier en particulier outputDirectory ou dans frames par défaut
//
{
    // Cette méthode permet d’extraire les images avec le rectangle de corrélation
    // et de les mettre dans un dossier en particulier
    if ( outputDirectory == "" )
    {
        outputDirectory = "../frames/corr_" + name + "/";
    }
    
    // extraction de toutes les images
    for ( auto iImage = listImage.begin ( ); iImage != listImage.end ( ); ++iImage )
    {
        // image corrélée
        Image * currImage = (*iImage);
        // extraction de l’image corrélée
        currImage -> ExtractCorrelationImage ( outputDirectory );
    }
}

//-------------------------------------------- Constructeurs - destructeur
Video::Video ( string videoPath, string videoName, bool framesCreation, cv::VideoCapture videoInput ) : video ( videoPath )
// Algorithme :
//      On crée une vidéo à partir d’un chemin vers une vidéo
//      On crée toutes les images de la vidéo si framesCreation est vrai
//      On crée une vidéo à partir d’un objet VideoCapture si videoInput est présent et que l’on a pas donné de chemin vers une vidéo
//
{
    #ifdef DEBUG
        cout << "Appel au constructeur de <Video>" << endl;
    #endif
    path = videoPath;
    name = videoName;

    // si on a une vidéo en entrée, alors on ne prend pas en compte le videoPath
    if ( (videoInput.isOpened ( )) and (videoPath == ""))
    {
        video = videoInput;
    }

    // vérification de l’ouverture du fichier
    if ( !video.isOpened())
    {
        std::cerr << "erreur, impossible d’ouvrir la vidéo" << endl;
    }
    else {
        string framesDirectory = "../frames/" + name + "/";
        // création du répertoire de stockage de toutes les images du nom de la vidéo
        if ( framesCreation )
        {
            std::filesystem::create_directories ( framesDirectory );
        }

        // les images auront pour nom un numéro (commençant à 0).
        int frameNumber = 0;

        // création de toutes les images contenues dans la vidéo
        while ( true )
        {
            cv::Mat currFrame;
            video >> currFrame;

            // fin de vidéo 
            if ( currFrame.empty ( ) )
            {
                break;
            }

            string imagePath = "";
            // création du fichier si demandé
            if ( framesCreation )
            {
                ostringstream filename;
                filename << framesDirectory << to_string ( frameNumber ) << ".png";
                cv::imwrite ( filename.str ( ), currFrame );
                imagePath = filename.str ( );
            }

            // initialisation des objets images 
            Image * currImage = new Image ( to_string ( frameNumber ), imagePath, currFrame );        
            listImage.push_back ( currImage );
            frameNumber++;
        }
    }
} //----- Fin de Video


Video::~Video ( )
// Algorithme :
//      On supprime toutes les images de la liste
//      On libère la vidéo
//
{
    #ifdef DEBUG
        cout << "Appel au destructeur de <Video>" << endl;
    #endif

    video.release ( );
    // Suppression de toutes les images dans video en utilisant les itérateurs
    // déclaration de l’itérateur 
    vector < Image * >::iterator iImage;
    // suppresion 
    for ( iImage = listImage.begin ( ); iImage != listImage.end ( ); ++iImage )
    {
        // on delete toute les images présentes dans la liste
        delete (*iImage);
    }


} //----- Fin de ~Video


