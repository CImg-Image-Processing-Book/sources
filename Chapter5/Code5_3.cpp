CImg<> sigmaFiltre(CImg<>& imgIn)
{
  CImgList<> g = imgIn.get_gradient();
  CImg<> grad = (g[0].get_sqr() + g[1].get_sqr()).sqrt();

  // Calcul de la somme des gradients sur un voisinage 3x3.
  CImg<> Sgrad = grad.get_convolve(CImg<>(3,3,1,1,1));

  float epsilon = 100;
  CImg_3x3(I,float);
  CImg<>
    rap = imgIn.get_div(grad + epsilon),
    imgOut(imgIn);

  cimg_for3x3(rap,x,y,0,0,I,float)
    imgOut(x,y) = (Ipp + Ipc + Ipn + Icp + Icc +
                   Icn + Inp + Inc + Inn)/(Sgrad(x,y) + epsilon);
  return imgOut;
}
