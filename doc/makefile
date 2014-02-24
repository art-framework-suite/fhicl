all: quick spec

quick: quick_start.pdf

spec: grammar.pdf

%.pdf: %.tex
	latexmk -pdf $<

clean:
	latexmk -c grammar
	latexmk -c quick_start

clobber:
	latexmk -C grammar
	latexmk -C quick_start
