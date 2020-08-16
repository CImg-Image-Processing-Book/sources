/*
  Algorithme de Bernsen.

  imgIn	: Image d'entrée
  cmin	: Borne inférieure du contraste
*/
CImg<> Bernsen(CImg<>& imgIn, float cmin)
{
  CImg<> imgOut(imgIn.width(),imgIn.height(),1,1,0);
  float valClass = 0;

  CImg<> N(5,5);
  cimg_for5x5(imgIn,x,y,0,0,N,float)
  {
    float min, max = N.max_min(min);
    imgOut(x,y) = max - min>cmin ? (max + min)/2 : valClass;
  }
  return imgOut;
}
