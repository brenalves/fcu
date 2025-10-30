OUTDIR = build
MAIN = main

all:
	mkdir -p $(OUTDIR)
	mkdir -p $(OUTDIR)/chapters
	latexmk -pdf -output-directory=$(OUTDIR) $(MAIN).tex
	mv $(OUTDIR)/$(MAIN).pdf $(MAIN).pdf