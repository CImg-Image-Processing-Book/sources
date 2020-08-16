/*
  BackProjTransform: Calcul d'une retroprojection simple.

  sinog : Sinogramme <=> données d'entrées
  bp    : Retroprojection simple des données d'entrées "sinog"
*/
CImg<> BackProjTransform(CImg<>& sinog)
{
  float orient_step = 180.0f/sinog.width();
  CImg<> bp(sinog.height(),sinog.height(),1,1,0);

  for (int o = 0; o<sinog.width(); ++o)
  {
    cimg_forXY(bp_sinog,x,y)
      bp(x,y) += sinog(o,x);
    bp.rotate(orient_step,sinog.height()/2.0f,sinog.height()/2.0f,2);
  }
  bp.rotate(180,sinog.height()/2.0f,sinog.height()/2.0f,2);

  return bp;
}
