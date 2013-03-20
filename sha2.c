/* sha256.c
 *
 * The sha256 hash function.
 *
 * See http://csrc.nist.gov/publications/fips/fips180-2/fips180-2.pdf
 */

/* nettle, low-level cryptographics library
 *
 * Copyright (C) 2001 Niels Möller
 *
 * The nettle library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or (at your
 * option) any later version.
 *
 * The nettle library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
 * License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with the nettle library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02111-1301, USA.
 */

/* Modelled after the sha1.c code by Peter Gutmann. */

#if HAVE_CONFIG_H
# include "config.h"
#endif

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "sha2.h"

#define WRITE_UINT32(p, i)      \
do {            \
  (p)[0] = ((i) >> 24) & 0xff;      \
  (p)[1] = ((i) >> 16) & 0xff;      \
  (p)[2] = ((i) >> 8) & 0xff;     \
  (p)[3] = (i) & 0xff;        \
} while(0)

#define MD_INCR(ctx) ((ctx)->count_high += !++(ctx)->count_low)

/* Takes the compression function f as argument. NOTE: also clobbers
   length and data. */
#define MD_UPDATE(ctx, length, data, f, incr)       \
  do {                  \
    if ((ctx)->index)             \
      {                 \
  /* Try to fill partial block */         \
  unsigned __md_left = sizeof((ctx)->block) - (ctx)->index; \
  if ((length) < __md_left)         \
    {               \
      memcpy((ctx)->block + (ctx)->index, (data), (length));  \
      (ctx)->index += (length);         \
      goto __md_done; /* Finished */        \
    }               \
  else                \
    {               \
      memcpy((ctx)->block + (ctx)->index, (data), __md_left); \
                  \
      f((ctx), (ctx)->block);         \
      (incr);             \
                  \
      (data) += __md_left;          \
      (length) -= __md_left;          \
    }               \
      }                 \
    while ((length) >= sizeof((ctx)->block))        \
      {                 \
  f((ctx), (data));           \
  (incr);               \
                  \
  (data) += sizeof((ctx)->block);         \
  (length) -= sizeof((ctx)->block);       \
      }                 \
    memcpy ((ctx)->block, (data), (length));        \
    (ctx)->index = (length);            \
  __md_done:                \
    ;                 \
  } while (0)

/* Pads the block to a block boundary with the bit pattern 1 0*,
   leaving size octets for the length field at the end. If needed,
   compresses the block and starts a new one. */
#define MD_PAD(ctx, size, f)            \
  do {                  \
    unsigned __md_i;              \
    __md_i = (ctx)->index;            \
                  \
    /* Set the first char of padding to 0x80. This is safe since there  \
       is always at least one byte free */        \
                  \
    assert(__md_i < sizeof((ctx)->block));          \
    (ctx)->block[__md_i++] = 0x80;            \
                  \
    if (__md_i > (sizeof((ctx)->block) - 2*sizeof((ctx)->count_low))) \
      { /* No room for length in this block. Process it and   \
     pad with another one */          \
  memset((ctx)->block + __md_i, 0, sizeof((ctx)->block) - __md_i); \
                  \
  f((ctx), (ctx)->block);           \
  __md_i = 0;             \
      }                 \
    memset((ctx)->block + __md_i, 0,          \
     sizeof((ctx)->block) - (size) - __md_i);     \
                      \
  } while (0)

void
_nettle_write_be32(unsigned length, uint8_t *dst,
       uint32_t *src)
{
  unsigned i;
  unsigned words;
  unsigned leftover;

  words = length / 4;
  leftover = length % 4;

  for (i = 0; i < words; i++, dst += 4)
    WRITE_UINT32(dst, src[i]);

  if (leftover)
    {
      uint32_t word;
      unsigned j = leftover;

      word = src[i];

      switch (leftover)
  {
  default:
    abort();
  case 3:
    dst[--j] = (word >> 8) & 0xff;
    /* Fall through */
  case 2:
    dst[--j] = (word >> 16) & 0xff;
    /* Fall through */
  case 1:
    dst[--j] = (word >> 24) & 0xff;
  }
    }
}

