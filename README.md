
# RcppUUID

[![CI](https://github.com/eddelbuettel/rcppuuid/workflows/ci/badge.svg)](https://github.com/eddelbuettel/rcppuuid/actions?query=workflow%3Aci)
[![License: GPL v2](https://img.shields.io/badge/License-GPL%20v2-blue.svg)](https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html)
[![CRAN Status](https://www.r-pkg.org/badges/version/RcppUUID)](https://cran.r-project.org/package=RcppUUID)
[![r-universe](https://eddelbuettel.r-universe.dev/badges/RcppUUID)](https://eddelbuettel.r-universe.dev/rcppuuid)
[![Dependencies](https://tinyverse.netlify.app/badge/RcppUUID)](https://cran.r-project.org/package=RcppUUID)
[![Downloads](https://cranlogs.r-pkg.org/badges/RcppUUID?color=brightgreen)](https://www.r-pkg.org:443/pkg/RcppUUID)
[![Last Commit](https://img.shields.io/github/last-commit/eddelbuettel/rcppuuid)](https://github.com/eddelbuettel/rcppuuid)

R package to generate Universally Unique Identifiers (UUIDs) version 4
and 5 using the Boost C++ library.

## Installation

To install the package from the CRAN run the following command:

``` r
install.packages("RcppUUID", repos = "https://cloud.r-project.org/")
```

Also you could install the dev-version with the `install_github()`
function from the `remotes` package:

``` r
remotes::install_github("eddelbuettel/rcppuuid")
```

This package contains the compiled code, therefore you have to use the
[Rtools](https://cran.r-project.org/bin/windows/Rtools/) to install it
on Windows.

## Usage

### Generate version 4 UUIDs

Generate single UUID:

``` r
RcppUUID::uuid_generate_random()
#> [1] "95a0b90b-46bc-4e16-b41e-cb04bb53aa71"
```

Generate multiple UUIDs:

``` r
RcppUUID::uuid_generate_random(5)
#> [1] "2d5caacd-7123-4072-b66f-74874f0424d9" "3c4f1e13-50af-46ab-a32a-f17cb1842875" "b0c0075d-f1fb-476c-9d27-0dd07c63ddef"
#> [4] "e6992ca8-7b32-45ab-9fa2-e11690c11c35" "4d9fce08-a71d-402f-9fa5-9e38fa136abb"
```

Check uniques for the uuids:

``` r
unique_n <- function(x) length(unique(x))
n <- 1000000
unique_n(RcppUUID::uuid_generate_random(n)) == n
#> [1] TRUE
```

Benchmarking:

Single UUID:

``` r
microbenchmark::microbenchmark(
  uuid = uuid::UUIDgenerate(FALSE),
  RcppUUID = RcppUUID::uuid_generate_random()
)
#> Unit: microseconds
#>      expr  min    lq     mean median   uq      max neval
#>      uuid 3.05 3.165 19.24921   3.28 3.36 1594.021   100
#>  RcppUUID 2.04 2.075  2.36520   2.11 2.20   20.280   100
```

Multiple UUIDs:

``` r
n <- 10000
microbenchmark::microbenchmark(
  uuid = uuid::UUIDgenerate(FALSE, n),
  RcppUUID = RcppUUID::uuid_generate_random(n)
)
#> Unit: milliseconds
#>      expr      min       lq     mean   median       uq      max neval
#>      uuid 25.47780 25.98014 29.13786 26.07774 26.19531 199.5827   100
#>  RcppUUID 12.76133 13.05205 17.27462 13.46904 13.69007 203.0705   100
```

### Generate version 5 UUIDs

Generate version UUIDs based on the text input:

``` r
RcppUUID::uuid_generate_name(letters[1:5])
#> [1] "54a0a790-c611-5b5b-b50e-ff01490ecdfa" "d5080e36-1ba4-5cb3-861c-34b25868f7db" "33ed51b6-a330-5830-bda9-2bac09e15753"
#> [4] "b74b2afe-06d5-5fea-99cc-a7de0b492704" "8535136c-b0d3-5373-aa79-ab67d33a2a8e"
```

For the each unique input will be generated unique UUID. Check
uniqueness:

``` r
uuids <- replicate(10, RcppUUID::uuid_generate_name(letters))
length(unique(as.vector(uuids))) == length(letters)
#> [1] TRUE
```

### Validate UUIDs

``` r
RcppUUID::uuid_validate(NA_character_)
#> [1] FALSE
RcppUUID::uuid_validate("")
#> [1] FALSE
RcppUUID::uuid_validate("not uuid")
#> [1] FALSE
RcppUUID::uuid_validate(RcppUUID::uuid_generate_random(5))
#> [1] TRUE TRUE TRUE TRUE TRUE
RcppUUID::uuid_validate(RcppUUID::uuid_generate_nil(5))
#> [1] TRUE TRUE TRUE TRUE TRUE
RcppUUID::uuid_validate(RcppUUID::uuid_generate_name(letters[1:5]))
#> [1] TRUE TRUE TRUE TRUE TRUE
```

## Bug reports

Use the following command to go to the page for bug report submissions:

``` r
bug.report(package = "RcppUUID")
```

Before reporting a bug or submitting an issue, please do the following:

-   Make sure that you error or issue was not reported or discussed
    earlier. Please, use the search;
-   Check the news list of the current version. Some errors could be
    caused by the package changes. It could be done with
    `news(package = "RcppUUID", Version == packageVersion("RcppUUID"))`
    command;
-   Make a minimal reproducible example of the code that consistently
    causes the error;
-   Make sure that the error occurs during the execution of a function
    from the `RcppUUID` package, not from other packages;
-   Try to reproduce the error with the last development version of the
    package from the git repository.

Please attach traceback() and sessionInfo() output to bug report. It may
save a lot of time.

## License

The `RcppUUID` package is distributed under
[GPLv2](http://www.gnu.org/licenses/gpl-2.0.html) license.

## Author

The package was written by [Artem Klevtsov](https://github.com/artemklevtsov)
and maintained in [this GitLab
repo](https://gitlab.com/artemklevtsov/rcppuuid).

The package in this repository is now maintained by [Dirk
Eddelbuettel](https://github.com/eddelbuettel). 
