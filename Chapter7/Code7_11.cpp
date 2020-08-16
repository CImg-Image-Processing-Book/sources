float D(float x1, float y1, float L1, float a1, float b1,
        float x2, float y2, float L2, float a2, float b2,
        float S, float m) {
  return std::sqrt(cimg::sqr(L1 - L2) +
                   cimg::sqr(a1 - a2) +
                   cimg::sqr(b1 - b2) +
                   m*m/(S*S)*(cimg::sqr(x1 - x2) +
                   cimg::sqr(y1 - y2)));
}
