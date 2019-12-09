**See [the release process docs](docs/howtos/cut-a-new-release.md) for the steps to take when cutting a new release.**

# Unreleased Changes

## Places

### What's new

- Added and exposed `storage::history::get_visit_page_with_bound`, which performs
  faster visit paging by first skipping directly to a `bound` timestamp and then
  skipping over `offset` items from `bound`, through FFI. ([#1019](https://github.com/mozilla/application-services/issues/1019))

[Full Changelog](https://github.com/mozilla/application-services/compare/v0.44.0...master)

## Push

### Breaking Changes

- `PushManager.decrypt` will now throw a `RecordNotFoundError` exception instead of `StorageError` if a matching subscription could not be found. ([#2355](https://github.com/mozilla/application-services/pull/2355))

## FxA Client

### What's new

- `FirefoxAccount.checkAuthorizationStatus` will check the status of the currently stored refresh token. ([#2332](https://github.com/mozilla/application-services/pull/2332))

## Logins

### Breaking Changes

- Login records with a `httpRealm` attribute will now have their `usernameField` and `passwordField`
  properties silently cleared, to help ensure data consistency. ([#2158](https://github.com/mozilla/application-services/pull/2158))
- The Android bindings now collect some basic performance and quality metrics via Glean.
  Applications that submit telemetry via Glean must request a data review for these metrics
  before integrating the logins component. See the component README.md for more details.
  ([#2225](https://github.com/mozilla/application-services/pull/2225))

### What's new

- Added invalid character checks from Desktop to `LoginsStorage.ensureValid` and introduced `INVALID_LOGIN_ILLEGAL_FIELD_VALUE` error. ([#2262](https://github.com/mozilla/application-services/pull/2262))

## Sync Manager

### Breaking Changes

- When asked to sync all engines, SyncManager will now sync all engines for which a handle has been set.
  Previously it would sync all known engines, panicking if a handle had not been set for some engine.
  While *technically* a breaking change, we expect that the new behaviour is almost certainly what
  consuming applications actually want in practice. ([#2313](https://github.com/mozilla/application-services/pull/2313))
