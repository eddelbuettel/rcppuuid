#include <Rcpp.h>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

using namespace Rcpp;

//' @rdname uuid
//' @export
// [[Rcpp::export(rng=false)]]
std::vector<std::string> uuid_generate_random(size_t n = 1)  {
  std::vector<std::string> res(n);
  boost::uuids::random_generator gen;
  #pragma omp parallel for
  for (size_t i = 0; i < n; ++i) {
    boost::uuids::uuid id = gen();
    res[i] = to_string(id);
  }
  return res;
}


//' @rdname uuid
//' @export
// [[Rcpp::export(rng=false)]]
std::vector<std::string> uuid_generate_nil(size_t n = 1)  {
  boost::uuids::nil_generator gen;
  boost::uuids::uuid id = gen();
  std::string val = to_string(id);
  std::vector<std::string> res(n);
  #pragma omp parallel for
  for (size_t i = 0; i < n; ++i) {
    res[i] = val;
  }
  return res;
}


//' @rdname uuid
//' @export
// [[Rcpp::export(rng=false)]]
std::vector<std::string> uuid_generate_name(const std::vector<std::string>& x)  {
  size_t n = x.size();
  std::vector<std::string> res(n);
  boost::uuids::name_generator_sha1 gen(boost::uuids::ns::x500dn());
  auto nil_uuid = boost::uuids::nil_generator()();
  #pragma omp parallel for
  for (size_t i = 0; i < n; ++i) {
    boost::uuids::uuid id = x[i].empty() ? nil_uuid : gen(x[i]);
    res[i] = to_string(id);
  }
  return res;
}


//' @rdname uuid
//' @export
// [[Rcpp::export(rng=false)]]
std::vector<bool> uuid_validate(const std::vector<std::string>& x) {
  size_t n = x.size();
  std::vector<bool> res(n);
  boost::uuids::string_generator gen;
  for (size_t i = 0; i < n; ++i) {
    if (x[i].empty()) {
      res[i] = false;
    } else {
      try {
        boost::uuids::uuid id = gen(x[i]);
        res[i] = id.is_nil() || id.version() != boost::uuids::uuid::version_unknown;
      } catch(...) {
        res[i] = false;
      }
    }
  }
  return res;
}
