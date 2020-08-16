/*
  Calcul des LBP et du contraste - version invariante à la rotation.

  imgIn : image d'entrée
  R     : Rayon du cercle des voisins
  P 	: Nombre de voisins
  lbp,C : images de sortie
*/
void CalculLBP(CImg<>& imgIn, float R, int p, CImg<>& lbp, CImg<>& C)
{
  float PI2 = 2*cimg::PI;

  cimg_for_insideXY(imgIn,x,y,(int)(R + 1))
  {
    float
      Ibar = 0,
      Vc = imgIn(x,y);

    // On échantillonne p points sur le cercle de rayon R.
    CImg<> xi(p,2,1,1,0), V(p);
    cimg_forX(V,n)
    {
      xi(n,0) = x - R*std::sin(PI2*n/p);
      xi(n,1) = y + R*std::cos(PI2*n/p);
      V(n) = imgIn.linear_atXY(xi(n,0),xi(n,1));
      Ibar += V(n);
    }
    // Moyenne des niveaux de gris des voisins.
    Ibar /= p;

    // Calcul de U.
    float U = 0;
    for (int n = 1; n<p; ++n)
    {
      float Vj = imgIn.linear_atXY(xi(n - 1,0),xi(n - 1,1));
      U += cimg::abs(V(n) - Vc>0 ? 1 : 0) -
           cimg::abs(Vj - Vc>0 ? 1 : 0);
    }
    float
      Vi = imgIn.linear_atXY(xi(p - 1,0),xi(p - 1,1)),
      Vj = imgIn.linear_atXY(xi(0,0),xi(0,1));
    U += cimg::abs((Vi - Vc>0 ? 1 : 0) -
                   (Vj - Vc>0 ? 1 : 0));

    if (U>2) lbp(x,y) = p + 1;
    else
      cimg_forX(V,n)
        lbp(x,y) += (V(n) - Vc>0 ? 1 : 0);

    cimg_forX(V,n)
      C(x,y) += cimg::sqr(V(n) - Ibar);
    C(x,y) /= p;
  }
}
