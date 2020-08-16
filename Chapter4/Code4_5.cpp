void GradientsMorphologiques(CImg<>& imgIn, int n)
{
  CImg<>
    B = CImg<>(n,n).fill(1),
    imgErode = imgIn.get_erode(B),
    imgDilate = imgIn.get_dilate(B),
    imgOpening = imgErode.get_dilate(B),
    imgClosing = imgDilate.get_erode(B),
    gradE = imgIn - imgErode,
    gradD = imgDilate - imgIn;

  // Gradient de Beucher.
  CImg<> imgBeucher = imgDilate - imgErode;

  // Hop Hat.
  CImg<>
    whiteTopHat = imgIn - imgOpening,
    blackTopHat = imgClosing - imgIn;

  // Détecteurs de contours marqués.
  CImg<>
    contourMin = gradE.min(gradD),
    contourMax = gradE.max(gradD);

  // Laplacien non linéaire.
  CImg<> Laplacien = gradD - gradE;
}
