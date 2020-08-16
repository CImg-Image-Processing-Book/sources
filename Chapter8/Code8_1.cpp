/*
  Méthode Horn et Schunck

  V        : image du champ de déplacement
  seq      : séquence de deux images  empilées en z
  nb_iters : nombre d'itérations du schéma numérique
  alpha    : paramètre de régularisation du champ de déplacement
*/
void HornSchunck(CImg<>& V, CImg<>& seq,
                 unsigned int nb_iters, float alpha)
{
  // Calcul du gradient suivant les axes 'x','y' et 't'.
  CImgList<> grad = (seq.get_slice(0).get_gradient("xy"),
  seq.get_gradient("z",1));

  CImg<> avg_kernel(3,3,1,1, // Masque de moyennage
                    0., 0.25, 0.,
                    0.25, 0., 0.25,
                    0., 0.25,0.),
         denom = grad[0].get_sqr() + grad[1].get_sqr() + 4*alpha;

  // Boucle d'itérations.
  for (unsigned int iter = 0; iter<nb_iters; ++iter)
  {
    CImg<> Vavg = V.get_convolve(avg_kernel);
    cimg_forXY(V,x,y) {
      float tmp = (grad[0](x,y)*Vavg(x,y,0) +
                   grad[1](x,y)*Vavg(x,y,1) +
                   grad[2](x,y))/denom(x,y);
      V(x,y,0) = Vavg(x,y,0) - grad[0](x,y)*tmp;
      V(x,y,1) = Vavg(x,y,1) - grad[1](x,y)*tmp;
    }
  }
}
