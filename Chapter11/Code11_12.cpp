/*
  Algorithme ART pour la reconstruction tomographique algébrique.

  A       : Matrice de projection
  p       : Mesures (ou projections)
  nbiter  : Nombre d'itérations
*/
CImg<> ART(CImg<>& A,CImg<>& p, int nbiter)
{
  float eps = 1e-8f;
  CImg<> f(1,A.width(),1,1,0);

  for (int k = 0; k<nbiter; ++k)
  {
    // Tirage aléatoire d'une mesure.
    int i = cimg::round(cimg::rand(p.height() - 1));

    // Extraction du vecteur de projection de la mesure i.
    CImg<>
      ai = A.get_row(i),
      aiT = ai.get_transpose();

    // Calcul de la norme au carré de ai.
    float norm2_ai = (ai*aiT)[0];

    // Mise à jour de l'image.
    if (norm2_ai>eps) f -= (((ai*f)(0,0) - p(0,i))/norm2_ai)*aiT;
  }
  return f;
}
