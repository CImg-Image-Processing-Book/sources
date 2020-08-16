CImg<> imgIn("test.bmp"); // Chargement de l'image
deriche(imgIn,alpha,0);   // Filtrage en X
imgIn.transpose();
deriche(imgIn,alpha,0);   // Filtrage en Y <=>

// Filtrage en X de l'image transposée
imgIn.transpose();
