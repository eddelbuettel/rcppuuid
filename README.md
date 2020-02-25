
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

R package to generate Universally Unique Identifiers (UUIDs).

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

Generate single UUID:

``` r
RcppUUID::uuid_generate_random(1)
#> [1] "94f99d02-9aef-4235-941f-733ba4c2e114"
```

Generate multiple UUIDs:

``` r
RcppUUID::uuid_generate_random(5)
#> [1] "d7fcfd4a-6b3b-4c63-8086-815967264b7f" "145ca48d-013c-46f2-a0d4-23ef0b9a819a" "4a14d8de-c452-48ba-adc4-7495a389b061"
#> [4] "61176f2b-58e7-4b88-af48-7e3f00ab7ac3" "6d42e8b6-1e9b-4908-8689-bdd338050359"
```

Check uniques:

``` r
n <- 1000000
length(unique(RcppUUID::uuid_generate_random(n))) == n
#> [1] TRUE
```

## Benchmarking

Single UUID:

``` r
microbenchmark::microbenchmark(
  uuid = uuid::UUIDgenerate(FALSE),
  RcppUUID = RcppUUID::uuid_generate_random(1)
)
#> Unit: microseconds
#>      expr    min      lq     mean  median     uq      max neval cld
#>      uuid 15.080 15.8810 36.09674 16.2625 16.635 1994.061   100   a
#>  RcppUUID  8.394  9.1435 13.11459  9.8820 10.487  228.525   100   a
```

Multiple UUIDs:

``` r
n <- 10000
microbenchmark::microbenchmark(
  uuid = replicate(n, uuid::UUIDgenerate(FALSE)),
  RcppUUID = RcppUUID::uuid_generate_random(n)
)
#> Unit: milliseconds
#>      expr        min         lq       mean     median         uq       max neval cld
#>      uuid 174.885527 183.911932 203.315408 191.169173 214.918204 361.96847   100   b
#>  RcppUUID   5.181347   5.462485   6.749716   5.752187   6.438479  36.75441   100  a
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
