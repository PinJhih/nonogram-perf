.PHONY: all clean
all:
	$(MAKE) -C src all

clean:
	$(MAKE) -C src clean
	- rm bin/*.exe bin/*.o
