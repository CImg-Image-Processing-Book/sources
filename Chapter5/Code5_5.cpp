CImg<> Kuwahara(CImg<>& imgIn)
{
  CImg<> imgOut(imgIn);

  // Filtres de Kuwahara.
  CImgList<unsigned char> Kuwahara(4,5,5,1,1,0);
  cimg_for_inXY(Kuwahara[0],0,0,2,2,i,j) Kuwahara(0,i,j) = 1;
  for (int i = 1; i<4; ++i)
    Kuwahara[i] = Kuwahara[0].get_rotate(i*90);

  // Analyse des voisinages.
  CImg<>
    mu(9,1,1,1,0),
    sigma(9,1,1,1,0),
    st,
    N(5,5);
  CImg<int> permutations;

  cimg_for5x5(imgIn,x,y,0,0,N,float)
  {
    CImgList<> res(4);
    for (int i = 0; i<4; ++i)
    {
      res[i] = N.get_mul(Kuwahara[i]);
      st = res[i].get_stats();
      mu[i] = st[2];
      sigma[i] = st[3];
    }
    sigma.sort(permutations);
    imgOut(x,y) = mu[permutations[0]];
  }
  return imgOut;
}
