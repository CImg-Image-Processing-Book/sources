/*
  RadonTransform: Calcul des projections (<=> Transformée de Radon).

  imgIn   : Image d'entrée
  nb_proj : Nombre de projections
*/
CImg<> RadonTransform(CImg<>& imgIn, int nb_proj)
{
  CImg<> sinogram(nb_proj,img.width(),1,1,0);
  for (int o = 0; o<nb_proj; ++o)
  {
    float
      orient = o*180.0f/nb_proj,
      xc = imgIn.width()/2.0f,
      yc = imgIn.height()/2.0f;
    CImg<> rot_img = imgIn.get_rotate(orient,xc,yc,2);
    cimg_forXY(rot_img,x,y)
      sinogram(o,x) += rot_img(x,y);
  }
  return sinogram;
}
