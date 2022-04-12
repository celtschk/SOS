.PHONY: code, text, all

all: code tests text

code: rule110.sos

tests: testwritebit.sos testreadbit.sos testwritestate.sos testreadstate.sos \
       testif.sos test110.sos

text: rule110.pdf

%.sos: rule110.nw
	notangle -R$*.sos rule110.nw | cpif $*.sos

rule110.tex: rule110.nw
	noweave -n -delay -x rule110.nw | cpif rule110.tex

rule110.pdf: rule110.tex
	pdflatex rule110
	pdflatex rule110
