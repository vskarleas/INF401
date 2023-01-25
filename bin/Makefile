
all: clean calculette  liens_et_prefixe  short_commands


clean:
	/bin/rm -rf `ls . | grep -v Makefile`

liens_et_prefixe:
	(cd ../SRC/liens_et_prefixe; ./link_bin_to_opt_gnu.sh)

short_commands:
	 (cd ../SRC/short_commands; ./do_install)

calculette:
	 (cd ../SRC/calculette; make ; make install)
