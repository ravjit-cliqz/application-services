/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#pragma once

#include <stdint.h>

typedef enum Sync15PasswordsErrorCode {
    Sync15Passwords_OtherError       = -2,
    Sync15Passwords_UnexpectedPanic  = -1,
    Sync15Passwords_NoError          = 0,
    Sync15Passwords_AuthInvalidError = 1,
    Sync15Passwords_NoSuchRecord     = 2,
    Sync15Passwords_DuplicateGuid    = 3,
    Sync15Passwords_InvalidKeyError  = 4,
    Sync15Passwords_NetworkError     = 5,
    Sync15Passwords_InterruptedError = 6,

    Sync15Passwords_InvalidLogin_EmptyOrigin = 64 + 0,
    Sync15Passwords_InvalidLogin_EmptyPassword = 64 + 1,
    Sync15Passwords_InvalidLogin_DuplicateLogin = 64 + 2,
    Sync15Passwords_InvalidLogin_BothTargets = 64 + 3,
    Sync15Passwords_InvalidLogin_NoTarget = 64 + 4,
    Sync15Passwords_InvalidLogin_IllegalFieldValue = 64 + 5,

} Sync15PasswordsErrorCode;

typedef struct Sync15PasswordsError {
    Sync15PasswordsErrorCode code;
    char *_Nullable message;
} Sync15PasswordsError;

typedef uint64_t Sync15PasswordEngineHandle;

typedef struct Sync15PasswordsInterruptHandle Sync15PasswordsInterruptHandle;

uint64_t sync15_passwords_num_open_connections(Sync15PasswordsError *_Nonnull error_out);

Sync15PasswordEngineHandle sync15_passwords_state_new(char const *_Nonnull db_path,
                                                      char const *_Nonnull encryption_key,
                                                      Sync15PasswordsError *_Nonnull error_out);

Sync15PasswordEngineHandle sync15_passwords_state_new_with_hex_key(char const *_Nonnull db_path,
                                                                   uint8_t const *encryption_key_bytes,
                                                                   uint32_t encryption_key_len,
                                                                   Sync15PasswordsError *_Nonnull error_out);

void sync15_passwords_state_destroy(Sync15PasswordEngineHandle handle,
                                    Sync15PasswordsError *_Nonnull error_out);

char *_Nullable sync15_passwords_get_by_id(Sync15PasswordEngineHandle handle,
                                          char const *_Nonnull id,
                                          Sync15PasswordsError *_Nonnull error_out);

char *_Nullable sync15_passwords_get_by_hostname(Sync15PasswordEngineHandle handle,
                                          char const *_Nonnull hostname,
                                          Sync15PasswordsError *_Nonnull error_out);

char *_Nullable sync15_passwords_get_all(Sync15PasswordEngineHandle handle,
                                         Sync15PasswordsError *_Nonnull error_out);

char *_Nullable sync15_passwords_sync(Sync15PasswordEngineHandle handle,
                                      char const *_Nonnull key_id,
                                      char const *_Nonnull access_token,
                                      char const *_Nonnull sync_key,
                                      char const *_Nonnull token_server_url,
                                      Sync15PasswordsError *_Nonnull error);

void sync15_passwords_wipe(Sync15PasswordEngineHandle handle,
                           Sync15PasswordsError *_Nonnull error);

void sync15_passwords_wipe_local(Sync15PasswordEngineHandle handle,
                                 Sync15PasswordsError *_Nonnull error);

void sync15_passwords_disable_mem_security(Sync15PasswordEngineHandle handle,
                                           Sync15PasswordsError *_Nonnull error);

void sync15_passwords_reset(Sync15PasswordEngineHandle handle,
                            Sync15PasswordsError *_Nonnull error);

void sync15_passwords_touch(Sync15PasswordEngineHandle handle,
                            char const *_Nonnull id,
                            Sync15PasswordsError *_Nonnull error);

uint8_t sync15_passwords_delete(Sync15PasswordEngineHandle handle,
                                char const *_Nonnull id,
                                Sync15PasswordsError *_Nonnull error);

void sync15_passwords_check_valid(Sync15PasswordEngineHandle handle,
                                char const *_Nonnull record_json,
                                Sync15PasswordsError *_Nonnull error);

char *_Nullable sync15_passwords_add(Sync15PasswordEngineHandle handle,
                                     char const *_Nonnull json,
                                     Sync15PasswordsError *_Nonnull error);

void sync15_passwords_update(Sync15PasswordEngineHandle handle,
                             char const *_Nonnull json,
                             Sync15PasswordsError *_Nonnull error);

void sync15_passwords_destroy_string(char const *_Nonnull str);

Sync15PasswordsInterruptHandle *_Nullable
sync15_passwords_new_interrupt_handle(Sync15PasswordEngineHandle handle,
                                      Sync15PasswordsError *_Nonnull error);

void sync15_passwords_interrupt(Sync15PasswordsInterruptHandle *_Nonnull handle,
                                Sync15PasswordsError *_Nonnull error);

void sync15_passwords_interrupt_handle_destroy(Sync15PasswordsInterruptHandle *_Nonnull handle);
