#define R_NO_REMAP
#include <Rinternals.h>
#include "utils.h"

void stop_bad_type(SEXP x, const char* expected, const char* what, const char* arg) {
  SEXP fn = Rf_lang3(Rf_install(":::"),
                     Rf_install("purrr"),
                     Rf_install("stop_bad_type"));

  SEXP call = Rf_lang5(PROTECT(fn),
                       PROTECT(sym_protect(x)),
                       PROTECT(Rf_mkString(expected)),
                       what ? PROTECT(Rf_mkString(what)) : R_NilValue,
                       arg ? PROTECT(Rf_mkString(arg)) : R_NilValue);

  PROTECT(call);

  SEXP node = CDR(CDR(CDR(call)));
  SET_TAG(node, Rf_install("what"));

  node = CDR(node);
  SET_TAG(node, Rf_install("arg"));

  Rf_eval(call, R_BaseEnv);
  Rf_error("Internal error: `stop_bad_type()` should have thrown earlier");
}

void stop_bad_element_type(SEXP x, int index, const char* expected, const char* arg) {
  SEXP fn = Rf_lang3(Rf_install(":::"),
                     Rf_install("purrr"),
                     Rf_install("stop_bad_element_type"));

  SEXP call = Rf_lang5(PROTECT(fn),
                       PROTECT(sym_protect(x)),
                       PROTECT(Rf_ScalarInteger(index)),
                       PROTECT(Rf_mkString(expected)),
                       arg ? PROTECT(Rf_mkString(arg)) : R_NilValue);

  PROTECT(call);
  SET_TAG(CDR(CDR(CDR(CDR(call)))), Rf_install("arg"));

  Rf_eval(call, R_BaseEnv);
  Rf_error("Internal error: `stop_bad_element_type()` should have thrown earlier");
}
