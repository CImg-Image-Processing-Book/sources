/*
  Algorithme pour supprimer la trame d'une image.

  imgIn  : Image d'entrée (image tramée)
  period : Période la trame
  imgOut : Image de sortie => restauration de l'image tramée
*/
CImg<> Detramage(CImg<>& imgIn, int period)
{
  // Calcul de la transformée de Fourier.
  CImgList<> F_Img = imgIn.get_FFT();

  // Calcul de la fréquence de coupure.
  int Freq_c = imgIn.height()/(2*period);

  // Filtrage fréquentiel pour séparer la trame de l'image.
  cimg_forXYC(F_Img[0],x,y,c)
  {
    if (y>Freq_c && y<F_Img[0].height() - Freq_c)
      F_Img[0](x,y,c) = F_Img[1](x,y,c) = 0;
  }
  // TF inverse et recupération de la partie réelle (symétrie).
  return F_Img.get_FFT(true)[0].normalize(0,255);
}
