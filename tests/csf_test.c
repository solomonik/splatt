
#include "../src/csf.h"
#include "../src/sptensor.h"

#include "ctest/ctest.h"
#include "splatt_test.h"


CTEST_DATA(csf_alloc)
{
  sptensor_t * tt;
  double * opts;
};

CTEST_SETUP(csf_alloc)
{
  data->tt = tt_read(DATASET(med4.tns));
  data->opts = splatt_default_opts();
  data->opts[SPLATT_OPTION_NTHREADS] = 1;
  data->opts[SPLATT_OPTION_TILE] = SPLATT_NOTILE;
}

CTEST_TEARDOWN(csf_alloc)
{
  tt_free(data->tt);
  free(data->opts);
}

CTEST2(csf_alloc, fill)
{
  ctensor_t cs;
  ctensor_alloc(&cs, data->tt, data->opts);

  ASSERT_EQUAL(1, cs.ntiles);
  ASSERT_EQUAL(data->tt->nnz, cs.nnz);
  ASSERT_EQUAL(data->tt->nmodes, cs.nmodes);

  for(idx_t m=0; m < cs.nmodes; ++m) {
    ASSERT_EQUAL(data->tt->dims[m], cs.dims[m]);
    ASSERT_EQUAL(1, cs.tile_dims[m]);
  }

  ctensor_free(&cs);
}

