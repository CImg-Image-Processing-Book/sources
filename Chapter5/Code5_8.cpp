CImg<>
  imgIn("image.bmp"), // Chargement de l'image
  imgX = imgIn.get_transpose(),
  imgY = imgIn;

deriche(imgX,alpha,0);   // Pré-lissage en 'Y' pour la dérivée en 'X'
deriche(imgY,alpha,0);   // Pré-lissage en 'X' pour la dérivée en 'Y'
imgX.transpose();imgY.transpose();
deriche(imgX,alpha,1);   // Dérivée première en 'X'
deriche(imgY,alpha,1);   // Dérivée première en 'Y'
imgY.transpose();

CImg<> Norme = (imgX.sqr() + imgY.sqr()).get_sqrt();
