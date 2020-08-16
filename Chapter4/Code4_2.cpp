CImg<unsigned char> img("yin.png");

// Définition de l'élément structurant, ici un carré de taille 3.
CImg<unsigned char> B = CImg<unsigned char>(3,3).fill(1);

// Calcul de l'ouverture et la fermeture.
CImg<unsigned char>
  imgErode = img.get_erode(B),         // Erosion
  imgDilate = img.get_dilate(B),       // Dilatation
  imgOpening = imgErode.get_dilate(B), // Ouverture
  imgClosing = imgDilate.get_erode(B); // Fermeture
