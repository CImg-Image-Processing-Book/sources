/*
  Calcul d'une image intégrale en un point.

  imgInt : Image intégrale
  x,y    : Pixel en lequel calculer la moyenne
  k      : Taille de la fenêtre
*/
float IntegralMean(CImg<>& imgInt, int x, int y, int k)
{
  int
    k2 = k/2,
    startx = std::max(0,x - k2),
    starty = std::max(0,y - k2),
    stopx = std::min(imgInt.width() - 1,x + k2 - 1),
    stopy = std::min(imgInt.height() - 1,y + k2 - 1);

  // Utilisation de l'image intégrale.
  float
    l1 = startx - 1<0 ? 0 : imgInt(startx - 1,stopy,0),
    l2 = starty - 1<0 ? 0 : imgInt(stopx,starty - 1,0),
    l3 = starty - 1<0 || startx - 1<0 ? 0 :
      imgInt(startx - 1,starty - 1,0),
    l4 = imgInt(stopx,stopy,0);

  return (l4 - l1 - l2 + l3)/
         ((stopy - starty + 1)*(stopx - startx + 1));
}
