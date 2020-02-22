
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

R package to generate Universally Unique Identifiers (UUIDs) version 4.
Based on the [sole](https://github.com/r-lyeh-archived/sole) C++
library.

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
RcppUUID::uuid_generate(1)
#> [1] "1700a888-a7c5-4dd4-9aad-a98128279f87"
```

Generate multiple UUIDs:

``` r
RcppUUID::uuid_generate(5)
#> [1] "04c01dc0-299d-461e-9b56-2f881376f445"
#> [2] "b18beaf4-b27c-4fed-a93c-08f80feb1fcf"
#> [3] "29e2778d-7b5b-4128-9184-3865953c69f0"
#> [4] "818d0636-d854-44a3-ab43-6fb9bbb60e40"
#> [5] "a09697a7-5cc5-41b3-86b3-07ba50bf8cd3"
```

Check uniques:

``` r
n <- 1000000
length(unique(RcppUUID::uuid_generate(n))) == n
#> [1] TRUE
```

## Benchmarking

Single UUID:

``` r
microbenchmark::microbenchmark(
  uuid = uuid::UUIDgenerate(FALSE),
  RcppUUID = RcppUUID::uuid_generate(1)
)
#> Unit: microseconds
#>      expr    min     lq      mean  median      uq      max neval cld
#>      uuid 15.221 16.270  59.07903 17.5115 18.4200 4167.623   100   a
#>  RcppUUID 13.318 44.686 163.90026 65.0965 95.2315 6306.544   100   a
```

Multiple UUIDs:

``` r
n <- 10000
microbenchmark::microbenchmark(
  uuid = replicate(n, uuid::UUIDgenerate(FALSE)),
  RcppUUID = RcppUUID::uuid_generate(n)
)
#> Unit: milliseconds
#>      expr       min        lq      mean    median        uq       max neval cld
#>      uuid 179.76032 200.29648 225.46853 215.11818 237.76798 410.55628   100   b
#>  RcppUUID  17.10199  19.23641  21.17651  20.07005  21.28216  42.02892   100  a
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
