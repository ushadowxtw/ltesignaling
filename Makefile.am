bin_PROGRAMS = ltesignaling
ltesignaling_SOURCES = ltesignaling.c cryptnas.c SNOW_3G.c public.c eea2.c \
	ZUC.c eeaapi.c kdf.c hmac_sha2.c sha2.c aes.c

# set the include path found by configure
INCLUDES = $(all_includes)

# the library search path.
ltesignaling_LDFLAGS = $(all_libraries) 
noinst_HEADERS = cryptnas.h SNOW_3G.h public.h eea2.h ZUC.h eeaapi.h kdf.h \
	hmac_sha2.h sha2.h aes.h
ltesignaling_LDADD = -lz
