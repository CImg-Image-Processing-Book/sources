CImg<> warp(img.width()/4,img.height()/4,1,2);
cimg_forXY(warp,x,y) {
  float u = 0, v = 0;
  cimglist_for(keypoints,p) {
    float
      xp = keypoints(p,0)*(img.width()-1)/100,
      yp = keypoints(p,1)*(img.height()-1)/100,
      r = cimg::hypot(4*x - xp,4*y - yp),
      phi_r = phi(r);
    u += W(0,p)*phi_r;
    v += W(1,p)*phi_r;
  }
  warp(x,y,0) = 4*x - u;
  warp(x,y,1) = 4*y - v;
}
warp.resize(img.width(),img.height(),1,2,3);
