TARGET=vocabulator

CXX=g++
LD=g++
INCDIRS=-I$(QTDIR)/include -I$(QTDIR)/include/QtWidgets -I$(QTDIR)/include/QtGui -I$(QTDIR)/include/QtCore
CXXFLAGS=-std=c++20 -Wall -pedantic
LDFLAGS=-std=c++20 -Wall -pedantic -licuuc -licui18n -L$(QTDIR)/lib -lQt6Widgets -lQt6Gui -lQt6Core

# Files
DEPS=Makefile.deps
HEADERS=$(wildcard src/*.h)
SOURCES=$(wildcard src/*.cpp)
MOC_HEADERS=src/mainwindow.h
MOC_SOURCES=$(MOC_HEADERS:src/%.h=src/moc_%.cpp)
UI_FILES=$(wildcard src/*.ui)
UI_HEADERS=$(UI_FILES:src/%.ui=src/ui_%.h)
OBJECTS=$(SOURCES:src/%.cpp=src/%.o) $(MOC_SOURCES:src/moc_%.cpp=src/moc_%.o)

# Qt
QTDIR=/opt/qt/6.7.2/gcc_64
UIC=$(QTDIR)/libexec/uic
MOC=$(QTDIR)/libexec/moc

# International Components for Unicode
ICU=-licuuc -licui18n

.PHONY: all
all: compile

.PHONY: run
run: compile
	./$(TARGET)

.PHONY: compile
compile: deps qt_specific $(TARGET)

.PHONY: qt_specific
qt_specific: $(UI_HEADERS) $(MOC_SOURCES) 

$(TARGET): $(OBJECTS)
	$(LD) $^ $(LDFLAGS) -o $@

%.o: %.cpp $(UI_HEADERS)
	$(CXX) $(CXXFLAGS) $(INCDIRS) -c $< -o $@

ui_%.h: %.ui
	$(UIC) $< -o $@

moc_%.cpp: %.h
	$(MOC) $(INCDIRS) $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJECTS) $(TARGET) $(UI_HEADERS) $(MOC_SOURCES) $(DEPS)

deps: $(UI_HEADERS)
	$(CXX) -MM $(filter-out $(MOC_SOURCES), $(SOURCES)) | sed '/^[^ \t]/ s/^/src\//' > $(DEPS)

-include $(DEPS)
