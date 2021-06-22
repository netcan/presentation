ADOC_SRC := $(shell find . -name "index.adoc")
COMMON_ADOC := $(shell find common -name "*.adoc")
HTML_TARGET := $(ADOC_SRC:.adoc=.html)

all: $(HTML_TARGET)

clean: $(HTML_TARGET)
	rm -rf $(HTML_TARGET)

%.html: %.adoc $(COMMON_ADOC)
	cd $(dir $<) && npx asciidoctor-revealjs index.adoc
