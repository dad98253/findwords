
LOCALES = es ms en
PO_FILES = $(foreach loc,$(LOCALES),$(loc).po)
MO_FILES = $(PO_FILES:.po=.gmo)

all: $(MO_FILES)

%.gmo: %.po
	msgfmt -o $@ $<

#update_po:
#	xgettext -o locales/messages.pot --keyword=gettext --language=gcc *.c
#	$(foreach po,$(PO_FILES),msgmerge --update $(po) locales/messages.pot;)

clean:
	rm -f *.gmo

#.PHONY: all update_po clean
.PHONY: all clean
