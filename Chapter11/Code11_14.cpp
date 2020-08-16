/*
  Simulation de la matrice de projection A (algorithme ART).

  size   : Largeur de l'image ( carré )
  nbProj : Nombre d'orientations des projections
*/
CImg<> MatriceProjection(int size, int nbProj)
{
  CImg<>
    A(size*size,nbProj*size,1,1,0),
    imgPixel(size,size,1,1,0);

  cimg_forXY(imgPixel,x,y)
  {
    imgPixel(x,y) = 1;

    for (int o = 0; o<nbProj; ++o)
    {
      float orient = o*180.0f/nbProj;
      CImg<> rot_img = imgPixel.get_rotate(orient,
                                           size/2.0f,size/2.0f,3);
      cimg_forXY(rot_img,i,j)
        A(x + y*size,i + o*size) += rot_img(i,j);
    }

    imgPixel(x,y) = 0;
  }
  return A;
}
