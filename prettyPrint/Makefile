all: prettyPrint.pdf

prettyPrint.pdf: prettyPrint.tex
	pdflatex prettyPrint
	# rail prettyPrint
	latexmk --pdf prettyPrint

clean:
	rm -f *.rai *.rao *.log *.dvi *.aux *.log *.lof *.out *.qst *.toc *~ *.idx *.ilg *.ind

clobber: clean
	rm -f prettyPrint.pdf
