int IterSquelette(CImg<unsigned char>& imgIn)
{
  // Image de marque des pixels pour suppression.
  CImg<unsigned char> D(imgIn.width(),imgIn.height(),1,1,0);

  // Voisinage.
  CImg_3x3(N,unsigned char);

  // Passe 1.
  int n1 = 0;
  cimg_for3x3(imgIn,x,y,0,0,N,unsigned char)
  {
    if (imgIn(x,y))
    {
      unsigned char
        B = Npp + Ncp + Nnp + Npc + Nnc + Npn + Ncn + Nnn,
        C = Nnc*(Nnc-Nnp) + Nnp*(Nnp-Ncp) +
            Ncp*(Ncp-Npp) + Npp*(Npp-Npc) +
            Npc*(Npc-Npn) + Npn*(Npn-Ncn) +
            Ncn*(Ncn-Nnn) + Nnn*(Nnn-Nnc);

      bool R1 = B>=2 && B<=6 && C==1 &&
                Ncn*Nnc*Ncp==0 &&
                Npc*Ncn*Nnc==0;
      if (R1)
      {
        // Marque sur (x,y) pour suppression.
        D(x,y) = 1;
        ++n1;
      }
    }
  }
  // Suppression des pixels marqués.
  cimg_forXY(imgIn,x,y)
    imgIn(x,y) -= (n1>0)*D(x,y);

  // Passe 2.
  int n2 = 0;
  D.fill(0);
  cimg_for3x3(imgIn,x,y,0,0,N,unsigned char)
  {
    if (imgIn(x,y))
    {
      unsigned char
        B = Npp + Ncp + Nnp + Npc + Nnc + Npn + Ncn + Nnn,
        C = Nnc*(Nnc-Nnp) + Nnp*(Nnp-Ncp) +
            Ncp*(Ncp-Npp) + Npp*(Npp-Npc) +
            Npc*(Npc-Npn) + Npn*(Npn-Ncn) +
            Ncn*(Ncn-Nnn) + Nnn*(Nnn-Nnc);

      bool R2 = B>=2 && B<=6 && C==1 &&
                Nnc*Ncp*Npc==0 &&
                Ncp*Npc*Ncn==0;
      if (R2)
      {
        // Marque sur (x,y) pour suppression */
        D(x,y) = 1;
        ++n2;
      }
    }
  }
  // Suppression des pixels marqués.
  cimg_forXY(imgIn,x,y)
    imgIn(x,y) -= (n2>0)*D(x,y);

  // Retourne le nombre de pixels supprimés.
  return n1 + n2;
}
