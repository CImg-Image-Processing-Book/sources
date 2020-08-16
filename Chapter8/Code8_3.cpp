CImg<> V;
for (int N = nb_scales - 1; N>=0; --N)
{
  float factor = (float)std::pow(2,(double)N);
  int
    s_width = std::max(1,(int)(seq.width()/factor)),
    s_height = std::max(1,(int)(seq.height()/factor));
  CImg<> scale_seq = seq.get_resize(s_width,s_height,-100,-100,2).
                         blur(N,N,0,true,false);
  if (V) (V *= 2).resize(s_width,s_height,1,-100,3);
  else V.assign(s_width,s_height,1,2,0);
  DirectMotion(V,scale_seq,nb_iters<<N,alpha);
}
