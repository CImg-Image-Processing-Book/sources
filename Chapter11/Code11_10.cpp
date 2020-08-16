/*
  SinogramFiltering: Filtrage des projections ( sinogramme )

  sinog  : Sinogramme <=> données d'entrées
  return : Sinogramme filtré par le filtre rampe
*/
CImg<> SinogramFiltering(CImg<>& sinog)
{
  // Calcul de la transformée de Fourier en 1D.
  CImgList<> FFTy_sinog = sinog.get_FFT('y');

  // Filtrage avec le filtre rampe.
  cimg_forX(FFTy_sinog[0],o)
  {
    for (int sigma = 0; sigma<sinog.height()/2; ++sigma)
     {
       float coeff = xi/sinog.height()/2.0f;
       FFTy_sinog[0](o,sigma) *= coeff;
       FFTy_sinog[0](o,sinog.height() - 1 - sigma) *= coeff;
       FFTy_sinog[1](o,sigma) *= coeff;
       FFTy_sinog[1](o,sinog.height() - 1 - sigma) *= coeff;
     }
  }
  // Calcul de la transformée de Fourier inverse 1D.
  CImgList<> iFFTy_sinog = FFTy_sinog.get_FFT('y',true);
  return iFFTy_sinog[0];
}
