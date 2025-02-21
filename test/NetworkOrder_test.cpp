// -*- C++ -*-  Copyright (c) Microsoft Corporation; see license.txt
#include "libHh/NetworkOrder.h"

#include "libHh/Array.h"
#include "libHh/BinaryIO.h"
#include "libHh/FileIO.h"
#include "libHh/Matrix.h"
#include "libHh/Stat.h"
using namespace hh;

int main() {
  {
    string ter_grid = "NetworkOrder_test.inp";
    RFile fi(ter_grid);
    int gridx, gridy;
    float fx;
    read_binary_std(fi(), ArView(fx));
    gridx = int(fx);
    float fy;
    read_binary_std(fi(), ArView(fy));
    gridy = int(fy);
    SHOW(gridx, gridy);
    assertx(gridx >= 4 && gridy >= 4);
    Matrix<float> ggridf(gridx, gridy);
#if 1
    assertx(read_binary_std(fi(), ggridf.array_view()));
#else
    Array<float> arf(gridx);
    for_int(y, gridy) {
      fi().read(reinterpret_cast<char*>(arf.data()), gridx * sizeof(arf[0]));
      assertx(fi());
      for_int(x, gridx) {
        from_std(&arf[x]);
        ggridf[x][y] = arf[x];
      }
    }
#endif
    HH_RSTAT(Sgrid, ggridf);
  }
}
