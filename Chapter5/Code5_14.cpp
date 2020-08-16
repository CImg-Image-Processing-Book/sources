/*
  Filtrage de diffusion 2D (Méthode de Perona et Malik).

  imgIn   : Image d'entrée
  nbiter  : Temps maximal de diffusion
  dt      : Pas temporel dans le schéma de discrétisation
  lambda  : Paramètre de la diffusitivité à régler par
            rapport à la norme de gradient à "conserver"
*/
CImg<> PeronaMalik2D(CImg<>& imgIn, int nbiter, float dt, float lambda)
{
  CImg<> imgOut= imgIn;

  for (int iter = 0; iter<nbiter; ++iter)
  {
    // Calcul des dérivées spatiales par les différences finies.
    CImgList<>
      NW = imgOut.get_gradient("xy",-1),
      SE = imgOut.get_gradient("xy",+1);

    cimg_forXY(imgOut,x,y)
    {
      float
        cN = 1/(1 + cimg::sqr(lambda*NW(1,x,y))),
        cS = 1/(1 + cimg::sqr(lambda*SE(1,x,y))),
        cE = 1/(1 + cimg::sqr(lambda*SE(0,x,y))),
        cW = 1/(1 + cimg::sqr(lambda*NW(0,x,y)));

      imgOut(x,y) += dt*(-cN*NW(1,x,y) + cS*SE(1,x,y) +
                         cE*SE(0,x,y) - cW*NW(0,x,y));
    }
  }
  return imgOut;
}
