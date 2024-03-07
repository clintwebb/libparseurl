## make file for libparseurl

all: libparseurl.so.1.0.1

ARGS=

MANPATH=/usr/share/man

# Need to be able to make 'man-pages' as well.  Not sure where to get the source for those... 


#	ar -r $@
#	ar -r $@ $^



libparseurl.o: parseurl.c parseurl.h
	gcc -c -fPIC parseurl.c -o $@ $(ARGS)

libparseurl.a: libparseurl.o
	@>$@
	@rm $@
	@ar rcs $@ $^

libparseurl.so.1.0.1: libparseurl.o
	gcc -shared -Wl,-soname,libparseurl.so.1 -o libparseurl.so.1.0.1 $^


lib-test: lib-test.c /usr/include/parseurl.h
	gcc lib-test.c -o $@ -lparseurl

install: libparseurl.so.1.0.1 parseurl.h
	cp parseurl.h /usr/include/
	cp libparseurl.so.1.0.1 /usr/lib/
	@-test /usr/lib/libparseurl.so && rm /usr/lib/libparseurl.so
	ln -s /usr/lib/libparseurl.so.1.0.1 /usr/lib/libparseurl.so
	nice ldconfig
	@mkdir tmp.install
	@cp doc/* tmp.install/
	@gzip tmp.install/*.3
	@cp -v tmp.install/*.3.gz $(MANPATH)/man3/
	@rm -r tmp.install
	@echo "Install complete."


clean:
	@-[ -e libparseurl.o ] && rm libparseurl.o
	@-[ -e libparseurl.a ] && rm libparseurl.a
	@-[ -e lib-test ] && rm lib-test
	@-[ -e libparseurl.so.1.0.1 ] && rm libparseurl.so.1.0.1
	@-[ -e tmp.install ]  && rm -r tmp.install

