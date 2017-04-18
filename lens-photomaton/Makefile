FORMS=$(wildcard forms/*.ui)
UI_PREFIX=ui_
UI_TARGET=lens_photomaton/forms/

.PHONY: ui
ui: $(FORMS)
	mkdir -p $(UI_TARGET)
	pyuic5 $< > $(subst forms/,$(UI_TARGET)$(UI_PREFIX),$(subst .ui,.py,$<))

.PHONY: win-exe
win-exe: clean ui
	pyinstaller --name cute-lenspics --onefile --windowed main.py

.PHONY: clean
clean:
	rm -rf build dist $(UI_TARGET)$(UI_PREFIX)*.py F*.png

all: clean ui
