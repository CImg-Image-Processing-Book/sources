/*
  JPEG_DCT: Calcul de la transformée en cosisnus discrète (DCT)

  block     : Image d'entrée
  cosvalues : Précalcul des valeurs du cosinus pour la DCT
  return    : DCT de l'image d'entrée
*/
CImg<> JPEG_DCT(CImg<>& block, CImg<>& cosvalues)
{
  unsigned int N = 8; // Résolution d'un bloc

  CImg<> dct(N,N,1,1,0);
  cimg_forXY(dct,i,j)
  {
    float
      ci = i==0 ? 1/sqrt(2.0f) : 1,
      cj = j==0 ? 1/sqrt(2.0f) : 1;

    cimg_forXY(block,x,y)
      dct(i,j) += block(x, y)*cosvalues(x,i)*cosvalues(y,j);

    dct(i,j) *= 2.0f/N*ci*cj;
  }
  return dct;
}
