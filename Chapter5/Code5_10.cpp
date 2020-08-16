CImg<> Melange(CImg<>& imgIn1, CImg<>& imgIn2)
{
 // Calcul de la transformée de Fourier des deux images.
 CImgList<>
   F_Img1 = imgIn1.get_FFT(),
   F_Img2 = imgIn2.get_FFT();

 // Calcul du module de la transformée de Fourier de l'image 1.
 CImg<> Img1_Mag = (F_Img1[0].get_pow(2) + F_Img1[1].get_pow(2)).
                   sqrt();

 // Calcul de la phase de la transformée de Fourier de l'image 2.
 CImg<> Img2_Arg(imgIn2.width(),imgIn2.height());
 cimg_forXY(Img2_Arg,x,y)
   Img2_Arg(x,y) = std::atan2(F_Img2(1,x,y),F_Img2(0,x,y));

 // Calcul des parties réelle et imaginaire de la composition.
 CImg<>
   R_img3(imgIn1.width(),imgIn1.height()),
   I_img3(R_img3);

 cimg_forXY(R_img3,x,y) {
   R_img3(x,y) = Img1_Mag(x,y)*std::cos(Img2_Arg(x,y));
   I_img3(x,y) = Img1_Mag(x,y)*std::sin(Img2_Arg(x,y));
 }

 // TF inverse et récuperation de la partie réelle.
 return (R_img3,I_img3).get_FFT(true)[0].normalize(0,255);
}
