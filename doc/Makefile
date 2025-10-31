OUTDIR = build
MAIN = main
CLS = UFFStex.cls

all:
	mkdir -p $(OUTDIR)
	cp -r chapters $(OUTDIR)/chapters
	cp -r figures $(OUTDIR)/figures
	cp $(MAIN).tex $(OUTDIR)/$(MAIN).tex
	cp $(CLS) $(OUTDIR)/$(CLS)
	cp bibliography.bib $(OUTDIR)/bibliography.bib
	cd $(OUTDIR) && latexmk -pdf $(MAIN).tex
	mv $(MAIN).pdf ../$(MAIN).pdf