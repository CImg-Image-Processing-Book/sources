CImg<unsigned char>
  imgIn("butterfly.bmp"),
  mess("message.bmp");

// Les pixels du texte sont mis à 1 sur un fond de 0.
mess.threshold(128);
CImg<unsigned char> imgIn2 = imgIn.get_channel(0) &= 0xFE;

// Encodage. On enlève les 1 en bits de poids faible.
imgIn2 = imgIn2 & 0xFE;

// Encodage du message dans le bit de poids faible.
CImg<unsigned char> imgOut = imgIn2 | mess;

// Décodage.
CImg<unsigned char> res = (imgOut&1) *= 255;
