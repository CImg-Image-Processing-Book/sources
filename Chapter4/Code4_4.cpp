/*
  Filtres alternés séquentiels.

  imgIn : Image d'entrée
  n     : Taille maximum des filtres
*/
CImg<> SAFiltering(CImg<>& imgIn, int n)
{
  CImg<> imgOut(imgIn);

  for (int k = 1; k<=n; ++k)
  {
    // Définition d'un élément structurant k x k.
    CImg<> mask = CImg<>(k,k).fill(1);

    // Ouverture à la taille k.
    imgOut.erode(mask).dilate(mask);

    // Fermeture à la taille k.
    imgOut.dilate(mask).erode(mask);
  }

  return imgOut;
}
