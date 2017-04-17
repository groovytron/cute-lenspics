FORMS=$(wildcard forms/*.ui)

.PHONY: ui
ui: $(FORMS)
	pyuic5 $< > $(subst forms/,ui_,$(subst .ui,.py,$<))

.PHONY: win-exe
win-exe: clean ui
	pyinstaller --name cute-lenspics --onefile --windowed main.py

.PHONY: clean
clean:
	rm -rf build dist

all: win-exe
