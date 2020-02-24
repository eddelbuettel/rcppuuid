
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
Library use the platform specific implementation or random device
instead.

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

To use random device instead platofrm specific implementation you can
use the `--with-random-device` configure argument when install package
from source.

## Usage

Generate single UUID:

``` r
RcppUUID::uuid_generate(1)
#> [1] "79fab637-72d1-419d-b21b-b36bd393d107"
```

Generate multiple UUIDs:

``` r
RcppUUID::uuid_generate(5)
#> [1] "3a2f9da7-a8f7-4b57-9219-96fdf9e7638e"
#> [2] "a222fbc7-739f-42f5-a1e2-3fc91f453fb9"
#> [3] "270058cd-0760-4862-ab2b-24340f32cc68"
#> [4] "1e51723c-5be7-4f8c-b7b9-a9a4b1c204b8"
#> [5] "6129660a-1f3f-4b36-b707-86243ef2f611"
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
#>      expr    min      lq     mean  median      uq      max neval cld
#>      uuid 15.224 16.2105 36.42521 17.2045 17.7045 1960.891   100   a
#>  RcppUUID 16.198 16.9845 21.05792 17.2740 17.6950   94.395   100   a
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
#>      uuid 179.87545 201.20595 232.13646 222.35388 244.32753 467.21675   100   b
#>  RcppUUID  50.82422  52.87099  54.39368  53.94923  55.16014  68.06015   100  a
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
