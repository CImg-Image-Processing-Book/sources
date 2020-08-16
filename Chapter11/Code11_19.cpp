CImg<> M(keypoints.size(),keypoints.size());
cimg_forXY(M,p,q) { // Remplissage de la matrice M
  float
    xp = keypoints(p,0)*(img.width()-1)/100,
    yp = keypoints(p,1)*(img.height()-1)/100,
    xq = keypoints(q,0)*(img.width()-1)/100,
    yq = keypoints(q,1)*(img.height()-1)/100,
    r = cimg::hypot(xq - xp,yq - yp);
  M(p,q) = phi(r);
}

CImg<> F(2,keypoints.size());
cimg_forY(F,p) { // Remplissage de la matrice F
  float
    xp = (keypoints(p,0) - keypoints(p,2))*(img.width()-1)/100,
    yp = (keypoints(p,1) - keypoints(p,3))*(img.height()-1)/100;
  F(0,p) = xp;
  F(1,p) = yp;
}
