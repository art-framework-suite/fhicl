all: quick spec

quick: quick_start.pdf

spec: grammar.pdf

%.pdf: %.tex *.cls *.sty
	latexmk -pdf -silent $<

clean:
	latexmk -c -silent grammar
	latexmk -c -silent quick_start

clobber:
	latexmk -C -silent grammar
	latexmk -C -silent quick_start
