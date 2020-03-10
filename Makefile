split:
	mkdir -p splitted 
	./splitter.sh $(INPUT_VIDEO) splitted

detect: $(shell echo splitted/*.mp4 | sed 's/mp4/csv/g' | sed 's/splitted/detected/g')

filter: $(shell echo detected/*.csv | sed 's/csv/mp4/g' | sed 's/detected/filtered/g')

join:
	./joiner.sh filtered $(OUTPUT_VIDEO)

filtered/%.mp4: detected/%.csv
	mkdir -p filtered
	./filter.py splitted/$*.mp4 detected/$*.csv filtered/$*.mp4 $(KEYWORDS)

detected/%.csv: splitted/%.mp4
	mkdir -p detected
	detector splitted/$*.mp4 yolov3.cfg yolov3.labels yolov3.weights > detected/$*.csv

