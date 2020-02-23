#include <uuid.h>
#include <Rcpp.h>

//' @title
//' Generate a version 4 UUID
//'
//' @description
//' Function generates a set of Universally Unique Identifiers.
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
// [[Rcpp::export(rng=false)]]
std::vector<std::string> uuid_generate(size_t n = 1) {
  std::vector<std::string> res(n);
  #pragma omp parallel for
  for (size_t i = 0; i < n; ++i) {
    uuid id = uuid_generator{}();
    res[i] = to_string(id);
  }
  return res;
}
