CImg<> LucasKanade2(CImg<>& seq)
{
  CImg<> B(2,2), C(1,2), W(n,n);
  int n = 9, n2 = n/2;

  CImgList<> eig;

  // Bornes pour les valeurs propres.
  float
    epsilon = 1e-8f,
    tau_D = 300;

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
    // Calcul sur le voisinage n*n de M et b.
    for (int k = -n2; k<=n2; ++k)
      for (int l = -n2; l<=n2; ++l)
      {
        float temp = cimg::sqr(W(k + n2,l + n2));
        B(0,0) += temp*cimg::sqr(grad(0,i + k,j + l));
        B(1,1) += temp*cimg::sqr(grad(1,i + k,j + l));
        B(0,1) += temp*(grad(0,i + k,j + l)*grad(1,i + k,j + l));
        C(0) += temp*(grad(0,i + k,j + l)*grad(2,i + k,j + l));
        C(1) += temp*(grad(1,i + k,j + l)*grad(2,i + k,j + l));
      }
    B(1,0) = B(0,1);

    // Analyse du spectre de B.
    eig = B.get_symmetric_eigen();
    CImg<> &val = eig[0], &vec = eig[1];

    B.invert();

    // Les valeurs propres de B sont grandes.
    if (std::min(val(0),val(1))>=tau_D)
    {
      CImg<> v = -B*C;
      field(i,j,0,0) = v(0);
      field(i,j,0,1) = v(1);
    }
    // Une seule valeur propre est grande et B n est pas singulière : Projection de v.
    else if (val(1)>=tau_D && cimg::abs(B.det())>epsilon)
    {
      CImg<> v = -B*C;
      const float tmp = v(0)*vec(1,0) + v(1)*vec(0,0);
      field(i,j,0,0) = -tmp*vec(1,0);
      field(i,j,0,1) = tmp*vec(0,0);
    }
  }
  return field;
}
