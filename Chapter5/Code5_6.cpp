/*
  Filtre de Deriche sur un signal 1D (le long de l'axe X).

  imgIn               : Image d'entrée
  alpha               : Paramètre d'échelle
  order               : Ordre du filtre
                        (0: lissage, 1: derivée première, 2: dérivée seconde)
  boundary_conditions : Conditions aux bords
*/
void deriche(CImg<>& imgIn, float alpha, unsigned int order=0,
             bool boundary_conditions=true)
{
  // Coefficients du filtre.
  float
    ema = std::exp(-alpha),
    ema2 = std::exp(-2*alpha),
    b1 = -2*ema,
    b2 = ema2,
    a0 = 0, a1 = 0, a2 = 0, a3 = 0,
    coefp = 0, coefn = 0;

  switch (order)
  {
  case 0 : { // Ordre 0 (lissage)
    float k = (1 - ema)*(1 - ema)/(1 + 2*alpha*ema - ema2);
    a0 = k;
    a1 = k*(alpha - 1)*ema;
    a2 = k*(alpha + 1)*ema;
    a3 = -k*ema2;
  } break;
  case 1 : { // Ordre 1 (dérivée première)
    float k = -(1 - ema)*(1 - ema)*(1 - ema)/(2*(ema + 1)*ema);
    a0 = a3 = 0;
    a1 = k*ema;
    a2 = -a1;
  } break;
  case 2 : { // Ordre 2 (dérivée seconde)
    float
      ea = std::exp(-alpha),
      k = -(ema2 - 1)/(2*alpha*ema),
      kn = -2*(-1 + 3*ea - 3*ea*ea + ea*ea*ea)/
           (3*ea + 1 + 3*ea*ea + ea*ea*ea);
    a0 = kn;
    a1 = -kn*(1 + k*alpha)*ema;
    a2 = kn*(1 - k*alpha)*ema;
    a3 = -kn*ema2;
  } break;
  }
  coefp = (a0 + a1)/(1 + b1 + b2);
  coefn = (a2 + a3)/(1 + b1 + b2);

  // Application du filtre récursif (ligne par ligne).
  CImg<> Y(imgIn.width());

  cimg_forYC(imgIn,y,c)
  {
    float *X = imgIn.data(0,y,0,c);

    // Parcours de gauche à droite.
    float yb = 0, yp = 0, xp = 0;
    if (boundary_conditions) {
      xp = X[0];
      yb = yp = coefp*xp;
    }
    cimg_forX(imgIn,m)
    {
      float
        xc = X[m],
        yc = Y[m] = a0*xc + a1*xp - b1*yp - b2*yb;
      xp = xc;
      yb = yp;
      yp = yc;
    }

    // Parcours de droite à gauche.
    float xn = 0, xa = 0, yn = 0, ya = 0;
    if (boundary_conditions) {
      xn = xa = X[imgIn.width() - 1];
      yn = ya = coefn*xn;
    }

    for (int n = imgIn.width() - 1; n>=0; --n)
    {
      float
        xc = X[n],
        yc = a2*xn + a3*xa - b1*yn - b2*ya;
      xa = xn;
      xn = xc;
      ya = yn;
      yn = yc;
      X[n] = Y[n] + yc;
    }
  }
}
