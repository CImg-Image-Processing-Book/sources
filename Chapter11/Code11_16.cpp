/*
  Sélection manuelle de points d'intérêt sur des images stéréo.

  I1,I2	: Images stéréo
  n     : Nombre de points
*/
CImgList<> SelectPoints(CImg<>& I1, CImg<>& I2, int n)
{
  CImgList<> m(n,2,3);
  int DG = 1;
  unsigned char red[] = { 255,0,0 }, green[] = { 0,255,0 };
  CImgDisplay Disp1(I1,"I1"), Disp2(I2,"I2");
  int i = 0;

  while (!Disp1.is_closed() && !Disp2.is_closed() && i<n)
  {
    switch (DG)
    {
    case 1 :
      Disp2.set_title("I2");
      Disp1.set_title("Cliquer ici");
      Disp1.wait();
      if (Disp1.button() && Disp1.mouse_y()>=0)
      {
        m(i,0,0) = Disp1.mouse_x();
        m(i,0,1) = Disp1.mouse_y();
        m(i,0,2) = 1;
        I1.draw_circle(m(i,0,0),m(i,0,1),5,red,1.0,1).display(Disp1);
        DG = 2;
      } break;
    case 2 :
      Disp1.set_title("I1");
      Disp2.set_title("Cliquer ici");
      Disp2.wait();
      if (Disp2.button() && Disp2.mouse_y()>=0)
      {
        m(i,1,0) = Disp2.mouse_x();
        m(i,1,1) = Disp2.mouse_y();
        m(i,1,2) = 1;
        I2.draw_circle(m(i,1,0),m(i,1,1),5,green,1.0,1).display(Disp2);
        DG = 1;
        ++i;
      } break;
    default : break;
    }
  }
  return m;
}
