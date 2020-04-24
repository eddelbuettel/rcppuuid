#include "wrap.h"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/random_generator.hpp>
#include <Rcpp.h>

using namespace Rcpp;
using namespace boost;
using boost::uuids::uuid;

//' @title Generate UUIDs Version 4
//'
//' @description
//' Function generates uuids using operating system provided entropy.
//'
//' @param n Number of generated UUIDs.
//' @return Character vector with UUIDs.
//'
//' @export
//'
//' @references
//' <https://www.boost.org/doc/libs/1_72_0/libs/uuid/doc/uuid.html#Random%20Generator>
//'
//' @examples
//' # generate random UUIDs
//' uuid_generate_random(2)
//'
// [[Rcpp::export(rng=false)]]
StringVector uuid_generate_random(size_t n = 1)  {
  std::vector<uuid> res(n);
  std::generate(res.begin(), res.end(), uuids::random_generator());
  return wrap(res);
}
