/*
  Résolution du problème direct

  V        : Image du champ de déplacement
  seq      : Séquence de deux images  empilées en z
  nb_iters : Nombre d'itérations du schéma numérique
  alpha    : Paramètre de régularisation du champ de déplacement
*/
void DirectMotion(CImg<>& V, CImg<>& seq,
                  unsigned int nb_iters, float alpha)
{
  // Normalisation de la séquence d'entrée
  // (améliore la convergence du schéma).
  CImg<> nseq = seq.get_normalize(0,1);

  // Définition du masque de moyennage spatial.
  CImg<> avg_kernel(3,3,1,1,
                    0., 0.25, 0.,
                    0.25, 0., 0.25,
                    0., 0.25, 0.);

  // Calcul du gradient suivant les axes 'x','y'.
  CImgList<> grad = seq.get_slice(0).get_gradient("xy");

  // Boucle d'itérations.
  float denom = 1 + 4*alpha;
  for (unsigned int iter = 0; iter<nb_iters; ++iter)
  {
    CImg<> Vavg = V.get_convolve(avg_kernel);
    cimg_forXY(V,x,y) {
      float
        X = x + V(x,y,0),
        Y = y + V(x,y,1),
        deltaI = nseq(x,y,0) - nseq.linear_atXY(X,Y,1);
      V(x,y,0) = (V(x,y,0) + deltaI*grad[0].linear_atXY(X,Y,0,0,0) +
                 4*alpha*Vavg(x,y,0))/denom;
      V(x,y,1) = (V(x,y,1) + deltaI*grad[1].linear_atXY(X,Y,0,0,0) +
                 4*alpha*Vavg(x,y,1))/denom;
    }
  }
}
