/*
  Simulation des projections p (algorithme ART)
	imgIn    : Image de départ
	nbProj   : Nombre d'orientations des projections
*/
CImg<> Projections(CImg<> img, int nbProj)
{
  int size = imgIn.width();
  CImg<> p(1,nbProj*size,1,1,0);

  for (int o = 0; o<nbProj; ++o)
  {
    float orient = o*180.0f/nbProj;
    CImg<> rot_img = imgIn.get_rotate(orient,size/2.0f,size/2.0f,3);
    cimg_forXY(rot_img,x,y)
      p(0,x + o*size) += rot_img(x,y);
  }
  return p;
}
