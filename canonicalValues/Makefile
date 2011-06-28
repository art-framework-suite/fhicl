all: canonicalValues.pdf

canonicalValues.pdf: canonicalValues.tex
	pdflatex canonicalValues
	# rail canonicalValues
	latexmk --pdf canonicalValues

clean:
	rm -f *.rai *.rao *.log *.dvi *.aux *.log *.lof *.out *.qst *.toc *~ *.idx *.ilg *.ind

clobber: clean
	rm -f canonicalValues.pdf
