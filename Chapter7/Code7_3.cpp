/*
  Propagate : Algorithme de propagation d'un contour implicite
  (modéle géodésique)

  imgIn :    Image à segmenter
  LevelSet : Fonction level-set (initialisée)
*/
void Propagate(CImg<>& imgIn, CImg<>& LevelSet)
{
  float
    delta_t = 2.0f,    // Pas temporel
    alpha = 0.05f,     // Pondération du terme de propagation
    beta = 0.8f,       // Pondération du terme d'advection
    ballon = 0;        // Force ballon (>0)
  int
    nbiter = 50000,    // Nombre d'itérations
    exp_cont = 1;      // Expansion (1) ou contraction (-1) de F0

  // Calcul des gradients regularisés.
  CImgList<> GradImg = imgIn.get_gradient("xy",4);

  // Fonction du modèle géodésique.
  CImg<> f(imgIn.width(),imgIn.height());
  cimg_forXY(f,x,y)
  {
    float
      gx = GradImg(0,x,y),
      gy = GradImg(1,x,y);
    f(x,y) = exp_cont*(1./(1 + std::sqrt(gx*gx + gy*gy)) + ballon);
  }

  // Calcul du gradient de f.
  CImgList<> Grad_f = f.get_gradient();

  // Schéma itératif de l'algorithme de propagation.
  for (int iter = 0; iter<nbiter; ++iter)
  {
  // Gradient spatial de psi.
    CImgList<>
      GradLS_moins = LevelSet.get_gradient("xy",-1),
      GradLS_plus = LevelSet.get_gradient("xy",1);

    cimg_forXY(LevelSet,x,y)
    {
      float
        Dxm = GradLS_moins(0,x,y),
        Dxp = GradLS_plus(0,x,y),
        Dym = GradLS_moins(1,x,y),
        Dyp = GradLS_plus(1,x,y);

      // Terme de vitesse de propagation : F0.
      float
        Nabla_plus = std::sqrt(cimg::sqr(std::max(Dxm,0)) +
                               cimg::sqr(std::min(Dxp,0)) +
                               cimg::sqr(std::max(Dym,0)) +
                               cimg::sqr(std::min(Dyp,0))),
        Nabla_moins = std::sqrt(cimg::sqr(std::max(Dxp,0)) +
                                cimg::sqr(std::min(Dxm,0)) +
                                cimg::sqr(std::max(Dyp,0)) +
                                cimg::sqr(std::min(Dym,0))),

        Fprop = -(std::max(f(x,y),0)*Nabla_plus + std::min(f(x,y),0)*Nabla_moins);

      // Terme de vitesse d'advection : Fadv.
      float
        u = Grad_f(0,x,y),
        v = Grad_f(1,x,y),
        Fadv = -(std::max(u,0)*Dxm + std::min(u,0)*Dxp +
                 std::max(v,0)*Dym + std::min(v,0)*Dyp);

      // Mise à jour de la fonction level-set.
      LevelSet(x,y) += delta_t*(alpha*Fprop + beta*Fadv);
    }
  }
}
