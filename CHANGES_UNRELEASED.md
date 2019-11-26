**See [the release process docs](docs/howtos/cut-a-new-release.md) for the steps to take when cutting a new release.**

# Unreleased Changes

## FxA Client

### What's Fixed

* Android: `migrateFromSessionToken` now accepts an `inPlaceMigration` migration option.
    When `inPlaceMigration` is true then the provided 'sessionToken' will be migrated instead of creating a new session token.


[Full Changelog](https://github.com/mozilla/application-services/compare/v0.44.0...master)
