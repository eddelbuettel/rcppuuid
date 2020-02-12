# regex pattern to validate
ptrn <- "[a-f0-9]{8}-?[a-f0-9]{4}-?4[a-f0-9]{3}-?[89ab][a-f0-9]{3}-?[a-f0-9]{12}"

expect_error(uuid_generate(NULL))
expect_error(uuid_generate(NA))
expect_equal(uuid_generate(0), character(0))
expect_true(is.character(uuid_generate(1)))
expect_true(grepl(ptrn, uuid_generate(1)))
expect_equal(length(uuid_generate(1)), 1)
expect_equal(length(uuid_generate(5)), 5)
expect_equal(length(unique(uuid_generate(100))), 100)
