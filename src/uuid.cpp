#include <sole.hpp>
#include <Rcpp.h>

//' @title
//' Generate a version 4 UUID
//'
//' @description
//' Function generates a new Universally Unique Identifier.
//'
//' @param n Number of generated UUIDs.
//'
//' @return Character vector with UUIDs.
//'
//' @export
//'
//' @examples
//' uuid_generate(5)
//'
// [[Rcpp::export(rng = false)]]
Rcpp::StringVector uuid_generate(size_t n = 1) {
  std::vector<sole::uuid> uuids(n);
  std::generate(uuids.begin(), uuids.end(), sole::uuid4);
  Rcpp::StringVector res = Rcpp::no_init(n);
  std::transform(uuids.begin(), uuids.end(), res.begin(), [](const sole::uuid& x) { return x.str(); });
  return res;
}
