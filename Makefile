# Makefile ראשי לכל חלקי הפרויקט

PARTS = part1 part2 part3 part4 part5 part6 part7 part8 part9 part10

.PHONY: all clean $(PARTS)

# ברירת מחדל - בונה את כל החלקים
all: $(PARTS)

# כלל רקורסיבי - נכנס לכל תיקייה ובונה
$(PARTS):
	@echo "🔨 Building $@ ..."
	$(MAKE) -C $@

# ניקוי כללי - מנקה בכל התיקיות
clean:
	@for dir in $(PARTS); do \
		echo "🧹 Cleaning $$dir ..."; \
		$(MAKE) -C $$dir clean; \
	done
