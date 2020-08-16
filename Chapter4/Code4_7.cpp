/*
  Algorithme de squelettisation.

  imgIn   : Image d'entrée
  maxiter : Nombre maximum d'itérations de la squelettisation
*/
int Squelettisation(CImg<unsigned char>& imgIn, int maxiter)
{
  int n, i = 0;
  do
  {
    ++i;
    n = IterSquelette(imgIn);
  }
  while (n>0 && i<maxiter);
  return i;
}
