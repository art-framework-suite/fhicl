BISON=/usr/local/Cellar/bison/3.0.2/bin/bison
FLEX=/usr/local/Cellar/flex/2.5.37/bin/flex
all: bnf.tab.h bnf.tab.c lex.yy.c preprocess parser
#grammar_new.pdf
#grammar.pdf: grammar.tex memarticle.cls
#	pdflatex grammar
#	rail grammar
#	latexmk --pdf grammar

createId.pdf: createId.tex
	pdflatex createId
	latexmk --pdf createId

#grammar_draft1.pdf: grammar_draft1.tex memarticle.cls
#	pdflatex $<
#	rail grammar_draft1
#	latexmk --pdf grammar_draft1

#grammar_new.pdf: grammar_new.tex memarticle.cls
#	latexmk --pdf grammar_new

bnf.y: bnf.y.inc bnf.y.template
	(m4 bnf.y.template > bnf.y)

bnf.tab.h bnf.tab.c: bnf.y
	$(BISON) -g -v -d $<

lex.yy.c: bnf.l bnf.tab.h
	$(FLEX) $<

parser: bnf.tab.c lex.yy.c
	c++ -o parser bnf.tab.c lex.yy.c -L/usr/local/opt/flex/lib -lfl -ly

test:   parser
	preprocess ../tests/pass/test1.fcl
	parser < temp.txt
	preprocess ../tests/pass/test2.fcl
	parser < temp.txt
	preprocess ../tests/pass/test3.fcl
	parser < temp.txt
	preprocess ../tests/pass/test4.fcl
	parser < temp.txt
	preprocess ../tests/pass/test5.fcl
	parser < temp.txt
	rm -rf temp.txt

preprocess: preprocess.cc
	g++ -o preprocess preprocess.cc
clean:
	rm -f *.rai *.rao *.log *.dvi *.aux *.log *.lof *.out *.qst *.toc *~ *.idx *.ilg *.ind
	rm -f bnf.tab.c bnf.tab.h lex.backup lex.yy.c lex.yy.c 
	rm -f bnf.output bnf.dot bnf.y

clobber: clean
	rm -f grammar.pdf grammar.fdb_latexmk parser

