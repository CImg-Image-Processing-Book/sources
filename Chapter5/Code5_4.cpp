CImg<> Nagao(CImg<>& imgIn)
{
  CImg<> imgOut(imgIn);

  // Filtres de Nagao.
  CImgList<unsigned char> Nagao(9,5,5,1,1,0);
  Nagao(0,0,0) = Nagao(0,0,1) = Nagao(0,0,2) = Nagao(0,0,3) =
    Nagao(0,0,4) = Nagao(0,1,1) = Nagao(0,1,2) = Nagao(0,1,3) =
    Nagao(0,2,2) = 1;
  for (int i = 1; i<4; ++i) Nagao[i] = Nagao[0].get_rotate(i*90);

  Nagao(4,1,1) = Nagao(4,1,2) = Nagao(4,1,3) = Nagao(4,2,1) =
    Nagao(4,2,2) = Nagao(4,2,3) = Nagao(4,3,1) = Nagao(4,3,2) =
    Nagao(4,3,3) = 1;
  Nagao(5,0,0) = Nagao(5,0,1) = Nagao(5,0,2) = Nagao(5,1,0) =
    Nagao(5,1,1) = Nagao(5,1,2) = Nagao(5,2,0) = Nagao(5,2,1) =
    Nagao(5,2,2) = 1;
  for (int i = 1; i<4; ++i) Nagao[5 + i] = Nagao[5].get_rotate(i*90);

  // Analyse des voisinages.
  CImg<>
    mu(9,1,1,1,0),
    sigma(9,1,1,1,0),
    st,
    N(5,5);
  CImg<int> permutations;
  cimg_for5x5(imgIn,x,y,0,0,N,float)
  {
    CImgList<> res(9);
    for (int i = 0; i<9; ++i)
    {
      res[i] = N.get_mul(Nagao[i]);
      st = res[i].get_stats();
      mu[i] = st[2];
      sigma[i] = st[3];
    }
    // Recherche de la variance minimale.
    sigma.sort(permutations);

    // Affectation de la moyenne au pixel central.
    imgOut(x,y) = mu[permutations[0]];
  }
  return imgOut;
}
