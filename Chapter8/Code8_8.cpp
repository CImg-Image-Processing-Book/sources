/*
  Recalage d'images par corrélation de phase

  IS : Image source
  IC : Image cible
  tx : Composante horizontale de la translation (sortie)
  ty : Composante vertiacale de la translation (sortie)
*/
void CorrelationPhase(CImg<>& IS, CImg<>& IC, int& tx, int& ty)
{
  float eps = 1.0e-8f;

  // Calcul des transformées de Fourier des images.
  CImgList<>
    fft_S = IS.get_FFT("xy"),
    fft_T = IC.get_FFT("xy");

  // Calcul du spectre de puissance croisée :
  // R = (TF(img_S) x conf(TF(img_T)))/|TF(img_S) x conf(TF(img_T))|
  CImg<>
    r_R = fft_S(0).get_mul(fft_T(0)) + fft_S(1).get_mul(fft_T(1)),
    i_R = fft_T(0).get_mul(fft_S(1)) - fft_S(0).get_mul(fft_T(1)),
    deno_R = (r_R.get_mul(r_R) + i_R.get_mul(i_R)).get_sqrt();
  r_R.div(deno_R + eps);
  i_R.div(deno_R + eps);

  // Calcul de la corrélation de phase (r = TF-1(R)).
  CImg<>::FFT(r_R,i_R,true);
  CImg<> r = (r_R.get_mul(r_R) + i_R.get_mul(i_R)).get_sqrt();

  // Recherche du maximum de la corrélation de phase
  float r_max = 0;
  int
    w = IS.width(),
    h = IS.height();

  cimg_forXY(r,x,y)
  {
    if (r(x,y)>r_max) {
      r_max = r(x,y);
      tx = -((x - 1 + (w/4))%(w/2) - (w/4) + 1);
      ty = -((y - 1 + (h/4))%(h/2) - (h/4) + 1);
    }
  }
}
