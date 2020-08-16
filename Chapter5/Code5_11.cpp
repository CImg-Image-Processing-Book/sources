// Chargement de l'image.
CImg<> img("image.bmp");

// Calcul de la transformée de Fourier.
CImgList<> imgFFT = img.get_FFT();

// Calcul du module de l'image (en décibels) : Spectre.
CImg<> imgS = (imgFFT[0].pow(2) +
               imgFFT[1].pow(2)).get_sqrt() + 0.01f;
imgS.log10();

// Réarrangement des données (positionner le zéro au milieu).
CImg<> imgSR = imgS.get_shift(imgS.width()/2,imgS.height()/2,0,0,2);

// Affichage du résultat.
(img,imgS,imgSR).display("Image d'entrée - "
                         "Spectre (Données FFT brutes) - "
                         "Spectre (Données FFT réarrangées)");
