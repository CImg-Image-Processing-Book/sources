/*
  ExtractContour : Calcul de la position approximative du contour à
  partir de la carte levelset (psi) : Isocontour de valeur 0.

  LevelSet : Level set (psi function)
  Return   : Image binaire (1<=> contour)
*/
CImg<> ExtractContour(CImg<>& LevelSet)
{
 CImg<> Contour(LevelSet.width(),LevelSet.height(),1,1,0);
 CImg_3x3(I,float);
 cimg_for3x3(LevelSet,x,y,0,0,I,float)
 {
   // Recherche de l'ensemble des pixels possédant un voisin de signe opposé.
   if (Icc*Icp<=0 || Icc*Icn<=0 || Icc*Ipc<=0 || Icc*Inc<=0)
     Contour(x,y) = 1;
 }

 return Contour;
}
