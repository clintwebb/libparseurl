## make file for libparseurl

all: libparseurl.a

ARGS=

# Need to be able to make 'man-pages' as well.  Not sure where to get the source for those... 

libparseurl.o: libparseurl.c parseurl.h
	gcc -c -o $@ libparseurl.c $(ARGS)

libparseurl.a: libparseurl.o
	@>$@
	@rm $@
	ar -r $@
	ar -r $@ $^


lib-test: lib-test.c /usr/include/parseurl.h /usr/lib/libparseurl.a
	gcc -o $@ lib-test.c -lparseurl

install: libparseurl.a parseurl.h
	cp parseurl.h /usr/include/
	cp libparseurl.a /usr/lib/
	@echo "Install complete."

clean:
	@-[ -e libparseurl.o ] && rm libparseurl.o
	@-[ -e libparseurl.a ] && rm libparseurl.a
	@-[ -e lib-test ] && rm lib-test

