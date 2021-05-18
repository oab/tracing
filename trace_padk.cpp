#include "common.h"

const int s0 = 16;
const int s1 = 16;
const int s2 = 16;
const int s2padded = s2 + 2;
const int size = s0*s1*s2padded;

int gamma_padded(int i, int j, int k) {
  return  i * s1 * s2padded + j * s2padded + k;
}

void SC_PADDING_K ()
{
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
      for (int k=1; k<s2+1; k++) {
        u[gamma_padded(i,j,k)] =
        u[gamma_padded(i,j,k)] + c4 * (c3 * (c1 *
        v[gamma_padded((mod(i-1,s0)),j,k)] +
        v[gamma_padded((mod(i+1,s0)),j,k)] +
        v[gamma_padded(i,(mod(j-1,s1)),k)] +
        v[gamma_padded(i,(mod(j+1,s1)),k)] +
        v[gamma_padded(i,j,k-1)] +
        v[gamma_padded(i,j,k+1)]) -
        3 * c2 * u[gamma_padded(i,j,k)] - c0 *
        ((v[gamma_padded((mod(i+1,s0)),j,k)] -
        v[gamma_padded((mod(i-1,s0)),j,k)]) *
        u0[gamma_padded(i,j,k)] +
        (v[gamma_padded(i,(mod(j+1,s1)),k)] -
        v[gamma_padded(i,(mod(j-1,s1)),k)]) *
        u1[gamma_padded(i,j,k)] +
        (v[gamma_padded(i,j,k+1)] -
        v[gamma_padded(i,j,k-1)]) *
        u2[gamma_padded(i,j,k)]));
      }
      // update the padding values
      u[gamma_padded(i,j,0)] = u[gamma_padded(i,j,s2)];
      u[gamma_padded(i,j,s2+1)] = u[gamma_padded(i,j,0)];
    }
  }
}

int main() {
  SC_PADDING_K();
}
