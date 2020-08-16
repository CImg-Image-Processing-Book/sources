/*
  Filtrage de diffusion 2D+T (Méthode de Perona et Malik).

  seqIn   : Images d'entrées (les images de la séquence
             sont rangées dans l'axe "z" de l'objet CImg)
  nbiter  : Temps maximal de diffusion
  dt      : Pas temporel dans le schéma de discrétisation
  lambda  : Paramètre de la diffusitivité à régler par
            rapport à la norme de gradient à "conserver"
*/
CImg<> PeronaMalik2D(CImg<>& seqIn, int nbiter, float dt, float lambda)
{
  CImg<> seqOut = seqIn;

  for (int iter = 0; iter<nbiter; ++iter)
  {
    // Calcul des dérivées spatiales et temporelle par les différences finies.
    CImgList<>
      NWP = seqIn.get_gradient("xyz",-1),
      SEF = seqIn.get_gradient("xyz",+1);

    cimg_forXYZ(seqOut,x,y,t)
    {
      float
        cW = 1/(1 + cimg::sqr(lambda*NWP(0,x,y,t)));
        cE = 1/(1 + cimg::sqr(lambda*SEF(0,x,y,t)));
        cN = 1/(1 + cimg::sqr(lambda*NWP(1,x,y,t)));
        cS = 1/(1 + cimg::sqr(lambda*SEF(1,x,y,t)));
        cP = 1/(1 + cimg::sqr(lambda*NWP(2,x,y,t)));
        cF = 1/(1 + cimg::sqr(lambda*SEF(2,x,y,t)));

      seqOut(x,y,t) += dt*(-cW*NWP(0,x,y,t) + cE*SEF(0,x,y,t)
                           -cN*NWP(1,x,y,t) + cS*SEF(1,x,y,t)
                           -cP*NWP(2,x,y,t) + cF*SEF(2,x,y,t));
    }
  }
  return seqOut;
}
