CImg<>
  imgIn("test.bmp"), // Chargement de l'image
  img2X = imgIn,
  img2Y = imgIn.get_transpose();

deriche(img2X,alpha,2);   // Dérivée seconde en 'X'
deriche(img2Y,alpha,2);   // Dérivée seconde en 'Y'
img2Y.transpose();

CImg<> Laplacian = img2X + img2Y;
