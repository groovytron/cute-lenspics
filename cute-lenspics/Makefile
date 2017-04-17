FORMS=$(wildcard forms/*.ui)

.PHONY: ui
ui: $(FORMS)
	pyuic5 $< > $(subst forms/,ui_,$(subst .ui,.py,$<))

all: ui
