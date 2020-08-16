CImg<> M(4,4), b(1,4), W(n,n);
int n = 9, n2 = n/2;

CImgList<> grad = seq.get_gradient("xyz",4);

// Fonction de fenêtrage.
float
  sigma = 10,
  color = 1;

W.draw_gaussian(n2,n2,sigma,&color);
M.fill(0);
b.fill(0);

for (int k = -n2; k<=n2; ++k)
  for (int l = -n2; l<=n2; ++l)
  {
    float temp = cimg::sqr(W(k + n2,l + n2));
    A(0,0) = k; A(1,0) = -l; A(2,0) = 1; A(3,0) = 0;
    A(0,1) = l; A(1,1) = k;  A(2,1) = 0; A(3,1) = 1;
    CImg<> At = A.get_transpose();

    g(0,0) = grad(0,x + k,y + l);
    g(0,1) = grad(1,x + k,y + l);

    M += temp*At*g*g.get_transpose()*A;
    b += temp*At*g*grad(2,x + k,y + l);
  }

// Calcul de la solution de Ma = b.
CImg<> a = M.invert()*b;

// Calcul des paramètres de la similitude.
float
  theta = std::atan2(a(1),a(0)),
  alpha = a(0)/std::cos(theta);

CImg<> t = CImg<>::vector(a(2),a(3));
