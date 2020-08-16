CImg<> ColorMedianFiltering(CImg<>& imgIn)
{
  // Passage dans un espace colorimétrique perceptuellement uniforme.
  CImg<> imgOut(imgIn);
  imgIn.RGBtoLab();

  int n = 5;

  CImg<>
    V(n,n,1,3),
    vL(n,n),
    va(n,n),
    vb(n,n);

  cimg_for5x5(imgIn,x,y,0,0,vL,float)
  {
    cimg_get5x5(imgIn,x,y,0,1,va,float);
    cimg_get5x5(imgIn,x,y,0,2,vb,float);
    V.get_shared_channel(0) = vL;
    V.get_shared_channel(1) = va;
    V.get_shared_channel(2) = vb;

    // Calcul distance du pixel central.
    float dmin = 0;
    CImg<> z = V.get_vector_at(x,y);
    cimg_forXY(V,i,j)
    {
      CImg<> zi = V.get_vector_at(i,j);
      dmin += std::sqrt((z - zi).dot(z - zi));
    }
    cimg_forXY(V,i,j)
    {
      float d = 0;
      CImg<> z = V.get_vector_at(i,j);
      cimg_forXY(V,u,v)
      {
        CImg<> zi = V.get_vector_at(u,v);
        d += std::sqrt((z - zi).dot(z - zi));
      }
      if (d<dmin)
      {
        dmin = d;
        imgOut(x,y,0,0) = V(i,j,0,0);
        imgOut(x,y,0,1) = V(i,j,0,1);
        imgOut(x,y,0,2) = V(i,j,0,2);
      }
    }
  }
  return imgOut.LabtoRGB();
}
