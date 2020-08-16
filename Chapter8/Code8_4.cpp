CImg<> LucasKanade1(CImg<>& seq)
{
  CImg<>
    B(2,2),
    C(1,2),
    W(n,n);
  int
    n = 9,
    n2 = n/2;

  // Champ de vitesse.
  CImg<> field(seq.width(),seq.height(),1,2,0);

  // Gradient de la séquence d'images.
  CImgList<> grad = seq.get_gradient("xyz",4);

  // Fonction de fenêtrage.
  float
    sigma = 10,
    color = 1;
  W.draw_gaussian(n2,n2,sigma,&color);

  cimg_for_insideXY(seq,i,j,n)
  {
    B.fill(0);
    C.fill(0);
    // Calcul des matrices.
    for (int k = -n2; k<=n2; ++k)
      for (int l = -n2; l<=n2;++l)
      {
        float temp = cimg::sqr(W(k + n2,l + n2));
        B(0,0) += temp*cimg::sqr(grad(0,i + k,j + l));
        B(1,1) += temp*cimg::sqr(grad(1,i + k,j + l));
        B(0,1) += temp*(grad(0,i + k,j + l)*grad(1,i + k,j + l));
        C(0) += temp*(grad(0,i + k,j + l)*grad(2,i + k,j + l));
        C(1) += temp*(grad(1,i + k,j + l)*grad(2,i + k,j + l));
      }
    B(1,0) = B(0,1);

    // Calcul de la vitesse en (i,j).
    B.invert();
    CImg<> v = -B*C;
    field(i,j,0,0) = v(0);
    field(i,j,0,1) = v(1);
  }
  return field;
}
