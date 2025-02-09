AUTOMAKE_OPTIONS = foreign no-dependencies
dist_man1_MANS = permute.1

permute.1: permute.x $(top_builddir)/bin/permute
	$(HELP2MAN) --no-discard-stderr --include=permute.x $(top_builddir)/bin/permute -o $@-t
	chmod a=r $@-t
	mv -f $@-t $@


