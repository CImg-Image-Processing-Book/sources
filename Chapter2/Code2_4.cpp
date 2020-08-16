cimglist_for(blocs,l)
{
  CImg<int>& bloc = blocs[l];
  int
    x0 = bloc[0], y0 = bloc[1],
    x1 = bloc[2], y1 = bloc[3];
  CImg<unsigned char> color(1,1,1,3);
  color.rand(0,255);
  res.draw_rectangle(x0,y0,x1,y1,color.data(),1);
  // Remplissage de l’image ’coords’ :
  coords.draw_rectangle(x0,y0,x1,y1,bloc.data());
}
