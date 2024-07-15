TESTS = check_rank_utils check_remote_ref
check_PROGRAMS = check_rank_utils check_remote_ref
check_rank_utils_SOURCES = check_rank_utils.c $(top_builddir)/src/rank_utils.c 
check_remote_ref_SOURCES = check_remote_ref.c $(top_builddir)/src/remote_ref.c 
AM_CFLAGS = @CHECK_CFLAGS@
AM_LDFLAGS = @CHECK_LIBS@
check_remote_ref_LDADD = -lm
