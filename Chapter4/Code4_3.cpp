/*
  Algorithme de Kramer-Bruckner.

  imgIn : Image d'entrée
  n     : Taille de l'élément structurant (carré)
*/
CImg<> KramerBruckner(CImg<>& imgIn, int n)
{
  CImg<>
    imgOut(imgIn),                      // Copie de l'image d'entrée
    mask = CImg<>(n,n).fill(1),         // Element structurant n x n
    imgErode = imgIn.get_erode(mask),   // Erosion
    imgDilate = imgIn.get_dilate(mask); // Dilatation

  cimg_forXY(imgOut,x,y)
  {
    float M = 0.5f*(imgErode(x,y) + imgDilate(x,y));
    imgOut(x,y) = (imgIn(x,y)<=M ? imgErode(x,y) : imgDilate(x,y));
  }

  return imgOut;
}
