#include "wrap.h"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/name_generator.hpp>
#include <Rcpp.h>

using namespace Rcpp;
using boost::uuids::name_generator_sha1;
using boost::uuids::ns::x500dn;
using boost::uuids::uuid;

uuid str2ns(const std::string& ns) {
  if (ns == "dns") {
    return boost::uuids::ns::dns();
  } else if (ns == "url") {
    return boost::uuids::ns::url();
  } else if (ns == "oid") {
    return boost::uuids::ns::oid();
  } else if (ns == "x500dn") {
    return boost::uuids::ns::x500dn();
  } else {
    stop("Unsupported namespace");
  }
}

//' @title Generate UUIDs Version 5
//'
//' @description
//' Function generates name-based uuid is derived from content in a namespace.
//' A uuid with identical content shall yield the same uuid.
//' Hashing algorithm is SHA1.
//'
//' @param x Character vector.
//' @param ns Namespace string. Allowed values: dns, url, oid, x500dn.
//' @return Character vector with UUIDs.
//'
//' @note
//' This function generates valid uuids for the `NA` and empty strings.
//'
//' @export
//'
//' @references
//' <https://www.boost.org/doc/libs/1_72_0/libs/uuid/doc/uuid.html#Name%20Generator>
//'
//' @export
//'
//' @examples
//' # generate name UUIDs
//' uuid_generate_name(c("one", "two"))
//'
// [[Rcpp::export(rng=false)]]
StringVector uuid_generate_name(StringVector x, const std::string& ns = "x500dn")  {
  std::vector<uuid> res(x.size());
  name_generator_sha1 gen(str2ns(ns));
  std::transform(x.begin(), x.end(), res.begin(), gen);
  return wrap(res);
}
