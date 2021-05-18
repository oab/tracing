#include "common.h"

const int s0 = 16;
const int s1 = 16;
const int s2 = 16;
const int size = s0*s1*s2;

int gamma(int i, int j, int k)
{
  return  i * s1 * s2 + j * s2 + k;
}



void SC_NO_PADDING() {
  Vars<int,size> VAR(u);
  Vars<int,size> VAR(v);
  Vars<int,size> VAR(u0);
  Vars<int,size> VAR(u1);
  Vars<int,size> VAR(u2);

  Var<int> VAR(c0);
  Var<int> VAR(c1);
  Var<int> VAR(c2);
  Var<int> VAR(c3);
  Var<int> VAR(c4);

  for (int i=0; i<s0; i++) {
    for (int j=0; j<s1; j++) {
      for (int k=0; k<s2; k++) {
        u[gamma(i,j,k)] =
        u[gamma(i,j,k)] + c4 * (c3 * (c1 *
        v[gamma((mod(i-1,s0)),j,k)] +
        v[gamma((mod(i+1,s0)),j,k)] +
        v[gamma(i,(mod(j-1,s1)),k)] +
        v[gamma(i,(mod(j+1,s1)),k)] +
        v[gamma(i,j,(mod(k-1,s2)))] +
        v[gamma(i,j,(mod(k+1,s2)))]) -
        3 * c2 * u[gamma(i,j,k)] - c0 *
        ((v[gamma((mod(i+1,s0)),j,k)] -
        v[gamma((mod(i-1,s0)),j,k)]) *
        u0[gamma(i,j,k)] +
        (v[gamma(i,(mod(j+1,s1)),k)] -
        v[gamma(i,(mod(j-1,s1)),k)]) *
        u1[gamma(i,j,k)] +
        (v[gamma(i,j,(mod(k+1,s2)))] -
        v[gamma(i,j,(mod(k-1,s2)))]) *
        u2[gamma(i,j,k)]));
      }
    }
  }
}

int main() {
  SC_NO_PADDING();
}
