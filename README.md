
<!-- README.md is generated from README.Rmd. Please edit that file -->

# RcppUUID

<!-- badges: start -->

[![GitLab CI Build
Status](https://gitlab.com/artemklevtsov/rcppuuid/badges/master/pipeline.svg)](https://gitlab.com/artemklevtsov/rcppuuid/pipelines)
[![AppVeyor Build
status](https://ci.appveyor.com/api/projects/status/if9qot73i61ts59y?svg=true)](https://ci.appveyor.com/project/artemklevtsov/rcppuuid)
[![Codecov Code
Coverage](https://codecov.io/gl/artemklevtsov/rcppuuid/branch/master/graph/badge.svg)](https://codecov.io/gl/artemklevtsov/rcppuuid)
[![CRAN
Status](http://www.r-pkg.org/badges/version/RcppUUID)](https://cran.r-project.org/package=RcppUUID)
[![License: GPL
v2](https://img.shields.io/badge/License-GPL%20v2-blue.svg)](https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html)

<!-- badges: end -->

R package to generate Universally Unique Identifiers (UUIDs) version 4
and 5.

## Installation

To install the package from the CRAN run the following command:

``` r
install.packages("RcppUUID", repos = "https://cloud.r-project.org/")
```

Also you could install the dev-version with the `install_gitlab()`
function from the `remotes` package:

``` r
remotes::install_gitlab("artemklevtsov/rcppuuid")
```

This package contains the compiled code, therefore you have to use the
[Rtools](https://cran.r-project.org/bin/windows/Rtools/) to install it
on Windows.

## Usage

### Generate version 4 UUIDs

Generate single UUID:

``` r
RcppUUID::uuid_generate_random(1)
#> [1] "ca141f08-f799-4a7c-8468-c8360660b029"
```

Generate multiple UUIDs:

``` r
RcppUUID::uuid_generate_random(5)
#> [1] "1a4959ea-9790-4004-b0ce-adeaa3b66199" "ec42102d-49a8-4c38-9c75-e7f8af651d74" "ef8b350e-5bf4-4bf5-b0da-397b617498d9"
#> [4] "89eb3374-21ec-4a8c-b731-0fa2542bd58a" "c0fe4663-1e10-44d3-92ce-d72cdb51db2c"
```

Check uniques:

``` r
n <- 1000000
length(unique(RcppUUID::uuid_generate_random(n))) == n
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
#>      expr    min      lq     mean  median      uq      max neval cld
#>      uuid 14.278 14.9105 33.79106 15.1435 15.4240 1852.201   100   a
#>  RcppUUID  7.129  7.6680  8.72125  8.3140  8.7985   41.344   100   a
```

Multiple UUIDs:

``` r
n <- 10000
microbenchmark::microbenchmark(
  uuid = uuid::UUIDgenerate(FALSE, n),
  RcppUUID = RcppUUID::uuid_generate_random(n)
)
#> Unit: milliseconds
#>      expr       min        lq     mean    median        uq      max neval cld
#>      uuid 72.080692 73.009557 76.87999 73.463078 73.671392 284.4107   100   b
#>  RcppUUID  7.554901  7.868102 11.07176  8.437234  9.014238 265.7360   100  a
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

  - Make sure that you error or issue was not reported or discussed
    earlier. Please, use the search;
  - Check the news list of the current version. Some errors could be
    caused by the package changes. It could be done with `news(package =
    "RcppUUID", Version == packageVersion("RcppUUID"))` command;
  - Make a minimal reproducible example of the code that consistently
    causes the error;
  - Make sure that the error occurs during the execution of a function
    from the `RcppUUID` package, not from other packages;
  - Try to reproduce the error with the last development version of the
    package from the git repository.

Please attach traceback() and sessionInfo() output to bug report. It may
save a lot of time.

## License

The `RcppUUID` package is distributed under
[GPLv2](http://www.gnu.org/licenses/gpl-2.0.html) license.
