SUBdir=puzzle solver

.PHONY: all $(SUBdir)
all: $(SUBdir)

$(SUBdir):
	$(MAKE) -C $@

clean:
	$(MAKE) -C puzzle clean
	$(MAKE) -C solver clean
