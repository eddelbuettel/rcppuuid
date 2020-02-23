
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
#> [1] "3037a109-1f65-4f34-ac60-69730596442d"
```

Generate multiple UUIDs:

``` r
RcppUUID::uuid_generate(5)
#> [1] "7fc1fbfb-b050-4a5d-acfc-c03094c7f131"
#> [2] "af7c0750-dc5d-410b-867a-38c66218ceaf"
#> [3] "b37fedc9-3af5-444b-9ad8-b188cceb6e60"
#> [4] "1a68b7e7-c110-4c8b-9e45-3c9029e37ac8"
#> [5] "579dc2f1-8c38-4b9a-ba0a-e28427d6e184"
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
#>      expr    min      lq      mean  median      uq      max neval cld
#>      uuid 15.323 16.1925  39.53524 17.6065 18.4155 2198.415   100   a
#>  RcppUUID 48.332 52.5675 130.83716 60.1960 72.5415 6177.065   100   a
```

Multiple UUIDs:

``` r
n <- 10000
microbenchmark::microbenchmark(
  uuid = replicate(n, uuid::UUIDgenerate(FALSE)),
  RcppUUID = RcppUUID::uuid_generate(n)
)
#> Unit: milliseconds
#>      expr       min        lq      mean    median       uq       max neval cld
#>      uuid 180.05588 194.97129 229.71894 217.38809 243.4737 432.34116   100   b
#>  RcppUUID  47.21502  48.92965  52.58226  50.83771  54.1418  80.33077   100  a
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
