for (unsigned int l = 0; l<blocs.size(); ) {
  CImg<int>& bloc = blocs[l];
  int
    x0 = bloc[0], y0 = bloc[1],
    x1 = bloc[2], y1 = bloc[3];
  if (std::min(x1 - x0,y1 - y0)>8 &&
      normGrad.get_crop(x0,y0,x1,y1).max()>threshold) {
    int
      xc = (x0 + x1)/2,
      yc = (y0 + y1)/2;
    CImg<int>::vector(x0,y0,xc - 1,yc - 1).move_to(blocs);
    CImg<int>::vector(xc,y0,x1,yc - 1).move_to(blocs);
    CImg<int>::vector(x0,yc,xc - 1,y1).move_to(blocs);
    CImg<int>::vector(xc,yc,x1,y1).move_to(blocs);
    blocs.remove(l);
  } else ++l;
 }
