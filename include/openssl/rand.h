/*
 * Copyright 1995-2016 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the OpenSSL license (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#ifndef HEADER_RAND_H
# define HEADER_RAND_H

# include <stdlib.h>
# include <openssl/ossl_typ.h>
# include <openssl/e_os2.h>

# if defined(OPENSSL_SYS_WINDOWS)
#  include <windows.h>
# endif

#ifdef  __cplusplus
extern "C" {
#endif

/* Already defined in ossl_typ.h */
/* typedef struct rand_meth_st RAND_METHOD; */

struct rand_meth_st {
    int (*seed) (const void *buf, int num);
    int (*bytes) (unsigned char *buf, int num);
    void (*cleanup) (void);
    int (*add) (const void *buf, int num, double entropy);
    int (*pseudorand) (unsigned char *buf, int num);
    int (*status) (void);
};

# ifdef BN_DEBUG
extern int rand_predictable;
# endif

int RAND_set_rand_method(const RAND_METHOD *meth);
const RAND_METHOD *RAND_get_rand_method(void);
# ifndef OPENSSL_NO_ENGINE
int RAND_set_rand_engine(ENGINE *engine);
# endif
RAND_METHOD *RAND_OpenSSL(void);
#if OPENSSL_API_COMPAT < 0x10100000L
# define RAND_cleanup() while(0) continue
#endif
int RAND_bytes(unsigned char *buf, int num);
DEPRECATEDIN_1_1_0(int RAND_pseudo_bytes(unsigned char *buf, int num))
void RAND_seed(const void *buf, int num);
#if defined(__ANDROID__) && defined(__NDK_FPABI__)
__NDK_FPABI__	/* __attribute__((pcs("aapcs"))) on ARM */
#endif
void RAND_add(const void *buf, int num, double entropy);
int RAND_load_file(const char *file, long max_bytes);
int RAND_write_file(const char *file);
const char *RAND_file_name(char *file, size_t num);
int RAND_status(void);
# ifndef OPENSSL_NO_EGD
int RAND_query_egd_bytes(const char *path, unsigned char *buf, int bytes);
int RAND_egd(const char *path);
int RAND_egd_bytes(const char *path, int bytes);
# endif
int RAND_poll(void);

#if defined(OPENSSL_SYS_WINDOWS) || defined(OPENSSL_SYS_WIN32)
DEPRECATEDIN_1_1_0(void RAND_screen(void))
DEPRECATEDIN_1_1_0(int RAND_event(UINT, WPARAM, LPARAM))
#endif

/* BEGIN ERROR CODES */
/*
 * The following lines are auto generated by the script mkerr.pl. Any changes
 * made after this point may be overwritten when the script is next run.
 */
void ERR_load_RAND_strings(void);

/* Error codes for the RAND functions. */

/* Function codes. */
# define RAND_F_FIPS_RAND                                 102
# define RAND_F_FIPS_RAND_SET_DT                          103
# define RAND_F_FIPS_SET_PRNG_SEED                        104
# define RAND_F_FIPS_SET_TEST_MODE                        105
# define RAND_F_FIPS_X931_SET_DT                          106
# define RAND_F_RAND_BYTES                                100
# define RAND_F_RAND_GET_RAND_METHOD                      101

/* Reason codes. */
# define RAND_R_NOT_IN_TEST_MODE                          101
# define RAND_R_NO_KEY_SET                                102
# define RAND_R_PRNG_ERROR                                103
# define RAND_R_PRNG_KEYED                                104
# define RAND_R_PRNG_NOT_SEEDED                           100
# define RAND_R_PRNG_SEED_MUST_NOT_MATCH_KEY              105
# define RAND_R_PRNG_STUCK                                106

#ifdef  __cplusplus
}
#endif
#endif
