/*
  Algorithme des 8 points.

  m : Liste des points à apparier
  n : Nombre de points
*/
CImg<> MatriceFondamentale(CImgList<>& m, int n)
{
  CImg<>
    F(3,3),
    A(9,n);

  // Construction de la matrice A.
  for (int i = 0; i<n; ++i)
  {
    A(0,i) = m(i,1,0)*m(i,0,0);
    A(1,i) = m(i,1,0)*m(i,0,1);
    A(2,i) = m(i,1,0);
    A(3,i) = m(i,1,1)*m(i,0,0);
    A(4,i) = m(i,1,1)*m(i,0,1);
    A(5,i) = m(i,1,1);
    A(6,i) = m(i,0,0);
    A(7,i) = m(i,0,1);
    A(8,i) = 1;
  }

  // Décomposition en valeurs singulières.
  CImg<> U, S, V;
  A.SVD(U,S,V);

  // Calcul de F : Dernière colonne de V.
  CImg<> f = V.get_column(8);
  F(0,0) = f(0);
  F(1,0) = f(1);
  F(2,0) = f(2);
  F(0,1) = f(3);
  F(1,1) = f(4);
  F(2,1) = f(5);
  F(0,2) = f(6);
  F(1,2) = f(7);
  F(2,2) = f(8);

  return F;
}
