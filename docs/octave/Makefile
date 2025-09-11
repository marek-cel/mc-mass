SOURCES=\
	rectangular_skewed_frustum.m

################################################################################

.SUFFIXES: .m .md

all: $(SOURCES:.m=.md)

%.md: %.m
	@echo "\e[1;32m"'Converting $< to $@'"\e[0m"
	@octave $< > $@

################################################################################

clean:
	@echo "\e[1;33m"'Cleaning up...'"\e[0m"
	@rm -f *.md