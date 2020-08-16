/*
  JPEGDecoder: Calcul de l'image reconstruite à partir des DCT

  img_dct   : DCT quantifiées <=> données d'entrée
  quality   : Facteur de qualité ( faible = meilleure qaulité )
  cosvalues : Précalcul des valeurs du cosinus pour la DCT
  return    : Image reconstruite
*/
CImg<> JPEGDecoder(CImg<>& img_dct, float quality, CImg<>& cosvalues)
{
  unsigned int N = 8; // Résolution d'un bloc

  // Matrice de quantification.
  CImg<> Q(N,N);
  Q(0,0) = 16;  Q(0,1) = 11;  Q(0,2) = 10;  Q(0,3) = 16;
  Q(0,4) = 24;  Q(0,5) = 40;  Q(0,6) = 51;  Q(0,7) = 61;
  Q(1,0) = 12;  Q(1,1) = 12;  Q(1,2) = 14;  Q(1,3) = 19;
  Q(1,4) = 26;  Q(1,5) = 58;  Q(1,6) = 60;  Q(1,7) = 55;
  Q(2,0) = 14;  Q(2,1) = 13;  Q(2,2) = 16;  Q(2,3) = 24;
  Q(2,4) = 40;  Q(2,5) = 57;  Q(2,6) = 69;  Q(2,7) = 56;
  Q(3,0) = 14;  Q(3,1) = 17;  Q(3,2) = 22;  Q(3,3) = 29;
  Q(3,4) = 51;  Q(3,5) = 87;  Q(3,6) = 80;  Q(3,7) = 62;
  Q(4,0) = 18;  Q(4,1) = 22;  Q(4,2) = 37;  Q(4,3) = 56;
  Q(4,4) = 68;  Q(4,5) = 109; Q(4,6) = 103; Q(4,7) = 77;
  Q(5,0) = 24;  Q(5,1) = 35;  Q(5,2) = 55;  Q(5,3) = 64;
  Q(5,4) = 81;  Q(5,5) = 104; Q(5,6) = 113; Q(5,7) = 92;
  Q(6,0) = 49;  Q(6,1) = 64;  Q(6,2) = 78;  Q(6,3) = 87;
  Q(6,4) = 103; Q(6,5) = 121; Q(6,6) = 120; Q(6,7) = 101;
  Q(7,0) = 72;  Q(7,1) = 92;  Q(7,2) = 95;  Q(7,3) = 98;
  Q(7,4) = 112; Q(7,5) = 100; Q(7,6) = 103; Q(7,7) = 99;
  Q *= quality;

  CImg<>
    decomp(img_dct.width(),img_dct.height(),1,1,0),
    dct(N,N),
    blk(N,N);

  for (int k = 0; k<img_dct.width()/N; ++k)
    for (int l = 0; l<img_dct.height()/N; ++l)
    {
      dct = img_dct.get_crop(k*N,l*N,(k + 1)*N - 1,(l + 1)*N - 1);
      dct.mul(Q);
      blk = JPEG_IDCT(dct,cosvalues) + 128;

      cimg_forXY(blk,i,j)
        decomp(k*N + i,l*N + j) = blk(i,j);
    }
  return decomp;
}
