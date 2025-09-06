APPLICATIONS+=init

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