/* Generated by the shadata program. */
static const uint32_t
K[64] =
{
  0x428a2f98UL, 0x71374491UL, 0xb5c0fbcfUL, 0xe9b5dba5UL,
  0x3956c25bUL, 0x59f111f1UL, 0x923f82a4UL, 0xab1c5ed5UL,
  0xd807aa98UL, 0x12835b01UL, 0x243185beUL, 0x550c7dc3UL,
  0x72be5d74UL, 0x80deb1feUL, 0x9bdc06a7UL, 0xc19bf174UL,
  0xe49b69c1UL, 0xefbe4786UL, 0xfc19dc6UL, 0x240ca1ccUL,
  0x2de92c6fUL, 0x4a7484aaUL, 0x5cb0a9dcUL, 0x76f988daUL,
  0x983e5152UL, 0xa831c66dUL, 0xb00327c8UL, 0xbf597fc7UL,
  0xc6e00bf3UL, 0xd5a79147UL, 0x6ca6351UL, 0x14292967UL,
  0x27b70a85UL, 0x2e1b2138UL, 0x4d2c6dfcUL, 0x53380d13UL,
  0x650a7354UL, 0x766a0abbUL, 0x81c2c92eUL, 0x92722c85UL,
  0xa2bfe8a1UL, 0xa81a664bUL, 0xc24b8b70UL, 0xc76c51a3UL,
  0xd192e819UL, 0xd6990624UL, 0xf40e3585UL, 0x106aa070UL,
  0x19a4c116UL, 0x1e376c08UL, 0x2748774cUL, 0x34b0bcb5UL,
  0x391c0cb3UL, 0x4ed8aa4aUL, 0x5b9cca4fUL, 0x682e6ff3UL,
  0x748f82eeUL, 0x78a5636fUL, 0x84c87814UL, 0x8cc70208UL,
  0x90befffaUL, 0xa4506cebUL, 0xbef9a3f7UL, 0xc67178f2UL,
};

#define COMPRESS(ctx, data) (_nettle_sha256_compress((ctx)->state, (data), K))

/* Initialize the SHA values */

void
sha256_init(struct sha256_ctx *ctx)
{
  /* Initial values, also generated by the shadata program. */
  static const uint32_t H0[_SHA256_DIGEST_LENGTH] =
  {
    0x6a09e667UL, 0xbb67ae85UL, 0x3c6ef372UL, 0xa54ff53aUL,
    0x510e527fUL, 0x9b05688cUL, 0x1f83d9abUL, 0x5be0cd19UL,
  };

  memcpy(ctx->state, H0, sizeof(H0));

  /* Initialize bit count */
  ctx->count_low = ctx->count_high = 0;

  /* Initialize buffer */
  ctx->index = 0;
}

void
sha256_update(struct sha256_ctx *ctx,
	      unsigned length, const uint8_t *data)
{
  MD_UPDATE (ctx, length, data, COMPRESS, MD_INCR(ctx));
}

static void
sha256_write_digest(struct sha256_ctx *ctx,
		    unsigned length,
		    uint8_t *digest)
{
  uint32_t high, low;

  assert(length <= SHA256_DIGEST_SIZE);

  MD_PAD(ctx, 8, COMPRESS);

  /* There are 512 = 2^9 bits in one block */
  high = (ctx->count_high << 9) | (ctx->count_low >> 23);
  low = (ctx->count_low << 9) | (ctx->index << 3);

  /* This is slightly inefficient, as the numbers are converted to
     big-endian format, and will be converted back by the compression
     function. It's probably not worth the effort to fix this. */
  WRITE_UINT32(ctx->block + (SHA256_DATA_SIZE - 8), high);
  WRITE_UINT32(ctx->block + (SHA256_DATA_SIZE - 4), low);
  COMPRESS(ctx, ctx->block);

  _nettle_write_be32(length, digest, ctx->state);
}

void
sha256_digest(struct sha256_ctx *ctx,
	      unsigned length,
	      uint8_t *digest)
{
  sha256_write_digest(ctx, length, digest);
  sha256_init(ctx);
}
