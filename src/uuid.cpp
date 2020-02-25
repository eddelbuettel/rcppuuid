#include <Rcpp.h>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

using namespace Rcpp;
using namespace boost::uuids;

//' @rdname uuid_generate
//' @export
// [[Rcpp::export(rng=false)]]
std::vector<std::string> uuid_generate_random(size_t n = 1)  {
  std::vector<std::string> res(n);
  auto gen = random_generator();
  #pragma omp parallel for
  for (size_t i = 0; i < n; ++i) {
    uuid id = gen();
    res[i] = to_string(id);
  }
  return res;
}


//' @rdname uuid_generate
//' @export
// [[Rcpp::export(rng=false)]]
std::vector<std::string> uuid_generate_nil(size_t n = 1)  {
  auto gen = nil_generator();
  uuid id = gen();
  std::string val = to_string(id);
  std::vector<std::string> res(n);
#pragma omp parallel for
  for (size_t i = 0; i < n; ++i) {
    res[i] = val;
  }
  return res;
}


//' @rdname uuid_generate
//' @export
// [[Rcpp::export(rng=false)]]
std::vector<std::string> uuid_generate_name(const std::vector<std::string>& x)  {
  size_t n = x.size();
  std::vector<std::string> res(n);
  auto ns = ns::x500dn();
  auto gen = name_generator_sha1(ns);
#pragma omp parallel for
  for (size_t i = 0; i < n; ++i) {
    if (x[i].empty()) {
      res[i] = to_string(nil_generator()());
    } else {
      uuid id = gen(x[i]);
      res[i] = to_string(id);
    }
  }
  return res;
}
