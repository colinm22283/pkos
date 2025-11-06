APPLICATIONS+=init
APPLICATIONS+=pksh
APPLICATIONS+=pkwin
APPLICATIONS+=cat
APPLICATIONS+=ls
APPLICATIONS+=tree
APPLICATIONS+=mount
APPLICATIONS+=unmount
APPLICATIONS+=mkdir
APPLICATIONS+=touch
APPLICATIONS+=nn
APPLICATIONS+=fbtest
APPLICATIONS+=echo
APPLICATIONS+=heapstat
APPLICATIONS+=rm
APPLICATIONS+=socktest
APPLICATIONS+=pkwball

.PHONY: all
all: $(foreach a, $(APPLICATIONS), app-$a)

.PHONY: clean
clean:  $(foreach a, $(APPLICATIONS), clean-$a)
	
.PHONY: app-%
app-%:
	cd $(KERNEL_DIR) && $(MAKE) APPLICATION_DIR=$(CURDIR)/$* application

.PHONY: clean-%
clean-%:
	cd $* && $(MAKE) clean

