/*
  JPEG_IDCT: Calcul de la transformée en cosisnus discrète inverse (iDCT).

  dct       : DCT <=> données d'entrée
  cosvalues : Précalcul des valeurs du cosinus pour la DCT
  return    : Image de sortie
*/
CImg<> JPEG_IDCT(CImg<>& dct, CImg<>& cosvalues)
{
  unsigned int N = 8; // Résolution d'un bloc

  CImg<> img(N,N,1,1,0);
  cimg_forXY(img,x,y)
  {
    cimg_forXY(dct,i,j)
    {
      float
        ci = (i==0) ? 1/std::sqrt(2) : 1,
        cj = (j==0) ? 1/std::sqrt(2) : 1;
      img(x,y) += ci*cj*dct(i,j)*cosvalues(x,i)*cosvalues(y,j);
    }
    img(x,y) *= 2.0f/N;
  }
  return img;
}
