/*
  Filtre de Kalman linéaire.

  I     : Liste des images
  pos   : Position initiale de l'objet à suivre
  size  : Taille de la fenêtre encadrant l'objet
*/
void Kalmann(CImgList<>& I, CImg<int>& pos, CImg<int>& size)
{
  CImg<>
    prevState(1,4),
    currState(1,4);
  CImg<int>
    prevPos(pos),
    currPos(1,2),
    estimPos(1,2);

  prevState(0,0) = pos(0);
  prevState(0,1) = pos(1);
  prevState(0,2) = 0;
  prevState(0,3) = 0;

  CImg<> T = I[0].get_crop(pos(0) - size(0), pos(1) - size(1),
                           pos(0) + size(0), pos(1) + size(1));

  // Matrice D, modèle à vitesse constante et Delta t = 1.
  CImg<> D = CImg<>::identity_matrix(4);
  D(2,0) = D(3,1) = 1;

  // Matrice M.
  CImg<> M(4,2,1,1,0);
  M(0,0) = M(1,1) = 1;
  CImg<> Mt = M.get_transpose();

  // Covariance du modèle.
  CImg<> SigmaD = CImg<>::identity_matrix(4)*5;
  SigmaD(2,2) = SigmaD(3,3) = 1;

  // Covariance de la mesure.
  CImg<> SigmaM = CImg<>::identity_matrix(2)*50;

  // Estimation a priori de l'erreur.
  CImg<> PkPrevious(4,4,1,1,0);

  // Estimation a posteriori de l'erreur.
  CImg<> PkCurrent(4,4);
  for (int i = 1; i<I.size(); ++i)
  {
    // Prédiction.
    currState = D*prevState;
    PkCurrent = SigmaD + D*PkPrevious*D.get_transpose();

    // Correction.
    CImg<> Kt = PkCurrent*Mt*((M*PkCurrent*Mt+ SigmaM).get_invert());
    currState = currState + Kt*(estimPos - M*currState);
    CImg<> I = CImg<>::identity_matrix(PkCurrent.width());
    PkCurrent = (I - Kt*M)*PkCurrent;

    // Mise à jour de la position.
    currPos(0) = (int)currState(0);
    currPos(1) = (int)currState(1);
    prevPos(0) = (int)currState(0);
    prevPos(1) = (int)currState(1);
    prevState = currState;
    PkPrevious = PkCurrent;
  }
}
