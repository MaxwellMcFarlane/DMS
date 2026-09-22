# Tools utility directory

This folder contains a small set of utility components used by the SCADA sample projects:

- `baseclass.h` / `baseclass.cpp`: a lightweight base type that provides a simple object ID counter.
- `config.h` / `config.cpp`: a small configuration helper that manages file presence checks, default values, and simple config persistence.
- `log.h` / `log.cpp`: a file logging helper that supports appending, truncating, flushing, and closing log streams.
- `main.cpp`: a small demo program that exercises the logging and configuration helpers.
- `macros.h`: a shared header with a tiny debug macro used by the utility classes.

## Notes

- The code is intentionally simple and meant for demonstration and prototyping.
- The directory is now easier to navigate because the shared behavior is centralized around the utility classes and the build entry point is kept in one place.
